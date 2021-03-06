/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: RPCFunctions.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: RPC functions source file
=============================================================*/

#include "Main.h"

extern CClient		*pClient;
extern CGame		*pGame;
extern CChatBox		*pChatBox;

void CRPCFunctions::RegisterFunctions()
{
	// Make sure we have a valid client pointer
	if(!pClient)
		return;

	// Register all the functions
	pClient->RegisterRPCFunction(JoinAccepted, RPC_JOIN_ACCEPTED); 
	pClient->RegisterRPCFunction(JoinRejected, RPC_JOIN_REJECTED); 
	pClient->RegisterRPCFunction(NewPlayer, RPC_NEW_PLAYER); 
	pClient->RegisterRPCFunction(NewVehicle, RPC_NEW_VEHICLE); 
	pClient->RegisterRPCFunction(DeletePlayer, RPC_DELETE_PLAYER); 
	pClient->RegisterRPCFunction(SpawnPlayer, RPC_SPAWN_PLAYER);
	pClient->RegisterRPCFunction(EnterVehicle, RPC_ENTER_VEHICLE); 
	pClient->RegisterRPCFunction(VehicleEntryComplete, RPC_VEHICLE_ENTRY_COMPLETE);
	pClient->RegisterRPCFunction(VehicleExitComplete, RPC_VEHICLE_EXIT_COMPLETE);
	pClient->RegisterRPCFunction(RemoveFromVehicle, RPC_REMOVE_FROM_VEHICLE);
	pClient->RegisterRPCFunction(ExitVehicle, RPC_EXIT_VEHICLE); 
	pClient->RegisterRPCFunction(ِChatMessage, RPC_CHAT_MESSAGE); 
}

void CRPCFunctions::JoinAccepted(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get local player id
	EntityId localId;
	if(!pBitStream->Read(localId))
		return;

	// Get server name
	char szName[128];
	if(!pBitStream->Read(szName))
		return;

	// Set local player id
	pGame->GetLocalPlayer()->SetId(localId);
	// Set network state to playing
	pClient->SetNetworkState(NET_STATE_PLAYING);
	// Set player state onfoot
	pGame->GetLocalPlayer()->SetState(PLAYER_STATE_ONFOOT);
	// Tell the server to spawn us
	BitStream bitStream;
	pClient->RPC(RPC_SPAWN_PLAYER, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
	// Display message
	pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, 0xFFFFFFFF, "Successfully joined %s.", szName);
}

void CRPCFunctions::JoinRejected(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get reason
	char szReason[64];
	if(!pBitStream->Read(szReason))
		strcpy(szReason, "Unknown");

	// Display the message
	pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, 0xFFFFFFFF, "Joining failed (Reason: %s).", szReason);
	// Set the network state to disconnected
	pClient->SetNetworkState(NET_STATE_DISCONNECT);
}

void CRPCFunctions::ِChatMessage(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get player name
	char szName[MAX_NAME_LENGTH];
	if(!pBitStream->Read(szName))
		return;

	// Get the player message
	char szMessage[MAX_INPUT_MESSAGE];
	if(!pBitStream->Read(szMessage))
		return;

	// Make sure the message and name are valid
	if(szMessage == NULL || szName == NULL)
		return;

	// Add to the chatbox
	pChatBox->AddMessage(LINE_TYPE_CHAT, szName, D3DCOLOR_ARGB(200, 0, 200, 0), 0xFFFFFFFF, szMessage);
}

void CRPCFunctions::NewPlayer(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	Log("nplayer");
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;
	
	Log("valid ptrs");
	// Read player id
	EntityId playerId = INVALID_PLAYER_ID;
	if(!pBitStream->Read(playerId))
		return;

	Log("id %d", playerId);
	// Read player name
	char szPlayerName[MAX_NAME_LENGTH];
	if(!pBitStream->Read(szPlayerName))
		return;

	Log("name %s", szPlayerName);
	// Make sure the player id and name are valid
	if(szPlayerName == NULL || playerId == INVALID_PLAYER_ID || playerId > MAX_PLAYERS)
		return;

	pChatBox->AddMessage(LINE_TYPE_INFO, "", 0x0, 0xFFFFFFFF, "%s (ID: %d) has joined the server", szPlayerName, playerId);
	// Add the player
	Log("adding ...");
	pGame->GetPlayerManager()->AddPlayer(playerId, szPlayerName);
	Log("nplayer end");
}

void CRPCFunctions::NewVehicle(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Read vehicle id
	EntityId vehicleId = INVALID_VEHICLE_ID;
	if(!pBitStream->Read(vehicleId))
		return;

	// Read model id
	DWORD dwModel = NULL;
	if(!pBitStream->Read(dwModel))
		return;

	// Read model id
	CVector3 vecPosition;
	if(!pBitStream->Read((char *)&vecPosition, sizeof(CVector3)))
		return;

	// Make sure the vehicle id is valid
	if(vehicleId == INVALID_VEHICLE_ID || vehicleId > MAX_VEHICLES)
		return;

	// Add the vehicle
	pGame->GetVehicleManager()->AddVehicle(vehicleId, dwModel, vecPosition);
}

void CRPCFunctions::DeletePlayer(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Read player id
	EntityId playerId = INVALID_PLAYER_ID;
	if(!pBitStream->Read(playerId))
		return;

	// Make sure the player id is valid
	if(playerId == INVALID_PLAYER_ID || playerId > MAX_PLAYERS || !pGame->GetPlayerManager()->IsPlayerConnected(playerId))
		return;

	// Remove the player
	pGame->GetPlayerManager()->DeletePlayer(playerId);
}


