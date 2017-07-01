/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Vehicle.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Vehicle class source file
=============================================================*/

#include "Main.h"

extern CClient			*pClient;
extern CGame			*pGame;

CVehicle::CVehicle(EntityId vehicleId, unsigned int uiModelIndex, CVector3 vecPosition)
{
	// Save vehicle id
	m_vehicleId = vehicleId;
	// Set the position vector
	memcpy(&m_vecPosition, &vecPosition, sizeof(CVector3));
	// Reset the last sync position vector
	memset(&m_vecLastSyncPosition, 0, sizeof(CVector3));
	// Reset the interpolation vector
	memset(&m_vecInterpolation, 0, sizeof(CVector3));
	// Create the vehicle info instance
	m_pVehicleInfo = new CVehicleInfo(NULL);
	// TEMP: Force the game to choose the Admiral model
	int iModelIndex = 0;
	int *piModelIndex = &iModelIndex;
	DWORD dwHash = 0x4B5C5320;
	DWORD dwFunc = (pGame->GetBaseAddress() + 0x98AAE0);
	_asm
	{
		push piModelIndex
		push dwHash
		call dwFunc
		add esp, 8
	}
	// Create the model instance
	CModel *pModel = new CModel(iModelIndex);
	m_pVehicleInfo->SetModelHandler(pModel);
	// Reset the vehicle game id
	m_uiGameIndex = INVALID_VEHICLE_ID;
}

CVehicle::~CVehicle()
{
	// Destroy the vehicle
	Destroy();
}

void CVehicle::Create()
{
	// Load the model
	if(!GetVehicleInfo()->GetModelHandler() || !GetVehicleInfo()->GetModelHandler()->Load(true))
		return;

	// Create the vehicle
	CVector3 vecPosition = m_vecPosition;
	DWORD dwModelHash = GetVehicleInfo()->GetModelHandler()->GetModelHash();
	unsigned int uiVehicleIndex = NULL;
	unsigned int *puiVehicleIndex = &uiVehicleIndex;
	_asm
	{
		push 1
		push puiVehicleIndex
		push vecPosition.fZ
		push vecPosition.fY
		push vecPosition.fX
		push dwModelHash
		call CAddress::FUNC_CreateVehicle
		add esp, 24
	}
	// Set vehicle game id
	m_uiGameIndex = uiVehicleIndex;
	// Set vehicle pointer
	CVVehicleInfo *pVehicleInfo = CPools::AtHandle<CVVehicleInfo *>(uiVehicleIndex, *(DWORD *)CAddress::VAR_VehiclePool);
	GetVehicleInfo()->SetHandler(pVehicleInfo);
}

void CVehicle::Destroy()
{
}

void CVehicle::Sync(RakNet::BitStream *pBitStream)
{
	// Read position
	CVector3 vecPosition;
	if(!pBitStream->Read((char *)&vecPosition, sizeof(CVector3)))
		return;

	// Read move speed
	CVector3 vecMoveSpeed;
	if(!pBitStream->Read((char *)&vecMoveSpeed, sizeof(CVector3)))
		return;

	// Set the player moving speed
	GetVehicleInfo()->SetMoveSpeed(vecMoveSpeed);
	// Read rotation
	float fRotation = 0.0f;
	if(!pBitStream->Read(fRotation))
		return;

	// Set rotation
	SetCurrentRotation(fRotation);
	// Get our position
	CVector3 vecCurrentPosition;
	GetVehicleInfo()->GetPosition(vecCurrentPosition);
	// Check if we need to update
	if(vecPosition != m_vecLastSyncPosition)
	{
		// Calculate the relative error
		m_vecInterpolation = (vecPosition - vecCurrentPosition);
		// Update the player position
		UpdatePosition();
	}
	// Set the last sync position
	m_vecLastSyncPosition = vecPosition;
}

void CVehicle::UpdatePosition()
{
	// Get the current player position
	CVector3 vecCurrentPosition;
	GetVehicleInfo()->GetPosition(vecCurrentPosition);
	// Get the interpolation compensation
	CVector3 vecInterpolation = (m_vecInterpolation * 1.0f); // TICK_RATE = 100
	// Calculate the new position
	CVector3 vecNewPosition = (vecCurrentPosition + vecInterpolation);
	// Set the new place
	m_vecInterpolation = vecNewPosition;

	GetVehicleInfo()->SetPosition(vecNewPosition);
	// Create the goto point task
	/*CTask *pTask = CSimpleTasks::CreateGoToPointTask(vecNewPosition, false);
	// Apply task to the player
	if(pTask)
		GetPlayerPed()->SetPedTask(pTask, TASK_PRIORITY_MAX, true);*/

}

void CVehicle::Process()
{
	// update the position
	UpdatePosition();
}

float CVehicle::GetCurrentRotation()
{
	DWORD FUNC_GetVehicleHeading = (pGame->GetBaseAddress() + 0xB799A0);
	int iVehicleId = m_uiGameIndex;
	float fRotation = 0.0f;
	float *pfRotation = &fRotation;
	_asm
	{
		push pfRotation
		push iVehicleId
		call FUNC_GetVehicleHeading
		add esp, 8
	}
	return fRotation;
}

void CVehicle::SetCurrentRotation(float fRotation)
{
	DWORD FUNC_SetVehicleHeading = (pGame->GetBaseAddress() + 0xB79A20);
	int iVehicleId = m_uiGameIndex;
	_asm
	{
		push fRotation
		push iVehicleId
		call FUNC_SetVehicleHeading
		add esp, 8
	}
}
