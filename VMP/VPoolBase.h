/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VPoolBase.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game poolbase handler header file
=============================================================*/

#ifndef VPOOLBASE_H
#define VPOOLBASE_H

#pragma pack(push, 1)
class CVPoolBase
{
	public:
		void			*pAllElements;				// 0x0000 - 0x0004 (Verify that, seems to allocate (MaxElements * ElementSize)
		void			*pCurrentElement;			// 0x0004 - 0x0008
		DWORD			dwElementSize;				// 0x0008 - 0x000C
		int				iCurrentElements;			// 0x000C - 0x0010
		DWORD			dwUnk1;						// 0x0010 - 0x0014 (Initialized at -1)
		DWORD			dwUnk2;						// 0x0014 - 0x0018 (Initialized at 0)
		int				iIsInitialized;				// 0x0018 - 0x001C

};
#pragma pack(pop)

#endif