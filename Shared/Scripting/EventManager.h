/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: EventManager.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: Scripting events manager header file
=============================================================*/


#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Event.h"

class CEventManager
{
	public:
		CEventManager();
		~CEventManager();

		///////////////////////////////////////////////////////////////////////
		CEvent *GetAt(char *szEvent);

		///////////////////////////////////////////////////////////////////////
		void RegisterEvent(char *szEvent, char *szFunctionName);
		void UnregisterEvent(char *szEvent, char *szFunctionName);

		///////////////////////////////////////////////////////////////////////
		int CallEvent(lua_State *pVM, LogFunction_t pfnLogFunction, char *szEvent, char *szFormat, ...);

	private:
		std::list<CEvent *>		m_listEvents;
};

#endif