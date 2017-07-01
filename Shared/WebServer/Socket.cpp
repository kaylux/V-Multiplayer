/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Socket.cpp
-- Project: Shared
-- Author(s): m0niSx
-- Description: Socket manipulation source file
=============================================================*/

#include "Socket.h"

CSocket::CSocket()
{
	// Create our socket
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	// Failed ?
	if(!m_Socket)
		return;
}

CSocket::CSocket(SOCKET sock, SOCKADDR_IN SocketAddr)
{
	m_Socket = sock;
	m_SocketAddr = SocketAddr;
}

CSocket::~CSocket()
{
	// Close the socket
	closesocket(m_Socket);
}

bool CSocket::Bind(bool bServer, char *szIP, int iPort)
{
	// Setup socket family type
	m_SocketAddr.sin_family = AF_INET;
	// Setup socket IP
	if(bServer)
		m_SocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	else 
		m_SocketAddr.sin_addr.s_addr = inet_addr(szIP);
	// Setup socket port
	m_SocketAddr.sin_port = htons(iPort);
	if(bServer)
	{
		if(bind(m_Socket, (LPSOCKADDR)&m_SocketAddr, sizeof(m_SocketAddr)))
			return false;
	}
	return true;
}

bool CSocket::Listen(int iClients)
{
	// Listen to the sockets
	if(listen(m_Socket, iClients) == SOCKET_ERROR)
		return false;

	return true;
}

CSocket *CSocket::Accept()
{
	SOCKADDR_IN SocketAddr;
	int iLen = sizeof(SocketAddr);
	// Accept the incoming connection
	SOCKET Socket = accept(m_Socket, (LPSOCKADDR)&SocketAddr, &iLen);
	// Accepting error
	if(!Socket)
		return NULL;
	// create the socket class
	CSocket *pSocket = new CSocket(Socket, SocketAddr);
	// Return the socket class
	return pSocket;
}

int CSocket::GetHost(char *szHost)
{
	strcpy(szHost, inet_ntoa(m_SocketAddr.sin_addr));
	return htons(m_SocketAddr.sin_port);
}

bool CSocket::Connect()
{
	int	iConnect = connect(m_Socket, (const LPSOCKADDR)&m_SocketAddr, sizeof(m_SocketAddr));
	if(iConnect == SOCKET_ERROR)
		return false;

	return true;
}

int CSocket::Send(const char *szBuffer, int iLen, char *szIP, int iPort)
{
	if(iPort != -1)
		Bind(false, szIP, iPort);

	int iBytesSended = sendto(m_Socket, szBuffer, iLen, NULL, (const sockaddr *)&m_SocketAddr, sizeof(m_SocketAddr));
	if(iBytesSended == SOCKET_ERROR)
		return -1;

	return iBytesSended;
}

int CSocket::Receive(char *szBuffer, int iLen)
{
	int iSize = sizeof(m_SocketAddr);
	int iBytesRecv = recvfrom(m_Socket, szBuffer, iLen, NULL, (sockaddr *)&m_SocketAddr, &iSize);
	if(iBytesRecv == SOCKET_ERROR)
		return -1;

	// Return
	return iBytesRecv;
}

