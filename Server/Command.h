/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Command.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Server commands process header file
=============================================================*/

#ifndef COMMAND_H
#define COMMAND_H

#define MAX_COMMANDS 20

typedef void (*CommandFunction_t)(...);

class CCommand
{
	public:
		CCommand();
		~CCommand();

		void Process(char *szBuffer);
		////////////////////////////////////////////////////////
		template <typename FunctionType>
		void RegisterCommand(char *szCommand, char *szFormat, FunctionType function)
		{
			// Make sure we're not over the limit
			if(m_byteCommands >= MAX_COMMANDS)
				return;

			// Save the command name
			strcpy(m_szCommand[m_byteCommands], szCommand);
			// Save the command format
			strcpy(m_szFormat[m_byteCommands], szFormat);
			// Save the command function
			m_cmdFunction[m_byteCommands] = reinterpret_cast<CommandFunction_t>(function);
			// Increase commands count
			m_byteCommands++;
		}

	private:
		BYTE					m_byteCommands;
		char					m_szCommand[MAX_COMMANDS][64];
		char					m_szFormat[MAX_COMMANDS][16];
		CommandFunction_t		m_cmdFunction[MAX_COMMANDS];
		//////////////////////////////////////////////////////////
		BYTE					GetCommandId(char *szCommand);
		CommandFunction_t		GetCommandFunction(char *szCommand);

};

#endif