/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VPedAudio.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game ped audio handler header file
=============================================================*/

#ifndef VPEDAUDIO_H
#define VPEDAUDIO_H

class CVPlayerPed;

class CVPedAudio__VFTable
{
	public:

	
};

#pragma pack(push, 1)
class CVPedAudio
{
	public:
		CVPedAudio__VFTable				*pVFTable;		// 0x0000 - 0x0004
		CVPlayerPed						*pPlayerPed;	// 0x0004 - 0x0008
		// TODO: Find the size
	
};
#pragma pack(pop)

#endif