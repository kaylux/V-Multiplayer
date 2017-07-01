/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VWorld.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game world handler source file
=============================================================*/

#include "Main.h"

void CVWorld::Add(CVEntity *pEntity)
{
	_asm
	{
		push 0
		push pEntity
		call CAddress::FUNC_CWorld__Add
		add esp, 8
	}
}

void CVWorld::Delete(CVEntity *pEntity)
{
	_asm
	{
		push 0
		push pEntity
		call CAddress::FUNC_CWorld__Remove
		add esp, 8
	}
}
