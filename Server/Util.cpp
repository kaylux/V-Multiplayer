/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Util.cpp
-- Project: Server
-- Author(s): m0niSx
-- Description: Utils source file
=============================================================*/


#include "Main.h"

void LogPrintf(bool bNewLine, char *szText, ...)
{
	// Start the arguments list
	va_list vArgs;
	va_start(vArgs, szText);
	// Open the log file
	FILE *pLogFile = fopen(LOG_FILE, "a");
	if(!pLogFile)
		return;

	// Get the system time
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	// Write time to the log file
	fprintf(pLogFile, "[%d:%d:%d] ", systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	// Write the text to the log file
	vfprintf(pLogFile, szText, vArgs);
	// Print text to the console
	vprintf(szText, vArgs);
	// New lines
	if(bNewLine)
	{
		fprintf(pLogFile, "\n");
		printf("\n");
	}
	// Close file
	fclose(pLogFile);
	// End the arguments list
	va_end(vArgs);
}

void LuaLog(char *szText, ...)
{
	// Start the arguments list
	va_list vArgs;
	va_start(vArgs, szText);
	// Log
	LogPrintf(true, szText, vArgs);
	// End the arguments list
	va_end(vArgs);
}

void ErrorExit(char *szText, ...)
{
	// Start the arguments list
	va_list vArgs;
	va_start(vArgs, szText);
	// Open the log file
	FILE *pFile = fopen(ERROR_FILE, "a");
	if(!pFile)
		return;

	// Get the system time
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	// Write time to the log file
	fprintf(pFile, "[%d:%d:%d] ", systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	// Write the text to the log file
	vfprintf(pFile, szText, vArgs);
	// New lines
	fprintf(pFile, "\n");
	// Close file
	fclose(pFile);
	// End the arguments list
	va_end(vArgs);
	// Simply quit
	exit(0);
}


