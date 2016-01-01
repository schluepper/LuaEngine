/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_TEMPLATE_H
#define _ELUNA_TEMPLATE_H

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};
#include "LuaEngine.h"
#include "ElunaUtility.h"
#include "SharedDefines.h"

enum ElunaEnvironments
{
    ENV_NONE,
    ENV_MAP,    // For current map only
    ENV_WORLD,  // For world state only
    ENV_BOTH,   // For world and map
    ENV_MAX
};

class ElunaFunction
{
public:
    struct ElunaRegister
    {
        ElunaEnvironments env;
        const char* name;
        int(*mfunc)(lua_State*);
    };

    static int thunk(lua_State* L)
    {
        ElunaRegister* l = static_cast<ElunaRegister*>(lua_touserdata(L, lua_upvalueindex(1)));
        if (Eluna::GetEluna(L)->current_thread_id != std::this_thread::get_id())
        {
            ELUNA_LOG_ERROR("[Eluna]: Race condition using global function. Report to devs with this message and details about what you were doing - Info: %s", l->name);
        }
        int args = lua_gettop(L);
        int expected = l->mfunc(L);
        args = lua_gettop(L) - args;
        if (args < 0 || args > expected)
        {
            ELUNA_LOG_ERROR("[Eluna]: %s returned unexpected amount of arguments %i out of %i. Report to devs", l->name, args, expected);
        }
        for (; args < expected; ++args)
            lua_pushnil(L);
        return expected;
    }

    static void SetMethods(Eluna* E, ElunaRegister* methodTable)
    {
        ASSERT(E);
        ASSERT(methodTable);

        lua_pushglobaltable(E->L);

        for (; methodTable && methodTable->name && methodTable->mfunc; ++methodTable)
        {
            if (methodTable->env >= ENV_MAX || methodTable->env < ENV_NONE)
            {
                ASSERT(false);
            }
            else if (methodTable->env == ENV_NONE)
                continue;
            else if (methodTable->env != ENV_BOTH)
            {
                if (!E->owner && methodTable->env == ENV_MAP)
                    continue;
                else if (E->owner && methodTable->env == ENV_WORLD)
                    continue;
            }
            lua_pushstring(E->L, methodTable->name);
            lua_pushlightuserdata(E->L, (void*)methodTable);
            lua_pushcclosure(E->L, thunk, 1);
            lua_rawset(E->L, -3);
        }

        lua_pop(E->L, 1);
    }
};

class ElunaObject
{
public:
    ElunaObject(void* obj, bool manageMemory) : _isvalid(false), _invalidate(!manageMemory), object(obj)
    {
        SetValid(true);
    }

    ~ElunaObject()
    {
    }

    // Get wrapped object pointer
    void* GetObj() const { return object; }
    // Returns whether the object is valid or not
    bool IsValid() const { return _isvalid; }
    // Returns whether the object can be invalidated or not
    bool CanInvalidate() const { return _invalidate; }

    // Sets the object pointer that is wrapped
    void SetObj(void* obj)
    {
        ASSERT(obj);
        object = obj;
        SetValid(true);
    }
    // Sets the object pointer to valid or invalid
    void SetValid(bool valid)
    {
        ASSERT(!valid || (valid && object));
        _isvalid = valid;
    }
    // Sets whether the pointer will be invalidated at end of calls
    void SetValidation(bool invalidate)
    {
        _invalidate = invalidate;
    }
    // Invalidates the pointer if it should be invalidated
    void Invalidate()
    {
        if (CanInvalidate())
            _isvalid = false;
    }

private:
    bool _isvalid;
    bool _invalidate;
    void* object;
};

template<typename T>
struct ElunaRegister
{
    ElunaEnvironments env;
    const char* name;
    int(*mfunc)(lua_State*, T*);
};

template<typename T>
class ElunaTemplate
{
public:
    static const char* tname;
    static bool manageMemory;

