/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VehicleInfo.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: VehicleInfo handler source file
=============================================================*/

#include "Main.h"

CVehicleInfo::CVehicleInfo(CVVehicleInfo *pVehicleInfo) : CEntity()
{
	// Set our vehicle info pointer
	m_pVehicleInfo = pVehicleInfo;
}

CVehicleInfo::~CVehicleInfo()
{

}

