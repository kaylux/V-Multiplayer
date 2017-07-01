/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VehicleManager.h
-- Project: Client
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
		EntityId GetVehicleIdFromVehicleInfo(CVVehicleInfo *pVehicleInfo);

		////////////////////////////////////////////////////////////////////////////
		void AddVehicle(EntityId vehicleId, unsigned int uiModelIndex, CVector3 vecPosition);
		void RemoveVehicle(EntityId vehicleId);

		////////////////////////////////////////////////////////////////////////////
		EntityId GetFreeSlot();

	private:
		EntityId		m_vehicles;
		bool			m_bCreated[MAX_VEHICLES];
		CVehicle		*m_pVehicle[MAX_VEHICLES];


};

#endif