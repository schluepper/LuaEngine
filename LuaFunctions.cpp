/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

extern "C"
{
#include "lua.h"
};

// Eluna
#include "LuaEngine.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaUtility.h"
#include "lmarshal.h"

// Method includes
#include "GlobalMethods.h"
#include "ObjectMethods.h"
#include "WorldObjectMethods.h"
#include "UnitMethods.h"
#include "PlayerMethods.h"
#include "CreatureMethods.h"
#include "GroupMethods.h"
#include "GuildMethods.h"
#include "GameObjectMethods.h"
#include "ElunaQueryMethods.h"
#include "AuraMethods.h"
#include "ItemMethods.h"
#include "WorldPacketMethods.h"
#include "SpellMethods.h"
#include "QuestMethods.h"
#include "MapMethods.h"
#include "CorpseMethods.h"
#include "VehicleMethods.h"
#include "BattleGroundMethods.h"

ElunaFunction::ElunaRegister GlobalMethods[] =
{
    // Hooks
    { ENV_BOTH, "RegisterServerEvent", &LuaGlobalFunctions::RegisterServerEvent },
    { ENV_BOTH, "RegisterPlayerEvent", &LuaGlobalFunctions::RegisterPlayerEvent },
    { ENV_BOTH, "RegisterGuildEvent", &LuaGlobalFunctions::RegisterGuildEvent },
    { ENV_BOTH, "RegisterGroupEvent", &LuaGlobalFunctions::RegisterGroupEvent },
    { ENV_BOTH, "RegisterCreatureEvent", &LuaGlobalFunctions::RegisterCreatureEvent },
    { ENV_BOTH, "RegisterUniqueCreatureEvent", &LuaGlobalFunctions::RegisterUniqueCreatureEvent },
    { ENV_BOTH, "RegisterCreatureGossipEvent", &LuaGlobalFunctions::RegisterCreatureGossipEvent },
    { ENV_BOTH, "RegisterGameObjectEvent", &LuaGlobalFunctions::RegisterGameObjectEvent },
    { ENV_BOTH, "RegisterGameObjectGossipEvent", &LuaGlobalFunctions::RegisterGameObjectGossipEvent },
    { ENV_BOTH, "RegisterItemEvent", &LuaGlobalFunctions::RegisterItemEvent },
    { ENV_BOTH, "RegisterItemGossipEvent", &LuaGlobalFunctions::RegisterItemGossipEvent },
    { ENV_BOTH, "RegisterPlayerGossipEvent", &LuaGlobalFunctions::RegisterPlayerGossipEvent },
    { ENV_BOTH, "RegisterBGEvent", &LuaGlobalFunctions::RegisterBGEvent },
    { ENV_BOTH, "RegisterMapEvent", &LuaGlobalFunctions::RegisterMapEvent },
    { ENV_BOTH, "RegisterInstanceEvent", &LuaGlobalFunctions::RegisterInstanceEvent },

    { ENV_BOTH, "ClearBattleGroundEvents", &LuaGlobalFunctions::ClearBattleGroundEvents },
    { ENV_BOTH, "ClearCreatureEvents", &LuaGlobalFunctions::ClearCreatureEvents },
    { ENV_BOTH, "ClearUniqueCreatureEvents", &LuaGlobalFunctions::ClearUniqueCreatureEvents },
    { ENV_BOTH, "ClearCreatureGossipEvents", &LuaGlobalFunctions::ClearCreatureGossipEvents },
    { ENV_BOTH, "ClearGameObjectEvents", &LuaGlobalFunctions::ClearGameObjectEvents },
    { ENV_BOTH, "ClearGameObjectGossipEvents", &LuaGlobalFunctions::ClearGameObjectGossipEvents },
    { ENV_BOTH, "ClearGroupEvents", &LuaGlobalFunctions::ClearGroupEvents },
    { ENV_BOTH, "ClearGuildEvents", &LuaGlobalFunctions::ClearGuildEvents },
    { ENV_BOTH, "ClearItemEvents", &LuaGlobalFunctions::ClearItemEvents },
    { ENV_BOTH, "ClearItemGossipEvents", &LuaGlobalFunctions::ClearItemGossipEvents },
    { ENV_BOTH, "ClearPlayerEvents", &LuaGlobalFunctions::ClearPlayerEvents },
    { ENV_BOTH, "ClearPlayerGossipEvents", &LuaGlobalFunctions::ClearPlayerGossipEvents },
    { ENV_BOTH, "ClearServerEvents", &LuaGlobalFunctions::ClearServerEvents },
    { ENV_BOTH, "ClearMapEvents", &LuaGlobalFunctions::ClearMapEvents },
    { ENV_BOTH, "ClearInstanceEvents", &LuaGlobalFunctions::ClearInstanceEvents },

    // Getters
    { ENV_BOTH, "GetMap", &LuaGlobalFunctions::GetMap },
    { ENV_BOTH, "GetLuaEngine", &LuaGlobalFunctions::GetLuaEngine },
    { ENV_BOTH, "GetCoreName", &LuaGlobalFunctions::GetCoreName },
    { ENV_BOTH, "GetCoreVersion", &LuaGlobalFunctions::GetCoreVersion },
    { ENV_BOTH, "GetCoreExpansion", &LuaGlobalFunctions::GetCoreExpansion },
    { ENV_BOTH, "GetQuest", &LuaGlobalFunctions::GetQuest },
    { ENV_WORLD, "GetPlayerByGUID", &LuaGlobalFunctions::GetPlayerByGUID },
    { ENV_WORLD, "GetPlayerByName", &LuaGlobalFunctions::GetPlayerByName },
    { ENV_BOTH, "GetGameTime", &LuaGlobalFunctions::GetGameTime },
    { ENV_WORLD, "GetPlayersInWorld", &LuaGlobalFunctions::GetPlayersInWorld },
    { ENV_WORLD, "GetGuildByName", &LuaGlobalFunctions::GetGuildByName },
    { ENV_WORLD, "GetGuildByLeaderGUID", &LuaGlobalFunctions::GetGuildByLeaderGUID },
    { ENV_WORLD, "GetPlayerCount", &LuaGlobalFunctions::GetPlayerCount },
    { ENV_BOTH, "GetPlayerGUID", &LuaGlobalFunctions::GetPlayerGUID },
    { ENV_BOTH, "GetItemGUID", &LuaGlobalFunctions::GetItemGUID },
    { ENV_BOTH, "GetObjectGUID", &LuaGlobalFunctions::GetObjectGUID },
    { ENV_BOTH, "GetUnitGUID", &LuaGlobalFunctions::GetUnitGUID },
    { ENV_BOTH, "GetGUIDLow", &LuaGlobalFunctions::GetGUIDLow },
    { ENV_BOTH, "GetGUIDType", &LuaGlobalFunctions::GetGUIDType },
    { ENV_BOTH, "GetGUIDEntry", &LuaGlobalFunctions::GetGUIDEntry },
    { ENV_BOTH, "GetAreaName", &LuaGlobalFunctions::GetAreaName },
    { ENV_BOTH, "bit_not", &LuaGlobalFunctions::bit_not },
    { ENV_BOTH, "bit_xor", &LuaGlobalFunctions::bit_xor },
    { ENV_BOTH, "bit_rshift", &LuaGlobalFunctions::bit_rshift },
    { ENV_BOTH, "bit_lshift", &LuaGlobalFunctions::bit_lshift },
    { ENV_BOTH, "bit_or", &LuaGlobalFunctions::bit_or },
    { ENV_BOTH, "bit_and", &LuaGlobalFunctions::bit_and },
    { ENV_BOTH, "GetItemLink", &LuaGlobalFunctions::GetItemLink },
    { ENV_WORLD, "GetMapById", &LuaGlobalFunctions::GetMapById },
    { ENV_BOTH, "GetCurrTime", &LuaGlobalFunctions::GetCurrTime },
    { ENV_BOTH, "GetTimeDiff", &LuaGlobalFunctions::GetTimeDiff },
    { ENV_BOTH, "PrintInfo", &LuaGlobalFunctions::PrintInfo },
    { ENV_BOTH, "PrintError", &LuaGlobalFunctions::PrintError },
    { ENV_BOTH, "PrintDebug", &LuaGlobalFunctions::PrintDebug },

    // Boolean
    { ENV_BOTH, "IsInventoryPos", &LuaGlobalFunctions::IsInventoryPos },
    { ENV_BOTH, "IsEquipmentPos", &LuaGlobalFunctions::IsEquipmentPos },
    { ENV_BOTH, "IsBankPos", &LuaGlobalFunctions::IsBankPos },
    { ENV_BOTH, "IsBagPos", &LuaGlobalFunctions::IsBagPos },

    // Other
    { ENV_BOTH, "ReloadEluna", &LuaGlobalFunctions::ReloadEluna },
    { ENV_BOTH, "SendWorldMessage", &LuaGlobalFunctions::SendWorldMessage },
    { ENV_BOTH, "WorldDBQuery", &LuaGlobalFunctions::WorldDBQuery },
    { ENV_BOTH, "WorldDBExecute", &LuaGlobalFunctions::WorldDBExecute },
    { ENV_BOTH, "CharDBQuery", &LuaGlobalFunctions::CharDBQuery },
    { ENV_BOTH, "CharDBExecute", &LuaGlobalFunctions::CharDBExecute },
    { ENV_BOTH, "AuthDBQuery", &LuaGlobalFunctions::AuthDBQuery },
    { ENV_BOTH, "AuthDBExecute", &LuaGlobalFunctions::AuthDBExecute },
    { ENV_BOTH, "CreateLuaEvent", &LuaGlobalFunctions::CreateLuaEvent },
    { ENV_BOTH, "RemoveEventById", &LuaGlobalFunctions::RemoveEventById },
    { ENV_BOTH, "RemoveEvents", &LuaGlobalFunctions::RemoveEvents },
    { ENV_NONE, "PerformIngameSpawn", &LuaGlobalFunctions::PerformIngameSpawn },
    { ENV_BOTH, "CreatePacket", &LuaGlobalFunctions::CreatePacket },
    { ENV_WORLD, "AddVendorItem", &LuaGlobalFunctions::AddVendorItem },
    { ENV_WORLD, "VendorRemoveItem", &LuaGlobalFunctions::VendorRemoveItem },
    { ENV_WORLD, "VendorRemoveAllItems", &LuaGlobalFunctions::VendorRemoveAllItems },
    { ENV_NONE, "Kick", &LuaGlobalFunctions::Kick },
    { ENV_NONE, "Ban", &LuaGlobalFunctions::Ban },
    { ENV_BOTH, "SaveAllPlayers", &LuaGlobalFunctions::SaveAllPlayers },
    { ENV_BOTH, "SendMail", &LuaGlobalFunctions::SendMail },
    { ENV_WORLD, "AddTaxiPath", &LuaGlobalFunctions::AddTaxiPath },
    { ENV_BOTH, "UintNew", &LuaGlobalFunctions::UintNew },
    { ENV_BOTH, "UintToString", &LuaGlobalFunctions::UintToString },
    { ENV_BOTH, "UintToHex", &LuaGlobalFunctions::UintToHex },
    { ENV_BOTH, "StateChannelSend", &LuaGlobalFunctions::StateChannelSend },
    { ENV_BOTH, "StateChannelRegister", &LuaGlobalFunctions::StateChannelRegister },
    { ENV_BOTH, "StateChannelUnregister", &LuaGlobalFunctions::StateChannelUnregister },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Object> ObjectMethods[] =
{
    // Getters
    { ENV_BOTH, "GetEntry", &LuaObject::GetEntry },                     // :GetEntry() - Returns the object's entryId
    { ENV_BOTH, "GetGUID", &LuaObject::GetGUID },                       // :GetGUID() - Returns uint64 guid as hex string
    { ENV_BOTH, "GetGUIDLow", &LuaObject::GetGUIDLow },                 // :GetGUIDLow() - Returns uint32 guid (low guid) that is used to differentiate objects of same type.
    { ENV_BOTH, "GetInt32Value", &LuaObject::GetInt32Value },           // :GetInt32Value(index) - returns an int value from object fields
    { ENV_BOTH, "GetUInt32Value", &LuaObject::GetUInt32Value },         // :GetUInt32Value(index) - returns an uint value from object fields
    { ENV_BOTH, "GetFloatValue", &LuaObject::GetFloatValue },           // :GetFloatValue(index) - returns a float value from object fields
    { ENV_BOTH, "GetByteValue", &LuaObject::GetByteValue },             // :GetByteValue(index, offset) - returns a byte value from object fields
    { ENV_BOTH, "GetUInt16Value", &LuaObject::GetUInt16Value },         // :GetUInt16Value(index, offset) - returns a uint16 value from object fields
    { ENV_BOTH, "GetUInt64Value", &LuaObject::GetUInt64Value },         // :GetUInt64Value(index) - returns a uint64 value from object fields
    { ENV_BOTH, "GetScale", &LuaObject::GetScale },                     // :GetScale()
    { ENV_BOTH, "GetTypeId", &LuaObject::GetTypeId },                   // :GetTypeId() - Returns the object's typeId

    // Setters
    { ENV_BOTH, "SetInt32Value", &LuaObject::SetInt32Value },           // :SetInt32Value(index, value) - Sets an int value for the object
    { ENV_BOTH, "SetUInt32Value", &LuaObject::SetUInt32Value },         // :SetUInt32Value(index, value) - Sets an uint value for the object
    { ENV_BOTH, "UpdateUInt32Value", &LuaObject::UpdateUInt32Value },   // :UpdateUInt32Value(index, value) - Sets an uint value for the object
    { ENV_BOTH, "SetFloatValue", &LuaObject::SetFloatValue },           // :SetFloatValue(index, value) - Sets a float value for the object
    { ENV_BOTH, "SetByteValue", &LuaObject::SetByteValue },             // :SetByteValue(index, offset, value) - Sets a byte value for the object
    { ENV_BOTH, "SetUInt16Value", &LuaObject::SetUInt16Value },         // :SetUInt16Value(index, offset, value) - Sets an uint16 value for the object
    { ENV_BOTH, "SetInt16Value", &LuaObject::SetInt16Value },           // :SetInt16Value(index, offset, value) - Sets an int16 value for the object
    { ENV_BOTH, "SetUInt64Value", &LuaObject::SetUInt64Value },         // :SetUInt64Value(index, value) - Sets an uint64 value for the object
    { ENV_BOTH, "SetScale", &LuaObject::SetScale },                     // :SetScale(scale)
    { ENV_BOTH, "SetFlag", &LuaObject::SetFlag },                       // :SetFlag(index, flag)

    // Boolean
    { ENV_BOTH, "IsInWorld", &LuaObject::IsInWorld },                   // :IsInWorld() - Returns if the object is in world
    { ENV_BOTH, "HasFlag", &LuaObject::HasFlag },                       // :HasFlag(index, flag)

    // Other
    { ENV_BOTH, "ToGameObject", &LuaObject::ToGameObject },             // :ToGameObject()
    { ENV_BOTH, "ToUnit", &LuaObject::ToUnit },                         // :ToUnit()
    { ENV_BOTH, "ToCreature", &LuaObject::ToCreature },                 // :ToCreature()
    { ENV_BOTH, "ToPlayer", &LuaObject::ToPlayer },                     // :ToPlayer()
    { ENV_BOTH, "ToCorpse", &LuaObject::ToCorpse },                     // :ToCorpse()
    { ENV_BOTH, "RemoveFlag", &LuaObject::RemoveFlag },                 // :RemoveFlag(index, flag)

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<WorldObject> WorldObjectMethods[] =
{
    // Getters
    { ENV_BOTH, "GetName", &LuaWorldObject::GetName },                              // :GetName()
    { ENV_BOTH, "GetMap", &LuaWorldObject::GetMap },                                // :GetMap() - Returns the WorldObject's current map object
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "GetPhaseMask", &LuaWorldObject::GetPhaseMask },                    // :GetPhaseMask()
#endif
    { ENV_BOTH, "GetInstanceId", &LuaWorldObject::GetInstanceId },                  // :GetInstanceId()
    { ENV_BOTH, "GetAreaId", &LuaWorldObject::GetAreaId },                          // :GetAreaId()
    { ENV_BOTH, "GetZoneId", &LuaWorldObject::GetZoneId },                          // :GetZoneId()
    { ENV_BOTH, "GetMapId", &LuaWorldObject::GetMapId },                            // :GetMapId() - Returns the WorldObject's current map ID
    { ENV_BOTH, "GetX", &LuaWorldObject::GetX },                                    // :GetX()
    { ENV_BOTH, "GetY", &LuaWorldObject::GetY },                                    // :GetY()
    { ENV_BOTH, "GetZ", &LuaWorldObject::GetZ },                                    // :GetZ()
    { ENV_BOTH, "GetO", &LuaWorldObject::GetO },                                    // :GetO()
    { ENV_BOTH, "GetLocation", &LuaWorldObject::GetLocation },                      // :GetLocation() - returns X, Y, Z and O co - ords (in that order)
    { ENV_BOTH, "GetPlayersInRange", &LuaWorldObject::GetPlayersInRange },          // :GetPlayersInRange([range]) - Returns a table with players in range of the WorldObject.
    { ENV_BOTH, "GetCreaturesInRange", &LuaWorldObject::GetCreaturesInRange },      // :GetCreaturesInRange([range, entry]) - Returns a table with creatures of given entry in range of the WorldObject.
    { ENV_BOTH, "GetGameObjectsInRange", &LuaWorldObject::GetGameObjectsInRange },  // :GetGameObjectsInRange([range, entry]) - Returns a table with gameobjects of given entry in range of the WorldObject.
    { ENV_BOTH, "GetNearestPlayer", &LuaWorldObject::GetNearestPlayer },            // :GetNearestPlayer([range]) - Returns nearest player in sight or given range.
    { ENV_BOTH, "GetNearestGameObject", &LuaWorldObject::GetNearestGameObject },    // :GetNearestGameObject([range, entry]) - Returns nearest gameobject with given entry in sight or given range entry can be 0 or nil for any.
    { ENV_BOTH, "GetNearestCreature", &LuaWorldObject::GetNearestCreature },        // :GetNearestCreature([range, entry]) - Returns nearest creature with given entry in sight or given range entry can be 0 or nil for any.
    { ENV_BOTH, "GetNearObject", &LuaWorldObject::GetNearObject },
    { ENV_BOTH, "GetNearObjects", &LuaWorldObject::GetNearObjects },
    { ENV_BOTH, "GetDistance", &LuaWorldObject::GetDistance },
    { ENV_BOTH, "GetExactDistance", &LuaWorldObject::GetExactDistance },
    { ENV_BOTH, "GetDistance2d", &LuaWorldObject::GetDistance2d },
    { ENV_BOTH, "GetExactDistance2d", &LuaWorldObject::GetExactDistance2d },
    { ENV_BOTH, "GetRelativePoint", &LuaWorldObject::GetRelativePoint },            // :GetRelativePoint(dist, rad) - Returns the x, y and z of a point dist away from worldobject.
    { ENV_BOTH, "GetAngle", &LuaWorldObject::GetAngle },                            // :GetAngle(WorldObject or x, y) - Returns angle between world object and target or x and y coords.

    // Boolean
    { ENV_BOTH, "IsWithinLoS", &LuaWorldObject::IsWithinLoS },

    // Other
    { ENV_BOTH, "SummonGameObject", &LuaWorldObject::SummonGameObject },            // :SummonGameObject(entry, x, y, z, o[, respawnDelay]) - Spawns an object to location. Returns the object or nil
    { ENV_BOTH, "SpawnCreature", &LuaWorldObject::SpawnCreature },                  // :SpawnCreature(entry, x, y, z, o[, spawnType, despawnDelay]) - Spawns a creature to location that despawns after given time (0 for infinite). Returns the creature or nil
    { ENV_BOTH, "SendPacket", &LuaWorldObject::SendPacket },                        // :SendPacket(packet) - Sends a specified packet to everyone around
    { ENV_MAP, "RegisterEvent", &LuaWorldObject::RegisterEvent },
    { ENV_MAP, "RemoveEventById", &LuaWorldObject::RemoveEventById },
    { ENV_MAP, "RemoveEvents", &LuaWorldObject::RemoveEvents },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Unit> UnitMethods[] =
{
    // Getters
    { ENV_BOTH, "GetLevel", &LuaUnit::GetLevel },                                   // :GetLevel()
    { ENV_BOTH, "GetHealth", &LuaUnit::GetHealth },                                 // :GetHealth()
    { ENV_BOTH, "GetDisplayId", &LuaUnit::GetDisplayId },                           // :GetDisplayId()
    { ENV_BOTH, "GetNativeDisplayId", &LuaUnit::GetNativeDisplayId },               // :GetNativeDisplayId()
    { ENV_BOTH, "GetPower", &LuaUnit::GetPower },                                   // :GetPower([type]) - returns power for power type. type can be omitted
    { ENV_BOTH, "GetMaxPower", &LuaUnit::GetMaxPower },                             // :GetMaxPower([type]) - returns max power for power type. type can be omitted
    { ENV_BOTH, "GetPowerType", &LuaUnit::GetPowerType },                           // :GetPowerType() - Returns the power type tye unit uses
    { ENV_BOTH, "GetMaxHealth", &LuaUnit::GetMaxHealth },                           // :GetMaxHealth()
    { ENV_BOTH, "GetHealthPct", &LuaUnit::GetHealthPct },                           // :GetHealthPct()
    { ENV_BOTH, "GetPowerPct", &LuaUnit::GetPowerPct },                             // :GetPowerPct([type]) - returns power percent for power type. type can be omitted
    { ENV_BOTH, "GetGender", &LuaUnit::GetGender },                                 // :GetGender() - returns the gender where male = 0 female = 1
    { ENV_BOTH, "GetRace", &LuaUnit::GetRace },                                     // :GetRace()
    { ENV_BOTH, "GetClass", &LuaUnit::GetClass },                                   // :GetClass()
    { ENV_BOTH, "GetRaceAsString", &LuaUnit::GetRaceAsString },                     // :GetRaceAsString([locale])
    { ENV_BOTH, "GetClassAsString", &LuaUnit::GetClassAsString },                   // :GetClassAsString([locale])
    { ENV_BOTH, "GetAura", &LuaUnit::GetAura },                                     // :GetAura(spellID) - returns aura object
    { ENV_BOTH, "GetCombatTime", &LuaUnit::GetCombatTime },                         // :GetCombatTime() - Returns how long the unit has been in combat
    { ENV_BOTH, "GetFaction", &LuaUnit::GetFaction },                               // :GetFaction() - Returns the unit's factionId
    { ENV_BOTH, "GetCurrentSpell", &LuaUnit::GetCurrentSpell },                     // :GetCurrentSpell(type) - Returns the currently casted spell of given type if any
    { ENV_BOTH, "GetCreatureType", &LuaUnit::GetCreatureType },                     // :GetCreatureType() - Returns the unit's type
    { ENV_BOTH, "GetMountId", &LuaUnit::GetMountId },                               // :GetMountId()
    { ENV_BOTH, "GetOwner", &LuaUnit::GetOwner },                                   // :GetOwner() - Returns the owner
    { ENV_BOTH, "GetFriendlyUnitsInRange", &LuaUnit::GetFriendlyUnitsInRange },     // :GetFriendlyUnitsInRange([range]) - Returns a list of friendly units in range, can return nil
    { ENV_BOTH, "GetUnfriendlyUnitsInRange", &LuaUnit::GetUnfriendlyUnitsInRange }, // :GetUnfriendlyUnitsInRange([range]) - Returns a list of unfriendly units in range, can return nil
    { ENV_BOTH, "GetOwnerGUID", &LuaUnit::GetOwnerGUID },                           // :GetOwnerGUID() - Returns the UNIT_FIELD_SUMMONEDBY owner
    { ENV_BOTH, "GetCreatorGUID", &LuaUnit::GetCreatorGUID },                       // :GetCreatorGUID() - Returns the UNIT_FIELD_CREATEDBY creator
    { ENV_BOTH, "GetMinionGUID", &LuaUnit::GetPetGUID },                            // :GetMinionGUID() - Decapreted. GetMinionGUID is same as GetPetGUID
    { ENV_BOTH, "GetCharmerGUID", &LuaUnit::GetCharmerGUID },                       // :GetCharmerGUID() - Returns the UNIT_FIELD_CHARMEDBY charmer
    { ENV_BOTH, "GetCharmGUID", &LuaUnit::GetCharmGUID },                           // :GetCharmGUID() - Returns the unit's UNIT_FIELD_CHARM guid
    { ENV_BOTH, "GetPetGUID", &LuaUnit::GetPetGUID },                               // :GetPetGUID() - Returns the unit's pet GUID
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "GetCritterGUID", &LuaUnit::GetCritterGUID },                       // :GetCritterGUID() - Returns the critter's GUID
#endif
    { ENV_BOTH, "GetControllerGUID", &LuaUnit::GetControllerGUID },                 // :GetControllerGUID() - Returns the Charmer or Owner GUID
    { ENV_BOTH, "GetControllerGUIDS", &LuaUnit::GetControllerGUIDS },               // :GetControllerGUIDS() - Returns the charmer, owner or unit's own GUID
    { ENV_BOTH, "GetStandState", &LuaUnit::GetStandState },                         // :GetStandState() - Returns the unit's stand state
    { ENV_BOTH, "GetVictim", &LuaUnit::GetVictim },                                 // :GetVictim() - Returns creature's current target
    { ENV_BOTH, "GetSpeed", &LuaUnit::GetSpeed },                                   // :GetSpeed(movementType) - Returns the unit's speed
    { ENV_BOTH, "GetStat", &LuaUnit::GetStat },                                     // :GetStat(stat)
    { ENV_BOTH, "GetBaseSpellPower", &LuaUnit::GetBaseSpellPower },                 // :GetBaseSpellPower()
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "GetVehicleKit", &LuaUnit::GetVehicleKit },                         // :GetVehicleKit() - Gets unit's Vehicle kit if the unit is a vehicle
    // { "GetVehicle", &LuaUnit::GetVehicle },                            // :GetVehicle() - Gets the Vehicle kit of the vehicle the unit is on
#endif
    { ENV_BOTH, "GetMovementType", &LuaUnit::GetMovementType },

    // Setters
    { ENV_BOTH, "SetFaction", &LuaUnit::SetFaction },                   // :SetFaction(factionId) - Sets the unit's faction
    { ENV_BOTH, "SetLevel", &LuaUnit::SetLevel },                       // :SetLevel(amount)
    { ENV_BOTH, "SetHealth", &LuaUnit::SetHealth },                     // :SetHealth(amount)
    { ENV_BOTH, "SetMaxHealth", &LuaUnit::SetMaxHealth },               // :SetMaxHealth(amount)
    { ENV_BOTH, "SetPower", &LuaUnit::SetPower },                       // :SetPower([type,] amount)
    { ENV_BOTH, "SetMaxPower", &LuaUnit::SetMaxPower },                 // :SetMaxPower([type,] amount)
    { ENV_BOTH, "SetPowerType", &LuaUnit::SetPowerType },               // :SetPowerType(type)
    { ENV_BOTH, "SetDisplayId", &LuaUnit::SetDisplayId },               // :SetDisplayId(id)
    { ENV_BOTH, "SetNativeDisplayId", &LuaUnit::SetNativeDisplayId },   // :SetNativeDisplayId(id)
    { ENV_BOTH, "SetFacing", &LuaUnit::SetFacing },                     // :SetFacing(o) - Sets the Unit facing / orientation to arg
    { ENV_BOTH, "SetFacingToObject", &LuaUnit::SetFacingToObject },     // :SetFacingToObject(worldObject) - Sets the Unit facing / orientation towards the WorldObject
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "SetPhaseMask", &LuaUnit::SetPhaseMask },               // :SetPhaseMask(Phase[, update]) - Sets the phase of the unit
#endif
    { ENV_BOTH, "SetSpeed", &LuaUnit::SetSpeed },                       // :SetSpeed(type, speed[, forced]) - Sets speed for the movement type (0 = walk, 1 = run ..)
    // { "SetStunned", &LuaUnit::SetStunned },                // :SetStunned([enable]) - Stuns or removes stun
    { ENV_BOTH, "SetRooted", &LuaUnit::SetRooted },                       // :SetRooted([enable]) - Roots or removes root
    { ENV_BOTH, "SetConfused", &LuaUnit::SetConfused },                   // :SetConfused([enable]) - Sets confused or removes confusion
    { ENV_BOTH, "SetFeared", &LuaUnit::SetFeared },                       // :SetFeared([enable]) - Fears or removes fear
    { ENV_BOTH, "SetPvP", &LuaUnit::SetPvP },                           // :SetPvP([apply]) - Sets the units PvP on or off
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "SetFFA", &LuaUnit::SetFFA },                           // :SetFFA([apply]) - Sets the units FFA tag on or off
    { ENV_BOTH, "SetSanctuary", &LuaUnit::SetSanctuary },               // :SetSanctuary([apply]) - Enables or disables units sanctuary flag
