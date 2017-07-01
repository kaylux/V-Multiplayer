/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: LuaInterface.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Lua interface header file
=============================================================*/

#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H

// Lua Includes
extern "C" 
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}
#include "EventManager.h"

class CLuaInterface
{
	public:
		CLuaInterface();
		~CLuaInterface();

		bool Initialize();
		bool LoadScript(char *szScript, char *szScriptName);

		///////////////////////////////////////////////////////////////////////
		inline lua_State *GetVM() { return m_pVM; };
		inline CEventManager *GetEventManager() { return m_pEventManager; };

		///////////////////////////////////////////////////////////////////////
		inline void SetLogFunction(LogFunction_t pfn_LogFunction) { m_pfnLogFunction = pfn_LogFunction; };

		///////////////////////////////////////////////////////////////////////
		virtual int CallEvent(char *szEvent, char *szFormat, ...);
		bool CheckFunctionType(lua_State *pVM, char *szEvent, char *szFormat);

	private:
		lua_State				*m_pVM;
		LogFunction_t			m_pfnLogFunction;
		CEventManager			*m_pEventManager;
};

#endif