/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Client.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Client networking source file
=============================================================*/

#include "Main.h"

extern CChatBox			*pChatBox;
extern CGame			*pGame;

CClient::CClient(char *szHost, int iPort) : CNetwork()
{
	// Save server values
	m_iPort = iPort;
	strcpy(m_szHost, szHost);
	// Set game stat
	m_networkState = NET_STATE_STARTUP;
	// Set the last tick
	m_dwLastTick = GetTickCount();

}

CClient::~CClient()
{
	// Set network state to disconnected
	m_networkState = NET_STATE_DISCONNECT;
	// Shutdown the client
	GetRakPeer()->Shutdown(300);
}

bool CClient::StartClient()
{
	// Verify we need startup
	if(m_networkState != NET_STATE_STARTUP)
		return false;

	// Try to startup raknet
	if(!Startup(-1, m_iPort))
		return false;

	// Set game state
	m_networkState = NET_STATE_WAIT_CONNECT;
	// Register PPC functions
	CRPCFunctions::RegisterFunctions();
	// Register scripting functions
	CScriptRPCFunctions::RegisterFunctions();
	return true;
}

void CClient::ProcessClient()
{
	// Do we need connection request
	if(m_networkState == NET_STATE_WAIT_CONNECT)
	{
		if((GetTickCount() - m_dwLastTick) > RECONNECT_TIME)
		{
			pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, 0xFFFFFFFF, "Connecting to %s:%d ...", m_szHost, m_iPort);
			// Send a connection request
			if(Connect(m_szHost, m_iPort))
				// Send network state
				m_networkState = NET_STATE_CONNECTING;
			else
			{
				// Add the failed message
				pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, 0xFFFFFFFF, "Connection request sending failed. Retrying ...");
				// Set the last tick
				m_dwLastTick = GetTickCount();
			}
		}
	}
	// Do we need to start receiving ?
	if(m_networkState == NET_STATE_CONNECTING || m_networkState == NET_STATE_JOINING || m_networkState == NET_STATE_PLAYING)
	{
		// Process the network
		CReceivedPacket receivedPacket = Process();
		if(receivedPacket.bReceived)
		{
			// Process packet message id
			switch(receivedPacket.ucPacketIdentifier)
			{
				// On client disconnect
				case ID_DISCONNECTION_NOTIFICATION:
					// Add message
					pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, D3DCOLOR_ARGB(255, 200, 0, 0), "You have been disconnected");
					// Set network state to disconnected
					m_networkState = NET_STATE_DISCONNECT;
					break;

				// If the connection is banned
				case ID_CONNECTION_BANNED:
					// Add message
					pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, D3DCOLOR_ARGB(255, 200, 0, 0), "You have been banned from this server");
					// Set network state to disconnected
					m_networkState = NET_STATE_DISCONNECT;
					break;

				// If the password is wrong
				case ID_INVALID_PASSWORD:
					// Add message
					pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, D3DCOLOR_ARGB(255, 200, 0, 0), "Wrong server password");
					// Set network state to disconnected
					m_networkState = NET_STATE_DISCONNECT;
					break;

				// On connection attempt failed
				case ID_CONNECTION_ATTEMPT_FAILED:
					// Add message
					pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, 0xFFFFFFFF, "Connection attempt failed. Retrying ...");
					// Set network state to disconnected
					m_networkState = NET_STATE_WAIT_CONNECT;
					// Set the last tick
					m_dwLastTick = GetTickCount();
					break;

				// If the server is full
				case ID_NO_FREE_INCOMING_CONNECTIONS:
					// Add message
					pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, 0xFFFFFFFF, "Server is full. Retrying ...");
					// Set network state to waiting connection
					m_networkState = NET_STATE_WAIT_CONNECT;
					// Set the last tick
					m_dwLastTick = GetTickCount();
					break;

				// On connection attempt succeeds
				case ID_CONNECTION_REQUEST_ACCEPTED:
					// Add message
					pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, 0xFFFFFFFF, "Connection attempt succeeded. Joining ...");
					// Join
					Join();
					break;

				// On client lose connection
				case ID_CONNECTION_LOST:
					Reconnect();
					break;

				// On onfoot sync packet received
				case ID_SYNC_PLAYER:
				{
					// Create the bitstream
					BitStream bitStream(receivedPacket.pPacket->data, receivedPacket.pPacket->length, false);
					MessageID msg;
					bitStream.Read((MessageID)msg);
					// Read the player id
					EntityId playerId = INVALID_PLAYER_ID;
					if(!bitStream.Read((EntityId)playerId))
						break;
				
					// Make sure the player is valid
					if(pGame->GetPlayerManager()->IsPlayerConnected(playerId))
						// Process the player sync
						pGame->GetPlayerManager()->GetAt(playerId)->Sync(&bitStream);

					break;
				}

				/*// On invehicle sync packet received
				case ID_SYNC_VEHICLE:
				{
					// Create the bitstream
					BitStream bitStream(receivePacket.pPacket->data, receivePacket.pPacket->length, false);
					// Read message id (ID_SYNC_VEHICLE)
					MessageID message;
					bitStream.Read(message);
					// Read the player id
					EntityId playerId = INVALID_PLAYER_ID;
					if(!bitStream.Read(playerId))
						break;
				
					// Make sure the player is valid
					if(!pGame->GetPlayerManager()->IsPlayerConnected(playerId))
						break;

					// Get the player vehicle id
					EntityId vehicleId = pGame->GetPlayerManager()->GetAt(playerId)->GetVehicleId();
					if(vehicleId == INVALID_VEHICLE_ID)
						break;

					// Process the vehicle sync
					pGame->GetVehicleManager()->GetAt(vehicleId)->Sync(&bitStream);
					break;
				}*/
			}
			// Deallocate the packet
			GetRakPeer()->DeallocatePacket(receivedPacket.pPacket);
		}
	}
}

void CClient::Reconnect()
{
	// Add message
	pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, 0xFFFFFFFF, "Connection lost. Reconnecting ...");
	// Set last tick
	m_dwLastTick = GetTickCount();
	// Set network state to wait connection attempt
	m_networkState = NET_STATE_WAIT_CONNECT;
}

void CClient::Join()
{
	// Set network state
	m_networkState = NET_STATE_JOINING;
	// Get local player name
	char szName[MAX_NAME_LENGTH];
	pGame->GetLocalPlayer()->GetName(szName);
	// Send RPC to the server
	BitStream bitStream;
	bitStream.Write(szName);
	RPC(RPC_CLIENT_JOIN, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
}

