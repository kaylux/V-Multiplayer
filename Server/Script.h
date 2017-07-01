/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Script.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Script header file
=============================================================*/

#ifndef SCRIPT_H
#define SCRIPT_H

class CScript
{
	public:
		CScript(char *szScript);
		~CScript();

		bool Load();
		void Unload();
		void Pulse();


	private:
		bool					m_bLoaded;
		char					m_szScriptPath[MAX_PATH];
		char					m_szScriptName[64];

};

#endif