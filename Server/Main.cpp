/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Main VMP server source file
=============================================================*/


#include "main.h"

CConfig				*pConfig;
CServer				*pServer;
CCommand			*pCommand;
//////////////////////////////////
CPlayerManager		*pPlayerManager;
CVehicleManager		*pVehicleManager;
CModuleManager		*pModuleManager;
CScriptManager		*pScriptManager;
//////////////////////////////////
CLuaInterface		*pLuaInterface;
//////////////////////////////////
CWebServer			*pWebServer;

int ii = 1;

// Commands Thread
void CommandThread(void *pThread);

void KickCommand(int iEntityId, char *szName, int iIdiot)
{
	LogPrintf(true, "kicking player %d - name: %s - idiot: %d", iEntityId, szName, iIdiot);
}

void BanCommand(int iEntityId)
{
	LogPrintf(true, "banning player %d", iEntityId);
}

void PlayerCommand()
{
	char szName[32];
	sprintf(szName, "player_%d", ii);
	pPlayerManager->AddPlayer(ii, szName);
	pPlayerManager->GetAt(ii)->SpawnForWorld();
	ii++;
}

void SayCommand(char *szText)
{
	char szName[MAX_NAME_LENGTH];
	strcpy(szName, "Admin");
	char szMessage[MAX_INPUT_MESSAGE];
	strcpy(szMessage, szText);
	// Send the clients the message
	BitStream bitStream;
	bitStream.Write(szName);
	bitStream.Write(szMessage);
	pServer->RPC(RPC_CHAT_MESSAGE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
	LogPrintf(true, "[CHAT] Admin: %s", szMessage);
}

int main(void)
{
	LogPrintf(true, "-------------------------------------");
	LogPrintf(true, "V:MP " VERSION " Dedicated Server");
	LogPrintf(true, "Build: " __DATE__ " - " __TIME__);
	LogPrintf(true, "Author(s): V:MP Team");
	LogPrintf(true, "Copyright (C) V:MP Team");
	LogPrintf(true, "-------------------------------------");
	LogPrintf(true, "");
	LogPrintf(false, "Loading config file ...");
	// Create config class object
	pConfig = new CConfig(CONFIG_FILE);
	// Read the file
	if(!pConfig || !pConfig->Initialize())
	{
		LogPrintf(true, " Failed.");
		ErrorExit("Failed to initialize the config file");
	}
	// Get values from config file
	int iPort = -1, iMaxPlayers = -1;
	bool bLan = false;
	bLan = pConfig->GetValueAsBoolean("Lan", 0);
	if((iMaxPlayers = pConfig->GetValueAsInteger("Max_Players", 0)) == -1 || (iPort = pConfig->GetValueAsInteger("Port", 0)) == -1)
	{
		LogPrintf(true, " Failed.");
		ErrorExit("Failed to read config values");
	}
	LogPrintf(true, " Done");
	LogPrintf(true, "");
	// Create manager class instances
	pPlayerManager = new CPlayerManager();
	pVehicleManager = new CVehicleManager();
	pModuleManager = new CModuleManager();
	pScriptManager = new CScriptManager();
	// Create lua interface
	pLuaInterface = new CLuaInterface();
	if(!pLuaInterface || !pLuaInterface->Initialize())
		ErrorExit("Failed to create the LUA interface");

	// Register script natives
	CScriptNatives::RegisterNatives();
	CPlayerNatives::RegisterNatives();
	CVehicleNatives::RegisterNatives();	
	// Set lua logging function
	pLuaInterface->SetLogFunction(LuaLog);
	// Initiliaze lua security
	CScriptNatives::RegisterSecurityNatives();
	// Load modules
	pModuleManager->LoadModules();
	// Load scripts
	pScriptManager->LoadScripts();
	/*// Get the webserver port from the config file
	int iWebPort = pConfig->GetValueAsInteger("WebServer_Port", 0);
	if(iWebPort > 0)
	{
		LogPrintf(true, "Starting web server on %d ...", iWebPort);
		// Create WebServer class instance
		pWebServer = new CWebServer("", iWebPort);
		// Initialize the web server
		if(!pWebServer->Initialize(true))
		{
			SAFE_DELETE(pWebServer);
			LogPrintf(true, "Failed to create the web server");
		}
		else
			LogPrintf(true, "Web Server successfully started");

		LogPrintf(true, "");
	}*/
	/*pVehicleManager->AddVehicle(0, 3, CVector3(-341.36f, 1149.80f, 14.79f));
	pVehicleManager->AddVehicle(1, 3, CVector3(-341.36f, 1135.80f, 14.79f));*/
	// Start the server
	LogPrintf(false, "Starting server on port %d (LAN: %s) ...", iPort, bLan ? "ON" : "OFF");
	// Create network class instance
	pServer = new CServer(iPort, iMaxPlayers);
	if(!pServer || !pServer->StartServer())
	{
		LogPrintf(true, " Failed");
		ErrorExit("Failed to start the server on port %d", iPort);
	}
	LogPrintf(true, " Done.");
	LogPrintf(true, "");
	LogPrintf(true, "");
	// Create the command class instance
	pCommand = new CCommand();
	// Register command functions
	// TODO: Create the CCommandFunction class
	pCommand->RegisterCommand("/kick", "isi", KickCommand);
	pCommand->RegisterCommand("/ban", "i", BanCommand);
	pCommand->RegisterCommand("/say", "s", SayCommand);
	pCommand->RegisterCommand("/player", "", PlayerCommand);
	// Create the command thread class instance
	CThread *pCommandThread = new CThread(CommandThread);
	// Start the thread
	if(!pCommandThread || !pCommandThread->Start())
		ErrorExit("Failed to start the commands thread");

	// Process the server
	while(pServer->IsRunning())
	{
		// Process the server
		pServer->ProcessServer();
		// Process the player manager
		pPlayerManager->Process();
		// Process modules pulse
		pModuleManager->Pulse();
		Sleep(5);
	}
	// Delete command thread class instance
	SAFE_DELETE(pCommandThread);
	// Delete class instances
	SAFE_DELETE(pConfig);
	SAFE_DELETE(pServer);
	SAFE_DELETE(pCommand);
	SAFE_DELETE(pPlayerManager);
	SAFE_DELETE(pVehicleManager);
	SAFE_DELETE(pModuleManager);
	SAFE_DELETE(pScriptManager);
	SAFE_DELETE(pLuaInterface);
	return 1;
}

void CommandThread(void *pThread)
{
	// Keep alive until we exit
	while(pServer->IsRunning())
	{
		// Get the command
		char szCommand[256];
		gets(szCommand);
		// Process the command
		pCommand->Process(szCommand);
		Sleep(5);
	}
}