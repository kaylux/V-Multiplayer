/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Server.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Server networking header file
=============================================================*/

#ifndef SERVER_H
#define SERVER_H

class CServer : public CNetwork
{
	public:
		CServer(int iPort, int iMaxPlayers);
		~CServer();

		bool StartServer();
		bool IsRunning() { return m_bRunning; };
		void ProcessServer();
		void GetName(char *szName);

	private:
		bool					m_bRunning;
		int						m_iPort;
		int						m_iMaxPlayers;
		

};

#endif
