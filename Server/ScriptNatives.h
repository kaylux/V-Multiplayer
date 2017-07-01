/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ScriptNatives.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Script natives header file
=============================================================*/

#ifndef SCRIPTNATIVES_H
#define SCRIPTNATIVES_H

class CScriptNatives
{
	public:	
		static void RegisterNatives();
		static void RegisterSecurityNatives();
		// Global server natives
		static int Printf(lua_State *pVM);
		static int SplitF(lua_State *pVM);
		static int RegisterEvent(lua_State *pVM);
		static int UnregisterEvent(lua_State *pVM);
		static int SendMessageToAll(lua_State *pVM);
		static int DisabledSecurityFunction(lua_State *pVM);
};

#endif