/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: SenderInfo.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: CSenderInfo class header file
=============================================================*/

#ifndef SENDERINFO_H
#define SENDERINFO_H

#include "Common.h"

class CSenderInfo
{
	public:
		CSenderInfo()
		{
			m_senderId = INVALID_PLAYER_ID;
			m_systemAddress = NULL;
		};
		CSenderInfo(RakNet::Packet *pPacket)
		{
			m_senderId = (EntityId)pPacket->systemAddress.systemIndex;
			m_systemAddress = pPacket->systemAddress;
		};
		/////////////////////////////////////////////////////////
		EntityId GetSenderId() { return m_senderId; };
		RakNet::SystemAddress GetSystemAddress() { return m_systemAddress; };

	private:
		EntityId					m_senderId;
		RakNet::SystemAddress		m_systemAddress;

};

#endif
		