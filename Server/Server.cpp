/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Server.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Server networking source file
=============================================================*/

#include "Main.h"

extern CPlayerManager			*pPlayerManager;
extern CConfig					*pConfig;

CServer::CServer(int iPort, int iMaxPlayers) : CNetwork()
{
	// Save server values
	m_iPort = iPort;
	m_iMaxPlayers = iMaxPlayers;
	// Reset values
	m_bRunning = false;
}

CServer::~CServer()
{
	// Reset values
	m_bRunning = false;
}

bool CServer::StartServer()
{
	// Try to startup raknet
	if(!Startup(m_iMaxPlayers, m_iPort))
		return false;

	// Set maximum players
	GetRakPeer()->SetMaximumIncomingConnections(m_iMaxPlayers);
	// Register RPC functions
	CRPCFunctions::RegisterFunctions();
	// Indicate that we are running
	m_bRunning = true;
	return true;
}

void CServer::ProcessServer()
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
				// Disconnect the player
				pPlayerManager->RemovePlayer((EntityId)receivedPacket.pPacket->systemAddress.systemIndex, LEFT_REASON_QUIT);
				break;

			// On client connect
			case ID_NEW_INCOMING_CONNECTION:
				LogPrintf(true, "Processing connection request from %s", receivedPacket.pPacket->systemAddress.ToString()); 
				break;

			// On client lose connection
			case ID_CONNECTION_LOST:
				// Disconnect the player
				pPlayerManager->RemovePlayer((EntityId)receivedPacket.pPacket->systemAddress.systemIndex, LEFT_REASON_TIMEOUT);
				break;

			// On onfoot sync packet received
			case ID_SYNC_PLAYER:
			{
				// Create the bitstream
				BitStream bitStream(receivedPacket.pPacket->data + sizeof(MessageID), receivedPacket.pPacket->length - sizeof(MessageID), false);
				// Get the sender id
				EntityId playerId = (EntityId)receivedPacket.pPacket->systemAddress.systemIndex;
				// Process the sync
				if(pPlayerManager->IsPlayerConnected(playerId) && pPlayerManager->GetAt(playerId)->IsSpawned())
					pPlayerManager->GetAt(playerId)->StoreSync(&bitStream);

				break;
			}

			// On inevhciel sync packet received
		/*	case ID_SYNC_VEHICLE:
			{
				// Create the bitstream
				BitStream bitStream(receivePacket.pPacket->data, receivePacket.pPacket->length, false);
				// Get the sender id
				EntityId playerId = (EntityId)receivePacket.pPacket->systemAddress.systemIndex;
				// Process the sync
				if(pPlayerManager->IsPlayerConnected(playerId) && pPlayerManager->GetAt(playerId)->IsSpawned())
					pPlayerManager->GetAt(playerId)->StoreVehicleSync(&bitStream);

				break;
			}*/

		}
		// Deallocate the packet
		GetRakPeer()->DeallocatePacket(receivedPacket.pPacket);
	}
}

void CServer::GetName(char *szName)
{
	// Reset the server name
	strcpy(szName, "");
	// Get the server name key values count
	for(BYTE i = 0; i < pConfig->GetValueCount("Server_Name"); i++)
	{
		// Get the key value
		char szValue[64];
		pConfig->GetValueAsString("Server_Name", i, szValue);
		// Add that new value to the name string
		strcat(szName, szValue);
	}
}



