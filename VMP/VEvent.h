/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VEvent.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game event handler header file
=============================================================*/

#ifndef VEVENT_H
#define VEVENT_H

#include <SharedUtility.h>
#include "VTask.h"

class CEventVFTable
{
	public:
};

#pragma pack(push, 1)
class CVEvent
{
	public:
		CEventVFTable		*pVFTable;			// 0x0000 - 0x0004
		PAD(pad0, 12);							// 0x0004 - 0x0010
		CVTask				*pTask;				// 0x0010 - 0x0014
		PAD(pad1, 280);							// 0x0014 - 0x012C

};
#pragma pack(pop)

#endif