#endif
    // { "SetCanFly", &LuaUnit::SetCanFly },                  // :SetCanFly(apply)
    // { "SetVisible", &LuaUnit::SetVisible },                // :SetVisible(x)
    { ENV_BOTH, "SetOwnerGUID", &LuaUnit::SetOwnerGUID },               // :SetOwnerGUID(guid) - Sets the guid of the owner
    { ENV_BOTH, "SetName", &LuaUnit::SetName },                         // :SetName(name) - Sets the unit's name
    { ENV_BOTH, "SetSheath", &LuaUnit::SetSheath },                     // :SetSheath(SheathState) - Sets unit's sheathstate
    { ENV_BOTH, "SetCreatorGUID", &LuaUnit::SetCreatorGUID },           // :SetOwnerGUID(uint64 ownerGUID) - Sets the owner's guid of a summoned creature, etc
    { ENV_BOTH, "SetMinionGUID", &LuaUnit::SetPetGUID },                // Decapreted. Same as SetPetGUID
    { ENV_BOTH, "SetCharmerGUID", &LuaUnit::SetCharmerGUID },           // :SetCharmerGUID(uint64 ownerGUID) - Sets the UNIT_FIELD_CHARMEDBY charmer GUID
    { ENV_BOTH, "SetPetGUID", &LuaUnit::SetPetGUID },                   // :SetPetGUID(uint64 guid) - Sets the pet's guid
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "SetCritterGUID", &LuaUnit::SetCritterGUID },           // :SetCritterGUID(uint64 guid) - Sets the critter's guid
#endif
    { ENV_BOTH, "SetWaterWalk", &LuaUnit::SetWaterWalk },               // :SetWaterWalk([enable]) - Sets WaterWalk on or off
    { ENV_BOTH, "SetStandState", &LuaUnit::SetStandState },             // :SetStandState(state) - Sets the stand state (Stand, Kneel, sleep, etc) of the unit

    // Boolean
    { ENV_BOTH, "IsAlive", &LuaUnit::IsAlive },                                 // :IsAlive()
    { ENV_BOTH, "IsDead", &LuaUnit::IsDead },                                   // :IsDead() - Returns true if the unit is dead, false if they are alive
    { ENV_BOTH, "IsDying", &LuaUnit::IsDying },                                 // :IsDying() - Returns true if the unit death state is JUST_DIED.
    { ENV_BOTH, "IsPvPFlagged", &LuaUnit::IsPvPFlagged },                       // :IsPvPFlagged()
    { ENV_BOTH, "IsInCombat", &LuaUnit::IsInCombat },                           // :IsInCombat()
    { ENV_BOTH, "IsBanker", &LuaUnit::IsBanker },                               // :IsBanker() - Returns true if the unit is a banker, false if not
    { ENV_BOTH, "IsBattleMaster", &LuaUnit::IsBattleMaster },                   // :IsBattleMaster() - Returns true if the unit is a battle master, false if not
    { ENV_BOTH, "IsCharmed", &LuaUnit::IsCharmed },                             // :IsCharmed() - Returns true if the unit is charmed, false if not
    { ENV_BOTH, "IsArmorer", &LuaUnit::IsArmorer },                             // :IsArmorer() - Returns true if the unit is an Armorer, false if not
    { ENV_BOTH, "IsAttackingPlayer", &LuaUnit::IsAttackingPlayer },             // :IsAttackingPlayer() - Returns true if the unit is attacking a player, false if not
    { ENV_BOTH, "IsInWater", &LuaUnit::IsInWater },                             // :IsInWater() - Returns true if the unit is in water
    { ENV_BOTH, "IsUnderWater", &LuaUnit::IsUnderWater },                       // :IsUnderWater() - Returns true if the unit is under water
    { ENV_BOTH, "IsAuctioneer", &LuaUnit::IsAuctioneer },                       // :IsAuctioneer()
    { ENV_BOTH, "IsGuildMaster", &LuaUnit::IsGuildMaster },                     // :IsGuildMaster()
    { ENV_BOTH, "IsInnkeeper", &LuaUnit::IsInnkeeper },                         // :IsInnkeeper()
    { ENV_BOTH, "IsTrainer", &LuaUnit::IsTrainer },                             // :IsTrainer()
    { ENV_BOTH, "IsGossip", &LuaUnit::IsGossip },                               // :IsGossip()
    { ENV_BOTH, "IsTaxi", &LuaUnit::IsTaxi },                                   // :IsTaxi()
    { ENV_BOTH, "IsSpiritHealer", &LuaUnit::IsSpiritHealer },                   // :IsSpiritHealer()
    { ENV_BOTH, "IsSpiritGuide", &LuaUnit::IsSpiritGuide },                     // :IsSpiritGuide()
    { ENV_BOTH, "IsTabardDesigner", &LuaUnit::IsTabardDesigner },               // :IsTabardDesigner()
    { ENV_BOTH, "IsServiceProvider", &LuaUnit::IsServiceProvider },             // :IsServiceProvider()
    { ENV_BOTH, "IsSpiritService", &LuaUnit::IsSpiritService },                 // :IsSpiritService()
    { ENV_BOTH, "HealthBelowPct", &LuaUnit::HealthBelowPct },                   // :HealthBelowPct(int32 pct)
    { ENV_BOTH, "HealthAbovePct", &LuaUnit::HealthAbovePct },                   // :HealthAbovePct(int32 pct)
    { ENV_BOTH, "IsMounted", &LuaUnit::IsMounted },                             // :IsMounted()
    { ENV_BOTH, "AttackStop", &LuaUnit::AttackStop },                           // :AttackStop()
    { ENV_BOTH, "Attack", &LuaUnit::Attack },                                   // :Attack(who[, meleeAttack])
    // { "IsVisible", &LuaUnit::IsVisible },                          // :IsVisible()
    // { "IsMoving", &LuaUnit::IsMoving },                            // :IsMoving()
    // { "IsFlying", &LuaUnit::IsFlying },                            // :IsFlying()
    { ENV_BOTH, "IsStopped", &LuaUnit::IsStopped },                             // :IsStopped()
    { ENV_BOTH, "HasUnitState", &LuaUnit::HasUnitState },                       // :HasUnitState(state) - state from UnitState enum
    { ENV_BOTH, "IsQuestGiver", &LuaUnit::IsQuestGiver },                       // :IsQuestGiver() - Returns true if the unit is a quest giver, false if not
    { ENV_BOTH, "IsWithinDistInMap", &LuaUnit::IsWithinDistInMap },             // :IsWithinDistInMap(worldObject, radius) - Returns if the unit is within distance in map of the worldObject
    { ENV_BOTH, "IsInAccessiblePlaceFor", &LuaUnit::IsInAccessiblePlaceFor },   // :IsInAccessiblePlaceFor(creature) - Returns if the unit is in an accessible place for the specified creature
    { ENV_BOTH, "IsVendor", &LuaUnit::IsVendor },                               // :IsVendor() - Returns if the unit is a vendor or not
    { ENV_BOTH, "IsRooted", &LuaUnit::IsRooted },                               // :IsRooted()
    { ENV_BOTH, "IsFullHealth", &LuaUnit::IsFullHealth },                       // :IsFullHealth() - Returns if the unit is full health
    { ENV_BOTH, "HasAura", &LuaUnit::HasAura },                                 // :HasAura(spellId) - Returns true if the unit has the aura from the spell
    { ENV_BOTH, "IsCasting", &LuaUnit::IsCasting },
    { ENV_BOTH, "IsStandState", &LuaUnit::IsStandState },                       // :IsStandState() - Returns true if the unit is standing
