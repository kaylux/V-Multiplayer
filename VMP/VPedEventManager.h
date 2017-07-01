/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VPedEventManager.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game ped event handler header file
=============================================================*/

#ifndef VPEDEVENTMANAGER_H
#define VPEDEVENTMANAGER_H

#include <SharedUtility.h>

#define MAX_GAME_EVENTS 16

class CVPlayerPed;

class CVPedEventManager__VFTable
{	
	public:


};

#pragma pack(push, 1)
class CVPedEventManager
{
	public:
		CVPedEventManager__VFTable		*pVFTable;					// 0x0000 - 0x0004
		CVPlayerPed						*pPlayerPed;				// 0x0004 - 0x0008
		int								iCurrentEvents;				// 0x0008 - 0x0012
		CVEvent							*pEvents[MAX_GAME_EVENTS];	// 0x000C - 0x004C
};
#pragma pack(pop)

#endif