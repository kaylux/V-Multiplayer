/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Vehicle.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Vehicle source file
=============================================================*/

#include "Main.h"

extern CServer			*pServer;
extern CLuaInterface	*pLuaInterface;
extern CPlayerManager	*pPlayerManager;

CVehicle::CVehicle(EntityId vehicleId, DWORD dwModel, CVector3 vecPosition)
{
	// Save the player id
	m_vehicleId = vehicleId;
	// Save model
	m_dwModelId = dwModel;
	// Reset values
	memset(&m_vecMoveSpeed, 0, sizeof(CVector3));
	memset(&m_vecTurnSpeed, 0, sizeof(CVector3));
	m_fRotation = 0.0f;
	// Set the vehicle position
	memcpy(&m_vecPosition, &vecPosition, sizeof(CVector3));
	// Reset driver and passengers values
	m_driverId = INVALID_PLAYER_ID;
	for(BYTE i = 0; i < 3; i++)
		m_passengerId[i] = INVALID_PLAYER_ID;

	// Tell all the clients that the vehicle is created
	if(pServer)
	{
		BitStream bitStream;
		bitStream.Write(vehicleId);
		bitStream.Write(dwModel);
		bitStream.Write((char *)&vecPosition, sizeof(CVector3));
		pServer->RPC(RPC_NEW_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
	}
}

CVehicle::~CVehicle()
{
} 

void CVehicle::AddForPlayer(EntityId playerId)
{
	// Tell the client to add the vehicle
	BitStream bitStream;
	bitStream.Write(m_vehicleId);
	bitStream.Write(m_dwModelId);
	bitStream.Write((char *)&m_vecPosition, sizeof(CVector3));
	pServer->RPC(RPC_NEW_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, playerId, false);
}

void CVehicle::StoreSync(RakNet::BitStream *pBitStream)
{
	/*// Read the message id (ID_TIMESTAMP)
	MessageID message;
	pBitStream->Read(message);
	// Read the timestamp
	RakNet::Time timeStamp;
	if(!pBitStream->Read(timeStamp))
		return;

	// Save the timestamp
	m_timeStamp = timeStamp;
	// Read the message id (ID_PLAYER_SYNC)
	pBitStream->Read(message);
	// Read position
	CVector3 vecPosition;
	if(!pBitStream->Read((char *)&vecPosition, sizeof(CVector3)))
		return;

	//LogPrintf(true, "Read pos(%f - %f - %f)", vecPosition.fX, vecPosition.fY, vecPosition.fZ); 
	// Store position
	memcpy(&m_vecPosition, &vecPosition, sizeof(CVector3));
	// Read move speed
	CVector3 vecMoveSpeed;
	if(!pBitStream->Read((char *)&vecMoveSpeed, sizeof(CVector3)))
		return;

	//LogPrintf(true, "speed (%f - %f - %f) - time: %d", vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ, m_timeStamp);
	// Store move speed
	memcpy(&m_vecMoveSpeed, &vecMoveSpeed, sizeof(CVector3));
	// Read rotation
	float fRotation = 0.0;
	if(!pBitStream->Read(fRotation))
		return;

	//LogPrintf(true, "Read rot(%f - %f)", vecRotation.fX, vecRotation.fY); 
	// Store position
	m_fRotation = fRotation;
	// Read analogs
	WORD wLRanalog;
	WORD wUDanalog;
	if(!pBitStream->Read(wUDanalog))
		return;

	if(!pBitStream->Read(wLRanalog))
		return;

	// Save analogs
	m_wUDanalog = wUDanalog;
	m_wLRanalog = wLRanalog;
	LogPrintf(true, "Read analog(0x%x - 0x%x)", wUDanalog, wLRanalog);
	// Process the sync
	ProcessSync();*/
}

void CVehicle::ProcessSync()
{
	/*// Create bitstream
	BitStream bitStream;
	// Write timestamp
	bitStream.Write((BYTE)ID_TIMESTAMP);
	bitStream.Write(m_timeStamp);
	// Write message id
	bitStream.Write((BYTE)ID_SYNC_PLAYER);
	// Write playerid
	bitStream.Write((int)m_playerId);
	// Write position vector
	bitStream.Write((char *)&m_vecPosition, sizeof(CVector3));
	// Write move speed vector
	bitStream.Write((char *)&m_vecMoveSpeed, sizeof(CVector3));
	// Write rotation vector
	bitStream.Write(m_fRotation);
	// Write analogs
	bitStream.Write(m_wUDanalog);
	bitStream.Write(m_wLRanalog);
	// Send to all the other clients
	pServer->GetRakPeer()->Send(&bitStream, LOW_PRIORITY, UNRELIABLE_SEQUENCED, 0, pServer->GetRakPeer()->GetSystemAddressFromIndex(m_playerId), true);*/
}

void CVehicle::SetPosition(CVector3 vecPosition)
{
	// Store the vehicle position
	memcpy(&m_vecPosition, &vecPosition, sizeof(CVector3));
	// Set the driver and passengers positions if there are any
	if(m_driverId != INVALID_PLAYER_ID)
		pPlayerManager->GetAt(m_driverId)->SetPosition(vecPosition);

	for(BYTE i = 0; i < 3; i++)
	{
		if(m_passengerId[i] != INVALID_PLAYER_ID)
			pPlayerManager->GetAt(m_passengerId[i])->SetPosition(vecPosition);
	}
}

void CVehicle::SetMoveSpeed(CVector3 vecMoveSpeed)
{
	// Store the vehicle move speed
	memcpy(&m_vecMoveSpeed, &vecMoveSpeed, sizeof(CVector3));
	// Set the driver and passengers move speed if there are any
	if(m_driverId != INVALID_PLAYER_ID)
		pPlayerManager->GetAt(m_driverId)->SetMoveSpeed(vecMoveSpeed);

	for(BYTE i = 0; i < 3; i++)
	{
		if(m_passengerId[i] != INVALID_PLAYER_ID)
			pPlayerManager->GetAt(m_passengerId[i])->SetMoveSpeed(vecMoveSpeed);
	}
}