#ifndef CLASSIC
    { ENV_BOTH, "IsOnVehicle", &LuaUnit::IsOnVehicle },                         // :IsOnVehicle() - Checks if the unit is on a vehicle
#endif

    // Other
    { ENV_BOTH, "AddAura", &LuaUnit::AddAura },                                 // :AddAura(spellId, target) - Adds an aura to the specified target
    { ENV_BOTH, "RemoveAura", &LuaUnit::RemoveAura },                           // :RemoveAura(spellId[, casterGUID]) - Removes an aura from the unit by the spellId, casterGUID(Original caster) is optional
    { ENV_BOTH, "RemoveAllAuras", &LuaUnit::RemoveAllAuras },                   // :RemoveAllAuras() - Removes all the unit's auras
    { ENV_BOTH, "ClearInCombat", &LuaUnit::ClearInCombat },                     // :ClearInCombat() - Clears the unit's combat list (unit will be out of combat), resets the timer to 0, etc
    { ENV_BOTH, "DeMorph", &LuaUnit::DeMorph },                                 // :DeMorph() - Sets display back to native
    { ENV_BOTH, "SendUnitWhisper", &LuaUnit::SendUnitWhisper },                 // :SendUnitWhisper(msg, lang, receiver[, bossWhisper]) - Sends a whisper to the receiver
    { ENV_BOTH, "SendUnitEmote", &LuaUnit::SendUnitEmote },                     // :SendUnitEmote(msg[, receiver, bossEmote]) - Sends a text emote
    { ENV_BOTH, "SendUnitSay", &LuaUnit::SendUnitSay },                         // :SendUnitSay(msg, language) - Sends a "Say" message with the specified language (all languages: 0)
    { ENV_BOTH, "SendUnitYell", &LuaUnit::SendUnitYell },                       // :SendUnitYell(msg, language) - Sends a "Yell" message with the specified language (all languages: 0)
    { ENV_BOTH, "CastSpell", &LuaUnit::CastSpell },                             // :CastSpell(target, spellID[, triggered]) - Casts spell on target (player/npc/creature), if triggered is true then instant cast
    { ENV_BOTH, "CastCustomSpell", &LuaUnit::CastCustomSpell },                 // :CastCustomSpell([Unit] target, uint32 spell, bool triggered = false, int32 bp0 = nil, int32 bp1 = nil, int32 bp2 = nil, [Item] castItem = nil, uint64 originalCaster = 0) - Casts spell on target (player/npc/creature), if triggered is true then instant cast. pb0, 1 and 2 are modifiers for the base points of the spell.
    { ENV_BOTH, "CastSpellAoF", &LuaUnit::CastSpellAoF },                       // :CastSpellAoF(x, y, z, spellID[, triggered]) - Casts the spell on coordinates, if triggered is false has mana cost and cast time
    { ENV_BOTH, "PlayDirectSound", &LuaUnit::PlayDirectSound },                 // :PlayDirectSound(soundId[, player]) - Unit plays soundID to player, or everyone around if no player
    { ENV_BOTH, "PlayDistanceSound", &LuaUnit::PlayDistanceSound },             // :PlayDistanceSound(soundId[, player]) - Unit plays soundID to player, or everyone around if no player. The sound fades the further you are
    { ENV_BOTH, "Kill", &LuaUnit::Kill },                                       // :Kill(target, durabilityLoss) - Unit kills the target. Durabilityloss is true by default
    { ENV_BOTH, "StopSpellCast", &LuaUnit::StopSpellCast },                     // :StopSpellCast([spellId]) - Stops the unit from casting a spell. If a spellId is defined, it will stop that unit from casting that spell
    { ENV_BOTH, "InterruptSpell", &LuaUnit::InterruptSpell },                   // :InterruptSpell(spellType[, delayed]) - Interrupts the unit's spell by the spellType. If delayed is true it will skip if the spell is delayed.
    { ENV_BOTH, "SendChatMessageToPlayer", &LuaUnit::SendChatMessageToPlayer }, // :SendChatMessageToPlayer(type, lang, msg, target) - Unit sends a chat message to the given target player
    { ENV_BOTH, "Emote", &LuaUnit::Emote },                                     // :Emote(emote)
    { ENV_BOTH, "CountPctFromCurHealth", &LuaUnit::CountPctFromCurHealth },     // :CountPctFromCurHealth(int32 pct)
    { ENV_BOTH, "CountPctFromMaxHealth", &LuaUnit::CountPctFromMaxHealth },     // :CountPctFromMaxHealth()
    { ENV_BOTH, "Dismount", &LuaUnit::Dismount },                               // :Dismount() - Dismounts the unit.
    { ENV_BOTH, "Mount", &LuaUnit::Mount },                                     // :Mount(displayId) - Mounts the unit on the specified displayId.
    // { "RestoreDisplayId", &LuaUnit::RestoreDisplayId },            // :RestoreDisplayId()
    // { "RestoreFaction", &LuaUnit::RestoreFaction },                // :RestoreFaction()
    // { "RemoveBindSightAuras", &LuaUnit::RemoveBindSightAuras },    // :RemoveBindSightAuras()
    // { "RemoveCharmAuras", &LuaUnit::RemoveCharmAuras },            // :RemoveCharmAuras()
    { ENV_BOTH, "ClearThreatList", &LuaUnit::ClearThreatList },                 // :ClearThreatList()
    { ENV_BOTH, "ClearUnitState", &LuaUnit::ClearUnitState },                   // :ClearUnitState(state)
    { ENV_BOTH, "AddUnitState", &LuaUnit::AddUnitState },                       // :AddUnitState(state)
    // { "DisableMelee", &LuaUnit::DisableMelee },                    // :DisableMelee([disable]) - if true, enables
    // { "SummonGuardian", &LuaUnit::SummonGuardian },                // :SummonGuardian(entry, x, y, z, o[, duration]) - summons a guardian to location. Scales with summoner, is friendly to him and guards him.
    { ENV_BOTH, "NearTeleport", &LuaUnit::NearTeleport },                       // :NearTeleport(x, y, z, o) - Teleports to give coordinates. Does not leave combat or unsummon pet.
    { ENV_BOTH, "MoveIdle", &LuaUnit::MoveIdle },                               // :MoveIdle()
    { ENV_BOTH, "MoveRandom", &LuaUnit::MoveRandom },                           // :MoveRandom(radius)
    { ENV_BOTH, "MoveHome", &LuaUnit::MoveHome },                               // :MoveHome()
    { ENV_BOTH, "MoveFollow", &LuaUnit::MoveFollow },                           // :MoveFollow(target[, dist, angle])
    { ENV_BOTH, "MoveChase", &LuaUnit::MoveChase },                             // :MoveChase(target[, dist, angle])
    { ENV_BOTH, "MoveConfused", &LuaUnit::MoveConfused },                       // :MoveConfused()
    { ENV_BOTH, "MoveFleeing", &LuaUnit::MoveFleeing },                         // :MoveFleeing(enemy[, time])
    { ENV_BOTH, "MoveTo", &LuaUnit::MoveTo },                                   // :MoveTo(id, x, y, z[, genPath]) - Moves to point. id is sent to WP reach hook. genPath defaults to true
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "MoveJump", &LuaUnit::MoveJump },                               // :MoveJump(x, y, z, zSpeed, maxHeight, id)
#endif
    { ENV_BOTH, "MoveStop", &LuaUnit::MoveStop },                               // :MoveStop()
    { ENV_BOTH, "MoveExpire", &LuaUnit::MoveExpire },                           // :MoveExpire([reset])
    { ENV_BOTH, "MoveClear", &LuaUnit::MoveClear },                             // :MoveClear([reset])
    { ENV_BOTH, "DealDamage", &LuaUnit::DealDamage },                           // :DealDamage(target, amount[, durabilityloss]) - Deals damage to target, durabilityloss is true by default
    { ENV_BOTH, "DealHeal", &LuaUnit::DealHeal },                               // :DealDamage(target, amount, spell[, critical]) - Heals target by given amount. This will be logged as being healed by spell as critical if true.
    { ENV_BOTH, "AddThreat", &LuaUnit::AddThreat },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Player> PlayerMethods[] =
{
    // Getters
    { ENV_BOTH, "GetSelection", &LuaPlayer::GetSelection },                                 // :GetSelection()
    { ENV_BOTH, "GetGMRank", &LuaPlayer::GetGMRank },                                       // :GetSecurity()
    { ENV_BOTH, "GetGuildId", &LuaPlayer::GetGuildId },                                     // :GetGuildId() - nil on no guild
    { ENV_BOTH, "GetCoinage", &LuaPlayer::GetCoinage },                                     // :GetCoinage()
    { ENV_BOTH, "GetTeam", &LuaPlayer::GetTeam },                                           // :GetTeam() - returns the player's team. 0 for ally, 1 for horde
    { ENV_BOTH, "GetItemCount", &LuaPlayer::GetItemCount },                                 // :GetItemCount(item_id[, check_bank])
    { ENV_BOTH, "GetGroup", &LuaPlayer::GetGroup },                                         // :GetGroup()
    { ENV_BOTH, "GetGuild", &LuaPlayer::GetGuild },                                         // :GetGuild()
    { ENV_BOTH, "GetAccountId", &LuaPlayer::GetAccountId },                                 // :GetAccountId()
    { ENV_BOTH, "GetAccountName", &LuaPlayer::GetAccountName },                             // :GetAccountName()
#ifndef CATA
#ifndef CLASSIC
    { ENV_BOTH, "GetArenaPoints", &LuaPlayer::GetArenaPoints },                             // :GetArenaPoints()
    { ENV_BOTH, "GetHonorPoints", &LuaPlayer::GetHonorPoints },                             // :GetHonorPoints()
#endif
#endif
    { ENV_BOTH, "GetLifetimeKills", &LuaPlayer::GetLifetimeKills },                         // :GetLifetimeKills() - Returns the player's lifetime (honorable) kills
    { ENV_BOTH, "GetPlayerIP", &LuaPlayer::GetPlayerIP },                                   // :GetPlayerIP() - Returns the player's IP Address
    { ENV_BOTH, "GetLevelPlayedTime", &LuaPlayer::GetLevelPlayedTime },                     // :GetLevelPlayedTime() - Returns the player's played time at that level
    { ENV_BOTH, "GetTotalPlayedTime", &LuaPlayer::GetTotalPlayedTime },                     // :GetTotalPlayedTime() - Returns the total played time of that player
    { ENV_BOTH, "GetItemByPos", &LuaPlayer::GetItemByPos },                                 // :GetItemByPos(bag, slot) - Returns item in given slot in a bag (bag: 19-22 slot: 0-35) or inventory (bag: 255 slot : 0-38)
    { ENV_BOTH, "GetItemByEntry", &LuaPlayer::GetItemByEntry },                             // :GetItemByEntry(entry) - Gets an item if the player has it
    { ENV_BOTH, "GetItemByGUID", &LuaPlayer::GetItemByGUID },
    { ENV_BOTH, "GetReputation", &LuaPlayer::GetReputation },                               // :GetReputation(faction) - Gets player's reputation with given faction
    { ENV_BOTH, "GetEquippedItemBySlot", &LuaPlayer::GetEquippedItemBySlot },               // :GetEquippedItemBySlot(slotId) - Returns equipped item by slot
    { ENV_BOTH, "GetQuestLevel", &LuaPlayer::GetQuestLevel },                               // :GetQuestLevel(quest) - Returns quest's level
    { ENV_BOTH, "GetChatTag", &LuaPlayer::GetChatTag },                                     // :GetChatTag() - Returns player chat tag ID
    { ENV_BOTH, "GetRestBonus", &LuaPlayer::GetRestBonus },                                 // :GetRestBonus() - Gets player's rest bonus
#ifdef WOTLK
    { ENV_BOTH, "GetPhaseMaskForSpawn", &LuaPlayer::GetPhaseMaskForSpawn },                 // :GetPhaseMaskForSpawn() - Gets the real phasemask for spawning things. Used if the player is in GM mode
#endif
    { ENV_BOTH, "GetReqKillOrCastCurrentCount", &LuaPlayer::GetReqKillOrCastCurrentCount }, // :GetReqKillOrCastCurrentCount(questId, entry) - Gets the objective (kill or cast) current count done
    { ENV_BOTH, "GetQuestStatus", &LuaPlayer::GetQuestStatus },                             // :GetQuestStatus(entry) - Gets the quest's status
    { ENV_BOTH, "GetInGameTime", &LuaPlayer::GetInGameTime },                               // :GetInGameTime() - Returns player's ingame time
    { ENV_BOTH, "GetComboPoints", &LuaPlayer::GetComboPoints },                             // :GetComboPoints() - Returns player's combo points
    { ENV_BOTH, "GetComboTarget", &LuaPlayer::GetComboTarget },                             // :GetComboTarget() - Returns the player's combo target
    { ENV_BOTH, "GetGuildName", &LuaPlayer::GetGuildName },                                 // :GetGuildName() - Returns player's guild's name or nil
    { ENV_BOTH, "GetFreeTalentPoints", &LuaPlayer::GetFreeTalentPoints },                   // :GetFreeTalentPoints() - Returns the amount of unused talent points
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "GetActiveSpec", &LuaPlayer::GetActiveSpec },                               // :GetActiveSpec() - Returns the active specID
    { ENV_BOTH, "GetSpecsCount", &LuaPlayer::GetSpecsCount },                               // :GetSpecsCount() - Returns the player's spec count