void CRPCFunctions::SpawnPlayer(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;
	
	// Read player id
	EntityId playerId = INVALID_PLAYER_ID;
	if(!pBitStream->Read(playerId))
		return;
	
	// Make sure the player id is valid
	if(playerId == INVALID_PLAYER_ID || playerId > MAX_PLAYERS)
		return;

	// Read spawning model id
	int iModel = 0;
	if(!pBitStream->Read(iModel))
		return;
	
	// Read spawning position
	CVector3 vecSpawnPosition;
	if(!pBitStream->Read((char *)&vecSpawnPosition, sizeof(CVector3)))
		return;

	// Read the player vehicle id
	EntityId vehicleId = INVALID_VEHICLE_ID;
	if(!pBitStream->Read(vehicleId))
		return;
	
	// Read the seatid
	BYTE byteSeatId = 0;
	if(vehicleId != INVALID_VEHICLE_ID)
	{
		if(!pBitStream->Read(byteSeatId))
			return;
	}
	// Is that local player ?
	if(playerId == pGame->GetLocalPlayer()->GetId())
	{
		// Spawn the player
		pGame->GetLocalPlayer()->Spawn(iModel);
		// Set the player position
		pGame->GetLocalPlayer()->GetPlayerPed()->SetPosition(vecSpawnPosition);
	}
	else
	{
		Log("spawn remote");
		// Is the player connected ?
		if(pGame->GetPlayerManager()->IsPlayerConnected(playerId))
		{
			// Spawn the player
			pGame->GetPlayerManager()->GetAt(playerId)->Spawn(iModel);
			pGame->GetPlayerManager()->GetAt(playerId)->GetPlayerPed()->SetPosition(vecSpawnPosition);
			/*if(vehicleId != INVALID_VEHICLE_ID)
				// Set the player vehicle id
				pGame->GetPlayerManager()->GetAt(playerId)->PutInVehicle(vehicleId, byteSeatId);*/
		}
	}
	Log("spawned");
}

void CRPCFunctions::EnterVehicle(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get the player id
	EntityId playerId = INVALID_PLAYER_ID;
	if(!pBitStream->Read(playerId))
		return;

	// Get vehicle id
	EntityId vehicleId = INVALID_VEHICLE_ID;
	if(!pBitStream->Read(vehicleId))
		return;

	// Get seat id
	BYTE byteSeatId = 0;
	if(!pBitStream->Read(byteSeatId))
		return;

	// Is it local player ?
	if(playerId == pGame->GetLocalPlayer()->GetId())
		pGame->GetLocalPlayer()->EnterVehicle(vehicleId, byteSeatId);
	else
	{
		// Make sure the player id is valid
		if(pGame->GetPlayerManager()->IsPlayerConnected(playerId))
			pGame->GetPlayerManager()->GetAt(playerId)->EnterVehicle(vehicleId, byteSeatId);
	}
}

void CRPCFunctions::VehicleEntryComplete(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get the player id
	EntityId playerId = NULL;
	if(!pBitStream->Read(playerId))
		return;

	// Validate the player id
	if(playerId > MAX_PLAYERS || !pGame->GetPlayerManager()->IsPlayerConnected(playerId))
		return;

	// Get the vehicle id
	EntityId vehicleId = NULL;
	if(!pBitStream->Read(vehicleId))
		return;

	// Make sure the vehicle is valid
	if(!pGame->GetVehicleManager()->IsVehicleCreated(vehicleId))
		return;

	// Get the seat id
	BYTE byteSeatId = 0;
	if(!pBitStream->Read(byteSeatId))
		return;

	// Make the player enter the vehicle
	pGame->GetPlayerManager()->GetAt(playerId)->PutInVehicle(vehicleId, byteSeatId);
}

void CRPCFunctions::ExitVehicle(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get the player id
	EntityId playerId = INVALID_PLAYER_ID;
	if(!pBitStream->Read(playerId))
		return;

	// Get the vehicle id
	EntityId vehicleId = INVALID_VEHICLE_ID;
	if(!pBitStream->Read(vehicleId))
		return;

	// Is it local player ?
	if(playerId == pGame->GetLocalPlayer()->GetId())
		pGame->GetLocalPlayer()->ExitVehicle(vehicleId);
	else
	{
		// Make sure the player id is valid
		if(pGame->GetPlayerManager()->IsPlayerConnected(playerId))
			pGame->GetPlayerManager()->GetAt(playerId)->ExitVehicle(vehicleId);
	}
}

void CRPCFunctions::VehicleExitComplete(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get the player id
	EntityId playerId = NULL;
	if(!pBitStream->Read(playerId))
		return;

	// Validate the player id
	if(playerId > MAX_PLAYERS || !pGame->GetPlayerManager()->IsPlayerConnected(playerId))
		return;

	// Make the player enter the vehicle
	pGame->GetPlayerManager()->GetAt(playerId)->RemoveFromVehicle();
}

void CRPCFunctions::RemoveFromVehicle(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get the player id
	EntityId playerId = NULL;
	if(!pBitStream->Read(playerId))
		return;

	// Validate the player id
	if(playerId > MAX_PLAYERS || !pGame->GetPlayerManager()->IsPlayerConnected(playerId))
		return;

	// Make the player enter the vehicle
	pGame->GetPlayerManager()->GetAt(playerId)->RemoveFromVehicle();
}

