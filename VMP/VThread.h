/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VThread.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game thread handler header file
=============================================================*/

#ifndef VTHREAD_H
#define VTHREAD_H

#include <SharedUtility.h>

class CVThread_VFTable
{
	PAD(pad0, 16);											// 0x0000 - 0x0010
	DWORD			dwDestroy;								// 0x0010 - 0x0014
};

#pragma pack(push, 1)
class CVThread
{
	public:
		CVThread_VFTable		*pVFTable;					// 0x0000 - 0x0004
		DWORD					dwThreadId;					// 0x0004 - 0x0008
		DWORD					dwNativeHash;				// 0x0008 - 0x000C
		DWORD					dwState;					// 0x000C - 0x0010 (0 = paused, 1 = running, 2 = killed)
		DWORD					dwNativeAddress;			// 0x0010 - 0x0014
		PAD(pad0, 4);										// 0x0014 - 0x001C
		void					*pTimerA;					// 0x001C - 0x0020
		void					*pTimerB;					// 0x0020 - 0x0024
		void					*pTimerC;					// 0x0024 - 0x0028
		PAD(pad1, 68);										// 0x0028 - 0x006C
		char					*szKillType;				// 0x006C - 0x0070
		// TODO: Find the size
};
#pragma pack(pop)


#endif