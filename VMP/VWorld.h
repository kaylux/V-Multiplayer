/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VWorld.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game world handler header file
=============================================================*/

#ifndef VWORLD_H
#define VWORLD_H

#include "VEntity.h"

class CVWorld
{
	public:
		static void Add(CVEntity *pEntity);
		static void Delete(CVEntity *pEntity);

};

#endif