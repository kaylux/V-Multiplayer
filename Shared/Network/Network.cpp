/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Network.cpp
-- Project: Shared
-- Author(s): m0niSx
-- Description: Networking source file
=============================================================*/

#include "Network.h"

CNetwork::CNetwork()
{
	// Create the RakPeer instance
	m_pRakPeer = RakPeerInterface::GetInstance();
	// Create function handler instance
	m_pFunctionHandler = new CFunctionHandler();
}

CNetwork::~CNetwork()
{
	// Delete RakPeerInterface instance
	RakPeerInterface::DestroyInstance(m_pRakPeer);
	// Delete function handler instance
	delete m_pFunctionHandler;
}

bool CNetwork::Startup(int iMaxPlayers, int iPort)
{
	// Try to startup raknet
	if(m_pRakPeer->Startup(iMaxPlayers == -1 ? 1 : iMaxPlayers, iMaxPlayers == -1 ? &SocketDescriptor() : &SocketDescriptor(iPort, NULL), 1) != RAKNET_STARTED)
		return false;

	return true;
}

bool CNetwork::Connect(char *szHost, int iPort)
{
	// Try to connect raknet
	if(m_pRakPeer->Connect(szHost, iPort, NULL, NULL) != CONNECTION_ATTEMPT_STARTED)
		return false;

	return true;
}

CReceivedPacket CNetwork::Process()
{
	// Create the receive packet structure
	CReceivedPacket receivedPacket;
	// Try to receive
	Packet *pPacket;
	if((pPacket = m_pRakPeer->Receive()) != 0)
	{
		// Get the packet identifier
		unsigned char ucPacketIdentitfier = GetPacketIdentifier(pPacket);
		// Process packet message id
		switch(ucPacketIdentitfier)
		{
			// On RPC function received
			case ID_VMP_RPC:
				BitStream bitStream(pPacket->data + sizeof(ucPacketIdentitfier), pPacket->length - sizeof(ucPacketIdentitfier), false);
				// Recieve the RPC id
				eRPCFunctions RPCId;
				bitStream.Read(RPCId);
				// Create the bitstream
				BitStream _bitStream;	
				bitStream.Read(&_bitStream);
				// Prepare the sender info structure
				CSenderInfo senderInfo(pPacket);
				// Find the function for the RPC ID
				RPCFunction_t pfn_Function = m_pFunctionHandler->GetFunctionAddressFromId(RPCId);
				// Call the function
				if(pfn_Function != NULL)
					pfn_Function(&_bitStream, &senderInfo);

				break;
		}
		// Set packet structure members
		receivedPacket.pPacket = pPacket;
		receivedPacket.ucPacketIdentifier = ucPacketIdentitfier;
		receivedPacket.bReceived = true;
		return receivedPacket;
	}
	// Set packet structure members
	receivedPacket.bReceived = false;
	return receivedPacket;
}

unsigned char CNetwork::GetPacketIdentifier(Packet *pPacket)
{
	if (pPacket == 0)
		return 255;

	if((unsigned char)pPacket->data[0] == ID_TIMESTAMP)
	{
		RakAssert(pPacket->length > sizeof(MessageID) + sizeof(Time));
		return (unsigned char) pPacket->data[sizeof(MessageID) + sizeof(Time)];
	}
	else
		return (unsigned char) pPacket->data[0];
}

void CNetwork::RegisterRPCFunction(RPCFunction_t function, eRPCFunctions functionId)
{
	// Register the RPC function
	m_pFunctionHandler->RegisterFunction(function, functionId);
}

void CNetwork::RPC(eRPCFunctions functionId, BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel,
				   EntityId playerId, bool bBroadCast)
{
	// Create the bitstream
	BitStream bitStream;
	// Write the send type
	bitStream.Write((BYTE)ID_VMP_RPC);
	// Write the function id 
	bitStream.Write(functionId);
	// Write the function bs data
	bitStream.Write(pBitStream);
	// Send
	m_pRakPeer->Send(&bitStream, priority, reliability, cOrderingChannel, 
		playerId == INVALID_PLAYER_ID ? UNASSIGNED_SYSTEM_ADDRESS : m_pRakPeer->GetSystemAddressFromIndex(playerId), bBroadCast);
}