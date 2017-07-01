/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerNatives.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Player script natives header file
=============================================================*/

#ifndef PLAYERNATIVES_H
#define PLAYERNATIVES_H

class CPlayerNatives
{
	public:	
		static void RegisterNatives();

		static int IsConnected(lua_State *pVM);
		static int SendMessage(lua_State *pVM);
		static int SetName(lua_State *pVM);
		static int GetName(lua_State *pVM);
};

#endif