#endif
    { ENV_BOTH, "GetSpellCooldownDelay", &LuaPlayer::GetSpellCooldownDelay },               // :GetSpellCooldownDelay(spellId) - Returns the spell's cooldown
    { ENV_BOTH, "GetGuildRank", &LuaPlayer::GetGuildRank },                                 // :GetGuildRank() - Gets the player's guild rank
    { ENV_BOTH, "GetDifficulty", &LuaPlayer::GetDifficulty },                               // :GetDifficulty([isRaid]) - Returns the current difficulty
    { ENV_BOTH, "GetHealthBonusFromStamina", &LuaPlayer::GetHealthBonusFromStamina },       // :GetHealthBonusFromStamina() - Returns the HP bonus from stamina
    { ENV_BOTH, "GetManaBonusFromIntellect", &LuaPlayer::GetManaBonusFromIntellect },       // :GetManaBonusFromIntellect() - Returns the mana bonus from intellect
    { ENV_BOTH, "GetMaxSkillValue", &LuaPlayer::GetMaxSkillValue },                         // :GetMaxSkillValue(skill) - Gets max skill value for the given skill
    { ENV_BOTH, "GetPureMaxSkillValue", &LuaPlayer::GetPureMaxSkillValue },                 // :GetPureMaxSkillValue(skill) - Gets max base skill value
    { ENV_BOTH, "GetSkillValue", &LuaPlayer::GetSkillValue },                               // :GetSkillValue(skill) - Gets current skill value
    { ENV_BOTH, "GetBaseSkillValue", &LuaPlayer::GetBaseSkillValue },                       // :GetBaseSkillValue(skill) - Gets current base skill value (no temp bonus)
    { ENV_BOTH, "GetPureSkillValue", &LuaPlayer::GetPureSkillValue },                       // :GetPureSkillValue(skill) - Gets current base skill value (no bonuses)
    { ENV_BOTH, "GetSkillPermBonusValue", &LuaPlayer::GetSkillPermBonusValue },             // :GetSkillPermBonusValue(skill) - Returns current permanent bonus
    { ENV_BOTH, "GetSkillTempBonusValue", &LuaPlayer::GetSkillTempBonusValue },             // :GetSkillTempBonusValue(skill) - Returns current temp bonus
    { ENV_BOTH, "GetReputationRank", &LuaPlayer::GetReputationRank },                       // :GetReputationRank(faction) - Returns the reputation rank with given faction
    { ENV_BOTH, "GetDrunkValue", &LuaPlayer::GetDrunkValue },                               // :GetDrunkValue() - Returns the current drunkness value
    { ENV_BOTH, "GetBattlegroundId", &LuaPlayer::GetBattlegroundId },                       // :GetBattlegroundId() - Returns the player's current battleground ID
    { ENV_BOTH, "GetBattlegroundTypeId", &LuaPlayer::GetBattlegroundTypeId },               // :GetBattlegroundTypeId() - Returns the player's current battleground type ID
    { ENV_BOTH, "GetXPRestBonus", &LuaPlayer::GetXPRestBonus },                             // :GetXPRestBonus(xp) - Returns the rested bonus XP from given XP
    { ENV_BOTH, "GetGroupInvite", &LuaPlayer::GetGroupInvite },                             // :GetGroupInvite() - Returns the group invited to
    { ENV_BOTH, "GetSubGroup", &LuaPlayer::GetSubGroup },                                   // :GetSubGroup() - Gets the player's current subgroup ID
    { ENV_BOTH, "GetNextRandomRaidMember", &LuaPlayer::GetNextRandomRaidMember },           // :GetNextRandomRaidMember(radius) - Gets a random raid member in given radius
    { ENV_BOTH, "GetOriginalGroup", &LuaPlayer::GetOriginalGroup },                         // :GetOriginalGroup() - Gets the original group object
    { ENV_BOTH, "GetOriginalSubGroup", &LuaPlayer::GetOriginalSubGroup },                   // :GetOriginalSubGroup() - Returns the original subgroup ID
#ifdef TRINITY
    { ENV_BOTH, "GetChampioningFaction", &LuaPlayer::GetChampioningFaction },               // :GetChampioningFaction() - Returns the player's championing faction
#endif
    { ENV_BOTH, "GetLatency", &LuaPlayer::GetLatency },                                     // :GetLatency() - Returns player's latency
    // { "GetRecruiterId", &LuaPlayer::GetRecruiterId },                          // :GetRecruiterId() - Returns player's recruiter's ID
    { ENV_BOTH, "GetDbLocaleIndex", &LuaPlayer::GetDbLocaleIndex },                         // :GetDbLocaleIndex() - Returns locale index
    { ENV_BOTH, "GetDbcLocale", &LuaPlayer::GetDbcLocale },                                 // :GetDbcLocale() - Returns DBC locale
    { ENV_BOTH, "GetCorpse", &LuaPlayer::GetCorpse },                                       // :GetCorpse() - Returns the player's corpse
    { ENV_BOTH, "GetGossipTextId", &LuaPlayer::GetGossipTextId },                           // :GetGossipTextId(worldObject) - Returns the WorldObject's gossip textId
    { ENV_BOTH, "GetQuestRewardStatus", &LuaPlayer::GetQuestRewardStatus },                 // :GetQuestRewardStatus(questId) - Returns the true/false of the quest reward status
#ifndef CATA
    { ENV_BOTH, "GetShieldBlockValue", &LuaPlayer::GetShieldBlockValue },                   // :GetShieldBlockValue() - Returns block value
#endif
#ifdef CLASSIC
    { ENV_BOTH, "GetHonorStoredKills", &LuaPlayer::GetHonorStoredKills },                     // :GetHonorStoredKills(on/off)
    { ENV_BOTH, "GetRankPoints", &LuaPlayer::GetRankPoints },                                 // :GetRankPoints()
    { ENV_BOTH, "GetHonorLastWeekStandingPos", &LuaPlayer::GetHonorLastWeekStandingPos },     // :GetHonorLastWeekStandingPos()
#endif

    // Setters
    { ENV_BOTH, "AdvanceSkillsToMax", &LuaPlayer::AdvanceSkillsToMax },     // :AdvanceSkillsToMax() - Advances all currently known skills to the currently known max level
    { ENV_BOTH, "AdvanceSkill", &LuaPlayer::AdvanceSkill },                 // :AdvanceSkill(skill_id, step) - Advances skill by ID and the amount(step)
    { ENV_BOTH, "AdvanceAllSkills", &LuaPlayer::AdvanceAllSkills },         // :AdvanceAllSkills(value) - Advances all current skills to your input(value)
    { ENV_BOTH, "AddLifetimeKills", &LuaPlayer::AddLifetimeKills },         // :AddLifetimeKills(val) - Adds lifetime (honorable) kills to your current lifetime kills
    { ENV_BOTH, "SetCoinage", &LuaPlayer::SetCoinage },                     // :SetCoinage(amount) - sets plr's coinage to this
#ifndef CLASSIC
    { ENV_BOTH, "SetKnownTitle", &LuaPlayer::SetKnownTitle },               // :SetKnownTitle(id)
    { ENV_BOTH, "UnsetKnownTitle", &LuaPlayer::UnsetKnownTitle },           // :UnsetKnownTitle(id)
#endif
    { ENV_BOTH, "SetBindPoint", &LuaPlayer::SetBindPoint },                 // :SetBindPoint(x, y, z, map, areaid) - sets home for hearthstone
#ifndef CATA
#ifndef CLASSIC
    { ENV_BOTH, "SetArenaPoints", &LuaPlayer::SetArenaPoints },             // :SetArenaPoints(amount)
    { ENV_BOTH, "SetHonorPoints", &LuaPlayer::SetHonorPoints },             // :SetHonorPoints(amount)
#endif
#endif
#ifdef CLASSIC
    { ENV_BOTH, "SetHonorStoredKills", &LuaPlayer::SetHonorStoredKills },     // :SetHonorStoredKills(kills, [on/off])
    { ENV_BOTH, "SetRankPoints", &LuaPlayer::SetRankPoints },                 // :SetRankPoints(rankPoints)
    { ENV_BOTH, "SetHonorLastWeekStandingPos", &LuaPlayer::SetHonorLastWeekStandingPos }, // :SetHonorLastWeekStandingPos(standingPos)
#endif
    { ENV_BOTH, "SetLifetimeKills", &LuaPlayer::SetLifetimeKills },         // :SetLifetimeKills(val) - Sets the overall lifetime (honorable) kills of the player
    { ENV_BOTH, "SetGameMaster", &LuaPlayer::SetGameMaster },               // :SetGameMaster([on]) - Sets GM mode on or off
    { ENV_BOTH, "SetGMChat", &LuaPlayer::SetGMChat },                       // :SetGMChat([on]) - Sets GM chat on or off
    { ENV_BOTH, "SetTaxiCheat", &LuaPlayer::SetTaxiCheat },                 // :SetTaxiCheat([on]) - Sets taxi cheat on or off
    { ENV_BOTH, "SetGMVisible", &LuaPlayer::SetGMVisible },                 // :SetGMVisible([on]) - Sets gm visibility on or off
    { ENV_BOTH, "SetPvPDeath", &LuaPlayer::SetPvPDeath },                   // :SetPvPDeath([on]) - Sets PvP death on or off
    { ENV_BOTH, "SetAcceptWhispers", &LuaPlayer::SetAcceptWhispers },       // :SetAcceptWhispers([on]) - Sets whisper accepting death on or off
    { ENV_BOTH, "SetRestBonus", &LuaPlayer::SetRestBonus },                 // :SetRestBonus(bonusrate) - Sets new restbonus rate
    { ENV_BOTH, "SetQuestStatus", &LuaPlayer::SetQuestStatus },             // :SetQuestStatus(entry, status) - Sets the quest's status
    { ENV_BOTH, "SetReputation", &LuaPlayer::SetReputation },               // :SetReputation(faction, value) - Sets the faction reputation for the player
    { ENV_BOTH, "SetFreeTalentPoints", &LuaPlayer::SetFreeTalentPoints },   // :SetFreeTalentPoints(points) - Sets the amount of unused talent points
    { ENV_BOTH, "SetGuildRank", &LuaPlayer::SetGuildRank },                 // :SetGuildRank(rank) - Sets player's guild rank
    // { "SetMovement", &LuaPlayer::SetMovement },                // :SetMovement(type) - Sets player's movement type
    { ENV_BOTH, "SetSkill", &LuaPlayer::SetSkill },                         // :SetSkill(skill, step, currVal, maxVal) - Sets the skill's boundaries and value
    { ENV_BOTH, "SetFactionForRace", &LuaPlayer::SetFactionForRace },       // :SetFactionForRace(race) - Sets the faction by raceID
    { ENV_BOTH, "SetDrunkValue", &LuaPlayer::SetDrunkValue },               // :SetDrunkValue(newDrunkValue) - Sets drunkness value
    { ENV_BOTH, "SetAtLoginFlag", &LuaPlayer::SetAtLoginFlag },             // :SetAtLoginFlag(flag) - Adds an at login flag
    { ENV_BOTH, "SetPlayerLock", &LuaPlayer::SetPlayerLock },               // :SetPlayerLock(on/off)
    { ENV_BOTH, "SetGender", &LuaPlayer::SetGender },                       // :SetGender(value) - 0 = male 1 = female
    { ENV_BOTH, "SetSheath", &LuaPlayer::SetSheath },                       // :SetSheath(SheathState) - Sets player's sheathstate
#ifndef TRINITY
    { ENV_BOTH, "SetFFA", &LuaPlayer::SetFFA },                             // :SetFFA([apply]) - Sets the units FFA tag on or off
#endif

    // Boolean
    { ENV_BOTH, "IsInGroup", &LuaPlayer::IsInGroup },                                               // :IsInGroup()
    { ENV_BOTH, "IsInGuild", &LuaPlayer::IsInGuild },                                               // :IsInGuild()
    { ENV_BOTH, "IsGM", &LuaPlayer::IsGM },                                                         // :IsGM()
    { ENV_BOTH, "IsAlliance", &LuaPlayer::IsAlliance },                                             // :IsAlliance()
    { ENV_BOTH, "IsHorde", &LuaPlayer::IsHorde },                                                   // :IsHorde()
#ifndef CLASSIC
    { ENV_BOTH, "HasTitle", &LuaPlayer::HasTitle },                                                 // :HasTitle(id)
#endif
    { ENV_BOTH, "HasItem", &LuaPlayer::HasItem },                                                   // :HasItem(itemId[, count, check_bank]) - Returns true if the player has the item(itemId) and specified count, else it will return false
    { ENV_BOTH, "Teleport", &LuaPlayer::Teleport },                                                 // :Teleport(Map, X, Y, Z, O) - Teleports player to specified co - ordinates. Returns true if success and false if not
    { ENV_BOTH, "AddItem", &LuaPlayer::AddItem },                                                   // :AddItem(id, amount) - Adds amount of item to player. Returns true if success and false if not
#ifndef CLASSIC
    { ENV_BOTH, "IsInArenaTeam", &LuaPlayer::IsInArenaTeam },                                       // :IsInArenaTeam(type) - type : 0 = 2v2, 1 = 3v3, 2 = 5v5
