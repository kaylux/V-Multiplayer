/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: SyncHooks.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Sync hooks header file
=============================================================*/

#ifndef SYNCHOOKS_H
#define SYNCHOOKS_H

#include "VPad.h"
#include "VPlayerPed.h"
#include <SharedUtility.h>

class CSyncHooks
{
	public:
		static void InstallSyncHooks();

		////////////////////////////////////////////////////
		static CVPlayerPed		*pPlayerPed;
		static CVPad			*pPad;
		static CVPad			oldPad;

};

#endif