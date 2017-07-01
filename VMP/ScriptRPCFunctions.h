/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ScriptRPCFunctions.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Scripting RPC functions header file
=============================================================*/

#ifndef SCRIPTRPCFUNCTIONS_H
#define SCRIPTRPCFUNCTIONS_H

class CScriptRPCFunctions
{
	public:
		static void RegisterFunctions();

		/////////////////////////////////////////////////////////////////////////////////
		static void SendMessage(BitStream *pBitStream, CSenderInfo *pSenderInfo);
		static void SetName(BitStream *pBitStream, CSenderInfo *pSenderInfo);


};

#endif