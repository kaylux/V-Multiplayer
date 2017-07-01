/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Player.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Player source file
=============================================================*/

#include "Main.h"

extern CServer			*pServer;
extern CLuaInterface	*pLuaInterface;
extern CVehicleManager	*pVehicleManager;

// TODO: maybe move that to shomewhere else
#define MAX_VEHICLE_DISTANCE_TO_ENTER 20.0f

CPlayer::CPlayer(EntityId playerId, char *szName, CVector3 vecSpawnPosition)
{
	// Save the player id
	m_playerId = playerId;
	// Save player name
	strcpy(m_szName, szName);
	// Mark as not spawned
	m_bSpawned = false;
	// Set the spawn position vector
	memcpy(&m_vecSpawnPosition, &vecSpawnPosition, sizeof(CVector3));
	// Reset values
	memset(&m_vecPosition, 0, sizeof(CVector3));
	memset(&m_vecMoveSpeed, 0, sizeof(CVector3));
	m_fRotation = 0.0f;
	m_vehicleId = INVALID_VEHICLE_ID;
	m_byteSeatId = 0;
	m_enterVehicleId = INVALID_VEHICLE_ID;
	m_byteEnterSeatId = 0;
	m_state = PLAYER_STATE_NOTSPAWNED;
}

CPlayer::~CPlayer()
{
	// Set the player state to disconnected
	SetState(PLAYER_STATE_DISCONNECTED);
} 

void CPlayer::SpawnForPlayer(EntityId playerId)
{
	// NOTE: idk if i need this or not, and i dont even remember why i created it, so leave it until a further notice
	/*// Send the spawn RPC to the client
	BitStream bitStream;
	pServer->RPC(RPC_SPAWN_PLAYER, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, playerId, false);*/
}

