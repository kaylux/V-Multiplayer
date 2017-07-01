/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: LocalPlayer.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Task handler header file
=============================================================*/

#ifndef TASK_H
#define TASK_H

#include "VTask.h"

class CTask
{
	public:
		CTask();
		~CTask();

		//////////////////////////////////////////////////////////////////////
		inline bool IsCreated() { return m_bCreated; };
		inline void SetCreated(bool bCreated) { m_bCreated = bCreated; };

		//////////////////////////////////////////////////////////////////////
		inline void SetHandler(CVTask *pTask)
		{
			// Do we have a valid task pointer ?
			if(!pTask)
				return;

			// Set our task pointer
			m_pTask = pTask;
		}
		inline CVTask *GetHandler() { return m_pTask; };

	private:
		bool			m_bCreated;
		CVTask			*m_pTask;
};

#endif