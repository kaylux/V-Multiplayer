/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Module.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Module header file
=============================================================*/

#ifndef MODULE_H
#define MODULE_H

extern "C"
{
	#include <lua.h>
}

struct stModuleContainer
{
	void *pLogPrintf;
	void *pLuaInterface;
	// Lua functions
	void *lua_gettop;
	void *lua_settop;
	void *lua_pushvalue;
	void *lua_remove;
	void *lua_insert;
	void *lua_replace;
	void *lua_checkstack;
	void *lua_xmove;
	void *lua_isnumber;
	void *lua_isstring;
	void *lua_iscfunction;
	void *lua_isuserdata;
	void *lua_type;
	void *lua_typename;
	void *lua_equal;
	void *lua_rawequal;
	void *lua_lessthan;
	void *lua_tonumber;
	void *lua_tointeger;
	void *lua_toboolean;
	void *lua_tolstring;
	void *lua_objlen;
	void *lua_tocfunction;
	void *lua_touserdata;
	void *lua_tothread;
	void *lua_topointer;
	void *lua_pushnil;
	void *lua_pushnumber;
	void *lua_pushinteger;
	void *lua_pushlstring;
	void *lua_pushstring;
	void *lua_pushvfstring;
	void *lua_pushfstring;
	void *lua_pushcclosure;
	void *lua_pushboolean;
	void *lua_pushlightuserdata;
	void *lua_pushthread;
	void *lua_gettable;
	void *lua_getfield;
	void *lua_rawget;
	void *lua_rawgeti;
	void *lua_createtable;
	void *lua_newuserdata;
	void *lua_getmetatable;
	void *lua_getfenv;
	void *lua_settable;
	void *lua_setfield;
	void *lua_rawset;
	void *lua_rawseti;
	void *lua_setmetatable;
	void *lua_setfenv;
	void *lua_gc;
	void *lua_error;
	void *lua_next;
	void *lua_concat;
	void *lua_getallocf;
	void *lua_setallocf;

};

typedef void (*OnModuleSetup_t)(stModuleContainer *pModuleContainer);
typedef bool (*OnModuleLoad_t)(char *szModuleName, lua_State *pVM);
typedef void (*OnScriptLoad_t)(char *szScriptName);
typedef void (*OnScriptUnload_t)(char *szScriptName);
typedef void (*OnModuleUnload_t)();
typedef void (*OnModulePulse_t)();

class CModule
{
	public:
		CModule(char *szModule);
		~CModule();

		bool Load();
		void Unload();
		void Pulse();
		void OnScriptLoad(char *szScriptName);
		void OnScriptUnload(char *szScriptName);

		void SetupContainer(stModuleContainer *pModuleContainer);

		void GetName(char *szName) { strcpy(szName, m_szModuleName); };

	private:
		bool					m_bLoaded;
		char					m_szModulePath[MAX_PATH];
		char					m_szModuleName[64];
		CLibrary				*m_pLibrary;
		//////////////////////////////////////////////
		OnModuleSetup_t			m_pfnModuleSetup;
		OnModuleLoad_t			m_pfnModuleLoad;
		OnModuleUnload_t		m_pfnModuleUnload;
		OnScriptLoad_t			m_pfnScriptLoad;
		OnScriptUnload_t		m_pfnScriptUnload;
		OnModulePulse_t			m_pfnModulePulse;

};

#endif