/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Library.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: Library manipulation header file
=============================================================*/

#ifndef LIBRARY_H
#define LIBRARY_H

#include <windows.h>

class CLibrary
{
	public:
		CLibrary(char *szLibrary);
		~CLibrary();

		bool Load();
		void Unload();
		void *GetProcedureAddress(char *szProcName);

	private:
		char			m_szPath[MAX_PATH];
		void			*m_pHandle;
		

};

#endif
