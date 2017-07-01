/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Common.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: General common definitions header file
=============================================================*/

#ifndef COMMON_H
#define COMMON_H


// Server Defines
#define LOG_FILE			"Server/Server_Log.txt"
#define ERROR_FILE			"Server/Server_Dump.txt"
#define CONFIG_FILE			"Server/Server_Settings.ini"
#define MAX_MODULES			8
#define MAX_SCRIPTS			16
#define MAX_EVENT_FUNCTIONS	10

// General defines
#define VERSION				"0.1 Alpha 1"
#define MAX_PLAYERS			32
#define MAX_VEHICLES		32

#define MAX_NAME_LENGTH		32
#define MAX_INPUT_MESSAGE	128

#define INVALID_PLAYER_ID	255
#define INVALID_VEHICLE_ID	255

// Macros
#define SAFE_DELETE(ptr) if(ptr) { delete ptr; ptr = NULL; }
#define SAFE_RELEASE(ptr) if(ptr) { ptr->Release(); }
#define PAD(a, b) char a[b]

// EntityId type
typedef unsigned short EntityId;

// Player state enumeration
enum ePlayerState
{
	PLAYER_STATE_NOTSPAWNED,
	PLAYER_STATE_ONFOOT,
	PLAYER_STATE_ENTERING_VEHICLE,
	PLAYER_STATE_INVEHICLE,
	PLAYER_STATE_EXITING_VEHICLE,
	PLAYER_STATE_DISCONNECTED,
};

#endif