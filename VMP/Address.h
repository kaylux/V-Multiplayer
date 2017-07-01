/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Address.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game addresses header file
=============================================================*/

#ifndef ADDRESS_H
#define ADDRESS_H

class CAddress
{
	public:
		static void Initialize(DWORD dwBaseAddr);

		// Callbacks
		static DWORD			CALLBACK_CScript__Process;
		static DWORD			CALLBACK_CPlayer__ProcessKeys;
		static DWORD			CALLBACK_CPopulation__Process;
		// Functions
		static DWORD			FUNC_CreatePlayer;
		static DWORD			FUNC_DeletePlayer;
		static DWORD			FUNC_ChangePlayerModel;
		static DWORD			FUNC_WarpPlayerIntoVehicleAsDriver;
		static DWORD			FUNC_WarpPlayerIntoVehicleAsPassenger;
		static DWORD			FUNC_RemovePlayerFromVehicle;

		static DWORD			FUNC_CPed__Constructor;
		static DWORD			FUNC_CPed__SetupIntelligence;
		static DWORD			FUNC_CPed__ProcessKeys;

		static DWORD			FUNC_CPedFactory__CreatePed;
		static DWORD			FUNC_CPedFactory__DestroyPed;

		static DWORD			FUNC_CPedTaskManager__SetPedTask;
		static DWORD			FUNC_CPedTaskManager__SetMouvementTask;
		static DWORD			FUNC_CPedTaskManager__ClearTasks;

		static DWORD			FUNC_CreateVehicle;
		static DWORD			FUNC_DeleteVehicle;

		static DWORD			FUNC_CCameraPool__CreateScreenFadeIn;
		static DWORD			FUNC_CCameraPool__CreateScreenFadeInUnhacked;
		static DWORD			FUNC_CCameraPool__CreateScreenFadeOut;
		static DWORD			FUNC_CCameraPool__CreateScreenFadeOutUnhacked;
		static DWORD			FUNC_CCameraPool__FadeScreen;

		static DWORD			FUNC_GetModelIndexFromName;
		static DWORD			FUNC_GetModelHashFromIndex;
		static DWORD			FUNC_IsModelLoaded;
		static DWORD			FUNC_RequestModel;
		static DWORD			FUNC_LoadRequestedModels;
		static DWORD			FUNC_CWorld__Add;
		static DWORD			FUNC_CWorld__Remove;
		static DWORD			FUNC_CPools__Allocate;
		static DWORD			FUNC_CPools__Free;
		static DWORD			FUNC_CPools__AtHandle;
		static DWORD			FUNC_CPools__FromHandle;
		static DWORD			FUNC_GetPlayerInfoFromIndex;
		static DWORD			FUNC_CTaskSimpleMoveGoToPoint__Constructor;
		static DWORD			FUNC_CTask__CreateEnterVehicle;
		static DWORD			FUNC_CTask__CreateExitVehicle;
		static DWORD			FUNC_CPads__IsControlJustPressed;
		static DWORD			FUNC_CreateBlip;
		static DWORD			FUNC_DeleteBlip;
		static DWORD			FUNC_GetThreadHandleFromIndex;
		// Variables
		static DWORD			VAR_PedPool;
		static DWORD			VAR_VehiclePool;
		static DWORD			VAR_CameraPool;
		static DWORD			VAR_TaskPool;
		static DWORD			VAR_ThreadPool;
		static DWORD			VAR_Pad;
		static DWORD			VAR_CurrentPlayerIndex;
		static DWORD			VAR_MaxWantedLevel;
		static DWORD			VAR_HUDState;
		static DWORD			VAR_RadarState;
		static DWORD			VAR_ThreadsNumber;
		static DWORD			VAR_ActiveThread;
		static DWORD			VAR_PedFactory;
		// Arrays
		static DWORD			ARRAY_PlayerInfo;
		static DWORD			ARRAY_ModelInfo;
		static DWORD			ARRAY_BlipInfo;

};

#endif