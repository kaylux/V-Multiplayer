/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: LocalPlayer.h
-- Project: Client
-- Author(s): m0niSx
-- Description: LocalPlayer class header file
=============================================================*/

#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include "Player.h"

class CLocalPlayer : public CPlayer
{
	public:
		CLocalPlayer(char *szPlayerName);
		~CLocalPlayer();

		void ProcessSync();

	private:
		DWORD				m_dwLastTick;
};

#endif