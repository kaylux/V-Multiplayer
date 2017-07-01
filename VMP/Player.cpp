/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Player.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Player class source file
=============================================================*/

#include "Main.h"

extern CClient			*pClient;
extern CGame			*pGame;

// TODO: maybe move that to shomewhere else
#define MAX_VEHICLE_DISTANCE_TO_ENTER 20.0f

CPlayer::CPlayer(bool bLocal, EntityId playerId, char *szPlayerName)
{
	// Save the local player indication flag
	m_bLocal = bLocal;
	// Save player id
	m_playerId = playerId;
	// Save player name
	strcpy(m_szPlayerName, szPlayerName);
	// Create player ped
	m_pPlayerPed = new CPlayerPed(NULL);
	// Create player info
	m_pPlayerInfo = new CPlayerInfo(NULL);
	// Create blip instance
	if(!m_bLocal)
		m_pBlip = new CBlip(BLIP_TYPE_PLAYER);

	// Reset the last sync position vector
	memset(&m_vecLastSyncPosition, 0, sizeof(CVector3));
	// Reset the task pointer
	m_pTask = NULL;
	// Reset game id
	m_byteGameId = INVALID_PLAYER_ID;
	// Reset vehicle values
	m_vehicleId = INVALID_VEHICLE_ID;
	m_byteSeatId = 0;
	// Reset enter vehicle values
	m_enterVehicleId = INVALID_VEHICLE_ID;
	m_byteSeatId = 0;
	// Reset vehicle entry and exit bools
	m_bEnteringVehicle = false;
	m_bExitingVehicle = false;
	// Reset player state
	m_state = PLAYER_STATE_NOTSPAWNED;
}

CPlayer::~CPlayer()
{
	// Reset player state
	m_state = PLAYER_STATE_NOTSPAWNED;
	// Delete the blip instance
	SAFE_DELETE(m_pBlip);	
	// Destroy the player
	Destroy();
	// Delete the player ped instance
	SAFE_DELETE(m_pPlayerPed);
	// Delete the player info instance
	SAFE_DELETE(m_pPlayerInfo);
}

void CPlayer::Create()
{
	// Make sure it is not the local player
	if(m_bLocal)
		return;

	// Get the player game id
	int iGameId = CGameUtils::GetFreePlayerSlot();
	if(iGameId == INVALID_PLAYER_INDEX)
		return;

	m_byteGameId = (BYTE)iGameId;
	// Create the model instance
	CModel *pModel = new CModel(PLAYER_MODEL_INDEX);
	// Make sure the model instance is created
	if(!pModel)
		return;

	// Load the player model
	if(!pModel->Load(true))
		return;

	// Create the player ped
	CVPlayerPed *pPlayerPed = NULL;
	WORD wPlayer = MAKEWORD(0, 1);
	WORD *pwPlayer = &wPlayer;
	DWORD dwModelHash = pModel->GetModelHash();
	CMatrix *pMatrix = new CMatrix;
	memcpy(pMatrix, 0, sizeof(CMatrix));
	_asm
	{
		push 1
		push pMatrix
		push iGameId
		push dwModelHash
		push pwPlayer
		mov ecx, CAddress::VAR_PedFactory
		call CAddress::FUNC_CPedFactory__CreatePed
		mov pPlayerPed, eax
	}
	// Set player info
	m_pPlayerInfo->SetHandler(CGameUtils::GetPlayerInfoFromIndex(m_byteGameId));
	// Set the player ped
	m_pPlayerPed->SetHandler(pPlayerPed);
	// Set the model handler
	m_pPlayerPed->SetModelHandler(pModel);
	// Setup the player intelligence
	_asm
	{
		push 2
		mov ecx, pPlayerPed
		call CAddress::FUNC_CPed__SetupIntelligence
	}
	//m_pPlayerInfo->DisableSprint(true);
}

void CPlayer::Spawn(unsigned int uiModelIndex)
{
	// Remove player from the world
	m_pPlayerPed->RemoveFromWorld();
	// Set the player model
	SetModel(uiModelIndex);
	// Add to the world
	m_pPlayerPed->AddToWorld();
	// Set the player color
	/*m_pPlayerInfo->SetColor(D3DCOLOR_ARGB(200, 0, 200, 0));
	// Set the player name to apply nametag
	m_pPlayerInfo->SetName(m_szPlayerName);*/
	// Attach the player blip
	//AttachBlip();
	// Set player state to be onfoot
	m_state = PLAYER_STATE_ONFOOT;
}

