/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ExceptionHandler.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Exception handler source file
=============================================================*/

#include "Main.h"

extern CGame		*pGame;

void CExceptionHandler::Install()
{
	// Set the exception handler callback
	SetUnhandledExceptionFilter(ExceptionHandlerCallback);
}

long WINAPI CExceptionHandler::ExceptionHandlerCallback(_EXCEPTION_POINTERS *pExceptionInfo)
{
	// Get the current time
	SYSTEMTIME systemTime;
	GetSystemTime(&systemTime);
	// Create the file name
	char szFileName[MAX_PATH];
	sprintf(szFileName, "VMP/Crash Log/%d-%d-%d_%d.%d.%d.vch", systemTime.wDay, systemTime.wMonth, systemTime.wYear, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	// Open the log file
	FILE *pFile = fopen(szFileName, "w");
	// Make sure the file is opened
	if(!pFile)
		return EXCEPTION_EXECUTE_HANDLER;

	// Write the exception informations
	fprintf(pFile, "======================== V:MP Exception Handler ===============================\n");
	fprintf(pFile, "Address: 0x%p (Base: 0x%p)\n\n", pExceptionInfo->ExceptionRecord->ExceptionAddress, pGame ? pGame->GetBaseAddress() : 0x0);
	fprintf(pFile, "Registers:\n");
	fprintf(pFile, "EAX: 0x%p - EBX: 0x%p - ECX: 0x%p - EDX: 0x%p\nESI: 0x%p - EDI: 0x%x - EBP: 0x%p - ESP: 0x%p\n\n", pExceptionInfo->ContextRecord->Eax, pExceptionInfo->ContextRecord->Ebx,
		pExceptionInfo->ContextRecord->Ecx, pExceptionInfo->ContextRecord->Edx, pExceptionInfo->ContextRecord->Esi, pExceptionInfo->ContextRecord->Edi,
		pExceptionInfo->ContextRecord->Ebp, pExceptionInfo->ContextRecord->Esp);

	DWORD dwEsp = pExceptionInfo->ContextRecord->Esp;
	fprintf(pFile, "Stack:\n");
	fprintf(pFile, "0x0: 0x%p - 0x4: 0x%p - 0x8: 0x%p - 0xC: 0x%p - 0x10: 0x%p - 0x14: 0x%p\n0x18: 0x%p - 0x1C: 0x%p - 0x20: 0x%p\n", *(DWORD *)(dwEsp), *(DWORD *)(dwEsp + 4),
		*(DWORD *)(dwEsp + 8), *(DWORD *)(dwEsp + 12), *(DWORD *)(dwEsp + 16), *(DWORD *)(dwEsp + 20), *(DWORD *)(dwEsp + 24), *(DWORD *)(dwEsp + 28), *(DWORD *)(dwEsp + 32));

	fprintf(pFile, "======================== V:MP Exception Handler ===============================");
	// Close the file
	fclose(pFile);
	return EXCEPTION_EXECUTE_HANDLER;
}
