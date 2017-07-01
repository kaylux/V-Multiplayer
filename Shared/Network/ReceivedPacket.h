/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ReceivedPacket.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: CReceivedPacket class header file
=============================================================*/

#ifndef RECEIVEDPACKET_H
#define RECEIVEDPACKET_H

#include "Common.h"

class CReceivedPacket
{
	public:
		bool				bReceived;
		unsigned char		ucPacketIdentifier;
		RakNet::Packet		*pPacket;
};

#endif