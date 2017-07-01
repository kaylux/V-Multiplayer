/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerManager.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Players manager header file
=============================================================*/

#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "Player.h"

enum eLeftReason
{
	LEFT_REASON_QUIT,
	LEFT_REASON_TIMEOUT,
	LEFT_REASON_KICKED
};

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

		////////////////////////////////////////////////////////////////////////////
		void AddPlayer(EntityId playerId, char *szName);
		bool IsNameExists(char *szName);
		void RemovePlayer(EntityId playerId, eLeftReason reason);

		////////////////////////////////////////////////////////////////////////////
		void HandlePlayerJoin(EntityId playerId);
		void SetSpawnPosition(CVector3 vecPosition);

		////////////////////////////////////////////////////////////////////////////
		void Process();

	private:
		EntityId		m_players;
		bool			m_bConnected[MAX_PLAYERS];
		CPlayer			*m_pPlayer[MAX_PLAYERS];
		CVector3		m_vecSpawnPosition;


};

#endif