void CPlayer::Destroy()
{
	// Destroy the player
	CVPlayerPed *pPlayerPed = m_pPlayerPed->GetHandler();
	_asm
	{
		push pPlayerPed
		mov ecx, CAddress::VAR_PedFactory
		// This does all the stuff we need (clear tasks and events, remove from vehicle, remove from the world and call the playerped destructor)
		call CAddress::FUNC_CPedFactory__DestroyPed 
	}
	// Reset pointers
	m_pPlayerPed->SetHandler(NULL);
	m_pPlayerInfo->SetHandler(NULL);
	// Reset player state
	m_state = PLAYER_STATE_NOTSPAWNED;
}

void CPlayer::SetModel(unsigned int uiModelIndex)
{
	/*// Save the player ped
	CVPlayerPed *pPlayerPed = m_pPlayerPed->GetHandler();	
	// Set the entity model
	m_pPlayerPed->SetModel(uiModelIndex);
	// Get the model hash
	DWORD dwModelHash = m_pPlayerPed->GetModelHandler()->GetModelHash();
	// Change the player model
	int iPlayerId = (int)m_byteGameId;
	_asm
	{
		push dwModelHash
		push iPlayerId
		call CAddress::FUNC_ChangePlayerModel
		add esp, 8
	}
	// Set back the player ped
	m_pPlayerPed->SetHandler(pPlayerPed);*/
}

void CPlayer::Sync(RakNet::BitStream *pBitStream)
{
	// Read position
	CVector3 vecPosition;
	if(!pBitStream->Read((char *)&vecPosition, sizeof(CVector3)))
		return;

	// Read move speed
	CVector3 vecMoveSpeed;
	if(!pBitStream->Read((char *)&vecMoveSpeed, sizeof(CVector3)))
		return;

	Log("%d CPlayer::Sync (%f - %f - %f) / (%f - %f - %f)", m_playerId, vecPosition.fX, vecPosition.fY, 
		vecPosition.fZ, vecMoveSpeed.fX, vecMoveSpeed.fY, vecMoveSpeed.fZ);
	// Set the player moving speed
	GetPlayerPed()->SetMoveSpeed(vecMoveSpeed);
	// Read rotation
	float fRotation = 0.0f;
	if(!pBitStream->Read(fRotation))
		return;

	// Set rotation
	GetPlayerPed()->SetCurrentRotation(fRotation);
	// Get our position
	CVector3 vecCurrentPosition;
	GetPlayerPed()->GetPosition(vecCurrentPosition);
	// Check if we need to update
	if(vecPosition != m_vecLastSyncPosition)
	{
		// Calculate the relative error
		m_vecInterpolation = vecPosition;//(vecPosition - vecCurrentPosition);
		// Interpolate the player
		Interpolate();
	}
	// Update the last sync position
	m_vecLastSyncPosition = vecPosition;
}

void CPlayer::Interpolate()
{
	// Get the current player position
	CVector3 vecCurrentPosition;
	GetPlayerPed()->GetPosition(vecCurrentPosition);
	Log("%d CPlayer::Interpolate (%f - %f - %f)", m_playerId, m_vecInterpolation.fX, m_vecInterpolation.fY, m_vecInterpolation.fZ);
	// Process task creation and destruction
	if(m_pTask == NULL && m_vecInterpolation != vecCurrentPosition)
	{
		// Create the goto point task
		m_pTask = CSimpleTasks::CreateTaskSimpleMoveGoToPoint(m_vecInterpolation, false);
		// Apply task to the player
		if(m_pTask)
			GetPlayerPed()->SetPedTask(m_pTask, TASK_PRIORITY_MAX, false);

		// Update the interpolation place
		m_vecInterpolation = vecCurrentPosition;
	}
	else
	{	
		// TODO: Handle checks for player arriving to his target
		// Delete the player task
		//DestroyPlayerTask();
		// Reset the moving flag
		//m_bMoving = false;
	}
}

void CPlayer::Process()
{
	// TODO: Find a fucking fix for that shit
	if(m_bLocal)
		return;

	// Interpolate the player
	Interpolate();
	// Process the vehicle entry and exit
	ProcessVehicleEntryAndExit();
}

void CPlayer::AttachBlip()
{
	// Make sure this is not the local player
	if(m_bLocal)
		return;

	// Set the blip param to our player index
	m_pBlip->SetBlipParam(m_byteGameId);
	// Create the blip
	m_pBlip->Create();
}

