/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: GameHooks.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game hooks header file
=============================================================*/

#ifndef GAMEHOOKS_H
#define GAMEHOOKS_H

class CGameHooks
{
	public:
		static void InstallGameHooks();

		static void CScript__Process();
		static void CMenu__Process();

	private:
		static bool			m_bScriptInit;
		static bool			m_bScreenFaded;
		static bool			m_bMenuInit;

};

#endif