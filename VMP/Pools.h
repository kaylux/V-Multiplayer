/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Pools.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Pools handler header file
=============================================================*/

#ifndef POOLS_H
#define POOLS_H

class CPools
{
	public:
		template <typename T>
		static T Allocate(DWORD dwPool)
		{
			T element = NULL;
			_asm
			{
				mov ecx, dwPool
				call CAddress::FUNC_CPools__Allocate
				mov element, eax
			}
			return element;
		};

		template <typename T>
		static void Free(T element, DWORD dwPool)
		{
			_asm
			{
				push element
				mov ecx, dwPool
				call CAddress::FUNC_CPools__Free
			}
		};

		template <typename T>
		static T AtHandle(unsigned int uiIndex, DWORD dwPool)
		{
			T handle = NULL;
			_asm
			{
				push uiIndex
				mov ecx, dwPool
				call CAddress::FUNC_CPools__AtHandle
				mov handle, eax
			}
			return handle;
		};

		template <typename T>
		static unsigned int FromHandle(T handle, DWORD dwPool)
		{
			unsigned int uiIndex = 0;
			_asm
			{
				push handle
				mov ecx, dwPool
				call CAddress::FUNC_CPools__FromHandle
				mov uiIndex, eax
			}
			return uiIndex;
		};

};

#endif