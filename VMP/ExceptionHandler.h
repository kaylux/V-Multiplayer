/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ExceptionHandler.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Exception handler header file
=============================================================*/

#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

class CExceptionHandler
{
	public:
		static void Install();

		// Exception handler callback
		static long WINAPI ExceptionHandlerCallback(_EXCEPTION_POINTERS *pExceptionInfo);

};

#endif