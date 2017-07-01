/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VehicleManager.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Vehicles manager source file
=============================================================*/

#include "Main.h"

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

void CVehicleManager::AddVehicle(EntityId vehicleId, unsigned int uiModelIndex, CVector3 vecPosition)
{
	// If the vehicle already exists then dont go any further
	if(m_bCreated[vehicleId])
		return;

	// Create the vehicle class instance
	m_pVehicle[vehicleId] = new CVehicle(vehicleId, uiModelIndex, vecPosition);
	// Check if the vehicle instance is created
	if(!m_pVehicle[vehicleId])
		return;

	// Create the vehicle ingame
	m_pVehicle[vehicleId]->Create();
	// Mark created
	m_bCreated[vehicleId] = true;
	// Increase vehicles count
	m_vehicles++;
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

EntityId CVehicleManager::GetVehicleIdFromVehicleInfo(CVVehicleInfo *pVehicleInfo)
{
	// Loop through players
	for(EntityId i = 0; i < MAX_VEHICLES; i++)
	{
		// Is the vehicle created ?
		if(m_bCreated[i])
		{
			// Compare handlers
			if(pVehicleInfo == m_pVehicle[i]->GetVehicleInfo()->GetHandler())
				return i;
		}
	}
	return INVALID_PLAYER_ID;
}