void CPlayer::SpawnForWorld()
{
	// Call the playerSpawn event
	pLuaInterface->CallEvent("playerSpawn", "n", m_playerId);
	// Send the spawn RPC to the client
	BitStream bitStream;
	bitStream.Write(m_playerId);
	bitStream.Write(211);
	bitStream.Write((char *)&m_vecSpawnPosition, sizeof(CVector3));
	bitStream.Write(INVALID_VEHICLE_ID);
	pServer->RPC(RPC_SPAWN_PLAYER, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
	// Mark spawned
	m_bSpawned = true;
	// Set the player state
	SetState(PLAYER_STATE_ONFOOT);
}

void CPlayer::SetState(ePlayerState state)
{
	// Does the state got changed ?
	if(m_state == state)
		return;

	// Set the new state
	m_state = state;
	// Call the playerChangedState event
	pLuaInterface->CallEvent("playerChangedState", "nn", m_playerId, state);
}

void CPlayer::StoreSync(RakNet::BitStream *pBitStream)
{
	// Read position
	CVector3 vecPosition;
	if(!pBitStream->Read((char *)&vecPosition, sizeof(CVector3)))
		return;

	// Store position
	memcpy(&m_vecPosition, &vecPosition, sizeof(CVector3));
	// Read move speed
	CVector3 vecMoveSpeed;
	if(!pBitStream->Read((char *)&vecMoveSpeed, sizeof(CVector3)))
		return;

	// Store move speed
	memcpy(&m_vecMoveSpeed, &vecMoveSpeed, sizeof(CVector3));
	// Read rotation
	float fRotation = 0.0;
	if(!pBitStream->Read(fRotation))
		return;
 
	// Store rotation
	m_fRotation = fRotation;
	// Process the sync
	ProcessSync(SYNC_TYPE_ONFOOT);

	LogPrintf(true, "id %d - pos(%f - %f - %f) - speed(%f - %f - %f)", m_playerId, m_vecPosition.fX, 
		m_vecPosition.fY, m_vecPosition.fZ, m_vecMoveSpeed.fX, m_vecMoveSpeed.fY, m_vecMoveSpeed.fZ);
}

void CPlayer::StoreVehicleSync(RakNet::BitStream *pBitStream)
{
	// Read the message id (ID_VEHICLE_SYNC)
	MessageID message;
	pBitStream->Read(message);
	// Read position
	CVector3 vecPosition;
	if(!pBitStream->Read((char *)&vecPosition, sizeof(CVector3)))
		return;

	// Store vehicle position
	pVehicleManager->GetAt(m_vehicleId)->SetPosition(vecPosition);
	// Read move speed
	CVector3 vecMoveSpeed;
	if(!pBitStream->Read((char *)&vecMoveSpeed, sizeof(CVector3)))
		return;

	// Store vehicle move speed
	pVehicleManager->GetAt(m_vehicleId)->SetMoveSpeed(vecMoveSpeed);
	// Read trun speed
	CVector3 vecTurnSpeed;
	if(!pBitStream->Read((char *)&vecTurnSpeed, sizeof(CVector3)))
		return;

	// Store vehicle move speed
	pVehicleManager->GetAt(m_vehicleId)->SetTurnSpeed(vecTurnSpeed);
	// Read rotation
	float fRotation = 0.0;
	if(!pBitStream->Read(fRotation))
		return;
 
	// Store vehicle rotation
	pVehicleManager->GetAt(m_vehicleId)->SetRotation(fRotation);

	LogPrintf(true, "Syncing vehicle (pos %f - %f - %f) - move speed (%f - %f - %f) - turn speed (%f - %f - %f) - rot %f", vecPosition.fX, vecPosition.fY, vecPosition.fZ,
		vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ, vecTurnSpeed.fX, vecTurnSpeed.fY, vecTurnSpeed.fZ, fRotation);

	// Process the sync
	ProcessSync(SYNC_TYPE_INVEHICLE);
}

void CPlayer::ProcessSync(eSyncType type)
{
	// Create bitstream
	BitStream bitStream;
	if(type == SYNC_TYPE_ONFOOT)
	{
		LogPrintf(true, "all written");
		// Write message id
		bitStream.Write((MessageID)ID_SYNC_PLAYER);
		// Write playerid
		bitStream.Write((EntityId)m_playerId);
		// Write position vector
		bitStream.Write((char *)&m_vecPosition, sizeof(CVector3));
		// Write move speed vector
		bitStream.Write((char *)&m_vecMoveSpeed, sizeof(CVector3));
		// Write rotation
		bitStream.Write(m_fRotation);
	}
	else if(type == SYNC_TYPE_INVEHICLE)
	{
		// Write message id
		bitStream.Write((BYTE)ID_SYNC_VEHICLE);
		// Write playerid
		bitStream.Write(m_playerId);
		// Get the vehicle position
		CVector3 vecPosition;
		pVehicleManager->GetAt(m_vehicleId)->GetPosition(vecPosition);
		// Write position vector
		bitStream.Write((char *)&vecPosition, sizeof(CVector3));
		// Get the vehicle move speed
		CVector3 vecMoveSpeed;
		pVehicleManager->GetAt(m_vehicleId)->GetMoveSpeed(vecMoveSpeed);
		// Write move speed vector
		bitStream.Write((char *)&vecMoveSpeed, sizeof(CVector3));
		// Get the vehicle turn speed
		CVector3 vecTurnSpeed;
		pVehicleManager->GetAt(m_vehicleId)->GetTurnSpeed(vecTurnSpeed);
		// Write move speed vector
		bitStream.Write((char *)&vecTurnSpeed, sizeof(CVector3));
		// Write rotation
		bitStream.Write(pVehicleManager->GetAt(m_vehicleId)->GetRotation());
	}
	// Send to all the other clients
	pServer->GetRakPeer()->Send(&bitStream, LOW_PRIORITY, UNRELIABLE_SEQUENCED, 0, pServer->GetRakPeer()->GetSystemAddressFromIndex(m_playerId), true);
}

void CPlayer::SetName(char *szName)
{
	// Set the new player name
	strcpy(m_szName, szName);
	// Send the SetName RPC
	BitStream bitStream;
	bitStream.Write(m_playerId);
	bitStream.Write(szName);
	pServer->RPC(RPC_SCRIPT_SET_NAME, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);

}

void CPlayer::SetPosition(CVector3 vecPosition)
{
	// Store the player position 
	memcpy(&m_vecPosition, &vecPosition, sizeof(CVector3));
	// TODO: Handle position change send to other clients if the player in on foot ONLY!
}

void CPlayer::SetMoveSpeed(CVector3 vecMoveSpeed)
{
	// Store the player move speed 
	memcpy(&m_vecMoveSpeed, &vecMoveSpeed, sizeof(CVector3));
	// TODO: Handle move speed change send to other clients if the player in on foot ONLY!
}

EntityId CPlayer::GetNearestVehicle()
{
	float fDistance = -1.0f;
	EntityId nearestId = INVALID_VEHICLE_ID;
	// Loop through all the vehicles
	for(EntityId i = 0; i < MAX_VEHICLES; i++)
	{
		// Is the vehicle created ?
		if(pVehicleManager->IsVehicleCreated(i))
		{
			// Get the vehicle position
			CVector3 vecVehiclePosition;
			pVehicleManager->GetAt(i)->GetPosition(vecVehiclePosition);
			// Get the distance between the vehicle and the player
			float fCurrentDistance = CMath::GetDistanceBetween3DPoints(vecVehiclePosition, m_vecPosition);
			// Is that the nearest one ?
			if(fCurrentDistance < MAX_VEHICLE_DISTANCE_TO_ENTER && (fCurrentDistance < fDistance || fDistance < 0))
			{
				fDistance = fCurrentDistance;
				nearestId = i;
			}
		}
	}
	// Return the nearest vehicle id
	return nearestId;
}

void CPlayer::EnterVehicle(bool bPassenger)
{
	// Are we in a valid state
	if(GetState() != PLAYER_STATE_ONFOOT)
		return;

	// Get the nearest vehicle
	EntityId vehicleId = GetNearestVehicle();
	if(vehicleId == INVALID_VEHICLE_ID)
		return;

	BYTE byteSeatId = 0;
	// Are we entering as a passenger ?
	/*if(bPassenger)
	{
		byteSeatId = pVehicleManager->GetAt(vehicleId)->GetFreeSeatId();
		if(byteSeatId == 0)
			return;
	}*/
	// Set the player state to entering vehicle
	SetState(PLAYER_STATE_ENTERING_VEHICLE);
	// Set entering values
	m_enterVehicleId = vehicleId;
	m_byteEnterSeatId = byteSeatId;
	// Send the RPC to the other players
	BitStream bitStream;
	bitStream.Write(m_playerId);
	bitStream.Write(vehicleId);
	bitStream.Write(byteSeatId);
	pServer->RPC(RPC_ENTER_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
}

void CPlayer::VehicleEntryComplete()
{
	// Are we entering a vehicle
	if(GetState() != PLAYER_STATE_ENTERING_VEHICLE)
		return;

	// Set the player state to invehicle
	SetState(PLAYER_STATE_INVEHICLE);
	// Set our vehicle id
	m_vehicleId = m_enterVehicleId;
	m_byteSeatId = m_byteEnterSeatId;
	// Set the vehicle driver or passenger id to our
	if(m_byteSeatId == 0)
		pVehicleManager->GetAt(m_vehicleId)->SetDriverId(m_playerId);
	else
		pVehicleManager->GetAt(m_vehicleId)->SetPassengerId(m_byteSeatId, m_playerId);

	// Reset enter vehicle variables
	m_enterVehicleId = INVALID_VEHICLE_ID;
	m_byteEnterSeatId = 0;
	// Send the RPC to the other players
	BitStream bitStream;
	bitStream.Write(m_playerId);
	bitStream.Write(m_vehicleId);
	bitStream.Write(m_byteSeatId);
	pServer->RPC(RPC_VEHICLE_ENTRY_COMPLETE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_playerId, true);
}

/*void CPlayer::PutInVehicle(EntityId vehicleId)
{
	// Is the vehicle valid
	if(vehicleId == INVALID_VEHICLE_ID)
		return;

}*/

void CPlayer::RemoveFromVehicle()
{
	// Are we in vehicle ?
	if(GetState() != PLAYER_STATE_INVEHICLE || m_vehicleId == INVALID_VEHICLE_ID)
		return;

	// Set the vehicle driver or passenger id to invalid
	if(m_byteSeatId == 0)
		pVehicleManager->GetAt(m_vehicleId)->SetDriverId(INVALID_PLAYER_ID);
	else
		pVehicleManager->GetAt(m_vehicleId)->SetPassengerId(m_byteSeatId, INVALID_PLAYER_ID);

	// Reset the vehicle values
	m_vehicleId = INVALID_VEHICLE_ID;
	m_byteSeatId = 0;
	// Set state to be onfoot
	SetState(PLAYER_STATE_ONFOOT);
	// Tell the rest of the clients to remove the player from the vehicle
	BitStream bitStream;
	bitStream.Write(m_playerId);
	pServer->RPC(RPC_REMOVE_FROM_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_playerId, true);
}

void CPlayer::ExitVehicle()
{
	// Are we in a vehicle ?
	if(m_vehicleId == INVALID_VEHICLE_ID || GetState() != PLAYER_STATE_INVEHICLE)
		return;

	// Set the player state to exiting vehicle
	SetState(PLAYER_STATE_EXITING_VEHICLE);
	// Send the RPC to the other players
	BitStream bitStream;
	bitStream.Write(m_playerId);
	bitStream.Write(m_vehicleId);
	pServer->RPC(RPC_EXIT_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
}

void CPlayer::VehicleExitComplete()
{
	// Are we exiting a vehicle
	if(GetState() != PLAYER_STATE_EXITING_VEHICLE)
		return;

	// Set the player state to onfoot
	SetState(PLAYER_STATE_ONFOOT);
	// Set the vehicle driver or passenger id to invalid
	if(m_byteSeatId == 0)
		pVehicleManager->GetAt(m_vehicleId)->SetDriverId(INVALID_PLAYER_ID);
	else
		pVehicleManager->GetAt(m_vehicleId)->SetPassengerId(m_byteSeatId, INVALID_PLAYER_ID);

	// Reset vehicle values
	m_vehicleId = INVALID_VEHICLE_ID;
	m_byteSeatId = 0;
	// Send the RPC to the other players
	BitStream bitStream;
	bitStream.Write(m_playerId);
	pServer->RPC(RPC_VEHICLE_EXIT_COMPLETE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_playerId, true);
}


