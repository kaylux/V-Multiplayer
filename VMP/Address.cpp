/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Address.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game addresses source file
=============================================================*/

// Yes, we better use that cuz im pretty much sure that GTA V will be using dynamic addresses
// and we will need to get the game base address and substract the image from it then add the address offset
// But that will be annoying to use everytime that we're dealing with addresses, so lets use that class instead
// to make life easier !! :)

#include "Main.h"

// Callbacks definitions
DWORD CAddress::CALLBACK_CScript__Process = NULL;
DWORD CAddress::CALLBACK_CPlayer__ProcessKeys = NULL;
DWORD CAddress::CALLBACK_CPopulation__Process = NULL;
// Player definitions
DWORD CAddress::FUNC_CreatePlayer = NULL;
DWORD CAddress::FUNC_DeletePlayer = NULL;
DWORD CAddress::FUNC_ChangePlayerModel = NULL;
DWORD CAddress::FUNC_WarpPlayerIntoVehicleAsDriver = NULL;
DWORD CAddress::FUNC_WarpPlayerIntoVehicleAsPassenger = NULL;
DWORD CAddress::FUNC_RemovePlayerFromVehicle = NULL;
// Ped definitions
DWORD CAddress::FUNC_CPed__Constructor = NULL;
DWORD CAddress::FUNC_CPed__SetupIntelligence = NULL;
DWORD CAddress::FUNC_CPed__ProcessKeys = NULL;
// PedFactory functions
DWORD CAddress::FUNC_CPedFactory__CreatePed = NULL;
DWORD CAddress::FUNC_CPedFactory__DestroyPed = NULL;
// PedTaskManager definitions
DWORD CAddress::FUNC_CPedTaskManager__SetPedTask = NULL;		
DWORD CAddress::FUNC_CPedTaskManager__SetMouvementTask;
DWORD CAddress::FUNC_CPedTaskManager__ClearTasks;
// Vehicle definitions
DWORD CAddress::FUNC_CreateVehicle = NULL;
DWORD CAddress::FUNC_DeleteVehicle = NULL;
// Screen fade definitions
DWORD CAddress::FUNC_CCameraPool__CreateScreenFadeIn;
DWORD CAddress::FUNC_CCameraPool__CreateScreenFadeInUnhacked;
DWORD CAddress::FUNC_CCameraPool__CreateScreenFadeOut;
DWORD CAddress::FUNC_CCameraPool__CreateScreenFadeOutUnhacked;
DWORD CAddress::FUNC_CCameraPool__FadeScreen;

DWORD CAddress::FUNC_GetModelIndexFromName = NULL;
DWORD CAddress::FUNC_GetModelHashFromIndex = NULL;
DWORD CAddress::FUNC_IsModelLoaded = NULL;
DWORD CAddress::FUNC_RequestModel = NULL;
DWORD CAddress::FUNC_LoadRequestedModels = NULL;
DWORD CAddress::FUNC_CWorld__Add = NULL;
DWORD CAddress::FUNC_CWorld__Remove = NULL;
DWORD CAddress::FUNC_CPools__Allocate = NULL;
DWORD CAddress::FUNC_CPools__Free = NULL;
DWORD CAddress::FUNC_CPools__AtHandle = NULL;
DWORD CAddress::FUNC_CPools__FromHandle = NULL;
DWORD CAddress::FUNC_GetPlayerInfoFromIndex = NULL;
DWORD CAddress::FUNC_CTaskSimpleMoveGoToPoint__Constructor = NULL;
DWORD CAddress::FUNC_CTask__CreateEnterVehicle = NULL;
DWORD CAddress::FUNC_CTask__CreateExitVehicle = NULL;
DWORD CAddress::FUNC_CPads__IsControlJustPressed = NULL;
DWORD CAddress::FUNC_CreateBlip = NULL;
DWORD CAddress::FUNC_DeleteBlip = NULL;
DWORD CAddress::FUNC_GetThreadHandleFromIndex = NULL;
DWORD CAddress::VAR_PedPool = NULL;
DWORD CAddress::VAR_VehiclePool = NULL;
DWORD CAddress::VAR_CameraPool = NULL;
DWORD CAddress::VAR_TaskPool = NULL;
DWORD CAddress::VAR_ThreadPool = NULL;
DWORD CAddress::VAR_Pad = NULL;
DWORD CAddress::VAR_CurrentPlayerIndex = NULL;
DWORD CAddress::VAR_MaxWantedLevel = NULL;
DWORD CAddress::VAR_HUDState = NULL;
DWORD CAddress::VAR_RadarState = NULL;
DWORD CAddress::VAR_ThreadsNumber = NULL;
DWORD CAddress::VAR_ActiveThread = NULL;
DWORD CAddress::VAR_PedFactory = NULL;
DWORD CAddress::ARRAY_PlayerInfo = NULL;
DWORD CAddress::ARRAY_ModelInfo = NULL;
DWORD CAddress::ARRAY_BlipInfo = NULL;