#endif
    { ENV_BOTH, "CanCompleteQuest", &LuaPlayer::CanCompleteQuest },
    { ENV_BOTH, "CanEquipItem", &LuaPlayer::CanEquipItem },                                         // :CanEquipItem(entry/item, slot) - Returns true if the player can equip given item/item entry
    { ENV_BOTH, "IsFalling", &LuaPlayer::IsFalling },                                               // :IsFalling() - Returns true if the unit is falling
    { ENV_BOTH, "ToggleAFK", &LuaPlayer::ToggleAFK },                                               // :ToggleAFK() - Toggles AFK state for player
    { ENV_BOTH, "ToggleDND", &LuaPlayer::ToggleDND },                                               // :ToggleDND() - Toggles DND state for player
    { ENV_BOTH, "IsAFK", &LuaPlayer::IsAFK },                                                       // :IsAFK() - Returns true if the player is afk
    { ENV_BOTH, "IsDND", &LuaPlayer::IsDND },                                                       // :IsDND() - Returns true if the player is in dnd mode
    { ENV_BOTH, "IsAcceptingWhispers", &LuaPlayer::IsAcceptingWhispers },                           // :IsAcceptWhispers() - Returns true if the player accepts whispers
    { ENV_BOTH, "IsGMChat", &LuaPlayer::IsGMChat },                                                 // :IsGMChat() - Returns true if the player has GM chat on
    { ENV_BOTH, "IsTaxiCheater", &LuaPlayer::IsTaxiCheater },                                       // :IsTaxiCheater() - Returns true if the player has taxi cheat on
    { ENV_BOTH, "IsGMVisible", &LuaPlayer::IsGMVisible },                                           // :IsGMVisible() - Returns true if the player is GM visible
    { ENV_BOTH, "HasQuest", &LuaPlayer::HasQuest },                                                 // :HasQuest(entry) - Returns true if player has the quest
    { ENV_BOTH, "InBattlegroundQueue", &LuaPlayer::InBattlegroundQueue },                           // :InBattlegroundQueue() - Returns true if the player is in a battleground queue
    // { "IsImmuneToEnvironmentalDamage", &LuaPlayer::IsImmuneToEnvironmentalDamage },    // :IsImmuneToEnvironmentalDamage() - Returns true if the player is immune to enviromental damage
    { ENV_BOTH, "CanSpeak", &LuaPlayer::CanSpeak },                                                 // :CanSpeak() - Returns true if the player can speak
    { ENV_BOTH, "HasAtLoginFlag", &LuaPlayer::HasAtLoginFlag },                                     // :HasAtLoginFlag(flag) - returns true if the player has the login flag
    // { "InRandomLfgDungeon", &LuaPlayer::InRandomLfgDungeon },                          // :InRandomLfgDungeon() - Returns true if the player is in a random LFG dungeon
    // { "HasPendingBind", &LuaPlayer::HasPendingBind },                                  // :HasPendingBind() - Returns true if the player has a pending instance bind
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "HasAchieved", &LuaPlayer::HasAchieved },                                           // :HasAchieved(achievementID) - Returns true if the player has achieved the achievement
#endif
    { ENV_BOTH, "CanUninviteFromGroup", &LuaPlayer::CanUninviteFromGroup },                         // :CanUninviteFromGroup() - Returns true if the player can uninvite from group
    { ENV_BOTH, "IsRested", &LuaPlayer::IsRested },                                                 // :IsRested() - Returns true if the player is rested
    // { "CanFlyInZone", &LuaPlayer::CanFlyInZone },                                      // :CanFlyInZone(mapid, zone) - Returns true if the player can fly in the area
    // { "IsNeverVisible", &LuaPlayer::IsNeverVisible },                                  // :IsNeverVisible() - Returns true if the player is never visible
    { ENV_BOTH, "IsVisibleForPlayer", &LuaPlayer::IsVisibleForPlayer },                             // :IsVisibleForPlayer(player) - Returns true if the player is visible for the target player
    // { "IsUsingLfg", &LuaPlayer::IsUsingLfg },                                          // :IsUsingLfg() - Returns true if the player is using LFG
    { ENV_BOTH, "HasQuestForItem", &LuaPlayer::HasQuestForItem },                                   // :HasQuestForItem(entry) - Returns true if the player has the quest for the item
    { ENV_BOTH, "HasQuestForGO", &LuaPlayer::HasQuestForGO },                                       // :HasQuestForGO(entry) - Returns true if the player has the quest for the gameobject
    { ENV_BOTH, "CanShareQuest", &LuaPlayer::CanShareQuest },                                       // :CanShareQuest(entry) - Returns true if the quest entry is shareable by the player
    // { "HasReceivedQuestReward", &LuaPlayer::HasReceivedQuestReward },                  // :HasReceivedQuestReward(entry) - Returns true if the player has recieved the quest's reward
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "HasTalent", &LuaPlayer::HasTalent },                                               // :HasTalent(talentId, spec) - Returns true if the player has the talent in given spec
#endif
    { ENV_BOTH, "IsInSameGroupWith", &LuaPlayer::IsInSameGroupWith },                               // :IsInSameGroupWith(player) - Returns true if the players are in the same group
    { ENV_BOTH, "IsInSameRaidWith", &LuaPlayer::IsInSameRaidWith },                                 // :IsInSameRaidWith(player) - Returns true if the players are in the same raid
    { ENV_BOTH, "IsGroupVisibleFor", &LuaPlayer::IsGroupVisibleFor },                               // :IsGroupVisibleFor(player) - Player is group visible for the target
    { ENV_BOTH, "HasSkill", &LuaPlayer::HasSkill },                                                 // :HasSkill(skill) - Returns true if the player has the skill
    { ENV_BOTH, "IsHonorOrXPTarget", &LuaPlayer::IsHonorOrXPTarget },                               // :IsHonorOrXPTarget(victim) - Returns true if the victim gives honor or XP
    { ENV_BOTH, "CanParry", &LuaPlayer::CanParry },                                                 // :CanParry() - Returns true if the player can parry
    { ENV_BOTH, "CanBlock", &LuaPlayer::CanBlock },                                                 // :CanBlock() - Returns true if the player can block
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "CanTitanGrip", &LuaPlayer::CanTitanGrip },                                         // :CanTitanGrip() - Returns true if the player has titan grip
#endif
    { ENV_BOTH, "InBattleground", &LuaPlayer::InBattleground },                                     // :InBattleground() - Returns true if the player is in a battleground
#ifndef CLASSIC
    { ENV_BOTH, "InArena", &LuaPlayer::InArena },                                                   // :InArena() - Returns true if the player is in an arena
#endif
    // { "IsOutdoorPvPActive", &LuaPlayer::IsOutdoorPvPActive },                          // :IsOutdoorPvPActive() - Returns true if the player is outdoor pvp active
    // { "IsARecruiter", &LuaPlayer::IsARecruiter },                                      // :IsARecruiter() - Returns true if the player is a recruiter
    { ENV_BOTH, "CanUseItem", &LuaPlayer::CanUseItem },                                             // :CanUseItem(item/entry) - Returns true if the player can use the item or item entry
    { ENV_BOTH, "HasSpell", &LuaPlayer::HasSpell },                                                 // :HasSpell(id)
    { ENV_BOTH, "HasSpellCooldown", &LuaPlayer::HasSpellCooldown },                                 // :HasSpellCooldown(spellId) - Returns true if the spell is on cooldown
    { ENV_BOTH, "IsInWater", &LuaPlayer::IsInWater },                                               // :IsInWater() - Returns true if the player is in water
#ifndef CLASSIC
    { ENV_BOTH, "CanFly", &LuaPlayer::CanFly },                                                     // :CanFly() - Returns true if the player can fly
#endif
    { ENV_BOTH, "IsMoving", &LuaPlayer::IsMoving },                                                 // :IsMoving()
#ifndef CLASSIC
    { ENV_BOTH, "IsFlying", &LuaPlayer::IsFlying },                                                 // :IsFlying()
#endif

    // Gossip
    { ENV_BOTH, "GossipMenuAddItem", &LuaPlayer::GossipMenuAddItem },                               // :GossipMenuAddItem(icon, msg, sender, intid[, code, popup, money])
    { ENV_BOTH, "GossipSendMenu", &LuaPlayer::GossipSendMenu },                                     // :GossipSendMenu(npc_text, unit[, menu_id]) - If unit is a player, you need to use a menu_id. menu_id is used to hook the gossip select function to the menu
    { ENV_BOTH, "GossipComplete", &LuaPlayer::GossipComplete },                                     // :GossipComplete()
    { ENV_BOTH, "GossipClearMenu", &LuaPlayer::GossipClearMenu },                                   // :GossipClearMenu() - Clears the gossip menu of options. Pretty much only useful with player gossip. Need to use before creating a new menu for the player

    // Other
    { ENV_BOTH, "SendClearCooldowns", &LuaPlayer::SendClearCooldowns },                            // :SendClearCooldowns(spellId, (unit)target) - Clears the cooldown of the target with a specified spellId
    { ENV_BOTH, "SendBroadcastMessage", &LuaPlayer::SendBroadcastMessage },                         // :SendBroadcastMessage(message)
    { ENV_BOTH, "SendAreaTriggerMessage", &LuaPlayer::SendAreaTriggerMessage },                     // :SendAreaTriggerMessage(message) - Sends a yellow message in the middle of your screen
    { ENV_BOTH, "SendNotification", &LuaPlayer::SendNotification },                                 // :SendNotification(message) - Sends a red message in the middle of your screen
    { ENV_BOTH, "SendPacket", &LuaPlayer::SendPacket },                                             // :SendPacket(packet, selfOnly) - Sends a packet to player or everyone around also if selfOnly is false
    { ENV_BOTH, "SendAddonMessage", &LuaPlayer::SendAddonMessage },                                 // :SendAddonMessage(prefix, message, channel, receiver) - Sends an addon message to the player. 
    { ENV_BOTH, "ModifyMoney", &LuaPlayer::ModifyMoney },                                           // :ModifyMoney(amount[, sendError]) - Modifies (does not set) money (copper count) of the player. Amount can be negative to remove copper
    { ENV_BOTH, "LearnSpell", &LuaPlayer::LearnSpell },                                             // :LearnSpell(id) - learns the given spell
    { ENV_BOTH, "LearnTalent", &LuaPlayer::LearnTalent },
    { ENV_BOTH, "RemoveItem", &LuaPlayer::RemoveItem },                                             // :RemoveItem(item/entry, amount) - Removes amount of item from player
    { ENV_BOTH, "RemoveLifetimeKills", &LuaPlayer::RemoveLifetimeKills },                           // :RemoveLifetimeKills(val) - Removes a specified amount(val) of the player's lifetime (honorable) kills
    { ENV_BOTH, "ResurrectPlayer", &LuaPlayer::ResurrectPlayer },                                   // :ResurrectPlayer([percent[, sickness(bool)]]) - Resurrects the player at percentage, player gets resurrection sickness if sickness set to true
    { ENV_BOTH, "PlaySoundToPlayer", &LuaPlayer::PlaySoundToPlayer },                               // :PlaySoundToPlayer(soundId) - Plays the specified sound to the player
    { ENV_BOTH, "EquipItem", &LuaPlayer::EquipItem },                                               // :EquipItem(entry/item, slot) - Equips given item or item entry for player to given slot. Returns the equipped item or nil
    { ENV_BOTH, "ResetSpellCooldown", &LuaPlayer::ResetSpellCooldown },                             // :ResetSpellCooldown(spellId, update(bool~optional)) - Resets cooldown of the specified spellId. If update is true, it will send WorldPacket SMSG_CLEAR_COOLDOWN to the player, else it will just clear the spellId from m_spellCooldowns. This is true by default
    { ENV_BOTH, "ResetTypeCooldowns", &LuaPlayer::ResetTypeCooldowns },                             // :ResetTypeCooldowns(category, update(bool~optional)) - Resets all cooldowns for the spell category(type). If update is true, it will send WorldPacket SMSG_CLEAR_COOLDOWN to the player, else it will just clear the spellId from m_spellCooldowns. This is true by default
    { ENV_BOTH, "ResetAllCooldowns", &LuaPlayer::ResetAllCooldowns },                               // :ResetAllCooldowns() - Resets all spell cooldowns
    { ENV_BOTH, "GiveXP", &LuaPlayer::GiveXP },                                                     // :GiveXP(xp[, victim, pureXP, triggerHook]) - Gives XP to the player. If pure is false, bonuses are count in. If triggerHook is false, GiveXp hook is not triggered.
    // { "RemovePet", &LuaPlayer::RemovePet },                                            // :RemovePet([mode, returnreagent]) - Removes the player's pet. Mode determines if the pet is saved and how
    // { "SummonPet", &LuaPlayer::SummonPet },                                            // :SummonPet(entry, x, y, z, o, petType, despwtime) - Summons a pet for the player
    { ENV_BOTH, "Say", &LuaPlayer::Say },                                                           // :Say(text, lang) - The player says the text
    { ENV_BOTH, "Yell", &LuaPlayer::Yell },                                                         // :Yell(text, lang) - The player yells the text
    { ENV_BOTH, "TextEmote", &LuaPlayer::TextEmote },                                               // :TextEmote(text) - The player does a textemote with the text
    { ENV_BOTH, "Whisper", &LuaPlayer::Whisper },                                                   // :Whisper(text, lang, receiver) - The player whispers the text to the receiver
    { ENV_BOTH, "CompleteQuest", &LuaPlayer::CompleteQuest },                                       // :CompleteQuest(entry) - Completes a quest by entry
    { ENV_BOTH, "IncompleteQuest", &LuaPlayer::IncompleteQuest },                                   // :IncompleteQuest(entry) - Uncompletes the quest by entry for the player
    { ENV_BOTH, "FailQuest", &LuaPlayer::FailQuest },                                               // :FailQuest(entry) - Player fails the quest entry
    { ENV_BOTH, "AddQuest", &LuaPlayer::AddQuest },
    { ENV_BOTH, "RemoveQuest", &LuaPlayer::RemoveQuest },
    // { "RemoveActiveQuest", &LuaPlayer::RemoveActiveQuest },                            // :RemoveActiveQuest(entry) - Removes an active quest
    // { "RemoveRewardedQuest", &LuaPlayer::RemoveRewardedQuest },                        // :RemoveRewardedQuest(entry) - Removes a rewarded quest
    { ENV_BOTH, "AreaExploredOrEventHappens", &LuaPlayer::AreaExploredOrEventHappens },             // :AreaExploredOrEventHappens(questId) - Satisfies an area or event requrement for the questId
    { ENV_WORLD, "GroupEventHappens", &LuaPlayer::GroupEventHappens },                               // :GroupEventHappens(questId, worldObject) - Satisfies a group event for the questId with the world object
    { ENV_BOTH, "KilledMonsterCredit", &LuaPlayer::KilledMonsterCredit },                           // :KilledMonsterCredit(entry) - Satisfies a monsterkill for the player
    // { "KilledPlayerCredit", &LuaPlayer::KilledPlayerCredit },                          // :KilledPlayerCredit() - Satisfies a player kill for the player
    // { "KillGOCredit", &LuaPlayer::KillGOCredit },                                      // :KillGOCredit(GOEntry[, GUID]) - Credits the player for destroying a GO, guid is optional
    { ENV_BOTH, "TalkedToCreature", &LuaPlayer::TalkedToCreature },                                 // :TalkedToCreature(npcEntry, creature) - Satisfies creature talk objective for the player
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "ResetPetTalents", &LuaPlayer::ResetPetTalents },                                   // :ResetPetTalents() - Resets player's pet's talents
#endif
    { ENV_BOTH, "AddComboPoints", &LuaPlayer::AddComboPoints },                                     // :AddComboPoints(target, count[, spell]) - Adds combo points to the target for the player
    // { "GainSpellComboPoints", &LuaPlayer::GainSpellComboPoints },                      // :GainSpellComboPoints(amount) - Player gains spell combo points
    { ENV_BOTH, "ClearComboPoints", &LuaPlayer::ClearComboPoints },                                 // :ClearComboPoints() - Clears player's combo points
    { ENV_BOTH, "RemoveSpell", &LuaPlayer::RemoveSpell },                                           // :RemoveSpell(entry[, disabled, learn_low_rank]) - Removes (unlearn) the given spell
    { ENV_BOTH, "ResetTalents", &LuaPlayer::ResetTalents },                                         // :ResetTalents([no_cost]) - Resets player's talents
    { ENV_BOTH, "ResetTalentsCost", &LuaPlayer::ResetTalentsCost },                                 // :ResetTalentsCost() - Returns the reset talents cost
    // { "AddTalent", &LuaPlayer::AddTalent },                                            // :AddTalent(spellid, spec, learning) - Adds a talent spell for the player to given spec
    { ENV_WORLD, "RemoveFromGroup", &LuaPlayer::RemoveFromGroup },                                   // :RemoveFromGroup() - Removes the player from his group
    { ENV_BOTH, "KillPlayer", &LuaPlayer::KillPlayer },                                             // :KillPlayer() - Kills the player
    { ENV_BOTH, "DurabilityLossAll", &LuaPlayer::DurabilityLossAll },                               // :DurabilityLossAll(percent[, inventory]) - The player's items lose durability. Inventory true by default
    { ENV_BOTH, "DurabilityLoss", &LuaPlayer::DurabilityLoss },                                     // :DurabilityLoss(item, percent) - The given item loses durability
    { ENV_BOTH, "DurabilityPointsLoss", &LuaPlayer::DurabilityPointsLoss },                         // :DurabilityPointsLoss(item, points) - The given item loses durability
    { ENV_BOTH, "DurabilityPointsLossAll", &LuaPlayer::DurabilityPointsLossAll },                   // :DurabilityPointsLossAll(points, inventory) - Player's items lose durability
    { ENV_BOTH, "DurabilityPointLossForEquipSlot", &LuaPlayer::DurabilityPointLossForEquipSlot },   // :DurabilityPointLossForEquipSlot(slot) - Causes durability loss for the item in the given slot
    { ENV_WORLD, "DurabilityRepairAll", &LuaPlayer::DurabilityRepairAll },                           // :DurabilityRepairAll([has_cost, discount, guildBank]) - Repairs all durability
    { ENV_WORLD, "DurabilityRepair", &LuaPlayer::DurabilityRepair },                                 // :DurabilityRepair(position[, has_cost, discount, guildBank]) - Repairs item durability of item in given position
