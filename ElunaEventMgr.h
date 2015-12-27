/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_EVENT_MGR_H
#define _ELUNA_EVENT_MGR_H

#include "ElunaUtility.h"
#include "Common.h"
#include <map>
#include <unordered_map>

#ifdef TRINITY
#include "Define.h"
#else
#include "Platform/Define.h"
#endif

class Eluna;
class EventMgr;
class ElunaEventProcessor;
class WorldObject;

struct LuaEvent
{
    LuaEvent(int funcRef, uint32 delay, uint32 repeats) :
        delay(delay), repeats(repeats), funcRef(funcRef), abort(false)
    {
    }
    LuaEvent() :
        delay(0), repeats(0), funcRef(0), abort(true)
    {
    }

    uint32 delay;   // Delay between event calls
    uint32 repeats; // Amount of repeats to make, 0 for infinite
    int funcRef;    // Lua function reference ID, also used as event ID
    bool abort;
};

class ElunaEventProcessor
{
    friend class EventMgr;

public:

    ElunaEventProcessor() : m_time(0)
    {
    }

    // obj can be nullptr for global events
    void Update(uint32 diff, Eluna* E, WorldObject* obj);
    void AddEvent(LuaEvent const& luaEvent, bool reschedule = false);
    void AddEvent(int funcRef, uint32 delay, uint32 repeats);

private:

    typedef std::multimap<uint64, LuaEvent*> EventList;
    typedef std::unordered_map<int, LuaEvent> EventMap;

    EventList eventList;
    EventMap eventMap;
    uint64 m_time;
};

class EventMgr
{
    friend class ElunaEventProcessor;
private:
    typedef std::unordered_map<ObjectGuid, ElunaEventProcessor> ProcessorMap;
    ProcessorMap processorMap;
    ElunaEventProcessor globalProcessor;
    Eluna* owner;

public:
    EventMgr(Eluna* eluna) : owner(eluna)
    {
        ASSERT(eluna);
    }

    void DeleteAll();

    void Delete(ObjectGuid const& guid, int funcref);
    void Delete(ObjectGuid const& guid);
    void DeleteGlobal(int funcref);
    void DeleteGlobal();

    void Update(uint32 diff, WorldObject* obj);
    void UpdateGlobal(uint32 diff);

    void AddEvent(ObjectGuid const& guid, int funcRef, uint32 delay, uint32 repeats);
    void AddGlobalEvent(int funcRef, uint32 delay, uint32 repeats);
};

#endif
