/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Main.cpp
-- Project: Launcher
-- Author(s): m0niSx
-- Description: Main VMP launcher source file
=============================================================*/

#include "Main.h"

#define GAME_EXECUTABLE "LaunchGTAIV.exe"
#define MOD_LIBRARY "VMP.dll"

// Main entry
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Check if the game executable files exists
	if(!FileExists(GAME_EXECUTABLE))
	{
		MessageBox(NULL, "Cannot find game executable file \""GAME_EXECUTABLE"\"", "V:MP Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Check if the mod library files exists
	if(!FileExists(MOD_LIBRARY))
	{
		MessageBox(NULL, "Cannot find mod library file \""MOD_LIBRARY"\"", "V:MP Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Initialize the STARTUPINFO structure
	STARTUPINFO StartupInfo;
	memset(&StartupInfo, 0, sizeof(StartupInfo));
	// Initialize the PROCESS_INFORMATION structure
	PROCESS_INFORMATION ProcessInfo;
	memset(&ProcessInfo, 0, sizeof(ProcessInfo));
	// Launch the game
	if(!CreateProcess(GAME_EXECUTABLE, "", NULL, NULL, true, CREATE_SUSPENDED, NULL, NULL, &StartupInfo, &ProcessInfo))
	{
		MessageBox(NULL, "Cannot launch game", "V:MP Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Try to inject the library
	if(!InjectLibrary(ProcessInfo.hProcess, MOD_LIBRARY))
	{
		MessageBox(NULL, "Cannot Inject library \"" MOD_LIBRARY "\" into game executable \"" GAME_EXECUTABLE "\"", "V:MP Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Resume the launcher 
	ResumeThread(ProcessInfo.hThread);
	return 1;
}

