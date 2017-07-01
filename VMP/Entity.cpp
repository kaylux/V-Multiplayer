/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Entity.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Entity class source file
=============================================================*/

#include "Main.h"

extern CGame	*pGame;

CEntity::CEntity()
{
	// Reset pointers
	m_pEntity = NULL;
	m_pModel = NULL;

}

CEntity::~CEntity()
{

}

void CEntity::AddToWorld()
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

	// Add to the world
	CVWorld::Add(m_pEntity);
}

void CEntity::RemoveFromWorld()
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

	// Add to the world
	CVWorld::Delete(m_pEntity);
}

void CEntity::SetPosition(CVector3 vecPosition)
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

	// Remove the entity from the world
	RemoveFromWorld();
	// Set entity position
	memcpy(&m_pEntity->pMatrix->vecPosition, &vecPosition, sizeof(CVector3));
	// Re-add the entity to the world
	AddToWorld();
}

void CEntity::SetModel(unsigned int uiModelIndex)
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

	// Delete the old model instance
	SAFE_DELETE(m_pModel);
	// Create a new model instance
	m_pModel = new CModel(uiModelIndex);
	// Load the model
	if(!m_pModel->Load(true))
		return;
}

void CEntity::GetPosition(CVector3 &vecPosition)
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

	// Get the entity position vector
	memcpy(&vecPosition, &m_pEntity->pMatrix->vecPosition, sizeof(CVector3));
}

DWORD CEntity::GetPhysics()
{
	// TODO: Revise that function
	DWORD FUNC__GetPhysics = (pGame->GetBaseAddress() + 0x9E7080);
	DWORD dwPhysics = NULL;
	DWORD pPhysics = (DWORD)m_pEntity;
	_asm
	{
		mov ecx, pPhysics
		call FUNC__GetPhysics
		mov dwPhysics, eax
	}

	return dwPhysics;
}

// TODO: Move these stuff to CPhysical class
void CEntity::SetMoveSpeed(CVector3 vecMoveSpeed)
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

/*	DWORD dwPhysics = GetPhysics();
	// Set the entity movespeed
	*(float *)(dwPhysics + 0x110) = vecMoveSpeed.fX;
	*(float *)(dwPhysics + 0x114) = vecMoveSpeed.fY;
	*(float *)(dwPhysics + 0x118) = vecMoveSpeed.fZ;*/

	DWORD FUNC__SetMoveSpeed = (pGame->GetBaseAddress() + 0xA47750);
	CVector3 *pvecMoveSpeed = &vecMoveSpeed;
	DWORD pPhysics = (DWORD)m_pEntity;
	_asm
	{
		push pvecMoveSpeed
		mov ecx, pPhysics
		call FUNC__SetMoveSpeed
	}
}

void CEntity::GetMoveSpeed(CVector3 &vecMoveSpeed)
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

	/*DWORD dwPhysics = GetPhysics();
	// Get the entity movespeed
	vecMoveSpeed.fX = *(float *)(dwPhysics + 0x110);
	vecMoveSpeed.fY = *(float *)(dwPhysics + 0x114);
	vecMoveSpeed.fZ = *(float *)(dwPhysics + 0x118);*/
	

	DWORD FUNC__GetMoveSpeed = (pGame->GetBaseAddress() + 0xA477F0);
	CVector3 *pvecMoveSpeed = &vecMoveSpeed;
	DWORD pPhysics = (DWORD)m_pEntity;
	_asm
	{
		push pvecMoveSpeed
		mov ecx, pPhysics
		call FUNC__GetMoveSpeed
	}
}

void CEntity::SetTurnSpeed(CVector3 vecTurnSpeed)
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

	DWORD FUNC__SetTurnSpeed = (pGame->GetBaseAddress() + 0xA47840);
	CVector3 *pvecTurnSpeed = &vecTurnSpeed;
	DWORD pPhysics = (DWORD)m_pEntity;
	_asm
	{
		push pvecTurnSpeed
		mov ecx, pPhysics
		call FUNC__SetTurnSpeed
	}
}

void CEntity::GetTurnSpeed(CVector3 &vecTurnSpeed)
{
	// If we dont have an entity pointer, then dont bother do the rest
	if(!m_pEntity)
		return;

	DWORD FUNC__GetTurnSpeed = (pGame->GetBaseAddress() + 0xA478E0);
	CVector3 *pvecTurnSpeed = &vecTurnSpeed;
	DWORD pPhysics = (DWORD)m_pEntity;
	_asm
	{
		push pvecTurnSpeed
		mov ecx, pPhysics
		call FUNC__GetTurnSpeed
	}
}