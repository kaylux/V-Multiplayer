/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Socket.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: Socket manipulation header file
=============================================================*/

#ifndef SOCKET_H
#define SOCKET_H

#ifdef WIN32
#	include <windows.h>
#else
#	include <sys/types.h>
#	include <sys/socket.h>
#	include <netdb.h>
#	define closesocket close
#endif

class CSocket
{
	public:
		CSocket();
		CSocket(SOCKET sock, SOCKADDR_IN SocketAddr);
		~CSocket();

		bool Bind(bool bServer, char *szIP, int iPort);
		bool Listen(int iClients);
		int GetHost(char *szHost);
		CSocket *Accept();
		bool Connect();
		int Send(const char *szBuffer, int iLen, char *szIP, int iPort);
		int Receive(char *szBuffer, int iLen);

		SOCKET GetSocket() { return m_Socket; };

	private:
		SOCKET			m_Socket;
		SOCKADDR_IN		m_SocketAddr;
};

#endif
