/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: WebServer.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: Web Server header file
=============================================================*/

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Socket.h"

class CWebServer
{
	public:
		CWebServer(char *szHost, int iPort);
		~CWebServer();

		bool Initialize(bool bServer);

	private:
		bool				m_bServer;
		char				m_szHost[16];
		int					m_iPort;
		CSocket				*m_pSocket;

};

#endif
