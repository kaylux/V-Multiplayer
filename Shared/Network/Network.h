/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Network.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: Networking header file
=============================================================*/

#ifndef NETWORK_H
#define NETWORK_H

// RakNet includes
#include <RakPeer.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
// Network include
#include "SenderInfo.h"
#include "ReceivedPacket.h"
#include "FunctionHandler.h"

using namespace RakNet;

class CNetwork
{
	public:
		CNetwork();
		~CNetwork();

		bool Startup(int iMaxPlayers, int iPort);
		bool Connect(char *szHost, int iPort);
		CReceivedPacket Process();

		/////////////////////////////////////////////////////
		void RegisterRPCFunction(RPCFunction_t function, eRPCFunctions functionId);
		void RPC(eRPCFunctions functionId, BitStream *pBitStream, PacketPriority priority, PacketReliability reliability, char cOrderingChannel, EntityId playerId, bool bBroadCast);

		/////////////////////////////////////////////////////
		RakPeerInterface *GetRakPeer() { return m_pRakPeer; };

	private:
		unsigned char			GetPacketIdentifier(Packet *pPacket);
		RakPeerInterface		*m_pRakPeer;
		///////////////////////////////////////////////////
		CFunctionHandler		*m_pFunctionHandler;
		

};

#endif
