/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerManager.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Players manager header file
=============================================================*/

#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"
#include "VTask.h"

class CPlayerManager
{
	public:
		CPlayerManager();
		~CPlayerManager();

		inline bool IsPlayerConnected(EntityId playerId) 
		{ 
			if(playerId > MAX_PLAYERS) 
				return false; 
			else 
				return m_bConnected[playerId]; 
		};
		inline CPlayer *GetAt(EntityId playerId) { return m_pPlayer[playerId]; };
		EntityId GetPlayerIdFromPlayerPed(CVPlayerPed *pPlayerPed);
		EntityId GetPlayerIdFromTask(CVTask *pTask); 

		////////////////////////////////////////////////////////////////////////////
		void AddPlayer(EntityId playerId, char *szName);
		void DeletePlayer(EntityId playerId);

		////////////////////////////////////////////////////////////////////////////
		void Process();

	private:
		EntityId		m_players;
		bool			m_bConnected[MAX_PLAYERS];
		CPlayer			*m_pPlayer[MAX_PLAYERS];


};

#endif