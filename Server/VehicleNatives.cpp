/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerNatives.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Player script natives source file
=============================================================*/

#include "Main.h"

extern CLuaInterface			*pLuaInterface;
extern CVehicleManager			*pVehicleManager;
extern CServer					*pServer;

void CVehicleNatives::RegisterNatives()
{
	lua_register(pLuaInterface->GetVM(), "isVehicleCreated", IsCreated);
	lua_register(pLuaInterface->GetVM(), "createVehicle", Create);
}

int CVehicleNatives::IsCreated(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "isVehicleCreated", "n"))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get the player id
	EntityId vehicleId = lua_tointeger(pVM, 1);
	// Push the return value
	lua_pushboolean(pVM, pVehicleManager->IsVehicleCreated(vehicleId));
	return 1;
}

int CVehicleNatives::Create(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "createVehicle", "nnnn"))
	{
		// Return failed
		lua_pushnumber(pVM, INVALID_VEHICLE_ID);
		return 1;
	}
	// Make sure we have an empty slot
	EntityId vehicleId = pVehicleManager->GetFreeSlot();
	if(vehicleId == INVALID_VEHICLE_ID)
	{
		// Return failed
		lua_pushnumber(pVM, INVALID_VEHICLE_ID);
		return 1;
	}
	// Get model
	DWORD dwModel = (DWORD)lua_tonumber(pVM, 1);
	// Get vehicle coords
	float fX = (float)lua_tonumber(pVM, 2);
	float fY = (float)lua_tonumber(pVM, 3);
	float fZ = (float)lua_tonumber(pVM, 4);
	// TODO: do some model validation inhere
	// Create the vehicle
	pVehicleManager->AddVehicle(vehicleId, dwModel, CVector3(fX, fY, fZ));
	// Return succeeded
	lua_pushnumber(pVM, vehicleId);
	return 1;
}

