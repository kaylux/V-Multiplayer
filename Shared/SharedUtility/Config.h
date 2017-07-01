/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Config.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Server configuration file reader header file
=============================================================*/

#ifndef CONFIG_H
#define CONFIG_H

// Make it cross compatible
#ifdef WIN32
#	include <windows.h>
#	include <stdio.h>
#endif

class CConfig
{
	public:
		CConfig(char *szFile);
		~CConfig();

		bool Initialize();
		///////////////////////////////////
		int GetValueCount(char *szKey);
		bool GetValueAsString(char *szKey, int iValueId, char *szValue);
		int GetValueAsInteger(char *szKey, int iValueId);
		bool GetValueAsBoolean(char *szKey, int iValueId);

	private:
		char			m_szFile[MAX_PATH];
		int				m_iValues;
		typedef struct  stKeySlot
		{
			int	 m_iKeyValues;
			char m_szKey[256];
			char m_szValue[20][256];

		};  stKeySlot m_keySlot[50];

};

#endif