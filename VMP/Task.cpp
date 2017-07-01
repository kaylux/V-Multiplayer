/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Task.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Task handler source file
=============================================================*/

#include "Main.h"

CTask::CTask()
{
	// Reset values
	m_bCreated = false;
	m_pTask = NULL;
	// Allocate for the new task
	CVTask *pTask = CPools::Allocate<CVTask *>(*(DWORD*)CAddress::VAR_TaskPool);
	// Do we have a valid task pointer ?
	if(pTask)
	{
		// Set our task pointer
		m_pTask = pTask;
		// Indicate that we are created
		m_bCreated = true;
	}

}

CTask::~CTask()
{

}

