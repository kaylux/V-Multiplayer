/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: GameThread.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: GameThread class source file
=============================================================*/

#include "Main.h"

extern CGame	*pGame;

CGameThread::CGameThread(CVThread *pThread)
{
	// Set the thread pointer
	m_pThread = pThread;
}

CGameThread::~CGameThread()
{
}


