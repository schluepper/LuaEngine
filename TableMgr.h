/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _TABLE_MGR_H
#define _TABLE_MGR_H

#include "ObjectGuid.h"
#include <unordered_map>

class Eluna;
class WorldObject;
struct lua_State;

class TableMgr
{
private:
    typedef std::unordered_map<ObjectGuid, int> RefMap;
    RefMap tableRefMap;
    Eluna* owner;

public:
    TableMgr(Eluna* eluna);

    void DeleteAllTableRefs();
    void DeleteTableRef(ObjectGuid const& guid);
    void PushTableRef(ObjectGuid const& guid);
    void CreateTable(ObjectGuid const& guid);
};

#endif
