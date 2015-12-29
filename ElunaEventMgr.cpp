/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "ElunaEventMgr.h"
#include "LuaEngine.h"
#include "Object.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};

void ElunaEventProcessor::Update(uint32 diff, Eluna* E, WorldObject* obj)
{
    m_time += diff;
    for (EventList::iterator it = eventList.begin(); it != eventList.end() && it->first <= m_time; it = eventList.begin())
    {
        LuaEvent* luaEvent = it->second;
        eventList.erase(it);

        if (!luaEvent->abort)
        {
            bool remove = luaEvent->repeats == 1;
            if (!remove)
                AddEvent(*luaEvent, true); // Reschedule before calling incase RemoveEvents used

            // Call the timed event
            E->OnTimedEvent(luaEvent->funcRef, luaEvent->delay, luaEvent->repeats ? luaEvent->repeats-- : luaEvent->repeats, obj);

            if (!remove)
                continue;
        }

        // Event should be deleted (executed last time or set to be aborted)
        luaL_unref(E->L, LUA_REGISTRYINDEX, luaEvent->funcRef);
        eventMap.erase(luaEvent->funcRef);
    }
}

void ElunaEventProcessor::AddEvent(LuaEvent const& luaEvent, bool reschedule /*= false*/)
{
    if (!reschedule)
    {
        ASSERT(eventMap.find(luaEvent.funcRef) == eventMap.end());
    }
    eventMap[luaEvent.funcRef] = luaEvent;
    eventList.insert(std::make_pair(m_time + luaEvent.delay, &eventMap[luaEvent.funcRef]));
}

void ElunaEventProcessor::AddEvent(int funcRef, uint32 delay, uint32 repeats)
{
    AddEvent(LuaEvent(funcRef, delay, repeats));
}

void EventMgr::DeleteAll()
{
    DeleteGlobal();
    for (auto& processor : processorMap)
        for (auto& luaEvent : processor.second.eventMap)
            luaEvent.second.abort = true;
}

void EventMgr::Delete(ObjectGuid const& guid, int funcref)
{
    auto it = processorMap.find(guid);
    if (it == processorMap.end())
        return;
    auto it2 = it->second.eventMap.find(funcref);
    if (it2 == it->second.eventMap.end())
        return;
    it2->second.abort = true;
}

void EventMgr::Delete(ObjectGuid const& guid)
{
    auto it = processorMap.find(guid);
    if (it == processorMap.end())
        return;
    for (auto& luaEvent : it->second.eventMap)
        luaEvent.second.abort = true;
}

void EventMgr::DeleteGlobal(int funcref)
{
    auto it2 = globalProcessor.eventMap.find(funcref);
    if (it2 == globalProcessor.eventMap.end())
        return;
    it2->second.abort = true;
}

void EventMgr::DeleteGlobal()
{
    for (auto& luaEvent : globalProcessor.eventMap)
        luaEvent.second.abort = true;
}

void EventMgr::Update(uint32 diff, WorldObject* obj)
{
    auto it = processorMap.find(obj->GET_GUID());
    if (it == processorMap.end())
        return;
    it->second.Update(diff, owner, obj);

    if (it->second.eventMap.empty())
        processorMap.erase(it);
}

void EventMgr::UpdateGlobal(uint32 diff)
{
    globalProcessor.Update(diff, owner, nullptr);
}

void EventMgr::AddEvent(ObjectGuid const& guid, int funcRef, uint32 delay, uint32 repeats)
{
    lua_rawgeti(owner->L, LUA_REGISTRYINDEX, funcRef);
    ASSERT(lua_isfunction(owner->L, -1));
    processorMap[guid].AddEvent(funcRef, delay, repeats);
}

void EventMgr::AddGlobalEvent(int funcRef, uint32 delay, uint32 repeats)
{
    globalProcessor.AddEvent(funcRef, delay, repeats);
}
