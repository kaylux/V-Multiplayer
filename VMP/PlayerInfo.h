/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerInfo.h
-- Project: Client
-- Author(s): m0niSx
-- Description: PlayerInfo handler header file
=============================================================*/

#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "VPlayerInfo.h"

class CPlayerInfo
{
	public:
		CPlayerInfo(CVPlayerInfo *pPlayerInfo);
		~CPlayerInfo();

		//////////////////////////////////////////////////////////////////////
		inline void SetHandler(CVPlayerInfo *pPlayerInfo)
		{
			// Set player info pointer
			m_pPlayerInfo = pPlayerInfo;
		}
		inline CVPlayerInfo *GetHandler() { return m_pPlayerInfo; };

		//////////////////////////////////////////////////////////////////////
		void SetName(char *szName) { m_pPlayerInfo ? strncpy(m_pPlayerInfo->szName, szName, 20) : szName = 0; };
		void SetColor(DWORD dwColor) { m_pPlayerInfo ? m_pPlayerInfo->dwColor = dwColor : dwColor = 0; };
		DWORD GetColor()  { return (m_pPlayerInfo ? m_pPlayerInfo->dwColor : 0); };
		bool IsSprintDisabled() { return (m_pPlayerInfo ? m_pPlayerInfo->bSprintDisabled : false); };
		void DisableSprint(bool bDisabled) { m_pPlayerInfo ? m_pPlayerInfo->bSprintDisabled = bDisabled : bDisabled = false; }; 


	private:
		CVPlayerInfo		*m_pPlayerInfo;
};

#endif