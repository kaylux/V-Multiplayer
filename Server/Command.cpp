/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Command.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Server commands process source file
=============================================================*/

#include "Main.h"

CCommand::CCommand()
{
	// Reset commands count
	m_byteCommands = 0;
	// Reset commands names & functions
	for(BYTE i = 0; i < MAX_COMMANDS; i++)
	{
		// Reset names
		strcpy(m_szCommand[i], "");
		// Reset function
		m_cmdFunction[i] = NULL;
	}
}

CCommand::~CCommand()
{
}

void CCommand::Process(char *szBuffer)
{
	// Get command
	char *szCommand = strtok(szBuffer, " ");
	// Get the command function
	CommandFunction_t function;
	if((function = GetCommandFunction(szCommand)) != NULL)
	{
		// Get arguments
		char *szArg = strtok(NULL, " ");
		char szArgument[20][128];
		unsigned int uiCount = 0;
		while(szArg != NULL)
		{
			// Save the argument
			strcpy(szArgument[uiCount], szArg);
			// Increase the arguments count
			uiCount++;
			// Get the next one
			szArg = strtok(NULL, " ");
		}
		// Get the command id
		BYTE byteCommandId = GetCommandId(szCommand);
		// Check if the number of arguments written is not less than the registerd one
		if(strlen(m_szFormat[byteCommandId]) > uiCount)
		{
			LogPrintf(true, "Not enough parameters for command \"%s\"", szCommand);
			return;
		}
		// Calculate the arguments len
		unsigned int uiLength = strlen(m_szFormat[byteCommandId])*4;
		// Push the function arguments into the stack for the call
		for(int i = strlen(m_szFormat[byteCommandId])-1; i >= 0; i--)
		{
			// If is an integer
			if(m_szFormat[byteCommandId][i] == 'i')
			{
				int iValue = atoi(szArgument[i]);
				_asm push iValue
			}
			// Float
			else if(m_szFormat[byteCommandId][i] == 'f')
			{
				float fValue = atof(szArgument[i]);
				_asm push fValue
			}
			// String
			else if(m_szFormat[byteCommandId][i] == 's')
			{
				char *szValue = szArgument[i];
				_asm push szValue
			}
		}
		// Call the function
		_asm
		{
			call function
			add esp, uiLength
		}
	}
}

CommandFunction_t CCommand::GetCommandFunction(char *szCommand)
{
	// Loop through the commands
	for(BYTE i = 0; i < m_byteCommands; i++)
	{
		// Is the command name equals for the searching one
		if(!strcmp(m_szCommand[i], szCommand))
			// Return command function
			return m_cmdFunction[i];
	}
	// Return invalid
	return NULL;
}

BYTE CCommand::GetCommandId(char *szCommand)
{
	// Loop through the commands
	for(BYTE i = 0; i < m_byteCommands; i++)
	{
		// Is the command name equals for the searching one
		if(!strcmp(m_szCommand[i], szCommand))
			// Return command function
			return i;
	}
	// Return invalid
	return 255;
}
