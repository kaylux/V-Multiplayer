/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Game.h
-- Project: Client
-- Author(s): m0niSx
-- Description: VMP client game header file
=============================================================*/

#ifndef GAME_H
#define GAME_H

#include <d3d9.h>
#include "Pad.h"
#include "GameGui.h"
#include "Address.h"
#include "MainMenu.h"
#include "NameTags.h"
#include "GameUtils.h"
#include "GameThread.h"
#include "LocalPlayer.h"
#include "PlayerManager.h"
#include "VehicleManager.h"

class CGame
{
	public:
		CGame();
		~CGame();

		
		///////////////////////////////////////////////////
		inline void SetHWND(HWND hWnd) { m_hWnd = hWnd; };
		inline HWND GetHWND() { return m_hWnd; };

		///////////////////////////////////////////////////
		inline IDirect3DDevice9 *GetDevice() { return m_pDevice; };

		///////////////////////////////////////////////////
		inline DWORD GetBaseAddress() { return m_dwBaseAddress; };

		///////////////////////////////////////////////////
		inline void SetGameState(eGameState gameState) { m_gameState = gameState; };
		inline eGameState GetGameState() { return m_gameState; };

		///////////////////////////////////////////////////
		void InitGame();
		void InstallPatches();
		void InitializeInGame(unsigned int uiLocalPlayerIndex);
		void SetupDevice(IDirect3DDevice9 *pDevice);
		void SetupNetwork(char *szHost, int iPort);
		void StartNetwork();
		void InitializeGUI();

		///////////////////////////////////////////////////
		void Process();

		///////////////////////////////////////////////////
		inline CLocalPlayer				*GetLocalPlayer() { return m_pLocalPlayer; };
		inline CPlayerManager			*GetPlayerManager() { return m_pPlayerManager; };
		inline CVehicleManager			*GetVehicleManager() { return m_pVehicleManager; };
		inline CGameGui					*GetGameGui() { return m_pGameGui; };
		inline CMainMenu				*GetMainMenu() { return m_pMainMenu; };
		inline CNameTags				*GetNameTags() { return m_pNameTags; };
		inline CPad						*GetPad() { return m_pPad; };
		inline CGameThread				*GetActiveThread() { return m_pActiveThread; };

		///////////////////////////////////////////////////
		inline void ToggleKeys(bool bToggle) { m_bKeys = bToggle; };
		inline bool IsKeysEnabled() { return m_bKeys; };

		///////////////////////////////////////////////////
		void ProcessVehicleEntry();

		///////////////////////////////////////////////////
		void							Fade(unsigned int uiTime, eFadeType fadeType);
		inline void						SetCurrentPlayerIndex(DWORD dwIndex) { *(DWORD *)(CAddress::VAR_CurrentPlayerIndex) = dwIndex; };
		inline DWORD					GetCurrentPlayerIndex() { return *(DWORD *)(CAddress::VAR_CurrentPlayerIndex); };
		inline void						SetMaxWantedLevel(int iLevel) { *(int *)(CAddress::VAR_MaxWantedLevel) = iLevel; };
		inline int						GetMaxWantedLevel() { return *(int *)(CAddress::VAR_MaxWantedLevel); };
		inline void						DisplayHUD(bool bToggle) { *(bool *)(CAddress::VAR_HUDState); };
		inline void						DisplayRadar(bool bToggle) { *(bool *)(CAddress::VAR_RadarState); };

	private:
		HWND						m_hWnd;
		DWORD						m_dwBaseAddress;
		eGameState					m_gameState;
		CLocalPlayer				*m_pLocalPlayer;
		CPlayerManager				*m_pPlayerManager;
		CVehicleManager				*m_pVehicleManager;
		CGameGui					*m_pGameGui;
		CMainMenu					*m_pMainMenu;
		CNameTags					*m_pNameTags;
		CPad						*m_pPad;
		CGameThread					*m_pActiveThread;
		IDirect3DDevice9			*m_pDevice;
		bool						m_bKeys;
		bool						m_bInVehicle;

};

#endif