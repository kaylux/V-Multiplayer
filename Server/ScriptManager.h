/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ScriptManager.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Script manager header file
=============================================================*/

#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

#include "Script.h"

class CScriptManager
{
	public:
		CScriptManager();
		~CScriptManager();

		void LoadScripts();
		void UnloadScript(int iScriptId);

	private:
		std::list<CScript *>			m_listScripts;


};

#endif