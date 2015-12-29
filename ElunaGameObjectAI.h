/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef _ELUNA_GAME_OBJECT_AI_H
#define _ELUNA_GAME_OBJECT_AI_H

#include "GameObject.h"
#include "LuaEngine.h"
#include "TableMgr.h"

#ifdef TRINITY
    #include "GameObjectAI.h"
#else
    // Temp workaround for MaNGOS - not supporting GameObjectAI yet
    class GameObjectAI { public: GameObjectAI(GameObject* g) : go(g) {}
    protected: GameObject* go;};
#endif

struct ElunaGameObjectAI : GameObjectAI
{
    ElunaGameObjectAI(GameObject* gameobject) : GameObjectAI(gameobject)
    {
        go->GetMap()->GetEluna()->GetTableMgr()->CreateTable(go->GET_GUID());
    }
    ~ElunaGameObjectAI()
    {
        go->GetMap()->GetEluna()->GetTableMgr()->DeleteTableRef(go->GET_GUID());
    }
};

#endif
