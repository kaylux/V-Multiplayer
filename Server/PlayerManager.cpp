/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerManager.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Players manager source file
=============================================================*/

#include "Main.h"

extern CServer			*pServer;
extern CLuaInterface	*pLuaInterface;

CPlayerManager::CPlayerManager()
{
	// Reset values
	m_players = 0;
	// Reset player values
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		m_bConnected[i] = false;
		m_pPlayer[i] = NULL;
	}
	// Reset the spawn position vector
	memset(&m_vecSpawnPosition, 0, sizeof(CVector3));

	// TODO: change this to setSpawnInfo function
	m_vecSpawnPosition.fX = -341.36f;
	m_vecSpawnPosition.fY = 1144.80f;
	m_vecSpawnPosition.fZ = 14.79f;
}

CPlayerManager::~CPlayerManager()
{
	// Reset values
	m_players = 0;
	// Reset player values
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		if(m_bConnected[i])
			SAFE_DELETE(m_pPlayer[i]);
	}
}

void CPlayerManager::AddPlayer(EntityId playerId, char *szName)
{
	// If the player already exists then dont go any further
	if(m_bConnected[playerId])
		return;

	// Create the player class instance
	m_pPlayer[playerId] = new CPlayer(playerId, szName, m_vecSpawnPosition);
	// Write player id to the bitstream
	BitStream bitStream;
	bitStream.Write(playerId);
	// Write name to the bitstream
	char szPlayerName[MAX_NAME_LENGTH];
	strcpy(szPlayerName, szName);	// To avoid reading fail in the client due to not writing the name string length properly
	bitStream.Write(szName);
	// Send the new player RPC
	if(pServer)
		pServer->RPC(RPC_NEW_PLAYER, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, playerId, true);

	// Mark connected
	m_bConnected[playerId] = true;
	// Increase players count
	m_players++;
	// Log message
	LogPrintf(true, "[JOIN] %s has joined the server (ID: %d)", szName, playerId);
	// Call the playerJoin event
	pLuaInterface->CallEvent("playerJoin", "n", playerId);
}

void CPlayerManager::RemovePlayer(EntityId playerId, eLeftReason reason)
{
	// If he's not connected then dont go any further
	if(!m_bConnected[playerId])
		return;

	// Get the player name
	char szName[MAX_NAME_LENGTH];
	m_pPlayer[playerId]->GetName(szName);
	// Delete the player instance
	SAFE_DELETE(m_pPlayer[playerId]);
	// Mark not connected
	m_bConnected[playerId] = false;
	// Decrease players count
	m_players--;
	// Get the leaving reason
	char szReason[8];
	if(reason == LEFT_REASON_QUIT)
		strcpy(szReason, "Quit");
	else if(reason == LEFT_REASON_TIMEOUT)
		strcpy(szReason, "Timeout");
	else if(reason == LEFT_REASON_KICKED)
		strcpy(szReason, "Kicked");

	// Call the playerDisconnect event
	pLuaInterface->CallEvent("playerDisconnect", "nn", playerId, reason);
	// Tell all the clients that the player has left
	BitStream bitStream;
	bitStream.Write(playerId);
	pServer->RPC(RPC_DELETE_PLAYER, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, playerId, true);
	// Log message
	LogPrintf(true, "[LEAVE] %s has left the server (Reason: %s)", szName, szReason);
}

void CPlayerManager::HandlePlayerJoin(EntityId playerId)
{
	// Make sure the player is valid
	if(!m_bConnected[playerId])
		return;

	// Loop through active players
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		if(m_bConnected[i] && i != playerId)
		{
			// Write player id to the bitstream
			BitStream bsPlayer;
			bsPlayer.Write(i);
			// Get the player name
			char szName[MAX_NAME_LENGTH];
			m_pPlayer[i]->GetName(szName);
			// Write name to the bitstream
			bsPlayer.Write(szName);
			// Send the new player RPC
			if(pServer)
				pServer->RPC(RPC_NEW_PLAYER, &bsPlayer, HIGH_PRIORITY, RELIABLE_ORDERED, 0, playerId, false);

			BitStream bsSpawn;
			// Write the player id
			bsSpawn.Write(i);
			// Write the spawn model
			bsSpawn.Write(211); // we go with Niko's model only for now
			// Write the player position vector
			bsSpawn.Write((char *)m_pPlayer[i]->GetPosition(), sizeof(CVector3));
			// Write the player vehicle id
			bsSpawn.Write(m_pPlayer[i]->GetVehicleId());
			// Write the player seat id
			if(m_pPlayer[i]->GetVehicleId() != INVALID_VEHICLE_ID)
				bsSpawn.Write(m_pPlayer[i]->GetSeatId());

			// Send the spawn player RPC
			if(pServer)
				pServer->RPC(RPC_SPAWN_PLAYER, &bsSpawn, HIGH_PRIORITY, RELIABLE_ORDERED, 0, playerId, false);

		}
	}
}

void CPlayerManager::SetSpawnPosition(CVector3 vecPosition)
{
	// Set the spawn position vector
	memcpy(&m_vecSpawnPosition, &vecPosition, sizeof(CVector3));
	// Set all the active players spawn position
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		// Make sure the player is connected
		if(m_bConnected[i])
			m_pPlayer[i]->SetSpawnPosition(m_vecSpawnPosition);
	}
}

bool CPlayerManager::IsNameExists(char *szName)
{
	// Loop through all active players
	for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		if(m_bConnected[i])
		{
			// Get the player name
			char szPlayerName[MAX_NAME_LENGTH];
			GetAt(i)->GetName(szPlayerName);
			// If the names matchs then return false
			if(!strcmp(szName, szPlayerName))
				return false;
		}
	}
	return true;
}

void CPlayerManager::Process()
{
	// Process all the players
	/*for(EntityId i = 0; i < MAX_PLAYERS; i++)
	{
		if(m_bConnected[i] && GetAt(i)->IsSpawned())
			m_pPlayer[i]->ProcessSync();
	}*/
}