#ifndef CATA
#ifndef CLASSIC
    { ENV_BOTH, "ModifyHonorPoints", &LuaPlayer::ModifyHonorPoints },                               // :ModifyHonorPoints(amount) - Modifies the player's honor points
    { ENV_BOTH, "ModifyArenaPoints", &LuaPlayer::ModifyArenaPoints },                               // :ModifyArenaPoints(amount) - Modifies the player's arena points
#endif
#endif
    { ENV_BOTH, "LeaveBattleground", &LuaPlayer::LeaveBattleground },                               // :LeaveBattleground([teleToEntryPoint]) - The player leaves the battleground
    // { "BindToInstance", &LuaPlayer::BindToInstance },                                  // :BindToInstance() - Binds the player to the current instance
    { ENV_BOTH, "UnbindInstance", &LuaPlayer::UnbindInstance },                                     // :UnbindInstance(map, difficulty) - Unbinds the player from an instance
    { ENV_BOTH, "UnbindAllInstances", &LuaPlayer::UnbindAllInstances },                             // :UnbindAllInstances() - Unbinds the player from all instances
    { ENV_BOTH, "RemoveFromBattlegroundRaid", &LuaPlayer::RemoveFromBattlegroundRaid },             // :RemoveFromBattlegroundRaid() - Removes the player from a battleground or battlefield raid
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "ResetAchievements", &LuaPlayer::ResetAchievements },                               // :ResetAchievements() - Resets player�s achievements
#endif
    { ENV_WORLD, "KickPlayer", &LuaPlayer::KickPlayer },                                             // :KickPlayer() - Kicks player from server
    { ENV_WORLD, "LogoutPlayer", &LuaPlayer::LogoutPlayer },                                         // :LogoutPlayer([save]) - Logs the player out and saves if true
    { ENV_BOTH, "SendTrainerList", &LuaPlayer::SendTrainerList },                                   // :SendTrainerList(WorldObject) - Sends trainer list from object to player
    { ENV_BOTH, "SendListInventory", &LuaPlayer::SendListInventory },                               // :SendListInventory(WorldObject) - Sends vendor list from object to player
    { ENV_BOTH, "SendShowBank", &LuaPlayer::SendShowBank },                                         // :SendShowBank(WorldObject) - Sends bank window from object to player
    { ENV_BOTH, "SendTabardVendorActivate", &LuaPlayer::SendTabardVendorActivate },                 // :SendTabardVendorActivate(WorldObject) - Sends tabard vendor window from object to player
    { ENV_BOTH, "SendSpiritResurrect", &LuaPlayer::SendSpiritResurrect },                           // :SendSpiritResurrect() - Sends resurrect window to player
    { ENV_BOTH, "SendTaxiMenu", &LuaPlayer::SendTaxiMenu },                                         // :SendTaxiMenu(creature) - Sends flight window to player from creature
    { ENV_BOTH, "RewardQuest", &LuaPlayer::RewardQuest },
    { ENV_BOTH, "SendAuctionMenu", &LuaPlayer::SendAuctionMenu },                                   // :SendAuctionMenu(unit) - Sends auction window to player. Auction house is sent by object.
    { ENV_BOTH, "SendShowMailBox", &LuaPlayer::SendShowMailBox },                                   // :SendShowMailBox([mailboxguid]) - Sends the mail window to player from the mailbox gameobject. The guid is required on patches below wotlk.
    { ENV_BOTH, "StartTaxi", &LuaPlayer::StartTaxi },                                               // :StartTaxi(pathId) - player starts the given flight path
    { ENV_BOTH, "GossipSendPOI", &LuaPlayer::GossipSendPOI },                                       // :GossipSendPOI(X, Y, Icon, Flags, Data, Name) - Sends a point of interest to the player
    { ENV_BOTH, "GossipAddQuests", &LuaPlayer::GossipAddQuests },                                   // :GossipAddQuests(unit) - Adds unit's quests to player's gossip menu
    { ENV_BOTH, "SendQuestTemplate", &LuaPlayer::SendQuestTemplate },                               // :SendQuestTemplate(questId, activeAccept) -- Sends quest template to player
    { ENV_NONE, "SpawnBones", &LuaPlayer::SpawnBones },                                             // :SpawnBones() - Removes the player's corpse and spawns bones
    { ENV_NONE, "RemovedInsignia", &LuaPlayer::RemovedInsignia },                                   // :RemovedInsignia(looter) - Looter removes the player's corpse, looting the player and replacing with lootable bones
    { ENV_WORLD, "SendGuildInvite", &LuaPlayer::SendGuildInvite },                                   // :SendGuildInvite(player) - Sends a guild invite to the specific player
    { ENV_NONE, "CreateCorpse", &LuaPlayer::CreateCorpse },                                         // :CreateCorpse() - Creates the player's corpse
    { ENV_BOTH, "Mute", &LuaPlayer::Mute },                                                         // :Mute(time[, reason]) - Mutes the player for given time in seconds.
    { ENV_BOTH, "SummonPlayer", &LuaPlayer::SummonPlayer },                                         // :SummonPlayer(player, map, x, y, z, zoneId[, delay]) - Sends a popup to the player asking if he wants to be summoned if yes, teleported to coords. ZoneID defines the location name shown in the popup Delay is the time until the popup closes automatically.
    { ENV_BOTH, "SaveToDB", &LuaPlayer::SaveToDB },                                                 // :SaveToDB() - Saves to database
    { ENV_WORLD, "GroupInvite", &LuaPlayer::GroupInvite },
    { ENV_WORLD, "GroupCreate", &LuaPlayer::GroupCreate },
#ifdef CLASSIC
    { ENV_BOTH, "UpdateHonor", &LuaPlayer::UpdateHonor },                                             // :UpdateHonor() - Updates Player Honor
    { ENV_BOTH, "ResetHonor", &LuaPlayer::ResetHonor },                                               // :ResetHonor() - Resets Player Honor
    { ENV_BOTH, "ClearHonorInfo", &LuaPlayer::ClearHonorInfo },                                       // :ClearHonorInfo() - Clear Player Honor Info
