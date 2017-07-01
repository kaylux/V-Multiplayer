/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: FunctionsIdentifiers.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: RPC functions identifiers header file
=============================================================*/

#ifndef FUNCTIONIDENTIFIERS_H
#define FUNCTIONIDENTIFIERS_H

#define	MAX_FUNCTIONS 250

enum eRPCFunctions
{
	RPC_JOIN_ACCEPTED,
	RPC_JOIN_REJECTED,
	RPC_CLIENT_JOIN,
	RPC_NEW_PLAYER,
	RPC_DELETE_PLAYER,
	RPC_NEW_VEHICLE,
	RPC_DELETE_VEHICLE,
	RPC_SPAWN_PLAYER,
	RPC_CHAT_MESSAGE,
	RPC_COMMAND,
	RPC_ENTER_VEHICLE,
	RPC_EXIT_VEHICLE,
	RPC_VEHICLE_ENTRY_COMPLETE,
	RPC_VEHICLE_EXIT_COMPLETE,
	RPC_REMOVE_FROM_VEHICLE,

	// Scripting natives
	RPC_SCRIPT_SEND_MESSAGE,
	RPC_SCRIPT_SET_NAME
};

#endif