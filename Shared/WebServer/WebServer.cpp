/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: WebServer.cpp
-- Project: Shared
-- Author(s): m0niSx
-- Description: Web Server source file
=============================================================*/

#include "WebServer.h"
#include <stdio.h>

CWebServer::CWebServer(char *szHost, int iPort)
{
	// Reset socket pointer
	m_pSocket = NULL;
	// Save values
	strcpy(m_szHost, szHost);
	m_iPort = iPort;
}

CWebServer::~CWebServer()
{
	// Delete socket class object
	if(m_pSocket)
		delete m_pSocket;
}

bool CWebServer::Initialize(bool bServer)
{
	// Create the socket class instance
	m_pSocket = new CSocket();
	if(!m_pSocket)
		return false;

	printf("setup svr\n");
	// Bind the socket
	if(!m_pSocket->Bind(bServer, m_szHost, m_iPort))
		return false;

	printf("binded\n");
	// Listen to the socket
	if(bServer)
	{
		if(!m_pSocket->Listen(32))
			return false;
	}
	// Save the webserver status
	m_bServer = bServer;
	return true;
}
