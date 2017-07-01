/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Main VMP client header file
=============================================================*/

#define DIRECTINPUT_VERSION DIRECTINPUT_HEADER_VERSION // No "DIRECTINPUT_VERSION undefined. Defaulting to version 0x0800" warning

// RakNet includes
#include <RakPeer.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>
#include <GetTime.h>
// Standard Includes
#include <windows.h>
#include <stdio.h>
// Detours Includes
#include <Detours.h>
// SharedUtility Includes
#include <Common.h>
#include <Maths.h>
#include <Config.h>
// V Includes
#include "VModel.h"
#include "VBlipInfo.h"
#include "VEvent.h"
#include "VPlayerInfo.h"
#include "VPlayerPed.h"
#include "VThread.h"
#include "VWorld.h"
#include "VWeapon.h"
#include "VPad.h"
#include "VPoolBase.h"
#include "VVehicleInfo.h"
#include "VGTAVector.h"
// Game Includes
#include "Game.h"
#include "Address.h"
#include "LocalPlayer.h"
#include "PlayerPed.h"
#include "PlayerInfo.h"
#include "BlipInfo.h"
#include "VehicleInfo.h"
#include "GameThread.h"
#include "Model.h"
#include "Entity.h"
#include "Pad.h"
#include "GameUtils.h"
#include "Pools.h"
#include "Task.h"
#include "Patches.h"
#include "ComplexTasks.h"
#include "SimpleTasks.h"
// DirectX Hooks
#include "Direct3D9.h"
#include "Direct3Device9.h"
// DirectInput Hooks
#include "DirectInput8.h"
#include "DirectInput8Device.h"
// DirectX rendering includes
#include "Font.h"
#include "ChatBox.h"
#include "ChatInput.h"
#include "NameTags.h"
// GUI Includes
#include "GameGui.h"
#include "MainMenu.h"
// Hooks Includes
#include "Hooks.h"
#include "GameHooks.h"
#include "SyncHooks.h"
#include "XliveHook.h"
// Netork Includes
#include <Network.h>
#include "Client.h"
#include "RPCFunctions.h"
#include "ScriptRPCFunctions.h"
#include "Player.h"
#include "Blip.h"
// Util Includes
#include "Util.h"
#include "ExceptionHandler.h"

// Window callback
void SubclassGameWindow(HWND hGameWindow);