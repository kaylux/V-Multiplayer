/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VehicleNatives.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Vehicle script natives header file
=============================================================*/

#ifndef VEHICLENATIVES_H
#define VEHICLENATIVES_H

class CVehicleNatives
{
	public:	
		static void RegisterNatives();

		static int IsCreated(lua_State *pVM);
		static int Create(lua_State *pVM);
};

#endif