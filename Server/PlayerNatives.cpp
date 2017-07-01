/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerNatives.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Player script natives source file
=============================================================*/

#include "Main.h"

extern CLuaInterface			*pLuaInterface;
extern CPlayerManager			*pPlayerManager;
extern CServer					*pServer;

void CPlayerNatives::RegisterNatives()
{
	lua_register(pLuaInterface->GetVM(), "isPlayerConnected", IsConnected);
	lua_register(pLuaInterface->GetVM(), "sendPlayerMessage", SendMessage);
	lua_register(pLuaInterface->GetVM(), "setPlayerName", SetName);
	lua_register(pLuaInterface->GetVM(), "getPlayerName", GetName);
}

int CPlayerNatives::IsConnected(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "isPlayerConnected", "n"))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get the player id
	EntityId playerId = lua_tointeger(pVM, 1);
	// Push the return value
	lua_pushboolean(pVM, pPlayerManager->IsPlayerConnected(playerId));
	return 1;
}

int CPlayerNatives::SendMessage(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "sendPlayerMessage", "nns"))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get the player id
	EntityId playerId = lua_tointeger(pVM, 1);
	if(!pPlayerManager->IsPlayerConnected(playerId))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get color
	DWORD dwColor = (DWORD)lua_tonumber(pVM, 2);
	// Get the message
	const char *szMessage = lua_tostring(pVM, 3);
	// Make sure the message is valid
	if(strlen(szMessage) == 0 || strlen(szMessage) > MAX_INPUT_MESSAGE)
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Send the AddMessage RPC
	BitStream bitStream;
	bitStream.Write(dwColor);
	bitStream.Write(szMessage);
	pServer->RPC(RPC_SCRIPT_SEND_MESSAGE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, playerId, false);
	// Return succeeded
	lua_pushboolean(pVM, true);
	return 1;
}

int CPlayerNatives::SetName(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "setPlayerName", "ns"))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get the player id
	EntityId playerId = lua_tointeger(pVM, 1);
	if(!pPlayerManager->IsPlayerConnected(playerId))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get the message
	const char *szName = lua_tostring(pVM, 2);
	// Make sure the player name is valid
	if(strlen(szName) < 3 || strlen(szName) > MAX_NAME_LENGTH || !pPlayerManager->IsNameExists((char *)szName))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Set the player name
	pPlayerManager->GetAt(playerId)->SetName((char *)szName);
	// Return succeeded
	lua_pushboolean(pVM, true);
	return 1;
}

int CPlayerNatives::GetName(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "getPlayerName", "n"))
	{
		// Return failed
		lua_pushstring(pVM, "");
		return 1;
	}
	// Get the player id
	EntityId playerId = lua_tointeger(pVM, 1);
	if(!pPlayerManager->IsPlayerConnected(playerId))
	{
		// Return failed
		lua_pushstring(pVM, "");
		return 1;
	}
	// Get the player name
	char szName[MAX_NAME_LENGTH];
	pPlayerManager->GetAt(playerId)->GetName(szName);
	// Return succeeded
	lua_pushstring(pVM, szName);
	return 1;
}