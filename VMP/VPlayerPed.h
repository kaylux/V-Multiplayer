/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VPlayerPed.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game playerped handler header file
=============================================================*/

#ifndef VPLAYERPED_H
#define VPLAYERPED_H

#include "VEntity.h"
#include "VVehicleInfo.h"
#include "VPedTaskManager.h"
#include "VPedEventManager.h"
#include "VWeapon.h"
#include "VPedAudio.h"

class CVPlayerInfo;
class CVPlayerPed;

// TODO: Move this to its own place maybe
#pragma pack(push, 1)
class CVPedIntelligence
{
	public:
		PAD(pad0, 64);								// 0x0000 - 0x0040
		CVPlayerPed			*pPlayerPed;			// 0x0040 - 0x0044
		CVPedTaskManager	*pPedTaskManager;		// 0x0044 - 0x0048
		PAD(pad1, 60);								// 0x0048 - 0x0084
		CVPedEventManager	*pPedEventManager;		// 0x0084 - 0x0088

};
#pragma pack(pop)

#pragma pack(push, 1)
class CVPlayerPed : public CVEntity
{
	public:
		// base class								// 0x0000 - 0x0074 
		PAD(pad0, 432);								// 0x0074 - 0x0224
		CVPedIntelligence	*pPedIntelligence;		// 0x0224 - 0x0228
		CVPlayerInfo		*pPlayerInfo;			// 0x0228 - 0x022C
		PAD(pad1, 64);								// 0x022C - 0x026C
		BYTE				byteState;				// 0x026C - 0x026D (3 = onfoot, 5 = invehicle)
		PAD(pad2, 127);								// 0x026D - 0x02EC
		CVWeapon			weapon[11];				// 0x02EC - 0x0370
		PAD(pad3, 21);								// 0x0370 - 0x0385
		bool				bWeaponVisible;			// 0x0385 - 0x0386
		PAD(pad4, 34);								// 0x0386 - 0x03A8
		void				*pTarget;				// 0x03A8 - 0x03AC (used for peds and objects)
		PAD(pad5, 1020);							// 0x03AC - 0x07A8
		int					iBlipIndex;				// 0x07A8 - 0x07AC
		PAD(pad6, 164);								// 0x07AC - 0x0850
		CVPedAudio			*pPedAudio;				// 0x0850 - 0x0854
		PAD(pad7, 560);								// 0x0854 - 0x0A84
		DWORD				dwDeath;				// 0x0A84 - 0x0A88 (1 or 2 = dead)
		PAD(pad8, 40);								// 0x0A88 - 0x0AB0
		float				fRotation;				// 0x0AB0 - 0x0AB4
		float				fTargetRotation;		// 0x0AB4 - 0x0AB8
		PAD(pad9, 136);								// 0x0AB0 - 0x0B40
		CVVehicleInfo		*pCurrentVehicle;		// 0x0B40 - 0x0B44
		PAD(pad10, 956);							// 0x0B44 - 0x0F00

};
#pragma pack(pop)

#endif