/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: GameThread.h
-- Project: Client
-- Author(s): m0niSx
-- Description: GameThread class header file
=============================================================*/

#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include "VThread.h"

class CGameThread
{
	public:
		CGameThread(CVThread *pThread);
		~CGameThread();
		
		///////////////////////////////////////////////////////////////////
		inline void SetHandler(CVThread *pThread)
		{
			// do we have a valid pointer ?
			if(pThread)
				// Set thread pointer
				m_pThread = pThread;
		}
		inline CVThread *GetHandler() { return m_pThread; };

		///////////////////////////////////////////////////////////////////
		void Destroy();


	private:
		CVThread				*m_pThread;
		
};

#endif