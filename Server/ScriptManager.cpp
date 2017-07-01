/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ScriptManager.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Scripts manager source file
=============================================================*/

#include "Main.h"

extern CConfig				*pConfig;
extern CModuleManager		*pModuleManager;

CScriptManager::CScriptManager()
{
	// Reset scripts list
	m_listScripts.clear();
}

CScriptManager::~CScriptManager()
{
	for(std::list<CScript *>::iterator i = m_listScripts.begin(); i != m_listScripts.end(); ++i)
	{
		if(*i)
			SAFE_DELETE((*i));
	}
}

void CScriptManager::LoadScripts()
{
	// Verify we have a valid config pointer
	if(!pConfig)
		return;

	// Get scripts count from config file
	int iScripts = pConfig->GetValueCount("Scripts");
	// Make sure the scripts count is not above the maximum allowed
	if(iScripts > MAX_SCRIPTS)
		iScripts = MAX_SCRIPTS;

	int iLoadedScripts = 0;
	LogPrintf(true, "Loading scripts (%d) ...", iScripts);
	LogPrintf(true, "--------------------------");
	LogPrintf(true, "");
	// Loop through config modules
	for(int i = 0; i < iScripts; i++)
	{
		// Get script name
		char szScript[32];
		pConfig->GetValueAsString("Scripts", i, szScript);
		// Create the script instance
		CScript *pScript = new CScript(szScript);
		if(!pScript)
			continue;

		LogPrintf(true, "Loading script \"%s\" ...", szScript);
		// Try to load the script
		if(!pScript->Load())
		{
			SAFE_DELETE(pScript);
			LogPrintf(true, "Failed to load \"%s\"", szScript);
			LogPrintf(true, "");
		}
		else
		{
			// Increase the loaded scripts count
			iLoadedScripts++;
			// Print loaded message
			LogPrintf(true, "Script \"%s\" successfully loaded (ID: %d)", szScript, iLoadedScripts);
			LogPrintf(true, "");
			// Add the script to the scripts list
			m_listScripts.push_back(pScript);
			// Call the on script load in modules
			pModuleManager->ScriptLoad(szScript);
		}
	}
	LogPrintf(true, "-------------------");
	LogPrintf(true, "Loaded scripts (%d/%d)", iLoadedScripts, iScripts);
	LogPrintf(true, "");
}

void CScriptManager::UnloadScript(int iScriptId)
{
	/*// Make sure the module is loaded
	if(!m_bLoaded[iModuleId])
		return;

	// Unload the module
	m_pModule[iModuleId]->Unload();
	// Delete the module class instance
	SAFE_DELETE(m_pModule[iModuleId]);*/
}
