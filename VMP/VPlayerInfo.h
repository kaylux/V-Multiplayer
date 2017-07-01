/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VPlayerInfo.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game playerinfoped handler header file
=============================================================*/

#ifndef VPLAYERINFO_H
#define VPLAYERINFO_H

#include "VPlayerPed.h"

#pragma pack(push, 1)
class CVPlayerInfo
{
	public:
		PAD(pad0, 76);									// 0x0000 - 0x004C
		char				szName[20];					// 0x004C - 0x0060 // TODO: Verify the length
		PAD(pad1, 1044);								// 0x0060 - 0x0474
		bool				bSprintDisabled;			// 0x0474 - 0x0475
		PAD(pad2, 101);									// 0x0475 - 0x04DA
		BYTE				bytePlayerIndex;			// 0x04DA - 0x04DB
		PAD(pad3, 149);									// 0x04DB - 0x0570
		DWORD				dwColor;					// 0x0570 - 0x0574
		PAD(pad4, 24);									// 0x0574 - 0x058C
		CVPlayerPed			*pPlayerPed;				// 0x058C - 0x0590
		PAD(pad5, 48);									// 0x0590 - 0x05C0


};
#pragma pack(pop)

#endif