/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: RPCFunctions.h
-- Project: Server
-- Author(s): m0niSx
-- Description: RPC functions header file
=============================================================*/

#ifndef RPCFUNCTIONS_H
#define RPCFUNCTIONS_H

class CRPCFunctions
{
	public:
		static void RegisterFunctions();

		static void ClientJoin(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void SpawnPlayer(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void EnterVehicle(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void ExitVehicle(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void VehicleEntryComplete(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void VehicleExitComplete(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void RemoveFromVehicle(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void ChatMessage(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void Command(BitStream *pBitStream, CSenderInfo *pSenderInfo);

};

#endif