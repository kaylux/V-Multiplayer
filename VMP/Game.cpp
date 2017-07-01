/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Game.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: VMP client game source file
=============================================================*/

#include "Main.h"

CChatBox				*pChatBox;
CChatInput				*pChatInput;
CClient					*pClient;

extern CConfig			*pConfig;

CGame::CGame()
{
	// Reset pointers
	m_pLocalPlayer = NULL;
	m_pPlayerManager = NULL;
	m_pVehicleManager = NULL;
	m_pGameGui = NULL;
	m_pMainMenu = NULL;
	m_pNameTags = NULL;
	m_pPad = NULL;
	m_pActiveThread = NULL;
	m_pDevice = NULL;
	// Enable keys by default
	m_bKeys = true;
	m_bInVehicle = false;
	// Get the game base address
	m_dwBaseAddress = (DWORD)GetModuleHandle(NULL);
	m_dwBaseAddress -= 0x400000;
	// Reset the HWND
	m_hWnd = NULL;
	// Set the game state to default
	m_gameState = GAME_STATE_LOADING_SCREEN;
}

CGame::~CGame()
{
	// Delete the chatbox instance
	SAFE_DELETE(pChatBox);
	// Delete the chatinput instance
	SAFE_DELETE(pChatInput);
	// Delete the network instance
	SAFE_DELETE(pClient);
	// Delete the managers instances
	SAFE_DELETE(m_pPlayerManager);
	SAFE_DELETE(m_pVehicleManager);
	// Delete the local player instance
	SAFE_DELETE(m_pLocalPlayer);
	// Delete the Pad instance
	SAFE_DELETE(m_pPad);
	// Delete the game thread instance
	SAFE_DELETE(m_pActiveThread);
	// Delete MainMenu instance
	SAFE_DELETE(m_pMainMenu);
	// Delete the nametags instance
	SAFE_DELETE(m_pNameTags);
	// Delete the GUI instance
	SAFE_DELETE(m_pGameGui);
}

void CGame::InitGame()
{
	// Init addresses
	CAddress::Initialize(m_dwBaseAddress);
	// Install ingame hooks
	CGameHooks::InstallGameHooks();
	// Install sync hooks
	CSyncHooks::InstallSyncHooks();
	// Install Patches
	CPatches::InstallPatches();
	// Intitialize Pad
	m_pPad = new CPad((CVPad *)CAddress::VAR_Pad);
	// Initialize game thread
	CVThread *pThread = new CVThread;
	memset(pThread, 0, sizeof(CVThread));
	m_pActiveThread = new CGameThread(pThread);
}

void CGame::InitializeInGame(unsigned int uiLocalPlayerIndex)
{
	// Create managers instances
	m_pPlayerManager = new CPlayerManager();
	m_pVehicleManager = new CVehicleManager();
	// Create the local player instance
	char szName[MAX_NAME_LENGTH];
	pConfig->GetValueAsString("Name", 0, szName);
	m_pLocalPlayer = new CLocalPlayer(szName);
	// Make sure the local player instance is created
	if(m_pLocalPlayer)
	{
		// Set local player game id
		m_pLocalPlayer->SetGameId(uiLocalPlayerIndex);
		// Set the local player info
		CVPlayerInfo *pPlayerInfo = CGameUtils::GetPlayerInfoFromIndex(uiLocalPlayerIndex);
		m_pLocalPlayer->GetPlayerInfo()->SetHandler(pPlayerInfo);
		// Set the local player ped
		m_pLocalPlayer->GetPlayerPed()->SetHandler(pPlayerInfo->pPlayerPed);

		m_pLocalPlayer->GetPlayerInfo()->DisableSprint(true);
		// Set the model handler
		CModel *pModel = new CModel(PLAYER_MODEL_INDEX);
		m_pLocalPlayer->GetPlayerPed()->SetModelHandler(pModel);
	}
	// Set the maximum wanted level
	/*SetMaxWantedLevel(0);
	// Hide the game HUD
	DisplayHUD(false);
	// Hide the game radar
	DisplayRadar(false);*/
	// Start the network
	StartNetwork();
}

