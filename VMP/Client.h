/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Client.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Client networking header file
=============================================================*/

#ifndef CLIENT_H
#define CLIENT_H

enum eNetworkState
{
	NET_STATE_STARTUP,
	NET_STATE_WAIT_CONNECT,
	NET_STATE_CONNECTING,
	NET_STATE_JOINING,
	NET_STATE_PLAYING,
	NET_STATE_DISCONNECT,
};

#define RECONNECT_TIME 3500 // 3.5 seconds

class CClient : public CNetwork
{
	public:
		CClient(char *szHost, int iPort);
		~CClient();

		bool StartClient();
		void ProcessClient();
		void Reconnect();
		void Join();
		inline eNetworkState GetNetworkState() { return m_networkState; };
		inline void SetNetworkState(eNetworkState networkState) { m_networkState = networkState; };

	private:
		DWORD					m_dwLastTick;
		eNetworkState			m_networkState;
		int						m_iPort;
		char					m_szHost[16];
		
};

#endif