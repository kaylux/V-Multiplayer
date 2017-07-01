/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Module.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Module source file
=============================================================*/

#include "Main.h"

extern CLuaInterface		*pLuaInterface;

CModule::CModule(char *szModule)
{
	// Add the module to the current modules path
	strcpy(m_szModulePath, "Modules\\");
	strcat(m_szModulePath, szModule);
	// Add the right extension
#ifdef WIN32
	strcat(m_szModulePath, ".dll");
#else
	strcat(m_szModulePath, ".so");
#endif
	// Reset variables
	m_bLoaded = false;
	m_pLibrary = NULL;
}

CModule::~CModule()
{
	// Unload the module
	Unload();
}

bool CModule::Load()
{
	// Create the library class instance
	m_pLibrary = new CLibrary(m_szModulePath);
	if(!m_pLibrary)
		return false;

	// Try to load the library
	if(!m_pLibrary->Load())
	{
		SAFE_DELETE(m_pLibrary);
		return false;
	}
	// Get the function addresses
	m_pfnModuleSetup = (OnModuleSetup_t)m_pLibrary->GetProcedureAddress("OnModuleSetup");
	m_pfnModuleLoad = (OnModuleLoad_t)m_pLibrary->GetProcedureAddress("OnModuleLoad");
	m_pfnModuleUnload = (OnModuleUnload_t)m_pLibrary->GetProcedureAddress("OnModuleUnload");
	m_pfnScriptLoad = (OnScriptLoad_t)m_pLibrary->GetProcedureAddress("OnScriptLoad");
	m_pfnScriptUnload = (OnScriptUnload_t)m_pLibrary->GetProcedureAddress("OnScriptUnload");
	m_pfnModulePulse = (OnModulePulse_t)m_pLibrary->GetProcedureAddress("OnModulePulse");
	// Verify addresses
	if(!m_pfnModuleSetup || !m_pfnModuleLoad)
	{
		m_pLibrary->Unload();
		SAFE_DELETE(m_pLibrary);
		return false;
	}
	// Call the module setup function
	stModuleContainer moduleContainer;
	SetupContainer(&moduleContainer);
	m_pfnModuleSetup(&moduleContainer);
	// Call the module load function
	if(!m_pfnModuleLoad(m_szModuleName, pLuaInterface->GetVM()))
	{
		m_pLibrary->Unload();
		SAFE_DELETE(m_pLibrary);
		return false;
	}
	// Mark as loaded
	m_bLoaded = true;
	return true;
}

void CModule::Unload()
{
	// Make sure we are loaded
	if(!m_bLoaded)
		return;

	// Call the unload function
	if(m_pfnModuleUnload)
		m_pfnModuleUnload();

	// Unload the library
	m_pLibrary->Unload();
}

void CModule::Pulse()
{
	// Make sure we are loaded
	if(!m_bLoaded)
		return;

	// Call the pulse function
	if(m_pfnModulePulse)
		m_pfnModulePulse();
}

void CModule::OnScriptLoad(char *szScriptName)
{
	// Make sure we are loaded
	if(!m_bLoaded)
		return;

	// Call the ScriptLoad function
	if(m_pfnScriptLoad)
		m_pfnScriptLoad(szScriptName);
}

void CModule::OnScriptUnload(char *szScriptName)
{
	// Make sure we are loaded
	if(!m_bLoaded)
		return;

	// Call the ScriptUnload function
	if(m_pfnScriptUnload)
		m_pfnScriptUnload(szScriptName);
}

void CModule::SetupContainer(stModuleContainer *pModuleContainer)
{
	pModuleContainer->pLogPrintf = LogPrintf;
	// Setup interafces
	pModuleContainer->pLuaInterface = pLuaInterface;
	// Setup lua functions
	pModuleContainer->lua_gettop = lua_gettop;
	pModuleContainer->lua_settop = lua_settop;
	pModuleContainer->lua_pushvalue = lua_pushvalue;
	pModuleContainer->lua_remove = lua_remove;
	pModuleContainer->lua_insert = lua_insert;
	pModuleContainer->lua_replace = lua_replace;
	pModuleContainer->lua_checkstack = lua_checkstack;
	pModuleContainer->lua_xmove = lua_xmove;
	pModuleContainer->lua_isnumber = lua_isnumber;
	pModuleContainer->lua_isstring = lua_isstring;
	pModuleContainer->lua_iscfunction = lua_iscfunction;
	pModuleContainer->lua_isuserdata = lua_isuserdata;
	pModuleContainer->lua_type = lua_type;
	pModuleContainer->lua_typename = lua_typename;
	pModuleContainer->lua_equal = lua_equal;
	pModuleContainer->lua_rawequal = lua_rawequal;
	pModuleContainer->lua_lessthan = lua_lessthan;
	pModuleContainer->lua_tonumber = lua_tonumber;
	pModuleContainer->lua_tointeger = lua_tointeger;
	pModuleContainer->lua_toboolean = lua_toboolean;
	pModuleContainer->lua_tolstring = lua_tolstring;
	pModuleContainer->lua_objlen = lua_objlen;
	pModuleContainer->lua_tocfunction = lua_tocfunction;
	pModuleContainer->lua_touserdata = lua_touserdata;
	pModuleContainer->lua_tothread = lua_tothread;
	pModuleContainer->lua_topointer = lua_topointer;
	pModuleContainer->lua_pushnil = lua_pushnil;
	pModuleContainer->lua_pushnumber = lua_pushnumber;
	pModuleContainer->lua_pushinteger = lua_pushinteger;
	pModuleContainer->lua_pushlstring = lua_pushlstring;
	pModuleContainer->lua_pushstring = lua_pushstring;
	pModuleContainer->lua_pushvfstring = lua_pushvfstring;
	pModuleContainer->lua_pushfstring = lua_pushfstring;
	pModuleContainer->lua_pushcclosure = lua_pushcclosure;
	pModuleContainer->lua_pushboolean = lua_pushboolean;
	pModuleContainer->lua_pushlightuserdata = lua_pushlightuserdata;
	pModuleContainer->lua_pushthread = lua_pushthread;
	pModuleContainer->lua_gettable = lua_gettable;
	pModuleContainer->lua_getfield = lua_getfield;
	pModuleContainer->lua_rawget = lua_rawget;
	pModuleContainer->lua_rawgeti = lua_rawgeti;
	pModuleContainer->lua_createtable = lua_createtable;
	pModuleContainer->lua_newuserdata = lua_newuserdata;
	pModuleContainer->lua_getmetatable = lua_getmetatable;
	pModuleContainer->lua_getfenv = lua_getfenv;
	pModuleContainer->lua_settable = lua_settable;
	pModuleContainer->lua_setfield = lua_setfield;
	pModuleContainer->lua_rawset = lua_rawset;
	pModuleContainer->lua_rawseti = lua_rawseti;
	pModuleContainer->lua_setmetatable = lua_setmetatable;
	pModuleContainer->lua_setfenv = lua_setfenv;
	pModuleContainer->lua_gc = lua_gc;
	pModuleContainer->lua_error = lua_error;
	pModuleContainer->lua_next = lua_next;
	pModuleContainer->lua_concat = lua_concat;
	pModuleContainer->lua_getallocf = lua_getallocf;
	pModuleContainer->lua_setallocf = lua_setallocf;
}