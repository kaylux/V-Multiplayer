/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ComplexTasks.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Complex tasks handler header file
=============================================================*/

#ifndef COMPLEXTASKS_H
#define COMPLEXTASKS_H

#include "Task.h"
#include "VVehicleInfo.h"

class CComplexTasks
{
	public:
		static CTask *CreateEnterVehicleTask(CVVehicleInfo *pVehicle, BYTE byteSeatId);
		static CTask *CreateExitVehicleTask(CVVehicleInfo *pVehicle, int iExitMode);
};

#endif
