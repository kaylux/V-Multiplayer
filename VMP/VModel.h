/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VModel.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game model handler header file
=============================================================*/

#ifndef VMODEL_H
#define VMODEL_H

#pragma pack(push, 1)
class CVModel
{
	public:
		PAD(pad0, 60);						// 0x0000 - 0x003C
		DWORD	dwHash;						// 0x003C - 0x0040
		// TODO: Find the size
};
#pragma pack(pop)

#endif