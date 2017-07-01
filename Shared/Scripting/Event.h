/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Event.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: Scripting events handler header file
=============================================================*/


#ifndef EVENT_H
#define EVENT_H

#include <list>

typedef void (*LogFunction_t)(char *szText, ...);

class CEvent
{
	public:
		CEvent(char *szEventName)
		{
			// Clear the functions list
			m_listFunctions.clear();
			// Save the event name
			strcpy(m_szEventName, szEventName);
		};
		~CEvent()
		{
		};

		///////////////////////////////////////////////////////////////////////
		inline void GetName(char *szName) { strcpy(szName, m_szEventName); };

		///////////////////////////////////////////////////////////////////////
		inline void AddFunction(char *szFunctionName)
		{
			// Add the function to the list
			m_listFunctions.push_back(szFunctionName);
		};

		inline void RemoveFunction(char *szFunctionName)
		{
			// ARemovedd the function from the list
			m_listFunctions.remove(szFunctionName);
		};

		///////////////////////////////////////////////////////////////////////
		int CallEvent(lua_State *pVM, LogFunction_t pfnLogFunction, char *szFormat, ...)
		{
			int iRetValue = 0;
			// Create the arguments list
			va_list vArgs;
			va_start(vArgs, szFormat);
			// Loop through all the functions
			for(std::list<char *>::iterator i = m_listFunctions.begin(); i != m_listFunctions.end(); ++i)
			{
				if(*i)
					// Call the event functions
					iRetValue = CallEventFunction(pVM, pfnLogFunction, (*i), szFormat, vArgs);
			}
			// End the arguments list
			va_end(vArgs);
			return iRetValue;
		};

		///////////////////////////////////////////////////////////////////////
		int CallEventFunction(lua_State *pVM, LogFunction_t pfnLogFunction, char *szFunction, char *szFormat, ...)
		{
			// Specify the function name
			lua_getglobal(pVM, szFunction);
			// Check if its a function
			if(!lua_isfunction(pVM, -1))
			{
				// Get the pushed stuff from the stack
				lua_pop(pVM, 1);
				// Return null
				return 0;
			}
			else
			{
				unsigned int uiCount = 0;
				// Create the arguments list
				va_list vArgs;
				va_start(vArgs, szFormat);
				// Keep looping until we finish processing all arguments
				while(*szFormat != NULL)
				{
					if(*szFormat == 'n') // Number
					{
						int iu = va_arg(vArgs, int);
						pfnLogFunction("getting num (%d) (%s)", iu, szFunction); 
						lua_pushnumber(pVM, iu);
					}
					else if(*szFormat == ' ') // Nil
						lua_pushnil(pVM);
					else if(*szFormat == 'b') // Boolean
						lua_pushboolean(pVM, va_arg(vArgs, bool)); 
					else if(*szFormat == 's') // Strings
						lua_pushstring(pVM, va_arg(vArgs, const char *));

					// Increase the arguments count
					uiCount++;
					// Increase the format
					szFormat++;
				}
				va_end(vArgs);
				// Execute the function
				int iReturn = lua_pcall(pVM, uiCount, 1, 0); // We'll go with one return for now
				if(iReturn == LUA_ERRRUN || iReturn == LUA_ERRMEM)
				{
					if(pfnLogFunction)
						pfnLogFunction("Error: %s", lua_tostring(pVM, -1));
				}
				int iRetValue = 0;
				// Check for return value
				if(lua_isnumber(pVM, -1))
					iRetValue = (int)lua_tonumber(pVM, -1);

				lua_pop(pVM, 1);
				return iRetValue;
			}
		};


	private:
		char					m_szEventName[64];
		std::list<char *>		m_listFunctions;
};

#endif