    // name will be used as type name
    // If gc is true, lua will handle the memory management for object pushed
    // gc should be used if pushing for example WorldPacket,
    // that will only be needed on lua side and will not be managed by TC/mangos/<core>
    static void Register(Eluna* E, const char* name, bool gc = false)
    {
        ASSERT(E);
        ASSERT(name);

        // check that metatable isn't already there
        lua_getglobal(E->L, name);
        ASSERT(lua_isnoneornil(E->L, -1));

        // pop nil
        lua_pop(E->L, 1);

        tname = name;
        manageMemory = gc;

        // create metatable for userdata of this type
        lua_newtable(E->L);
        int metatable = lua_gettop(E->L);

        // push metatable to stack to be accessed and modified by users
        lua_pushvalue(E->L, metatable);
        lua_setglobal(E->L, tname);

        // tostring
        lua_pushcfunction(E->L, ToString);
        lua_setfield(E->L, metatable, "__tostring");

        // concatenation
        lua_pushcfunction(E->L, Concat);
        lua_setfield(E->L, metatable, "__concat");

        // garbage collecting
        lua_pushcfunction(E->L, CollectGarbage);
        lua_setfield(E->L, metatable, "__gc");

        // make methods accessible through metatable
        lua_pushvalue(E->L, metatable);
        lua_setfield(E->L, metatable, "__index");

        // enable comparing values
        lua_pushcfunction(E->L, Equal);
        lua_setfield(E->L, metatable, "__eq");

        // special method to get the object type
        lua_pushcfunction(E->L, GetType);
        lua_setfield(E->L, metatable, "GetObjectType");

        // special method to decide object invalidation at end of call
        lua_pushcfunction(E->L, SetInvalidation);
        lua_setfield(E->L, metatable, "SetInvalidation");

        // pop metatable
        lua_pop(E->L, 1);
    }

    template<typename C>
    static void SetMethods(Eluna* E, ElunaRegister<C>* methodTable)
    {
        ASSERT(E);
        ASSERT(tname);
        ASSERT(methodTable);

        // get metatable
        lua_getglobal(E->L, tname);
        ASSERT(lua_istable(E->L, -1));

        for (; methodTable && methodTable->name && methodTable->mfunc; ++methodTable)
        {
            if (methodTable->env >= ENV_MAX || methodTable->env < ENV_NONE)
            {
                ASSERT(false);
            }
            else if (methodTable->env == ENV_NONE)
                continue;
            else if (methodTable->env != ENV_BOTH)
            {
                if (!E->owner && methodTable->env == ENV_MAP)
                    continue;
                else if (E->owner && methodTable->env == ENV_WORLD)
                    continue;
            }
            lua_pushstring(E->L, methodTable->name);
            lua_pushlightuserdata(E->L, (void*)methodTable);
            lua_pushcclosure(E->L, CallMethod, 1);
            lua_rawset(E->L, -3);
        }

        lua_pop(E->L, 1);
    }

    static void SetMethods(Eluna* E, ElunaFunction::ElunaRegister* methodTable)
    {
        ASSERT(E);
        ASSERT(tname);
        ASSERT(methodTable);

        // get metatable
        lua_getglobal(E->L, tname);
        ASSERT(lua_istable(E->L, -1));

        for (; methodTable && methodTable->name && methodTable->mfunc; ++methodTable)
        {
            if (methodTable->env >= ENV_MAX || methodTable->env < ENV_NONE)
            {
                ASSERT(false);
            }
            else if (methodTable->env == ENV_NONE)
                continue;
            else if (methodTable->env != ENV_BOTH)
            {
                if (!E->owner && methodTable->env == ENV_MAP)
                    continue;
                else if (E->owner && methodTable->env == ENV_WORLD)
                    continue;
            }
            lua_pushstring(E->L, methodTable->name);
            lua_pushlightuserdata(E->L, (void*)methodTable);
            lua_pushcclosure(E->L, ElunaFunction::thunk, 1);
            lua_rawset(E->L, -3);
        }

        lua_pop(E->L, 1);
    }

