/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: LocalPlayer.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: LocalPlayer class source file
=============================================================*/

#include "Main.h"

extern CClient		*pClient;
extern CGame		*pGame;

CLocalPlayer::CLocalPlayer(char *szPlayerName) : CPlayer(true, 0, szPlayerName)
{
	m_dwLastTick = GetTickCount();
}

CLocalPlayer::~CLocalPlayer()
{

}

void CLocalPlayer::ProcessSync()
{
	// Do we need to send sync ?
	if(pClient->GetNetworkState() == NET_STATE_PLAYING && (GetTickCount() - m_dwLastTick) >= 100)
	{
		// Process the onfoot sync
		if(GetState() == PLAYER_STATE_ONFOOT)
		{
			// Create bitstream
			BitStream bitStream;
			// Write message id
			bitStream.Write((MessageID)ID_SYNC_PLAYER);
			// Get position
			CVector3 vecPosition;
			GetPlayerPed()->GetPosition(vecPosition);
			// Write position vector
			bitStream.Write((char *)&vecPosition, sizeof(CVector3));
			// Get move speed
			CVector3 vecMoveSpeed;
			GetPlayerPed()->GetMoveSpeed(vecMoveSpeed); 
			// Write move speed vector
			bitStream.Write((char *)&vecMoveSpeed, sizeof(CVector3));
			// Get rotation
			float fRotation = GetPlayerPed()->GetCurrentRotation();
			// Write rotation
			bitStream.Write(fRotation);
			// Send the packet
			pClient->GetRakPeer()->Send(&bitStream, LOW_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
		}
		// Process the vehicle sync
		else if(GetState() == PLAYER_STATE_INVEHICLE)
		{
			// Get the player vehicle id
			EntityId vehicleId = GetVehicleId();
			if(vehicleId != INVALID_VEHICLE_ID)
			{
				// Get the player vehicle pointer
				CVVehicleInfo *pVehicleInfo = GetPlayerPed()->GetCurrentVehicle();
				if(pVehicleInfo)
				{
					CVehicleInfo *pVehicle = new CVehicleInfo(pVehicleInfo);
					// Create bitstream
					BitStream bitStream;
					// Write message id
					bitStream.Write((BYTE)ID_SYNC_VEHICLE);
					// Get position
					CVector3 vecPosition;
					pVehicle->GetPosition(vecPosition);
					// Write position vector
					bitStream.Write((char *)&vecPosition, sizeof(CVector3));
					// Get move speed
					CVector3 vecMoveSpeed;
					pVehicle->GetMoveSpeed(vecMoveSpeed); 
					// Write move speed vector
					bitStream.Write((char *)&vecMoveSpeed, sizeof(CVector3));
					// Get trun speed
					CVector3 vecTurnSpeed;
					pVehicle->GetTurnSpeed(vecTurnSpeed); 
					// Write trun speed vector
					bitStream.Write((char *)&vecTurnSpeed, sizeof(CVector3));
					// Get rotation
					float fRotation = pGame->GetVehicleManager()->GetAt(vehicleId)->GetCurrentRotation();
					// Write rotation
					bitStream.Write(fRotation);
					// Send the packet
					pClient->GetRakPeer()->Send(&bitStream, LOW_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
					// Delete the vehicle instance
					SAFE_DELETE(pVehicle);
				}
				else
				{
					Log("set out of veh");
					// If our state is in vehicle and the game indicates that we are not in vehicle,
					// then we should sync the fall of vehicle 
					BitStream bitStream;
					pClient->RPC(RPC_REMOVE_FROM_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
					// Set the state to be onfoot
					SetState(PLAYER_STATE_ONFOOT);
				}
			}
		}
		// Update sync tick
		m_dwLastTick = GetTickCount();
	}
}
