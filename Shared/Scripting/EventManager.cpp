/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: EventManager.cpp
-- Project: Shared
-- Author(s): m0niSx
-- Description: Scripting events manager source file
=============================================================*/

#include "LuaInterface.h"

CEventManager::CEventManager()
{
	// Reset events list
	m_listEvents.clear();
}

CEventManager::~CEventManager()
{
	for(std::list<CEvent *>::iterator i = m_listEvents.begin(); i != m_listEvents.end(); ++i)
	{
		if(*i)
			delete (*i);
	}
}

CEvent *CEventManager::GetAt(char *szEvent)
{
	// Loop through all the events
	for(std::list<CEvent *>::iterator i = m_listEvents.begin(); i != m_listEvents.end(); ++i)
	{
		if(*i)
		{
			// Get the event name
			char szName[64];
			(*i)->GetName(szName);
			// Is it the event we're looking for ?
			if(!strcmp(szName, szEvent))
				return (*i);
		}
	}
	return NULL;
}

void CEventManager::RegisterEvent(char *szEvent, char *szFunctionName)
{
	// Find the event
	CEvent *pEvent = GetAt(szEvent);
	// If there is not event found in the list, then add a new one to it
	if(!pEvent)
	{
		// Create the event instance
		pEvent = new CEvent(szEvent);
		if(!pEvent)
			return;

		// Add the event to the events list
		m_listEvents.push_back(pEvent);
	}
	// Add the function to the event functions list
	pEvent->AddFunction(szFunctionName);
}

void CEventManager::UnregisterEvent(char *szEvent, char *szFunctionName)
{
	// Find the event
	CEvent *pEvent = GetAt(szEvent);
	if(pEvent)	
		// Remove the function from the event functions
		pEvent->RemoveFunction(szFunctionName);

}

int CEventManager::CallEvent(lua_State *pVM, LogFunction_t pfnLogFunction, char *szEvent, char *szFormat, ...)
{
	// Find the event
	CEvent *pEvent = GetAt(szEvent);
	if(!pEvent)
		return 0;

	// Create the arguments list
	va_list vArgs;
	va_start(vArgs, szFormat);
	// Make a call to all the event functions
	int iRetValue = pEvent->CallEvent(pVM, pfnLogFunction, szFormat, vArgs);
	// End the arguments list
	va_end(vArgs);
	return iRetValue;
}