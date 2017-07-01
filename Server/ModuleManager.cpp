/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ModuleManager.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Modules manager source file
=============================================================*/

#include "Main.h"

extern CConfig		*pConfig;

CModuleManager::CModuleManager()
{
	// Reset modules list
	m_listModules.clear();
}

CModuleManager::~CModuleManager()
{
	for(std::list<CModule *>::iterator i = m_listModules.begin(); i != m_listModules.end(); ++i)
	{
		if(*i)
			SAFE_DELETE((*i));
	}
}

void CModuleManager::LoadModules()
{
	// Verify we have a valid config pointer
	if(!pConfig)
		return;

	// Get modules count from config file
	int iModules = pConfig->GetValueCount("Modules");
	// Make sure the modules count is not above the maximum allowed
	if(iModules > MAX_MODULES)
		iModules = MAX_MODULES;

	int iLoadedModules = 0;
	LogPrintf(true, "Loading Modules (%d) ...", iModules);
	LogPrintf(true, "-------------------------------");
	LogPrintf(true, "");
	// Loop through config modules
	for(int i = 0; i < iModules; i++)
	{
		// Get modules name
		char szModule[32];
		pConfig->GetValueAsString("Modules", i, szModule);
		// Create the module instance
		CModule *pModule = new CModule(szModule);
		if(!pModule)
			continue;

		LogPrintf(true, "Loading module \"%s\" ...", szModule);
		// Try to load the mdoule
		if(!pModule->Load())
		{
			SAFE_DELETE(pModule);
			LogPrintf(true, "Failed to load \"%s\"", szModule);
			LogPrintf(true, "");
		}
		else
		{
			// Get module name
			char szModuleName[64];
			pModule->GetName(szModuleName);
			// Increase the loaded modules count
			iLoadedModules++;
			// Print loaded message
			LogPrintf(true, "Module \"%s\" successfully loaded (ID: %d)", szModuleName, iLoadedModules);
			LogPrintf(true, "");
			// Add module handle to the modules list
			m_listModules.push_back(pModule);
		}
	}
	LogPrintf(true, "-------------------");
	LogPrintf(true, "Loaded modules (%d/%d)", iLoadedModules, iModules);
	LogPrintf(true, "");
}

void CModuleManager::UnloadModule(int iModuleId)
{
	/*// Unload the module
	m_pModule[iModuleId]->Unload();
	// Delete the module class instance
	SAFE_DELETE(m_pModule[iModuleId]);*/
}

void CModuleManager::Pulse()
{
	// Loop through all the modules
	for(std::list<CModule *>::iterator i = m_listModules.begin(); i != m_listModules.end(); ++i)
	{
		if(*i)
			(*i)->Pulse();
	}
}

void CModuleManager::ScriptLoad(char *szScriptName)
{
	// Loop through all the modules
	for(std::list<CModule *>::iterator i = m_listModules.begin(); i != m_listModules.end(); ++i)
	{
		if(*i)
			(*i)->OnScriptLoad(szScriptName);
	}
}

void CModuleManager::ScriptUnload(char *szScriptName)
{
	// Loop through all the modules
	for(std::list<CModule *>::iterator i = m_listModules.begin(); i != m_listModules.end(); ++i)
	{
		if(*i)
			(*i)->OnScriptUnload(szScriptName);
	}
}