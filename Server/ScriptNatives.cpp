/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ScriptNatives.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Script natives source file
=============================================================*/

#include "Main.h"

extern CLuaInterface			*pLuaInterface;
extern CServer					*pServer;

void CScriptNatives::RegisterNatives()
{
	lua_register(pLuaInterface->GetVM(), "printf", Printf);
	lua_register(pLuaInterface->GetVM(), "split", SplitF);
	lua_register(pLuaInterface->GetVM(), "registerEvent", RegisterEvent);
	lua_register(pLuaInterface->GetVM(), "unregisterEvent", UnregisterEvent);
	lua_register(pLuaInterface->GetVM(), "sendMessageToAll", SendMessageToAll);
}

void CScriptNatives::RegisterSecurityNatives()
{
	// Register disabled functions to our disabled natives
	lua_register(pLuaInterface->GetVM(), "dofile", DisabledSecurityFunction);
	lua_register(pLuaInterface->GetVM(), "loadfile", DisabledSecurityFunction);
	lua_register(pLuaInterface->GetVM(), "require", DisabledSecurityFunction);
	lua_register(pLuaInterface->GetVM(), "loadlib", DisabledSecurityFunction);
	lua_register(pLuaInterface->GetVM(), "getfenv", DisabledSecurityFunction);
	lua_register(pLuaInterface->GetVM(), "newproxy", DisabledSecurityFunction);
}

int CScriptNatives::DisabledSecurityFunction(lua_State *pVM)
{
	LogPrintf(true, "Disabled function was called");
	lua_pushboolean(pVM, false);
	return 1;
}

int CScriptNatives::Printf(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "printf", "s"))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}	
	// Get the argument
	const char *szText = lua_tostring(pVM, 1);
	// Make sure its valid
	if(szText != NULL)
		LogPrintf(true, (char *)szText);

	return 1;
}

int CScriptNatives::SplitF(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "split", "ssn"))
	{
		// Return failed
		lua_pushstring(pVM, "");
		return 1;
	}	
	// Get the string
	const char *szText = lua_tostring(pVM, 1);
	// Get the split
	const char *szSplit = lua_tostring(pVM, 2);
	// Get the index
	int iIndex = lua_tointeger(pVM, 3);
	// Split
	char *szSplitText = (char *)malloc(strlen(szText));
	int iSplitIndex = Split((char *)szText, szSplitText, (char *)szSplit, iIndex);
	// Return
	lua_pushstring(pVM, szSplitText);
	lua_pushnumber(pVM, iSplitIndex);
	// Free the allocated memory for the string
	free(szSplitText);
	return 2;
}

int CScriptNatives::RegisterEvent(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "registerEvent", "ss"))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get the event name
	const char *szEvent = lua_tostring(pVM, 1);
	// Get the function name
	const char *szFunction = lua_tostring(pVM, 2);
	// Register the function
	pLuaInterface->GetEventManager()->RegisterEvent((char *)szEvent, (char *)szFunction);
	// Return succeeded
	lua_pushboolean(pVM, true);
	return 1;
}

int CScriptNatives::UnregisterEvent(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "unregisterEvent", "ss"))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get the event name
	const char *szEvent = lua_tostring(pVM, 1);
	// Get the function name
	const char *szFunction = lua_tostring(pVM, 2);
	// Register the function
	pLuaInterface->GetEventManager()->UnregisterEvent((char *)szEvent, (char *)szFunction);
	// Return succeeded
	lua_pushboolean(pVM, true);
	return 1;
}

int CScriptNatives::SendMessageToAll(lua_State *pVM)
{
	// Check argument type
	if(!pLuaInterface->CheckFunctionType(pVM, "sendMessageToAll", "ns"))
	{
		// Return failed
		lua_pushboolean(pVM, false);
		return 1;
	}
	// Get color
	DWORD dwColor = (DWORD)lua_tonumber(pVM, 1);
	// Get the message
	const char *szMessage = lua_tostring(pVM, 2);
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
	if(pServer)
		pServer->RPC(RPC_SCRIPT_SEND_MESSAGE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);

	// Return succeeded
	lua_pushboolean(pVM, true);
	return 1;
}