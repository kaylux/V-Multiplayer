/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerManager.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Players manager source file
=============================================================*/

#include "Main.h"

extern CGame		*pGame;

CPlayerManager::CPlayerManager()
{
	// Reset players count
	m_players = 0;
	// Reset player values
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		m_bConnected[i] = false;
		m_pPlayer[i] = NULL;
	}
}

CPlayerManager::~CPlayerManager()
{
	// Reset players count
	m_players = 0;
	// Delete player instances
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		if(m_bConnected[i])
		{
			m_bConnected[i] = false;
			SAFE_DELETE(m_pPlayer[i]);
		}
	}
}

void CPlayerManager::AddPlayer(EntityId playerId, char *szName)
{
	Log("CPlMgr::AddPlayer");
	// If the player already exists then dont process
	if(m_bConnected[playerId])
		return;

	Log("cr instance");
	// Create the player class instance
	m_pPlayer[playerId] = new CPlayer(false, playerId, szName);
	// Is the player created ?
	if(!m_pPlayer[playerId])
		return;

	Log("cr ...");
	// Create the player ingame
	m_pPlayer[playerId]->Create();
	// Restore the current player id to the local player
	pGame->SetCurrentPlayerIndex(pGame->GetLocalPlayer()->GetGameId());
	// Mark connected
	m_bConnected[playerId] = true;
	// Increase players count
	m_players++;
}

void CPlayerManager::DeletePlayer(EntityId playerId)
{
	// Make sure the player is connected
	if(!m_bConnected[playerId])
		return;

	// Delete the player class instance
	SAFE_DELETE(m_pPlayer[playerId]);
	// Mark not connected
	m_bConnected[playerId] = false;
	// Decrease players count
	m_players--;
}

void CPlayerManager::Process()
{
	// Loop through players
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		// Is the player connected ?
		if(m_bConnected[i])
		{
			Log("proc pl %d cuz connected", i);
			// Process the player
			m_pPlayer[i]->Process();
		}
	}
}

EntityId CPlayerManager::GetPlayerIdFromPlayerPed(CVPlayerPed *pPlayerPed)
{
	// Loop through players
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		// Is the player connected ?
		if(m_bConnected[i])
		{
			// Compare handlers
			if(pPlayerPed == m_pPlayer[i]->GetPlayerPed()->GetHandler())
				return i;
		}
	}
	return INVALID_PLAYER_ID;
}

EntityId CPlayerManager::GetPlayerIdFromTask(CVTask *pTask)
{
	// Loop through players
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		// Is the player connected ?
		if(m_bConnected[i])
		{
			// Compare handlers
			if(m_pPlayer[i]->GetTask() && pTask == m_pPlayer[i]->GetTask()->GetHandler())
				return i;
		}
	}
	return INVALID_PLAYER_ID;
}
