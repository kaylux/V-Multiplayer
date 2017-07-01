/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Config.cpp
-- Project: Shared
-- Author(s): m0niSx
-- Description: configuration file reader source file
=============================================================*/


#include "Config.h"
#include "SharedUtility.h"

CConfig::CConfig(char *szFile)
{
	// Save values
	strcpy(m_szFile, szFile);
	// Reset values count
	m_iValues = 0;
	// Reset keys and keys values
	for(int i = 0; i < 50; i++)
	{
		strcpy(m_keySlot[i].m_szKey, "");
		m_keySlot[i].m_iKeyValues = 0;
		for(int j = 0; j < 20; j++)
			strcpy(m_keySlot[i].m_szValue[j], "");
	}
}

CConfig::~CConfig()
{
}

bool CConfig::Initialize()
{
	// Open the file
	FILE *pConfigFile = fopen(m_szFile, "r");
	if(!pConfigFile)
		return false;

	// Read the file line by line
	char szBuffer[512];
	char *szBuf;
	while(fgets(szBuffer, 512, pConfigFile))
	{
		// Copy the buffer into the szBuf
		szBuf = szBuffer;
		// Skip spaces
		while(isspace(*szBuf) && *szBuf != NULL)
			szBuf++;

		// Ignore comments lines or ended ones
		if(*szBuf == ';' || *szBuf == '\n' || *szBuf == '\r' || *szBuf == NULL)
			continue;

		// Keeps copying until we reach the end
		while(*szBuf != NULL)
		{
			// Skip spaces
			while(isspace(*szBuf) && *szBuf != NULL)
				szBuf++;

			// Ignore comments lines or ended ones
			if(*szBuf == ';' || *szBuf == '\n' || *szBuf == '\r' || *szBuf == NULL)
				break;

			// Copy the current string
			char szValue[128];
			int iCount = 0;
			while(IsReadable(*szBuf) && *szBuf != NULL)
			{
				// Copy the value
				szValue[iCount] = *szBuf;
				szValue[iCount+1] = '\0';
				// Increase the buffer and count
				*szBuf++;
				iCount++;
			}
			// Skip spaces
			while(isspace(*szBuf) && *szBuf != NULL)
				szBuf++;

			// If it is a "="
			if(*szBuf == '=')
			{
				// Copy the key
				strcpy(m_keySlot[m_iValues].m_szKey, szValue);
				// Increase the values
				m_iValues++;
			}
			else
			{
				// Copy the value
				int iValue = m_iValues-1;
				strcpy(m_keySlot[iValue].m_szValue[m_keySlot[iValue].m_iKeyValues], szValue);
				// Increase the key values
				m_keySlot[iValue].m_iKeyValues++;
			}
			// Ignore comments lines or ended ones
			if(*szBuf == ';' || *szBuf == '\n' || *szBuf == '\r' || *szBuf == NULL)
				break;

			// Increase the buffer
			szBuf++;
		}
	}
	// Close the file
	fclose(pConfigFile);
	return true;
}

int CConfig::GetValueCount(char *szKey)
{
	// Loop through the readed values
	for(int i = 0; i < m_iValues; i++)
	{
		// Is the key equals for the search
		if(!strcmp(szKey, m_keySlot[i].m_szKey))
			return m_keySlot[i].m_iKeyValues;
	}
	return -1;
}

bool CConfig::GetValueAsString(char *szKey, int iValueId, char *szValue)
{
	// Loop through the readed values
	for(int i = 0; i < m_iValues; i++)
	{
		// Is the key equals for the search
		if(!strcmp(szKey, m_keySlot[i].m_szKey))
		{
			// Copy the value
			strcpy(szValue, m_keySlot[i].m_szValue[iValueId]);
			// Return 
			return true;
		}
	}
	// Return invalid
	return false;
}

int CConfig::GetValueAsInteger(char *szKey, int iValueId)
{
	// Get the value
	char szValue[128];
	if(!GetValueAsString(szKey, iValueId, szValue))
		return -1;

	// Return the inetger value
	return atoi(szValue);
}

bool CConfig::GetValueAsBoolean(char *szKey, int iValueId)
{
	// Get the value
	char szValue[128];
	if(!GetValueAsString(szKey, iValueId, szValue))
		return false;

	// Return the inetger value
	return atoi(szValue) == 1 ? true : false;
}