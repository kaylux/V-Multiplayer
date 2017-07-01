/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VEntity.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game entity handler header file
=============================================================*/

#ifndef VENTITY_H
#define VENTITY_H

#include <SharedUtility.h>

#pragma pack(push, 1)
class CVEntity
{
	public:
		PAD(pad0, 32);						// 0x0000 - 0x0020
		CMatrix		*pMatrix;				// 0x0020 - 0x0024
		PAD(pad1, 4);						// 0x0024 - 0x0028
		DWORD		dwTypeFlag;				// 0x0028 - 0x002C	(and 0x3C0) if equals 0xC0 its ped else if equals to 0x100 its object
		PAD(pad2, 2);						// 0x002C - 0x002E
		WORD		wModelIndex;			// 0x002E - 0x0030
		PAD(pad3, 68);						// 0x0030 - 0x0074

};
#pragma pack(pop)

#endif