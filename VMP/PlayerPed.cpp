/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerPed.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: PlayerPed handler source file
=============================================================*/

#include "Main.h"

CPlayerPed::CPlayerPed(CVPlayerPed *pPlayerPed) : CEntity()
{
	// Set our ped pointer
	m_pPlayerPed = pPlayerPed;
}

CPlayerPed::~CPlayerPed()
{

}

void CPlayerPed::SetPedTask(CTask *pTask, eTaskPriority priority, bool bForceNewTask)
{
	// Do we have a valid player ped & task pointers ?
	if(!m_pPlayerPed || !pTask)
		return;

	// Call the CPedTaskManager__SetPedTask
	CVPedIntelligence *pPedIntelligence = m_pPlayerPed->pPedIntelligence;
	CVTask *pTaskHandler = pTask->GetHandler();
	int iForceNewTask = (int)bForceNewTask;
	_asm
	{
		push iForceNewTask
		push priority
		push pTaskHandler
		mov ecx, pPedIntelligence
		add ecx, 0x44
		call CAddress::FUNC_CPedTaskManager__SetPedTask
	}
}

void CPlayerPed::SetPedMouvementTask(CTask *pTask, int iPriority)
{
	// Do we have a valid player ped & task pointers ?
	if(!m_pPlayerPed || !pTask)
		return;

	// Ensure the priority
	if(iPriority < 0)
		iPriority = 0;
	else if(iPriority > 2)
		iPriority = 2;

	// Call the CPedTaskManager__SetMouvementTask
	CVPedTaskManager *pTaskManager = m_pPlayerPed->pPedIntelligence->pPedTaskManager;
	CVTask *pTaskHandler = pTask->GetHandler();
	_asm
	{
		push iPriority
		push pTaskHandler
		mov ecx, pTaskManager
		call CAddress::FUNC_CPedTaskManager__SetMouvementTask
	}
}

void CPlayerPed::ClearTasks()
{
	// Do we have a valid player ped pointer ?
	if(!m_pPlayerPed)
		return;

	// Call the CPedTaskManager__SetPedTask
	CVPedTaskManager *pTaskManager = m_pPlayerPed->pPedIntelligence->pPedTaskManager;
	_asm
	{
		mov ecx, pTaskManager
		call CAddress::FUNC_CPedTaskManager__ClearTasks
	}
}

