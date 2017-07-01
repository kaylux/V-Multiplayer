/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Script.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Script source file
=============================================================*/

#include "Main.h"

extern CLuaInterface		*pLuaInterface;

CScript::CScript(char *szScript)
{
	// Reset variables
	m_bLoaded = false;
	// Save script path
	strcpy(m_szScriptPath, "Scripts/");
	strcat(m_szScriptPath, szScript);
	strcat(m_szScriptPath, ".lua");
	// Save script name
	strcpy(m_szScriptName, szScript);
}

CScript::~CScript()
{
}

bool CScript::Load()
{
	// Make sure the file path is valid
	if(!FileExists(m_szScriptPath))
		return false;

	// Try to load script
	if(!pLuaInterface->LoadScript(m_szScriptPath, m_szScriptName))
		return false;

	// Call the scriptLoad event
	pLuaInterface->CallEvent("scriptLoad", "");
	return true;
}	

void CScript::Unload()
{
	// Make sure we are loaded
	if(!m_bLoaded)
		return;
}

void CScript::Pulse()
{
	// Make sure we are loaded
	if(!m_bLoaded)
		return;
}