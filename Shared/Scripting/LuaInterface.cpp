/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: LuaInterface.cpp
-- Project: Shared
-- Author(s): m0niSx
-- Description: Lua interface source file
=============================================================*/

#include "LuaInterface.h"
#include <windows.h>

CLuaInterface::CLuaInterface()
{
	// Reset VM pointer
	m_pVM = NULL;
	// Reset log function
	m_pfnLogFunction = NULL;
	// Reset event manager instance
	m_pEventManager = NULL;
}

CLuaInterface::~CLuaInterface()
{
	// Close lua VM
	lua_close(m_pVM);
	// Delete the events manager instance
	delete m_pEventManager;
}

bool CLuaInterface::Initialize()
{
	// Open a new lua VM
	m_pVM = lua_open();
	if(!m_pVM)
		return false;

	// Load lua librarys
	luaopen_base(m_pVM);
	luaopen_math(m_pVM);
	luaopen_string(m_pVM);
	luaopen_table(m_pVM);
	luaopen_debug(m_pVM);
	// Create the event manager class instance
	m_pEventManager = new CEventManager();
	if(!m_pEventManager)
		return false;

	return true;
}

bool CLuaInterface::LoadScript(char *szScript, char *szScriptName)
{
	// Make sure we have a valid VM pointer
	if(!m_pVM)
		return false;

	// Try to load the scrpt file
	if(luaL_loadfile(m_pVM, szScript))
	{
		// Report the error
		if(m_pfnLogFunction)
			m_pfnLogFunction("Script \"%s\" has failed to load\n %s", szScriptName, lua_tostring(m_pVM, -1));

		return false;
	}
	else
	{
		// Execute the script
		int iReturn = lua_pcall(m_pVM, 0, 0, 0);
		// Check for executing errors
		if(iReturn == LUA_ERRRUN || iReturn == LUA_ERRMEM)
		{
			if(m_pfnLogFunction)
				m_pfnLogFunction("Error On Scirpt %s\n%s", szScriptName, lua_tostring(m_pVM, -1));
			
			return false;
		}
		return true;
	}
}

int CLuaInterface::CallEvent(char *szEvent, char *szFormat, ...)
{
	return 1;
	// Create the arguments list
	va_list vArgs;
	va_start(vArgs, szFormat);
	// Make a call to all the event functions
	int iRetValue = m_pEventManager->CallEvent(m_pVM, m_pfnLogFunction, szEvent, szFormat, vArgs);
	// End the arguments list
	va_end(vArgs);
	return iRetValue;
}

bool CLuaInterface::CheckFunctionType(lua_State *pVM, char *szEvent, char *szFormat)
{
	// Loop through the arguments
	for(unsigned int i = 1; i < strlen(szFormat)+1; i++)
	{
		// Get argument type
		int iType = lua_type(pVM, i);
		if(iType == LUA_TNUMBER)
		{
			if(*szFormat != 'n')
			{
				if(m_pfnLogFunction)
					m_pfnLogFunction("Error in \"%s\" function. Invalid arguments (argument %d)", szEvent, i);
				
				return false;
			}
		}
		else if(iType == LUA_TSTRING)
		{
			if(*szFormat != 's')
			{
				if(m_pfnLogFunction)
					m_pfnLogFunction("Error in \"%s\" function. Invalid arguments (argument %d)", szEvent, i);
				
				return false;
			}
		}
		else if(iType == LUA_TBOOLEAN)
		{
			if(*szFormat != 'b')
			{
				m_pfnLogFunction("Error in \"%s\" function. Invalid arguments (argument %d)", szEvent, i);
				return false;
			}
		}
		else if(iType == LUA_TNIL)
		{
			if(*szFormat != ' ')
			{
				if(m_pfnLogFunction)
					m_pfnLogFunction("Error in \"%s\" function. Invalid arguments (argument %d)", szEvent, i);
				
				return false;
			}
		}
		else if(iType == LUA_TFUNCTION)
		{
			if(*szFormat != 'p')
			{
				if(m_pfnLogFunction)
					m_pfnLogFunction("Error in \"%s\" function. Invalid arguments (argument %d)", szEvent, i);
				
				return false;
			}
		}
		else
		{
			if(m_pfnLogFunction)
				m_pfnLogFunction("Error in \"%s\" function. Invalid arguments (argument %d)", szEvent, i);
			
			return false;
		}
		// Increase the format
		szFormat++;
	}
	return true;
}