    static int Push(lua_State* L, T const* obj)
    {
        int baseStack = lua_gettop(L);
        if (!obj)
        {
            lua_pushnil(L);
            return 1;
        }

        void* obj_voidptr = static_cast<void*>(const_cast<T*>(obj));

        lua_getglobal(L, ELUNA_OBJECT_STORE);
        ASSERT(lua_istable(L, -1));
        lua_pushlightuserdata(L, obj_voidptr);
        // Stack: objStore, obj_voidptr
        lua_rawget(L, -2);
        // Stack: objStore, objStore[obj_voidptr]

        if (ElunaObject* elunaObj = Eluna::CHECKTYPE(L, -1, tname, false))
        {
            // set userdata valid
            elunaObj->SetValid(true);
            lua_remove(L, -2);
            return 1;
        }
        lua_pop(L, 2);
        lua_getglobal(L, ELUNA_OBJECT_STORE);

        // Create new userdata
        ElunaObject** ptrHold = static_cast<ElunaObject**>(lua_newuserdata(L, sizeof(ElunaObject*)));
        // Stack: objStore, ptrHold
        if (!ptrHold)
        {
            ELUNA_LOG_ERROR("%s could not create new userdata", tname);
            lua_pop(L, 2);
            lua_pushnil(L);
            return 1;
        }
        *ptrHold = new ElunaObject(obj_voidptr, manageMemory);

        // Set metatable for it
        lua_getglobal(L, tname);
        // Stack: objStore, ptrHold, metatable
        if (!lua_istable(L, -1))
        {
            ELUNA_LOG_ERROR("%s missing metatable", tname);
            lua_pop(L, 3);
            lua_pushnil(L);
            return 1;
        }
        lua_setmetatable(L, -2);
        // Stack: objStore, ptrHold (with metatable)

        lua_pushlightuserdata(L, obj_voidptr);
        // Stack: objStore, ptrHold, obj_voidptr
        lua_pushvalue(L, -2);
        // Stack: objStore, ptrHold, obj_voidptr, ptrHold
        lua_rawset(L, -4); // Sets: objStore[obj_voidptr] = ptrHold
        // Stack: objStore, ptrHold
        lua_remove(L, -2);
        return 1;
    }

    static T* Check(lua_State* L, int narg, bool error = true)
    {
        ASSERT(tname);

        ElunaObject* elunaObj = Eluna::CHECKTYPE(L, narg, tname, error);
        if (!elunaObj)
            return NULL;

        if (!elunaObj->IsValid())
        {
            char buff[256];
            snprintf(buff, 256, "%s expected, got pointer to nonexisting (invalidated) object (%s). Check your code.", tname, luaL_typename(L, narg));
            if (error)
            {
                luaL_argerror(L, narg, buff);
            }
            else
            {
                ELUNA_LOG_ERROR("%s", buff);
            }
            return nullptr;
        }
        return static_cast<T*>(elunaObj->GetObj());
    }

    static int GetType(lua_State* L)
    {
        lua_pushstring(L, tname);
        return 1;
    }

    static int SetInvalidation(lua_State* L)
    {
        ElunaObject* elunaObj = Eluna::CHECKOBJ<ElunaObject>(L, 1);
        bool invalidate = Eluna::CHECKVAL<bool>(L, 2);

        elunaObj->SetValidation(invalidate);
        return 0;
    }

    static int CallMethod(lua_State* L)
    {
        T* obj = Eluna::CHECKOBJ<T>(L, 1); // get self
        if (!obj)
            return 0;
        ElunaRegister<T>* l = static_cast<ElunaRegister<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
        if (Eluna::GetEluna(L)->current_thread_id != std::this_thread::get_id())
        {
            ELUNA_LOG_ERROR("[Eluna]: Race condition using member function. Report to devs with this message and details about what you were doing - Info: %s", l->name);
        }
        int top = lua_gettop(L);
        int expected = l->mfunc(L, obj);
        int args = lua_gettop(L) - top;
        if (args < 0 || args > expected)
        {
            ELUNA_LOG_ERROR("[Eluna]: %s returned unexpected amount of arguments %i out of %i. Report to devs", l->name, args, expected);
        }
        if (args == expected)
            return expected;
        lua_settop(L, top);
        return 0;
    }

    // Metamethods ("virtual")

    // Remember special cases like ElunaTemplate<Vehicle>::CollectGarbage
    static int CollectGarbage(lua_State* L)
    {
        // Get object pointer (and check type, no error)
        ElunaObject* obj = Eluna::CHECKOBJ<ElunaObject>(L, 1, false);
        if (obj && manageMemory)
            delete static_cast<T*>(obj->GetObj());
        delete obj;
        return 0;
    }

    static int ToString(lua_State* L)
    {
        T* obj = Eluna::CHECKOBJ<T>(L, 1, true); // get self
        lua_pushfstring(L, "%s: (%p)", tname, obj);
        return 1;
    }

    static int Concat(lua_State* L)
    {
        luaL_tolstring(L, 1, nullptr);
        luaL_tolstring(L, 2, nullptr);
        lua_concat(L, 2);
        return 1;
    }

    static int Equal(lua_State* L)
    {
        Eluna::Push(L, Eluna::CHECKOBJ<T>(L, 1) == Eluna::CHECKOBJ<T>(L, 2));
        return 1;
    }
};

#endif