void CGame::SetupDevice(IDirect3DDevice9 *pDevice)
{
	// Save the device pointer
	m_pDevice = pDevice;
	// Create ChatBox class instance
	pChatBox = new CChatBox(pDevice);
	// Create ChatInput class instance
	pChatInput = new CChatInput(pDevice);
	// Create the nametags instance
	m_pNameTags = new CNameTags(pDevice);
	// Create the GUI instance
	m_pGameGui = new CGameGui(pDevice);
	// Create Main Menu instance
	m_pMainMenu = new CMainMenu();
}

void CGame::SetupNetwork(char *szHost, int iPort)
{
	// Create the network instance
	pClient = new CClient(szHost, iPort);
}

void CGame::StartNetwork()
{
	// Try to start the client
	if(!pClient->StartClient())
	{
		Log("Failed to start the network");
		ExitProcess(0);
	}
}

void CGame::InitializeGUI()
{
	// Initialize GUI
	if(!m_pGameGui || !m_pGameGui->Initialize(m_hWnd))
	{
		Log("Failed to initialize GUI");
		ExitProcess(0);
	}
	// Initialize MainMenu
	if(!m_pMainMenu || !m_pMainMenu->Initialize())
	{
		Log("Failed to initialize Main Menu");
		ExitProcess(0);
	}
}

void CGame::ProcessVehicleEntry()
{
	// Is the ENTER key pressed ?
	if(GetAsyncKeyState(VK_F6) == -32767)//if(m_pPad->IsControlJustPressed(PAD_ENTER))
		// Process vehicle entry and exit
		m_pLocalPlayer->HandleVehicleEntryAndExit(false);

}

void CGame::Fade(unsigned int uiTime, eFadeType fadeType)
{
	DWORD dwFadeHandle = NULL;
	// Create the screen fade from type
	if(fadeType == FADE_TYPE_IN)
	{
		_asm
		{
			push uiTime
			mov ecx, CAddress::VAR_CameraPool
			call CAddress::FUNC_CCameraPool__CreateScreenFadeIn
			mov dwFadeHandle, eax
		}
	}
	else if(fadeType == FADE_TYPE_IN_UNHACKED)
	{
		_asm
		{
			push uiTime
			mov ecx, CAddress::VAR_CameraPool
			call CAddress::FUNC_CCameraPool__CreateScreenFadeInUnhacked
			mov dwFadeHandle, eax
		}
	}
	else if(fadeType == FADE_TYPE_OUT)
	{
		_asm
		{
			push uiTime
			mov ecx, CAddress::VAR_CameraPool
			call CAddress::FUNC_CCameraPool__CreateScreenFadeOut
			mov dwFadeHandle, eax
		}
	}
	else if(fadeType == FADE_TYPE_OUT_UNHACKED)
	{
		_asm
		{
			push uiTime
			mov ecx, CAddress::VAR_CameraPool
			call CAddress::FUNC_CCameraPool__CreateScreenFadeOutUnhacked
			mov dwFadeHandle, eax
		}
	}
	// Fade the screen
	_asm
	{
		push dwFadeHandle
		mov ecx, CAddress::VAR_CameraPool
		call CAddress::FUNC_CCameraPool__FadeScreen
	}
}

void CGame::Process()
{
	// Process network
	if(pClient)
		pClient->ProcessClient();

	// Process local player sync
	if(m_pLocalPlayer && pClient->GetNetworkState() == NET_STATE_PLAYING)
		m_pLocalPlayer->ProcessSync();

	// Process all players
	if(m_pPlayerManager && pClient->GetNetworkState() == NET_STATE_PLAYING)
		m_pPlayerManager->Process();

	// Process local player
	if(m_pLocalPlayer)
		m_pLocalPlayer->Process();

	// Process vehicle entry and exit
	ProcessVehicleEntry();


}