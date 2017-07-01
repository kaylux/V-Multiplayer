/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Vehicle.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Vehicle class header file
=============================================================*/

#ifndef VEHICLE_H
#define VEHICLE_H

#include "Entity.h"
#include "VehicleInfo.h"

class CVehicle
{
	public:
		CVehicle(EntityId vehicleId, unsigned int uiModelIndex, CVector3 vecPosition);
		~CVehicle();
		
		//////////////////////////////////////////////////////////////////////
		inline void SetId(EntityId vehicleId) { m_vehicleId = vehicleId; };
		inline EntityId GetId() { return m_vehicleId; };

		//////////////////////////////////////////////////////////////////////
		inline void SetGameIndex(unsigned int uiIndex) { m_uiGameIndex = uiIndex; };
		inline unsigned int GetGameIndex() { return m_uiGameIndex; };

		//////////////////////////////////////////////////////////////////////
		float GetCurrentRotation();
		void SetCurrentRotation(float fRotation);

		//////////////////////////////////////////////////////////////////////
		void Create();
		void Destroy();

		//////////////////////////////////////////////////////////////////////
		inline void SetVehicleInfo(CVehicleInfo *pVehicleInfo) { m_pVehicleInfo = pVehicleInfo; };
		inline CVehicleInfo *GetVehicleInfo() { return m_pVehicleInfo; }; 

		//////////////////////////////////////////////////////////////////////
		void Sync(RakNet::BitStream *pBitStream);
		void UpdatePosition();
		void Process();


	private:
		EntityId				m_vehicleId;
		CVector3				m_vecPosition;
		CVector3				m_vecLastSyncPosition;
		CVector3				m_vecInterpolation;
		CVehicleInfo			*m_pVehicleInfo;
		unsigned int			m_uiGameIndex;
		
};

#endif