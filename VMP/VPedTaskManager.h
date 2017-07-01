/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VPedTaskManager.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game ped task handler header file
=============================================================*/

#ifndef VPEDTASKMANAGER_H
#define VPEDTASKMANAGER_H

#include "VTask.h"

class CVPlayerPed;

#pragma pack(push, 1)
class CVPedTaskManager
{
	public:
		CVTask				*pPrimaryTasks[5];				// 0x0000 - 0x0014
		CVTask				*pSecondaryTasks[5];			// 0x0014 - 0x002C
		CVTask				*pMouvementTask[3];				// 0x002C - 0x0038
		CVPlayerPed			*pPlayerPed;					// 0x0038 - 0x003C
		int					iUknown;						// 0x003C - 0x0040 (this indicates the current task maybe?)
	
};
#pragma pack(pop)

#endif