void CAddress::Initialize(DWORD dwBaseAddr)
{
	// Initliaze addresses

	// Intialize callbacks
	CALLBACK_CScript__Process						=	(dwBaseAddr + 0x80A092); // Yes its a test addresses of GTA IV
	CALLBACK_CPlayer__ProcessKeys					=	(dwBaseAddr + 0xD81A38);
	CALLBACK_CPopulation__Process					=	(dwBaseAddr + 0x906AB0);

	// Initialize functions

	// Player functions
	FUNC_CreatePlayer								=	(dwBaseAddr + 0xB90AB0);
	FUNC_DeletePlayer								=	(dwBaseAddr + 0x81B960);
	FUNC_ChangePlayerModel							=	(dwBaseAddr + 0xB90AF0);
	FUNC_GetPlayerInfoFromIndex						=	(dwBaseAddr + 0x817F20);
	FUNC_WarpPlayerIntoVehicleAsDriver				=	(dwBaseAddr + 0xB99F70);
	FUNC_WarpPlayerIntoVehicleAsPassenger			=	(dwBaseAddr + 0xB9A270);
	FUNC_RemovePlayerFromVehicle					=	(dwBaseAddr + 0xB99E70);
	// Ped functions
	FUNC_CPed__Constructor							=	(dwBaseAddr + 0x81CB90);
	FUNC_CPed__SetupIntelligence					=	(dwBaseAddr + 0x89EC20);
	FUNC_CPed__ProcessKeys							=	(dwBaseAddr + 0x9C0B00);
	// PedFactory functions
	FUNC_CPedFactory__CreatePed						=	(dwBaseAddr + 0x43A340);
	FUNC_CPedFactory__DestroyPed					=	(dwBaseAddr + 0x96D480);
	// PlayerTaskManager functions
	FUNC_CPedTaskManager__SetPedTask				=	(dwBaseAddr + 0x9E58B0);
	FUNC_CPedTaskManager__SetMouvementTask			=	(dwBaseAddr + 0x9E5E20);
	FUNC_CPedTaskManager__ClearTasks				=	(dwBaseAddr + 0x9E5B80);
	// Vehicle functions
	FUNC_CreateVehicle								=	(dwBaseAddr + 0xB80740);
	FUNC_DeleteVehicle								=	(dwBaseAddr + 0x8415D0);
	// Screen fade functions
	FUNC_CCameraPool__CreateScreenFadeIn			=	(dwBaseAddr + 0xAFD1D0);
	FUNC_CCameraPool__CreateScreenFadeInUnhacked	=	(dwBaseAddr + 0xAFD2B0);
	FUNC_CCameraPool__CreateScreenFadeOut			=	(dwBaseAddr + 0xAFD240);
	FUNC_CCameraPool__CreateScreenFadeOutUnhacked	=	(dwBaseAddr + 0xAFD320);
	FUNC_CCameraPool__FadeScreen					=	(dwBaseAddr + 0xAFEA00);
	// Model functions
	FUNC_GetModelIndexFromName						=	(dwBaseAddr + 0x98AC40);
	FUNC_GetModelHashFromIndex						=	(dwBaseAddr + 0x98AAE0);
	FUNC_IsModelLoaded								=	(dwBaseAddr + 0x832DD0);
	FUNC_RequestModel								=	(dwBaseAddr + 0x832C40);
	FUNC_LoadRequestedModels						=	(dwBaseAddr + 0x832C20);
	// World functions
	FUNC_CWorld__Add								=	(dwBaseAddr + 0x817350);
	FUNC_CWorld__Remove								=	(dwBaseAddr + 0x8173C0);
	// Pools functions
	FUNC_CPools__Allocate							=	(dwBaseAddr + 0x439CB0);
	FUNC_CPools__Free								=	(dwBaseAddr + 0x448300);
	FUNC_CPools__AtHandle							=	(dwBaseAddr + 0x426700);
	FUNC_CPools__FromHandle							=	(dwBaseAddr + 0x447230);
	// Tasks functions
	//FUNC_CTaskComplexGoToPointAndStandStill__Constructor	=	(dwBaseAddr + 0xA0DF00);

	FUNC_CTaskSimpleMoveGoToPoint__Constructor	=	(dwBaseAddr + 0xA13680);
	FUNC_CTask__CreateEnterVehicle				=	(dwBaseAddr + 0xA2BCF0);
	FUNC_CTask__CreateExitVehicle				=	(dwBaseAddr + 0xA2C920);
	// Pads functions
	FUNC_CPads__IsControlJustPressed			=	(dwBaseAddr + 0xBA9720);
	// Blips functions
	FUNC_CreateBlip								=	(dwBaseAddr + 0x8109C0);
	FUNC_DeleteBlip								=	(dwBaseAddr + 0x80E620);
	// Thread functions
	FUNC_GetThreadHandleFromIndex				=	(dwBaseAddr + 0x5A6A10);

	// Initialize variables
	VAR_PedPool									=	(dwBaseAddr + 0x18A82AC);
	VAR_VehiclePool								=	(dwBaseAddr + 0x1619240);
	VAR_CameraPool								=	(dwBaseAddr + 0x168F910);
	VAR_TaskPool								=	(dwBaseAddr + 0x164B01C);
	VAR_ThreadPool								=	(dwBaseAddr + 0x1983310);
	VAR_Pad										=	(dwBaseAddr + 0x10FB818);
	VAR_CurrentPlayerIndex						=	(dwBaseAddr + 0xF1CC68);
	VAR_MaxWantedLevel							=	(dwBaseAddr + 0xF27A14);
	VAR_HUDState								=	(dwBaseAddr + 0x118034C);
	VAR_RadarState								=	(dwBaseAddr + 0x118034F);
	VAR_ThreadsNumber							=	(dwBaseAddr + 0x1983314);
	VAR_ActiveThread							=	(dwBaseAddr + 0x1849AE0);
	VAR_PedFactory								=	(dwBaseAddr + 0x15E35A0);

	// Initialize arrays
	ARRAY_PlayerInfo							=	(dwBaseAddr + 0x11A7008);
	ARRAY_ModelInfo								=	(dwBaseAddr + 0x15F73B0);
	ARRAY_BlipInfo								=	(dwBaseAddr + 0x119ED50);
}