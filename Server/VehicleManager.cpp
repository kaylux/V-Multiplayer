/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VehicleManager.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Vehicles manager source file
=============================================================*/

#include "Main.h"

extern CServer			*pServer;
extern CLuaInterface	*pLuaInterface;

CVehicleManager::CVehicleManager()
{
	// Reset values
	m_vehicles = 0;
	// Reset vehicle values
	for(EntityId i = 0; i < MAX_VEHICLES; i++)
	{
		m_bCreated[i] = false;
		m_pVehicle[i] = NULL;
	}
}

CVehicleManager::~CVehicleManager()
{
	// Reset values
	m_vehicles = 0;
	// Reset player values
	for(EntityId i = 0; i < MAX_VEHICLES; i++)
	{
		if(m_bCreated[i])
			SAFE_DELETE(m_pVehicle[i]);
	}
}

void CVehicleManager::AddVehicle(EntityId vehicleId, DWORD dwModel, CVector3 vecPosition)
{
	// If the vehicle already exists then dont go any further
	if(m_bCreated[vehicleId])
		return;

	// Create the vehicle class instance
	m_pVehicle[vehicleId] = new CVehicle(vehicleId, dwModel, vecPosition);
	// Mark created
	m_bCreated[vehicleId] = true;
	// Increase vehicles count
	m_vehicles++;
	// Call the vehicleCreated event
	pLuaInterface->CallEvent("vehicleCreated", "n", vehicleId);
}

void CVehicleManager::RemoveVehicle(EntityId vehicleId)
{
	// If he's not connected then dont go any further
	if(!m_bCreated[vehicleId])
		return;

	// Delete the vehicle instance
	SAFE_DELETE(m_pVehicle[vehicleId]);
	// Mark not created
	m_bCreated[vehicleId] = false;
	// Decrease players count
	m_vehicles--;
	// Tell all the clients that the vehicle is destroyed
	BitStream bitStream;
	bitStream.Write(vehicleId);
	pServer->RPC(RPC_DELETE_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
	// Call the vehicleDestroyed event
	pLuaInterface->CallEvent("vehicleDestroyed", "n", vehicleId);
}

EntityId CVehicleManager::GetFreeSlot()
{
	// Make sure we havent reached our limit
	if(m_vehicles >= MAX_VEHICLES)
		return INVALID_VEHICLE_ID;

	// Loop through all the vehicles
	for(EntityId i = 0; i < MAX_VEHICLES; i++)
	{
		if(!m_bCreated[i])
			return i;
	}
	// Return invalid if no slot is available
	return INVALID_VEHICLE_ID;
}

void CVehicleManager::HandlePlayerJoin(EntityId playerId)
{
	// Loop through all the vehicles
	for(EntityId i = 0; i < MAX_VEHICLES; i++)
	{
		// Is the vehicle created ?
		if(m_bCreated[i])
			// Add the vehicle for the player
			m_pVehicle[i]->AddForPlayer(playerId);
	}
}