/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VehicleInfo.h
-- Project: Client
-- Author(s): m0niSx
-- Description: VehicleInfo handler header file
=============================================================*/

#ifndef VEHICLEINFO_H
#define VEHICLEINFO_H

#include "Entity.h"
#include "VVehicleInfo.h"
#include "VPlayerPed.h"

class CVehicleInfo : public CEntity
{
	public:
		CVehicleInfo(CVVehicleInfo *pVehicleInfo);
		~CVehicleInfo();

		//////////////////////////////////////////////////////////////////////
		inline void SetHandler(CVVehicleInfo *pVehicleInfo)
		{
			// do we have a valid pointer ?
			if(pVehicleInfo)
			{
				// Set player info pointer
				m_pVehicleInfo = pVehicleInfo;
				// Set the entity pointer
				SetEntityHandler(reinterpret_cast<CVEntity *>(pVehicleInfo));
			}
		}
		inline CVVehicleInfo *GetHandler() { return m_pVehicleInfo; };

		//////////////////////////////////////////////////////////////////////
		CVPlayerPed *GetDriver() { return (m_pVehicleInfo == NULL ? NULL : (CVPlayerPed *)m_pVehicleInfo->pDriver); };
		CVPlayerPed *GetPassenger(BYTE byteSeatId) { return (m_pVehicleInfo == NULL ? NULL : (CVPlayerPed *)m_pVehicleInfo->pPassenger[byteSeatId]); };

	private:
		CVVehicleInfo		*m_pVehicleInfo;
};

#endif