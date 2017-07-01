/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ScriptRPCFunctions.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Scripting RPC functions source file
=============================================================*/

#include "Main.h"

extern CClient		*pClient;
extern CGame		*pGame;
extern CChatBox		*pChatBox;

void CScriptRPCFunctions::RegisterFunctions()
{
	// Make sure we have a valid client pointer
	if(!pClient)
		return;

	// Register all the functions
	pClient->RegisterRPCFunction(SendMessage, RPC_SCRIPT_SEND_MESSAGE); 
	pClient->RegisterRPCFunction(SetName, RPC_SCRIPT_SET_NAME);
}

void CScriptRPCFunctions::SendMessage(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get color
	DWORD dwColor = 0x0;
	if(!pBitStream->Read(dwColor))
		return;

	// Get message
	char szMessage[128];
	if(!pBitStream->Read(szMessage))
		return;

	// Display message
	pChatBox->AddMessage(LINE_TYPE_INFO, "", NULL, dwColor, szMessage);
}

void CScriptRPCFunctions::SetName(BitStream *pBitStream, CSenderInfo *pSenderInfo)
{
	// Make sure we have a valid pointers
	if(!pBitStream || !pSenderInfo)
		return;

	// Get playerid
	EntityId playerId;
	if(!pBitStream->Read(playerId))
		return;

	// Get name
	char szName[MAX_NAME_LENGTH];
	if(!pBitStream->Read(szName))
		return;

	// Set the player name
	if(pGame->GetLocalPlayer()->GetId() == playerId)
		pGame->GetLocalPlayer()->SetName(szName);
	else
		pGame->GetPlayerManager()->GetAt(playerId)->SetName(szName);

}



