/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Main VMP server header file
=============================================================*/

// RakNet includes
#include <RakPeer.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
// Standard Includes
#ifdef WIN32
#	include <windows.h>
#endif
#include <stdio.h>
// Util includes
#include "Util.h"
#include "Command.h"
// Network includes
#include <Network.h>
#include "Server.h"
#include "RPCFunctions.h"
// WebServer Includes
#include <Socket.h>
#include <WebServer.h>
// Shared Includes
#include <Library.h>
#include <Thread.h>
#include <Common.h>
#include <SharedUtility.h>
#include <Config.h>
#include <Maths.h>
// Managers Includes
#include "PlayerManager.h"
#include "VehicleManager.h"
#include "ModuleManager.h"
#include "ScriptManager.h"
// Entitys Includes
#include "Player.h"
#include "Vehicle.h"
// Modules Includes
#include "Module.h"
// Scripting Includes
#include <LuaInterface.h>
#include "ScriptNatives.h"
#include "PlayerNatives.h"
#include "VehicleNatives.h"
#include "Script.h"