void CPlayer::DetachBlip()
{
	// Make sure this is not the local player
	if(m_bLocal)
		return;

	// Destroy the blip
	m_pBlip->Destroy();
}

EntityId CPlayer::GetNearestVehicle()
{
	float fDistance = -1.0f;
	EntityId nearestId = INVALID_VEHICLE_ID;
	// Get the player position
	CVector3 vecPosition;
	m_pPlayerPed->GetPosition(vecPosition);
	// Loop through all the vehicles
	for(EntityId i = 0; i < MAX_VEHICLES; i++)
	{
		// Is the vehicle created ?
		if(pGame->GetVehicleManager()->IsVehicleCreated(i))
		{
			// Get the vehicle position
			CVector3 vecVehiclePosition;
			pGame->GetVehicleManager()->GetAt(i)->GetVehicleInfo()->GetPosition(vecVehiclePosition);
			// Get the distance between the vehicle and the player
			float fCurrentDistance = CMath::GetDistanceBetween3DPoints(vecVehiclePosition, vecPosition);
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

void CPlayer::ProcessVehicleEntryAndExit()
{
	// Is that local player ?
	if(!m_bLocal)
		return;

	// Are we entering vehicle ?
	if(GetState() == PLAYER_STATE_ENTERING_VEHICLE)
	{
		// Did we get into the vehicle ?
		if(GetPlayerPed()->GetCurrentVehicle() != NULL)
		{
			// Tell the server to make us in vehicle
			BitStream bitStream;
			pClient->RPC(RPC_VEHICLE_ENTRY_COMPLETE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
			// Set player state in vehicle
			SetState(PLAYER_STATE_INVEHICLE);
			// Set the player vehicle id
			m_vehicleId = m_enterVehicleId;
			m_byteSeatId = m_byteEnterSeatId;
			// Reset enter vehicle values
			m_enterVehicleId = INVALID_VEHICLE_ID;
			m_byteSeatId = 0;
		}
	}
	// Are we exiting vehicle ?
	if(GetState() == PLAYER_STATE_EXITING_VEHICLE)
	{
		// Did we get out of the vehicle ?
		if(GetPlayerPed()->GetCurrentVehicle() == NULL)
		{
			// Tell the server to make us out of vehicle
			BitStream bitStream;
			pClient->RPC(RPC_VEHICLE_EXIT_COMPLETE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
			// Set player state on foot
			SetState(PLAYER_STATE_ONFOOT);
			// Set the player vehicle id
			m_vehicleId = INVALID_VEHICLE_ID;
			m_byteSeatId = 0;
		}
	}
}

void CPlayer::HandleVehicleEntryAndExit(bool bPassenger)
{
	// Make sure this the local player
	if(!m_bLocal)
		return;

	// Are we trying to enter a vehicle ?
	if(m_state == PLAYER_STATE_ONFOOT && GetPlayerPed()->GetCurrentVehicle() == NULL)
	{
		// Request the vehicle entry
		BitStream bitStream;
		bitStream.Write(bPassenger); 
		pClient->RPC(RPC_ENTER_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
	}
	// Are we trying to exit a vehicle ?
	else if(m_state == PLAYER_STATE_INVEHICLE && GetPlayerPed()->GetCurrentVehicle() != NULL)
	{
		// Request the vehicle exit
		BitStream bitStream;
		pClient->RPC(RPC_EXIT_VEHICLE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
	}
}

void CPlayer::EnterVehicle(EntityId vehicleId, BYTE byteSeatId)
{
	Log("CPlayer::EnterVehicle(%d, %d) for %d", vehicleId, byteSeatId, m_playerId);
	// Make sure the vehicle is valid
	if(!pGame->GetVehicleManager()->IsVehicleCreated(vehicleId))
		return;

	Log("CPlayer::EnterVehicle 2");
	// Set entering vehicle values
	m_enterVehicleId = vehicleId;
	m_byteEnterSeatId = byteSeatId;
	// Get the vehicle info pointer
	CVVehicleInfo *pVehicle = pGame->GetVehicleManager()->GetAt(vehicleId)->GetVehicleInfo()->GetHandler();
	Log("CPlayer::EnterVehicle veh 0x%x", pVehicle);
	// Create the enter vehicle task
	m_pTask = CComplexTasks::CreateEnterVehicleTask(pVehicle, byteSeatId);
	Log("CPlayer::EnterVehicle task 0x%x", m_pTask);
	// Set the player state
	SetState(PLAYER_STATE_ENTERING_VEHICLE);
	// Set the player task
	if(m_pTask != NULL)
		m_pPlayerPed->SetPedTask(m_pTask, TASK_PRIORITY_PRIMARY, false);

	Log("CPlayer::EnterVehicle end");
}

void CPlayer::PutInVehicle(EntityId vehicleId, BYTE byteSeatId)
{
	// Is the vehicle id valid
	if(vehicleId == INVALID_VEHICLE_ID || !pGame->GetVehicleManager()->IsVehicleCreated(vehicleId))
		return;

	// Set the player state
	SetState(PLAYER_STATE_INVEHICLE);
	// Set the player current vehicle and seat
	m_vehicleId = vehicleId;
	m_byteSeatId = byteSeatId;
	// Get the vehicle info pointer
	CVVehicleInfo *pVehicle = pGame->GetVehicleManager()->GetAt(vehicleId)->GetVehicleInfo()->GetHandler();
	// Is the current vehicle differente from the requested one ?
	if(GetPlayerPed()->GetCurrentVehicle() == pVehicle)
		return;

	// Get vehicle game id
	unsigned int uiVehicleIndex = pGame->GetVehicleManager()->GetAt(vehicleId)->GetGameIndex();
	unsigned int uiPlayerIndex = m_byteGameId;
	// Put player in vehicle
	if(byteSeatId == 0)
	{
		_asm
		{
			push uiVehicleIndex
			push uiPlayerIndex
			call CAddress::FUNC_WarpPlayerIntoVehicleAsDriver
			add esp, 8
		}
	}
	else
	{
		int iSeatId = byteSeatId;
		_asm
		{
			push iSeatId
			push uiVehicleIndex
			push uiPlayerIndex
			call CAddress::FUNC_WarpPlayerIntoVehicleAsPassenger
			add esp, 12
		}
	}
}

void CPlayer::ExitVehicle(EntityId vehicleId)
{
	// Get the move speed
	CVector3 vecMoveSpeed;
	m_pPlayerPed->GetMoveSpeed(vecMoveSpeed);
	// Get the vehicle model index
	int iModelId = pGame->GetVehicleManager()->GetAt(vehicleId)->GetVehicleInfo()->GetModelHandler()->GetModelIndex();
	int iExitMode = 0xF;
	// TODO: Revise that thing
	if(vecMoveSpeed.fX < -10 || vecMoveSpeed.fX > 10 || vecMoveSpeed.fY < -10 || vecMoveSpeed.fY > 10)
	{
		switch(iModelId)
		{
			case 2: case 4: case 5: case 7: case 8: case 10: case 11:
			case 31: case 32: case 49: case 50: case 51: case 52:
			case 53: case 55: case 56: case 60: case 66: case 73:
			case 85: case 86: case 94: case 104:
				iExitMode = 0x40B;
			break;

			default:
			{
				if(iModelId != 12 && iModelId < 166)
					iExitMode = 0x100E;
			}
		}
	}
	// Set player state
	SetState(PLAYER_STATE_EXITING_VEHICLE);
	// Create the exit vehicle task
	m_pTask = CComplexTasks::CreateExitVehicleTask(m_pPlayerPed->GetCurrentVehicle(), iExitMode);
	// Set the player task
	if(m_pTask != NULL)
		m_pPlayerPed->SetPedTask(m_pTask, TASK_PRIORITY_PRIMARY, false);

}

void CPlayer::RemoveFromVehicle()
{
	// Set state on foot
	SetState(PLAYER_STATE_ONFOOT);	
	// Reset the player vehicle values
	m_vehicleId = INVALID_VEHICLE_ID;
	m_byteSeatId = 0;
	// Are we in a vehicle ?
	if(m_pPlayerPed->GetCurrentVehicle() == NULL)
		return;

	// Get the actual player position
	CVector3 vecPosition;
	m_pPlayerPed->GetPosition(vecPosition);
	// Remove player from vehicle
	unsigned int uiPlayerIndex = m_byteGameId;
	_asm
	{
		push vecPosition.fZ
		push vecPosition.fY
		push vecPosition.fX
		push uiPlayerIndex
		call CAddress::FUNC_RemovePlayerFromVehicle
		add esp, 16
	}
}

void CPlayer::HandleTaskDestroy()
{
	Log("CPlayer::HandleTaskDestroy %d", m_playerId);
	// Do we have a valid task ?
	if(m_pTask == NULL)
		return;

	// Delete the task instance
	SAFE_DELETE(m_pTask);
	Log("task destroy handled");
}