#endif

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Creature> CreatureMethods[] =
{
    // Getters
    { ENV_BOTH, "GetAITarget", &LuaCreature::GetAITarget },
    { ENV_BOTH, "GetAITargets", &LuaCreature::GetAITargets },
    { ENV_BOTH, "GetAITargetsCount", &LuaCreature::GetAITargetsCount },
    { ENV_BOTH, "GetHomePosition", &LuaCreature::GetHomePosition },
    { ENV_BOTH, "GetCorpseDelay", &LuaCreature::GetCorpseDelay },
    { ENV_BOTH, "GetCreatureSpellCooldownDelay", &LuaCreature::GetCreatureSpellCooldownDelay },
    { ENV_BOTH, "GetScriptId", &LuaCreature::GetScriptId },
    { ENV_BOTH, "GetAIName", &LuaCreature::GetAIName },
    { ENV_BOTH, "GetScriptName", &LuaCreature::GetScriptName },
    { ENV_BOTH, "GetAttackDistance", &LuaCreature::GetAttackDistance },
    { ENV_BOTH, "GetAggroRange", &LuaCreature::GetAggroRange },
    { ENV_BOTH, "GetDefaultMovementType", &LuaCreature::GetDefaultMovementType },
    { ENV_BOTH, "GetRespawnDelay", &LuaCreature::GetRespawnDelay },
    { ENV_BOTH, "GetWanderRadius", &LuaCreature::GetWanderRadius },
    { ENV_BOTH, "GetCurrentWaypointId", &LuaCreature::GetCurrentWaypointId },
#ifdef TRINITY
    { ENV_BOTH, "GetWaypointPath", &LuaCreature::GetWaypointPath },
    { ENV_BOTH, "GetLootMode", &LuaCreature::GetLootMode },
#endif
    { ENV_BOTH, "GetLootRecipient", &LuaCreature::GetLootRecipient },
    { ENV_BOTH, "GetLootRecipientGroup", &LuaCreature::GetLootRecipientGroup },
    { ENV_BOTH, "GetNPCFlags", &LuaCreature::GetNPCFlags },
#ifndef CATA
    { ENV_BOTH, "GetShieldBlockValue", &LuaCreature::GetShieldBlockValue },
#endif
    { ENV_BOTH, "GetDBTableGUIDLow", &LuaCreature::GetDBTableGUIDLow },

    // Setters
    { ENV_BOTH, "SetHover", &LuaCreature::SetHover },
    { ENV_BOTH, "SetDisableGravity", &LuaCreature::SetDisableGravity },
    { ENV_BOTH, "SetAggroEnabled", &LuaCreature::SetAggroEnabled },
    { ENV_BOTH, "SetNoCallAssistance", &LuaCreature::SetNoCallAssistance },
    { ENV_BOTH, "SetNoSearchAssistance", &LuaCreature::SetNoSearchAssistance },
    { ENV_BOTH, "SetDefaultMovementType", &LuaCreature::SetDefaultMovementType },
    { ENV_BOTH, "SetRespawnDelay", &LuaCreature::SetRespawnDelay },
    { ENV_BOTH, "SetWanderRadius", &LuaCreature::SetWanderRadius },
    { ENV_BOTH, "SetInCombatWithZone", &LuaCreature::SetInCombatWithZone },
    { ENV_BOTH, "SetDisableReputationGain", &LuaCreature::SetDisableReputationGain },
#ifdef TRINITY
    { ENV_BOTH, "SetLootMode", &LuaCreature::SetLootMode },
#endif
    { ENV_BOTH, "SetNPCFlags", &LuaCreature::SetNPCFlags },
    { ENV_BOTH, "SetDeathState", &LuaCreature::SetDeathState },
    { ENV_BOTH, "SetWalk", &LuaCreature::SetWalk },
    { ENV_BOTH, "SetHomePosition", &LuaCreature::SetHomePosition },
    { ENV_BOTH, "SetEquipmentSlots", &LuaCreature::SetEquipmentSlots },

    // Booleans
    { ENV_BOTH, "IsWorldBoss", &LuaCreature::IsWorldBoss },
    { ENV_BOTH, "IsRacialLeader", &LuaCreature::IsRacialLeader },
    { ENV_BOTH, "IsCivilian", &LuaCreature::IsCivilian },
#ifdef TRINITY
    { ENV_BOTH, "IsTrigger", &LuaCreature::IsTrigger },
#endif
    { ENV_BOTH, "IsGuard", &LuaCreature::IsGuard },
    { ENV_BOTH, "IsElite", &LuaCreature::IsElite },
    { ENV_BOTH, "IsInEvadeMode", &LuaCreature::IsInEvadeMode },
    { ENV_BOTH, "HasCategoryCooldown", &LuaCreature::HasCategoryCooldown },
    { ENV_BOTH, "CanWalk", &LuaCreature::CanWalk },
    { ENV_BOTH, "CanSwim", &LuaCreature::CanSwim },
    { ENV_BOTH, "CanAggro", &LuaCreature::CanAggro },
#ifdef TRINITY
    { ENV_BOTH, "CanStartAttack", &LuaCreature::CanStartAttack },
#endif
    { ENV_BOTH, "HasSearchedAssistance", &LuaCreature::HasSearchedAssistance },
    { ENV_BOTH, "IsTappedBy", &LuaCreature::IsTappedBy },
    { ENV_BOTH, "HasLootRecipient", &LuaCreature::HasLootRecipient },
    { ENV_BOTH, "CanAssistTo", &LuaCreature::CanAssistTo },
    { ENV_BOTH, "IsTargetableForAttack", &LuaCreature::IsTargetableForAttack },
    { ENV_BOTH, "CanCompleteQuest", &LuaCreature::CanCompleteQuest },
    { ENV_BOTH, "CanRegenerateHealth", &LuaCreature::CanRegenerateHealth },
    { ENV_BOTH, "IsReputationGainDisabled", &LuaCreature::IsReputationGainDisabled },
#ifdef TRINITY
    { ENV_BOTH, "IsDamageEnoughForLootingAndReward", &LuaCreature::IsDamageEnoughForLootingAndReward },
    { ENV_BOTH, "HasLootMode", &LuaCreature::HasLootMode },
#endif
    { ENV_BOTH, "HasSpell", &LuaCreature::HasSpell },
    { ENV_BOTH, "HasQuest", &LuaCreature::HasQuest },
    { ENV_BOTH, "HasSpellCooldown", &LuaCreature::HasSpellCooldown },
    { ENV_BOTH, "CanFly", &LuaCreature::CanFly },

    // Other
    { ENV_BOTH, "FleeToGetAssistance", &LuaCreature::FleeToGetAssistance },
    { ENV_BOTH, "CallForHelp", &LuaCreature::CallForHelp },
    { ENV_BOTH, "CallAssistance", &LuaCreature::CallAssistance },
    { ENV_BOTH, "RemoveCorpse", &LuaCreature::RemoveCorpse },
    { ENV_BOTH, "DespawnOrUnsummon", &LuaCreature::DespawnOrUnsummon },
    { ENV_BOTH, "Respawn", &LuaCreature::Respawn },
    { ENV_BOTH, "AttackStart", &LuaCreature::AttackStart },
#ifdef TRINITY
    { ENV_BOTH, "AddLootMode", &LuaCreature::AddLootMode },
    { ENV_BOTH, "ResetLootMode", &LuaCreature::ResetLootMode },
    { ENV_BOTH, "RemoveLootMode", &LuaCreature::RemoveLootMode },
#endif
    { ENV_BOTH, "SaveToDB", &LuaCreature::SaveToDB },
    { ENV_BOTH, "SelectVictim", &LuaCreature::SelectVictim },
    { ENV_BOTH, "MoveWaypoint", &LuaCreature::MoveWaypoint },
    { ENV_BOTH, "UpdateEntry", &LuaCreature::UpdateEntry },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<GameObject> GameObjectMethods[] =
{
    // Getters
    { ENV_BOTH, "GetDisplayId", &LuaGameObject::GetDisplayId },
    { ENV_BOTH, "GetGoState", &LuaGameObject::GetGoState },
    { ENV_BOTH, "GetLootState", &LuaGameObject::GetLootState },
    { ENV_BOTH, "GetLootRecipient", &LuaGameObject::GetLootRecipient },
    { ENV_BOTH, "GetLootRecipientGroup", &LuaGameObject::GetLootRecipientGroup },
    { ENV_BOTH, "GetDBTableGUIDLow", &LuaGameObject::GetDBTableGUIDLow },

    // Setters
    { ENV_BOTH, "SetGoState", &LuaGameObject::SetGoState },
    { ENV_BOTH, "SetLootState", &LuaGameObject::SetLootState },
    { ENV_BOTH, "SetRespawnTime", &LuaGameObject::SetRespawnTime },

    // Boolean
    { ENV_BOTH, "IsTransport", &LuaGameObject::IsTransport },
    // { "IsDestructible", &LuaGameObject::IsDestructible },    // :IsDestructible()
    { ENV_BOTH, "IsActive", &LuaGameObject::IsActive },
    { ENV_BOTH, "HasQuest", &LuaGameObject::HasQuest },
    { ENV_BOTH, "IsSpawned", &LuaGameObject::IsSpawned },

    // Other
    { ENV_BOTH, "RemoveFromWorld", &LuaGameObject::RemoveFromWorld },
    { ENV_BOTH, "UseDoorOrButton", &LuaGameObject::UseDoorOrButton },
    { ENV_BOTH, "Despawn", &LuaGameObject::Despawn },
    { ENV_BOTH, "Respawn", &LuaGameObject::Respawn },
    { ENV_BOTH, "SaveToDB", &LuaGameObject::SaveToDB },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Item> ItemMethods[] =
{
    // Getters
    { ENV_BOTH, "GetOwnerGUID", &LuaItem::GetOwnerGUID },                   // :GetOwnerGUID() - Returns the owner's guid
    { ENV_BOTH, "GetOwner", &LuaItem::GetOwner },                           // :GetOwner() - Returns the owner object (player)
    { ENV_BOTH, "GetCount", &LuaItem::GetCount },                           // :GetCount() - Returns item stack count
    { ENV_BOTH, "GetMaxStackCount", &LuaItem::GetMaxStackCount },           // :GetMaxStackCount() - Returns item max stack count
    { ENV_BOTH, "GetSlot", &LuaItem::GetSlot },                             // :GetSlot() - returns the slot the item is in
    { ENV_BOTH, "GetBagSlot", &LuaItem::GetBagSlot },                       // :GetBagSlot() - returns the bagslot of the bag the item is in
    { ENV_BOTH, "GetEnchantmentId", &LuaItem::GetEnchantmentId },           // :GetEnchantmentId(enchant_slot) - Returns the enchantment in given slot. (permanent = 0)
    { ENV_BOTH, "GetSpellId", &LuaItem::GetSpellId },                       // :GetSpellId(index) - Returns spellID at given index (0 - 4)
    { ENV_BOTH, "GetSpellTrigger", &LuaItem::GetSpellTrigger },             // :GetSpellTrigger(index) - Returns spell trigger at given index (0 - 4)
    { ENV_BOTH, "GetItemLink", &LuaItem::GetItemLink },                     // :GetItemLink([localeID]) - Returns the shift clickable link of the item. Name translated if locale given and exists
    { ENV_BOTH, "GetClass", &LuaItem::GetClass },                           // :GetClass()
    { ENV_BOTH, "GetSubClass", &LuaItem::GetSubClass },                     // :GetSubClass()
    { ENV_BOTH, "GetName", &LuaItem::GetName },                             // :GetName()
    { ENV_BOTH, "GetDisplayId", &LuaItem::GetDisplayId },                   // :GetDisplayId()
    { ENV_BOTH, "GetQuality", &LuaItem::GetQuality },                       // :GetQuality()
    { ENV_BOTH, "GetBuyCount", &LuaItem::GetBuyCount },                     // :GetBuyCount()
    { ENV_BOTH, "GetBuyPrice", &LuaItem::GetBuyPrice },                     // :GetBuyPrice()
    { ENV_BOTH, "GetSellPrice", &LuaItem::GetSellPrice },                   // :GetSellPrice()
    { ENV_BOTH, "GetInventoryType", &LuaItem::GetInventoryType },           // :GetInventoryType()
    { ENV_BOTH, "GetAllowableClass", &LuaItem::GetAllowableClass },         // :GetAllowableClass()
    { ENV_BOTH, "GetAllowableRace", &LuaItem::GetAllowableRace },           // :GetAllowableRace()
    { ENV_BOTH, "GetItemLevel", &LuaItem::GetItemLevel },                   // :GetItemLevel()
    { ENV_BOTH, "GetRequiredLevel", &LuaItem::GetRequiredLevel },           // :GetRequiredLevel()
#ifdef WOTLK
    { ENV_BOTH, "GetStatsCount", &LuaItem::GetStatsCount },                 // :GetStatsCount()
#endif
    { ENV_BOTH, "GetRandomProperty", &LuaItem::GetRandomProperty },         // :GetRandomProperty()
#ifndef CLASSIC
    { ENV_BOTH, "GetRandomSuffix", &LuaItem::GetRandomSuffix },             // :GetRandomSuffix()
#endif
    { ENV_BOTH, "GetItemSet", &LuaItem::GetItemSet },                       // :GetItemSet()
    { ENV_BOTH, "GetBagSize", &LuaItem::GetBagSize },                       // :GetBagSize()

    // Setters
    { ENV_BOTH, "SetOwner", &LuaItem::SetOwner },                           // :SetOwner(player) - Sets the owner of the item
    { ENV_BOTH, "SetBinding", &LuaItem::SetBinding },                       // :SetBinding(bound) - Sets the item binding to true or false
    { ENV_BOTH, "SetCount", &LuaItem::SetCount },                           // :SetCount(count) - Sets the item count

    // Boolean
    { ENV_BOTH, "IsSoulBound", &LuaItem::IsSoulBound },                     // :IsSoulBound() - Returns true if the item is soulbound
#if (!defined(TBC) && !defined(CLASSIC))
    { ENV_BOTH, "IsBoundAccountWide", &LuaItem::IsBoundAccountWide },       // :IsBoundAccountWide() - Returns true if the item is account bound
#endif
    { ENV_BOTH, "IsBoundByEnchant", &LuaItem::IsBoundByEnchant },           // :IsBoundByEnchant() - Returns true if the item is bound with an enchant
    { ENV_BOTH, "IsNotBoundToPlayer", &LuaItem::IsNotBoundToPlayer },       // :IsNotBoundToPlayer(player) - Returns true if the item is not bound with player
    { ENV_BOTH, "IsLocked", &LuaItem::IsLocked },                           // :IsLocked() - Returns true if the item is locked
    { ENV_BOTH, "IsBag", &LuaItem::IsBag },                                 // :IsBag() - Returns true if the item is a bag
#ifndef CLASSIC
    { ENV_BOTH, "IsCurrencyToken", &LuaItem::IsCurrencyToken },             // :IsCurrencyToken() - Returns true if the item is a currency token
#endif
    { ENV_BOTH, "IsNotEmptyBag", &LuaItem::IsNotEmptyBag },                 // :IsNotEmptyBag() - Returns true if the item is not an empty bag
    { ENV_BOTH, "IsBroken", &LuaItem::IsBroken },                           // :IsBroken() - Returns true if the item is broken
    { ENV_BOTH, "CanBeTraded", &LuaItem::CanBeTraded },                     // :CanBeTraded() - Returns true if the item can be traded
    { ENV_BOTH, "IsInTrade", &LuaItem::IsInTrade },                         // :IsInTrade() - Returns true if the item is in trade
    { ENV_BOTH, "IsInBag", &LuaItem::IsInBag },                             // :IsInBag() - Returns true if the item is in a bag
    { ENV_BOTH, "IsEquipped", &LuaItem::IsEquipped },                       // :IsEquipped() - Returns true if the item is equipped
    { ENV_BOTH, "HasQuest", &LuaItem::HasQuest },                           // :HasQuest(questId) - Returns true if the item starts the quest
    { ENV_BOTH, "IsPotion", &LuaItem::IsPotion },                           // :IsPotion() - Returns true if the item is a potion
#ifndef CATA
    { ENV_BOTH, "IsWeaponVellum", &LuaItem::IsWeaponVellum },               // :IsWeaponVellum() - Returns true if the item is a weapon vellum
    { ENV_BOTH, "IsArmorVellum", &LuaItem::IsArmorVellum },                 // :IsArmorVellum() - Returns true if the item is an armor vellum
#endif
    { ENV_BOTH, "IsConjuredConsumable", &LuaItem::IsConjuredConsumable },   // :IsConjuredConsumable() - Returns true if the item is a conjured consumable
    // { "IsRefundExpired", &LuaItem::IsRefundExpired },          // :IsRefundExpired() - Returns true if the item's refund time has expired
    { ENV_BOTH, "SetEnchantment", &LuaItem::SetEnchantment },               // :SetEnchantment(enchantid, enchantmentslot) - Sets a new enchantment for the item. Returns true on success
    { ENV_BOTH, "ClearEnchantment", &LuaItem::ClearEnchantment },           // :ClearEnchantment(enchantmentslot) - Removes the enchantment from the item if one exists. Returns true on success

    // Other
    { ENV_BOTH, "SaveToDB", &LuaItem::SaveToDB },                           // :SaveToDB() - Saves to database

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Aura> AuraMethods[] =
{
    // Getters
    { ENV_BOTH, "GetCaster", &LuaAura::GetCaster },
    { ENV_BOTH, "GetCasterGUID", &LuaAura::GetCasterGUID },
    { ENV_BOTH, "GetCasterLevel", &LuaAura::GetCasterLevel },
    { ENV_BOTH, "GetDuration", &LuaAura::GetDuration },
    { ENV_BOTH, "GetMaxDuration", &LuaAura::GetMaxDuration },
    { ENV_BOTH, "GetAuraId", &LuaAura::GetAuraId },
    { ENV_BOTH, "GetStackAmount", &LuaAura::GetStackAmount },
    { ENV_BOTH, "GetOwner", &LuaAura::GetOwner },

    // Setters
    { ENV_BOTH, "SetDuration", &LuaAura::SetDuration },
    { ENV_BOTH, "SetMaxDuration", &LuaAura::SetMaxDuration },
    { ENV_BOTH, "SetStackAmount", &LuaAura::SetStackAmount },

    // Other
    { ENV_BOTH, "Remove", &LuaAura::Remove },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Spell> SpellMethods[] =
{
    // Getters
    { ENV_BOTH, "GetCaster", &LuaSpell::GetCaster },
    { ENV_BOTH, "GetCastTime", &LuaSpell::GetCastTime },
    { ENV_BOTH, "GetEntry", &LuaSpell::GetEntry },
    { ENV_BOTH, "GetDuration", &LuaSpell::GetDuration },
    { ENV_BOTH, "GetPowerCost", &LuaSpell::GetPowerCost },
    { ENV_BOTH, "GetTargetDest", &LuaSpell::GetTargetDest },
    { ENV_BOTH, "GetTarget", &LuaSpell::GetTarget },

    // Setters
    { ENV_BOTH, "SetAutoRepeat", &LuaSpell::SetAutoRepeat },

    // Boolean
    { ENV_BOTH, "IsAutoRepeat", &LuaSpell::IsAutoRepeat },

    // Other
    { ENV_BOTH, "Cancel", &LuaSpell::Cancel },
    { ENV_BOTH, "Cast", &LuaSpell::Cast },
    { ENV_BOTH, "Finish", &LuaSpell::Finish },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Quest> QuestMethods[] =
{
    // Getters
    { ENV_BOTH, "GetId", &LuaQuest::GetId },
    { ENV_BOTH, "GetLevel", &LuaQuest::GetLevel },
    // { "GetMaxLevel", &LuaQuest::GetMaxLevel },                   // :GetMaxLevel() - Returns the quest's max level
    { ENV_BOTH, "GetMinLevel", &LuaQuest::GetMinLevel },
    { ENV_BOTH, "GetNextQuestId", &LuaQuest::GetNextQuestId },
    { ENV_BOTH, "GetPrevQuestId", &LuaQuest::GetPrevQuestId },
    { ENV_BOTH, "GetNextQuestInChain", &LuaQuest::GetNextQuestInChain },
    { ENV_BOTH, "GetFlags", &LuaQuest::GetFlags },
    { ENV_BOTH, "GetType", &LuaQuest::GetType },

    // Boolean
    { ENV_BOTH, "HasFlag", &LuaQuest::HasFlag },
#ifndef CLASSIC
    { ENV_BOTH, "IsDaily", &LuaQuest::IsDaily },
#endif
    { ENV_BOTH, "IsRepeatable", &LuaQuest::IsRepeatable },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Group> GroupMethods[] =
{
    // Getters
    { ENV_WORLD, "GetMembers", &LuaGroup::GetMembers },
    { ENV_BOTH, "GetLeaderGUID", &LuaGroup::GetLeaderGUID },
    { ENV_BOTH, "GetGUID", &LuaGroup::GetGUID },
    { ENV_BOTH, "GetMemberGroup", &LuaGroup::GetMemberGroup },
    { ENV_BOTH, "GetMemberGUID", &LuaGroup::GetMemberGUID },
    { ENV_BOTH, "GetMembersCount", &LuaGroup::GetMembersCount },

    // Setters
    { ENV_WORLD, "SetLeader", &LuaGroup::SetLeader },
    { ENV_WORLD, "SetMembersGroup", &LuaGroup::SetMembersGroup },
    { ENV_WORLD, "SetTargetIcon", &LuaGroup::SetTargetIcon },

    // Boolean
    { ENV_BOTH, "IsLeader", &LuaGroup::IsLeader },
    { ENV_WORLD, "AddMember", &LuaGroup::AddMember },
    { ENV_WORLD, "RemoveMember", &LuaGroup::RemoveMember },
    { ENV_WORLD, "Disband", &LuaGroup::Disband },
    { ENV_BOTH, "IsFull", &LuaGroup::IsFull },
    // { "IsLFGGroup", &LuaGroup::IsLFGGroup },                     // :IsLFGGroup() - Returns true if the group is an LFG group
    { ENV_BOTH, "IsRaidGroup", &LuaGroup::IsRaidGroup },
    { ENV_BOTH, "IsBGGroup", &LuaGroup::IsBGGroup },
    // { "IsBFGroup", &LuaGroup::IsBFGroup },                       // :IsBFGroup() - Returns true if the group is a battlefield group
    { ENV_BOTH, "IsMember", &LuaGroup::IsMember },
    { ENV_BOTH, "IsAssistant", &LuaGroup::IsAssistant },
    { ENV_BOTH, "SameSubGroup", &LuaGroup::SameSubGroup },
    { ENV_BOTH, "HasFreeSlotSubGroup", &LuaGroup::HasFreeSlotSubGroup },

    // Other
    { ENV_BOTH, "SendPacket", &LuaGroup::SendPacket },
    // { "ConvertToLFG", &LuaGroup::ConvertToLFG },                 // :ConvertToLFG() - Converts the group to an LFG group
    { ENV_WORLD, "ConvertToRaid", &LuaGroup::ConvertToRaid },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Guild> GuildMethods[] =
{
    // Getters
    { ENV_WORLD, "GetMembers", &LuaGuild::GetMembers },                  // :GetMembers() - returns a table containing the players in this guild. (Online?)
    { ENV_BOTH, "GetLeaderGUID", &LuaGuild::GetLeaderGUID },            // :GetLeaderGUID() - Returns the guild learder's guid
    { ENV_BOTH, "GetId", &LuaGuild::GetId },                            // :GetId() - Gets the guild's ID
    { ENV_BOTH, "GetName", &LuaGuild::GetName },                        // :GetName() - Gets the guild name
    { ENV_BOTH, "GetMOTD", &LuaGuild::GetMOTD },                        // :GetMOTD() - Gets the guild MOTD string
    { ENV_BOTH, "GetInfo", &LuaGuild::GetInfo },                        // :GetInfo() - Gets the guild info string
    { ENV_BOTH, "GetMemberCount", &LuaGuild::GetMemberCount },          // :GetMemberCount() - Returns the amount of players in the guild

    // Setters
#ifndef CLASSIC
    { ENV_WORLD, "SetBankTabText", &LuaGuild::SetBankTabText },          // :SetBankTabText(tabId, text)
#endif
    { ENV_WORLD, "SetMemberRank", &LuaGuild::SetMemberRank },         // :SetMemberRank(player, newRank) - Sets the player rank in the guild to the new rank
#ifndef CATA
    { ENV_WORLD, "SetLeader", &LuaGuild::SetLeader },                    // :SetLeader() - Sets the guild's leader
#endif

    // Other
    { ENV_BOTH, "SendPacket", &LuaGuild::SendPacket },                  // :SendPacket(packet) - sends packet to guild
    { ENV_BOTH, "SendPacketToRanked", &LuaGuild::SendPacketToRanked },  // :SendPacketToRanked(packet, rankId) - sends packet to guild, specifying a rankId will only send the packet to your ranked members
    { ENV_WORLD, "Disband", &LuaGuild::Disband },                        // :Disband() - Disbands the guild
    { ENV_WORLD, "AddMember", &LuaGuild::AddMember },                    // :AddMember(player, rank) - adds the player to the guild. Rank is optional
    { ENV_WORLD, "DeleteMember", &LuaGuild::DeleteMember },              // :DeleteMember(player, disbanding, kicked) - Deletes the player from the guild. Disbanding and kicked are optional bools
#ifndef CLASSIC
    { ENV_WORLD, "DepositBankMoney", &LuaGuild::DepositBankMoney },      // :DepositBankMoney(money) - Deposits money into the guild bank
    { ENV_WORLD, "WithdrawBankMoney", &LuaGuild::WithdrawBankMoney },    // :WithdrawBankMoney(money) - Withdraws money from the guild bank
#endif

    { ENV_NONE, nullptr, nullptr },
};

#ifndef CLASSIC
#ifndef TBC
ElunaRegister<Vehicle> VehicleMethods[] =
{
    // Getters
    { ENV_BOTH, "GetOwner", &LuaVehicle::GetOwner },                    // :GetOwner() - Returns the the vehicle unit
    { ENV_BOTH, "GetEntry", &LuaVehicle::GetEntry },                    // :GetEntry() - Returns vehicle ID
    { ENV_BOTH, "GetPassenger", &LuaVehicle::GetPassenger },            // :GetPassenger(seatId) - Returns the passenger by seatId

    // Boolean
    { ENV_BOTH, "IsOnBoard", &LuaVehicle::IsOnBoard },                  // :IsOnBoard(unit) - Returns true if the unit is on board

    // Other
    { ENV_BOTH, "AddPassenger", &LuaVehicle::AddPassenger },            // :AddPassenger(passenger, seatId) - Adds a vehicle passenger
    { ENV_BOTH, "RemovePassenger", &LuaVehicle::RemovePassenger },      // :RemovePassenger(passenger) - Removes the passenger from the vehicle

    { ENV_NONE, nullptr, nullptr },
};
#endif
#endif

ElunaRegister<ElunaQuery> QueryMethods[] =
{
    { ENV_BOTH, "NextRow", &LuaQuery::NextRow },                        // :NextRow() - Advances to next rown in the query. Returns true if there is a next row, otherwise false
    { ENV_BOTH, "GetColumnCount", &LuaQuery::GetColumnCount },          // :GetColumnCount() - Gets the column count of the query
    { ENV_BOTH, "GetRowCount", &LuaQuery::GetRowCount },                // :GetRowCount() - Gets the row count of the query
    { ENV_BOTH, "GetRow", &LuaQuery::GetRow },

    { ENV_BOTH, "GetBool", &LuaQuery::GetBool },                        // :GetBool(column) - returns a bool from a number column (for example tinyint)
    { ENV_BOTH, "GetUInt8", &LuaQuery::GetUInt8 },                      // :GetUInt8(column) - returns the value of an unsigned tinyint column
    { ENV_BOTH, "GetUInt16", &LuaQuery::GetUInt16 },                    // :GetUInt16(column) - returns the value of a unsigned smallint column
    { ENV_BOTH, "GetUInt32", &LuaQuery::GetUInt32 },                    // :GetUInt32(column) - returns the value of an unsigned int or mediumint column
    { ENV_BOTH, "GetUInt64", &LuaQuery::GetUInt64 },                    // :GetUInt64(column) - returns the value of an unsigned bigint column as string
    { ENV_BOTH, "GetInt8", &LuaQuery::GetInt8 },                        // :GetInt8(column) - returns the value of an tinyint column
    { ENV_BOTH, "GetInt16", &LuaQuery::GetInt16 },                      // :GetInt16(column) - returns the value of a smallint column
    { ENV_BOTH, "GetInt32", &LuaQuery::GetInt32 },                      // :GetInt32(column) - returns the value of an int or mediumint column
    { ENV_BOTH, "GetInt64", &LuaQuery::GetInt64 },                      // :GetInt64(column) - returns the value of a bigint column as string
    { ENV_BOTH, "GetFloat", &LuaQuery::GetFloat },                      // :GetFloat(column) - returns the value of a float column
    { ENV_BOTH, "GetDouble", &LuaQuery::GetDouble },                    // :GetDouble(column) - returns the value of a double column
    { ENV_BOTH, "GetString", &LuaQuery::GetString },                    // :GetString(column) - returns the value of a string column, always returns a string
    { ENV_BOTH, "IsNull", &LuaQuery::IsNull },                          // :IsNull(column) - returns true if the column is null

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<WorldPacket> PacketMethods[] =
{
    // Getters
    { ENV_BOTH, "GetOpcode", &LuaPacket::GetOpcode },
    { ENV_BOTH, "GetSize", &LuaPacket::GetSize },

    // Setters
    { ENV_BOTH, "SetOpcode", &LuaPacket::SetOpcode },

    // Readers
    { ENV_BOTH, "ReadByte", &LuaPacket::ReadByte },
    { ENV_BOTH, "ReadUByte", &LuaPacket::ReadUByte },
    { ENV_BOTH, "ReadShort", &LuaPacket::ReadShort },
    { ENV_BOTH, "ReadUShort", &LuaPacket::ReadUShort },
    { ENV_BOTH, "ReadLong", &LuaPacket::ReadLong },
    { ENV_BOTH, "ReadULong", &LuaPacket::ReadULong },
    { ENV_BOTH, "ReadGUID", &LuaPacket::ReadGUID },
    { ENV_BOTH, "ReadString", &LuaPacket::ReadString },
    { ENV_BOTH, "ReadFloat", &LuaPacket::ReadFloat },
    { ENV_BOTH, "ReadDouble", &LuaPacket::ReadDouble },

    // Writers
    { ENV_BOTH, "WriteByte", &LuaPacket::WriteByte },                   // :WriteByte(val) - Writes an int8 value
    { ENV_BOTH, "WriteUByte", &LuaPacket::WriteUByte },                 // :WriteUByte(val) - Writes a uint8 value
    { ENV_BOTH, "WriteShort", &LuaPacket::WriteShort },                 // :WriteShort(val) - Writes an int16 value
    { ENV_BOTH, "WriteUShort", &LuaPacket::WriteUShort },               // :WriteUShort(val) - Writes a uint16 value
    { ENV_BOTH, "WriteLong", &LuaPacket::WriteLong },                   // :WriteLong(val) - Writes an int32 value
    { ENV_BOTH, "WriteULong", &LuaPacket::WriteULong },                 // :WriteULong(val) - Writes a uint32 value
    { ENV_BOTH, "WriteGUID", &LuaPacket::WriteGUID },                   // :WriteGUID(guid) - Writes a uint64 value
    { ENV_BOTH, "WriteString", &LuaPacket::WriteString },               // :WriteString(val) - Writes a string value
    { ENV_BOTH, "WriteFloat", &LuaPacket::WriteFloat },                 // :WriteFloat(val) - Writes a float value
    { ENV_BOTH, "WriteDouble", &LuaPacket::WriteDouble },               // :WriteDouble(val) - Writes a double value

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Map> MapMethods[] =
{
    // Getters
    { ENV_BOTH, "GetName", &LuaMap::GetName },                          // :GetName() - Returns the map's name UNDOCUMENTED
    { ENV_BOTH, "GetDifficulty", &LuaMap::GetDifficulty },              // :GetDifficulty() - Returns the map's difficulty UNDOCUMENTED
    { ENV_BOTH, "GetInstanceId", &LuaMap::GetInstanceId },              // :GetInstanceId() - Returns the map's instance ID UNDOCUMENTED
    { ENV_MAP,  "GetInstanceData", &LuaMap::GetInstanceData },
    { ENV_BOTH, "GetPlayers", &LuaMap::GetPlayers },
    { ENV_BOTH, "GetPlayerCount", &LuaMap::GetPlayerCount },            // :GetPlayerCount() - Returns the amount of players on map except GM's UNDOCUMENTED
    { ENV_BOTH, "GetMapId", &LuaMap::GetMapId },                        // :GetMapId() - Returns the map's ID UNDOCUMENTED
    { ENV_BOTH, "GetAreaId", &LuaMap::GetAreaId },                      // :GetAreaId(x, y, z) - Returns the map's area ID based on coords UNDOCUMENTED
    { ENV_BOTH, "GetHeight", &LuaMap::GetHeight },                      // :GetHeight(x, y[, phasemask]) - Returns ground Z coordinate. UNDOCUMENTED
    { ENV_BOTH, "GetWorldObject", &LuaMap::GetWorldObject },            // :GetWorldObject(guid) - Returns a worldobject (player, creature, gameobject..) from the map by it's guid

    // Setters
    { ENV_BOTH, "SetWeather", &LuaMap::SetWeather },

    // Boolean
#ifndef CLASSIC
    { ENV_BOTH, "IsArena", &LuaMap::IsArena },                          // :IsArena() - Returns the true if the map is an arena, else false UNDOCUMENTED
#endif
    { ENV_BOTH, "IsBattleground", &LuaMap::IsBattleground },            // :IsBattleground() - Returns the true if the map is a battleground, else false UNDOCUMENTED
    { ENV_BOTH, "IsDungeon", &LuaMap::IsDungeon },                      // :IsDungeon() - Returns the true if the map is a dungeon , else false UNDOCUMENTED
    { ENV_BOTH, "IsEmpty", &LuaMap::IsEmpty },                          // :IsEmpty() - Returns the true if the map is empty, else false UNDOCUMENTED
#ifndef CLASSIC
    { ENV_BOTH, "IsHeroic", &LuaMap::IsHeroic },                        // :IsHeroic() - Returns the true if the map is a heroic dungeon, else false UNDOCUMENTED
#endif
    { ENV_BOTH, "IsRaid", &LuaMap::IsRaid },                            // :IsRaid() - Returns the true if the map is a raid map, else false UNDOCUMENTED

    // Other
    { ENV_BOTH, "SaveInstanceData", &LuaMap::SaveInstanceData },

    { ENV_NONE, nullptr, nullptr },
};

ElunaRegister<Corpse> CorpseMethods[] =
{
    // Getters
    { ENV_BOTH, "GetOwnerGUID", &LuaCorpse::GetOwnerGUID },
    { ENV_BOTH, "GetGhostTime", &LuaCorpse::GetGhostTime },
    { ENV_BOTH, "GetType", &LuaCorpse::GetType },

    // Other
    { ENV_BOTH, "ResetGhostTime", &LuaCorpse::ResetGhostTime },
    { ENV_BOTH, "SaveToDB", &LuaCorpse::SaveToDB },

    { ENV_NONE, nullptr, nullptr }
};

ElunaRegister<AuctionHouseEntry> AuctionMethods[] =
{
    { ENV_NONE, nullptr, nullptr }
};

ElunaRegister<BattleGround> BattleGroundMethods[] =
{
    // Getters
    { ENV_BOTH, "GetName", &LuaBattleGround::GetName },
    { ENV_BOTH, "GetAlivePlayersCountByTeam", &LuaBattleGround::GetAlivePlayersCountByTeam },
    { ENV_BOTH, "GetMap", &LuaBattleGround::GetMap },
    { ENV_BOTH, "GetBonusHonorFromKillCount", &LuaBattleGround::GetBonusHonorFromKillCount },
    { ENV_BOTH, "GetBracketId", &LuaBattleGround::GetBracketId },
    { ENV_BOTH, "GetEndTime", &LuaBattleGround::GetEndTime },
    { ENV_BOTH, "GetFreeSlotsForTeam", &LuaBattleGround::GetFreeSlotsForTeam },
    { ENV_BOTH, "GetInstanceId", &LuaBattleGround::GetInstanceId },
    { ENV_BOTH, "GetMapId", &LuaBattleGround::GetMapId },
    { ENV_BOTH, "GetTypeId", &LuaBattleGround::GetTypeId },
    { ENV_BOTH, "GetMaxLevel", &LuaBattleGround::GetMaxLevel },
    { ENV_BOTH, "GetMinLevel", &LuaBattleGround::GetMinLevel },
    { ENV_BOTH, "GetMaxPlayers", &LuaBattleGround::GetMaxPlayers },
    { ENV_BOTH, "GetMinPlayers", &LuaBattleGround::GetMinPlayers },
    { ENV_BOTH, "GetMaxPlayersPerTeam", &LuaBattleGround::GetMaxPlayersPerTeam },
    { ENV_BOTH, "GetMinPlayersPerTeam", &LuaBattleGround::GetMinPlayersPerTeam },
    { ENV_BOTH, "GetWinner", &LuaBattleGround::GetWinner },
    { ENV_BOTH, "GetStatus", &LuaBattleGround::GetStatus },

    { ENV_NONE, nullptr, nullptr }
};

template<typename T> const char* ElunaTemplate<T>::tname = nullptr;
template<typename T> bool ElunaTemplate<T>::manageMemory = false;

#if (!defined(TBC) && !defined(CLASSIC))
// fix compile error about accessing vehicle destructor
template<> int ElunaTemplate<Vehicle>::CollectGarbage(lua_State* L)
{
    ASSERT(!manageMemory);

    // Get object pointer (and check type, no error)
    ElunaObject* obj = Eluna::CHECKOBJ<ElunaObject>(L, 1, false);
    delete obj;
    return 0;
}
#endif

void RegisterFunctions(Eluna* E)
{
    ElunaFunction::SetMethods(E, GlobalMethods);

    ElunaTemplate<Object>::Register(E, "Object");
    ElunaTemplate<Object>::SetMethods(E, ObjectMethods);

    ElunaTemplate<WorldObject>::Register(E, "WorldObject");
    ElunaTemplate<WorldObject>::SetMethods(E, ObjectMethods);
    ElunaTemplate<WorldObject>::SetMethods(E, WorldObjectMethods);

    ElunaTemplate<Unit>::Register(E, "Unit");
    ElunaTemplate<Unit>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Unit>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Unit>::SetMethods(E, UnitMethods);

    ElunaTemplate<Player>::Register(E, "Player");
    ElunaTemplate<Player>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Player>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Player>::SetMethods(E, UnitMethods);
    ElunaTemplate<Player>::SetMethods(E, PlayerMethods);

    ElunaTemplate<Creature>::Register(E, "Creature");
    ElunaTemplate<Creature>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Creature>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Creature>::SetMethods(E, UnitMethods);
    ElunaTemplate<Creature>::SetMethods(E, CreatureMethods);

    ElunaTemplate<GameObject>::Register(E, "GameObject");
    ElunaTemplate<GameObject>::SetMethods(E, ObjectMethods);
    ElunaTemplate<GameObject>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<GameObject>::SetMethods(E, GameObjectMethods);

    ElunaTemplate<Corpse>::Register(E, "Corpse");
    ElunaTemplate<Corpse>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, WorldObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, CorpseMethods);

    ElunaTemplate<Item>::Register(E, "Item");
    ElunaTemplate<Item>::SetMethods(E, ObjectMethods);
    ElunaTemplate<Item>::SetMethods(E, ItemMethods);

#ifndef CLASSIC
#ifndef TBC
    ElunaTemplate<Vehicle>::Register(E, "Vehicle");
    ElunaTemplate<Vehicle>::SetMethods(E, VehicleMethods);
#endif
#endif

    ElunaTemplate<Group>::Register(E, "Group");
    ElunaTemplate<Group>::SetMethods(E, GroupMethods);

    ElunaTemplate<Guild>::Register(E, "Guild");
    ElunaTemplate<Guild>::SetMethods(E, GuildMethods);

    ElunaTemplate<Aura>::Register(E, "Aura");
    ElunaTemplate<Aura>::SetMethods(E, AuraMethods);

    ElunaTemplate<Spell>::Register(E, "Spell");
    ElunaTemplate<Spell>::SetMethods(E, SpellMethods);

    ElunaTemplate<Quest>::Register(E, "Quest");
    ElunaTemplate<Quest>::SetMethods(E, QuestMethods);

    ElunaTemplate<Map>::Register(E, "Map");
    ElunaTemplate<Map>::SetMethods(E, MapMethods);

    ElunaTemplate<AuctionHouseEntry>::Register(E, "AuctionHouseEntry");
    ElunaTemplate<AuctionHouseEntry>::SetMethods(E, AuctionMethods);

    ElunaTemplate<BattleGround>::Register(E, "BattleGround");
    ElunaTemplate<BattleGround>::SetMethods(E, BattleGroundMethods);

    ElunaTemplate<WorldPacket>::Register(E, "WorldPacket", true);
    ElunaTemplate<WorldPacket>::SetMethods(E, PacketMethods);

    ElunaTemplate<ElunaQuery>::Register(E, "ElunaQuery", true);
    ElunaTemplate<ElunaQuery>::SetMethods(E, QueryMethods);
}
