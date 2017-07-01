/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: SDK.h
-- Project: SDK
-- Author(s): m0niSx
-- Description: Modules SDK header file
=============================================================*/

#ifndef SDK_H
#define SDK_H

// Includes
#include "Lua.h"
// Interfaces
#include "Interfaces/LuaInterface.h"
#include "Interfaces/InterfaceUtils.h"

// Macros
#ifdef WIN32
#	define EXPORT extern "C" __declspec(dllexport)
#else
#	define EXPORT extern "C"
#endif


// Function container
struct stModuleContainer
{
	void *pLogPrintf;
	void *pLuaInterface;
	// Lua functions
	void *lua_gettop;
	void *lua_settop;
	void *lua_pushvalue;
	void *lua_remove;
	void *lua_insert;
	void *lua_replace;
	void *lua_checkstack;
	void *lua_xmove;
	void *lua_isnumber;
	void *lua_isstring;
	void *lua_iscfunction;
	void *lua_isuserdata;
	void *lua_type;
	void *lua_typename;
	void *lua_equal;
	void *lua_rawequal;
	void *lua_lessthan;
	void *lua_tonumber;
	void *lua_tointeger;
	void *lua_toboolean;
	void *lua_tolstring;
	void *lua_objlen;
	void *lua_tocfunction;
	void *lua_touserdata;
	void *lua_tothread;
	void *lua_topointer;
	void *lua_pushnil;
	void *lua_pushnumber;
	void *lua_pushinteger;
	void *lua_pushlstring;
	void *lua_pushstring;
	void *lua_pushvfstring;
	void *lua_pushfstring;
	void *lua_pushcclosure;
	void *lua_pushboolean;
	void *lua_pushlightuserdata;
	void *lua_pushthread;
	void *lua_gettable;
	void *lua_getfield;
	void *lua_rawget;
	void *lua_rawgeti;
	void *lua_createtable;
	void *lua_newuserdata;
	void *lua_getmetatable;
	void *lua_getfenv;
	void *lua_settable;
	void *lua_setfield;
	void *lua_rawset;
	void *lua_rawseti;
	void *lua_setmetatable;
	void *lua_setfenv;
	void *lua_gc;
	void *lua_error;
	void *lua_next;
	void *lua_concat;
	void *lua_getallocf;
	void *lua_setallocf;

};

// Functions definitions
// LogPrintf
typedef void (*LogPrintf_t)(char *szFormat, ...);
extern LogPrintf_t LogPrintf;

// Interfaces
extern CLuaInterface			*pLuaInterface;

// Lua functions
extern lua_gettop_t lua_gettop;
extern lua_settop_t lua_settop;
extern lua_pushvalue_t lua_pushvalue;
extern lua_remove_t lua_remove;
extern lua_insert_t lua_insert;
extern lua_replace_t lua_replace;
extern lua_checkstack_t lua_checkstack;
extern lua_xmove_t lua_xmove;
extern lua_isnumber_t lua_isnumber;
extern lua_isstring_t lua_isstring;
extern lua_iscfunction_t lua_iscfunction;
extern lua_isuserdata_t lua_isuserdata; 
extern lua_type_t lua_type; 
extern lua_typename_t lua_typename; 
extern lua_equal_t lua_equal;
extern lua_rawequal_t lua_rawequal;
extern lua_lessthan_t lua_lessthan; 
extern lua_tonumber_t lua_tonumber; 
extern lua_tointeger_t lua_tointeger; 
extern lua_toboolean_t lua_toboolean;
extern lua_tolstring_t lua_tolstring;
extern lua_objlen_t lua_objlen;
extern lua_tocfunction_t lua_tocfunction;
extern lua_touserdata_t lua_touserdata;
extern lua_tothread_t lua_tothread;
extern lua_topointer_t lua_topointer;
extern lua_pushnil_t lua_pushnil;
extern lua_pushnumber_t lua_pushnumber;
extern lua_pushinteger_t lua_pushinteger;
extern lua_pushlstring_t lua_pushlstring;
extern lua_pushstring_t lua_pushstring;
extern lua_pushvfstring_t lua_pushvfstring;
extern lua_pushfstring_t lua_pushfstring;
extern lua_pushcclosure_t lua_pushcclosure;
extern lua_pushboolean_t lua_pushboolean;
extern lua_pushlightuserdata_t lua_pushlightuserdata;
extern lua_pushthread_t lua_pushthread;
extern lua_gettable_t lua_gettable;
extern lua_getfield_t lua_getfield;
extern lua_rawget_t lua_rawget;
extern lua_rawgeti_t lua_rawgeti;
extern lua_createtable_t lua_createtable;
extern lua_newuserdata_t lua_newuserdata;
extern lua_getmetatable_t lua_getmetatable; 
extern lua_getfenv_t lua_getfenv;
extern lua_settable_t lua_settable;
extern lua_setfield_t lua_setfield;
extern lua_rawset_t lua_rawset;
extern lua_rawseti_t lua_rawseti;
extern lua_setmetatable_t lua_setmetatable;
extern lua_setfenv_t lua_setfenv;
extern lua_gc_t lua_gc;
extern lua_error_t lua_error;
extern lua_next_t lua_next;
extern lua_concat_t lua_concat;
extern lua_getallocf_t lua_getallocf;
extern lua_setallocf_t lua_setallocf;

// Functions
inline CLuaInterface *GetLuaInterface()
{
	return pLuaInterface;
}

#endif