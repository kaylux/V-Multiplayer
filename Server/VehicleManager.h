/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VehicleManager.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Vehicles manager header file
=============================================================*/

#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include "Vehicle.h"

class CVehicleManager
{
	public:
		CVehicleManager();
		~CVehicleManager();

		inline bool IsVehicleCreated(EntityId vehicleId)
		{ 
			if(vehicleId > MAX_VEHICLES) 
				return false; 
			else 
				return m_bCreated[vehicleId]; 
		};
		inline CVehicle *GetAt(EntityId vehicleId) { return m_pVehicle[vehicleId]; };

		////////////////////////////////////////////////////////////////////////////
		void AddVehicle(EntityId vehicleId, DWORD dwModel, CVector3 vecPosition);
		void RemoveVehicle(EntityId vehicleId);

		////////////////////////////////////////////////////////////////////////////
		EntityId GetFreeSlot();
		void HandlePlayerJoin(EntityId playerId);

	private:
		EntityId		m_vehicles;
		bool			m_bCreated[MAX_VEHICLES];
		CVehicle		*m_pVehicle[MAX_VEHICLES];


};

#endif