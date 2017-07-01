/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Util.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Utils source file
=============================================================*/


#include "Main.h"

void Log(char *szText, ...)
{
	// Start the arguments list
	va_list vArgs;
	va_start(vArgs, szText);
	// Open the log file
	FILE *pLogFile = fopen("VMP/Log.txt", "a");
	if(!pLogFile)
		return;

	// Get the system time
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	// Write time to the log file
	fprintf(pLogFile, "[%d:%d:%d] ", systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	// Write the text to the log file
	vfprintf(pLogFile, szText, vArgs);
	// New lines
	fprintf(pLogFile, "\n");
	// Close file
	fclose(pLogFile);
	// End the arguments list
	va_end(vArgs);
}

void UnProtect(DWORD dwAddress, size_t sSize)
{
	// Unprotect the address
	DWORD dwOldProtection;
	VirtualProtect((LPVOID)dwAddress, sSize, PAGE_EXECUTE_READWRITE, &dwOldProtection);
}

