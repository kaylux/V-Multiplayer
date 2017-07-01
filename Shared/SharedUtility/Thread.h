/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Thread.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: Thread manipulation header file
=============================================================*/

#ifndef THREAD_H
#define THREAD_H

#include <windows.h>

typedef void (*ThreadCallback_t)(void *pThread);

class CThread
{
	public:
		CThread(ThreadCallback_t pfn_ThreadCallback);
		~CThread();

		bool Start();
		void Stop();
		bool IsStarted() { return m_bStarted; };
		void SetStarted(bool bState) { m_bStarted = bState; };
		void CallCallback(CThread *pThread) { m_pfnThreadCallback((void *)pThread); };
#ifdef WIN32
		static void ThreadFunction(LPVOID lpThread);
#else
		static void *ThreadFunction(void *pThread);
#endif

	private:
		bool				m_bStarted;
		ThreadCallback_t	m_pfnThreadCallback;
#ifdef WIN32
		HANDLE				m_hThread;
#else
		pthread_t			m_Thread;
#endif

};

#endif
