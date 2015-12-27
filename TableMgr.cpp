/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "LuaEngine.h"
#include "TableMgr.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};

TableMgr::TableMgr(Eluna * eluna) : owner(eluna)
{
    ASSERT(eluna);
}

void TableMgr::DeleteAllTableRefs()
{
    while (!tableRefMap.empty())
        DeleteTableRef(tableRefMap.begin()->first);
}

void TableMgr::DeleteTableRef(ObjectGuid const & guid)
{
    const auto it = tableRefMap.find(guid);
    if (it != tableRefMap.end())
    {
        luaL_unref(owner->L, LUA_REGISTRYINDEX, it->second);
        tableRefMap.erase(it);
    }
}

void TableMgr::PushTableRef(ObjectGuid const & guid)
{
    const auto it = tableRefMap.find(guid);
    if (it != tableRefMap.end())
        lua_rawgeti(owner->L, LUA_REGISTRYINDEX, it->second);
    else
        lua_pushnil(owner->L);
}

void TableMgr::CreateTable(ObjectGuid const & guid)
{
    DeleteTableRef(guid);

    lua_newtable(owner->L);
    int ref = luaL_ref(owner->L, LUA_REGISTRYINDEX);
    if (ref != LUA_REFNIL)
        tableRefMap[guid] = ref;
}
