/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ModuleManager.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Modules manager header file
=============================================================*/

#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <list>
#include "Module.h"

class CModuleManager
{
	public:
		CModuleManager();
		~CModuleManager();

		void LoadModules();
		void UnloadModule(int iModuleId);
		void Pulse();
		void ScriptLoad(char *szScriptName);
		void ScriptUnload(char *szScriptName);

	private:
		std::list<CModule *>		m_listModules;


};

#endif