/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: SDK.cpp
-- Project: SDK
-- Author(s): m0niSx
-- Description: Modules SDK source file
=============================================================*/

#include "SDK.h"

LogPrintf_t LogPrintf;
CLuaInterface			*pLuaInterface;
// Lua functions
lua_gettop_t lua_gettop;
lua_settop_t lua_settop;
lua_pushvalue_t lua_pushvalue;
lua_remove_t lua_remove;
lua_insert_t lua_insert;
lua_replace_t lua_replace;
lua_checkstack_t lua_checkstack;
lua_xmove_t lua_xmove;
lua_isnumber_t lua_isnumber;
lua_isstring_t lua_isstring;
lua_iscfunction_t lua_iscfunction;
lua_isuserdata_t lua_isuserdata; 
lua_type_t lua_type; 
lua_typename_t lua_typename; 
lua_equal_t lua_equal;
lua_rawequal_t lua_rawequal;
lua_lessthan_t lua_lessthan; 
lua_tonumber_t lua_tonumber; 
lua_tointeger_t lua_tointeger; 
lua_toboolean_t lua_toboolean;
lua_tolstring_t lua_tolstring;
lua_objlen_t lua_objlen;
lua_tocfunction_t lua_tocfunction;
lua_touserdata_t lua_touserdata;
lua_tothread_t lua_tothread;
lua_topointer_t lua_topointer;
lua_pushnil_t lua_pushnil;
lua_pushnumber_t lua_pushnumber;
lua_pushinteger_t lua_pushinteger;
lua_pushlstring_t lua_pushlstring;
lua_pushstring_t lua_pushstring;
lua_pushvfstring_t lua_pushvfstring;
lua_pushfstring_t lua_pushfstring;
lua_pushcclosure_t lua_pushcclosure;
lua_pushboolean_t lua_pushboolean;
lua_pushlightuserdata_t lua_pushlightuserdata;
lua_pushthread_t lua_pushthread;
lua_gettable_t lua_gettable;
lua_getfield_t lua_getfield;
lua_rawget_t lua_rawget;
lua_rawgeti_t lua_rawgeti;
lua_createtable_t lua_createtable;
lua_newuserdata_t lua_newuserdata;
lua_getmetatable_t lua_getmetatable; 
lua_getfenv_t lua_getfenv;
lua_settable_t lua_settable;
lua_setfield_t lua_setfield;
lua_rawset_t lua_rawset;
lua_rawseti_t lua_rawseti;
lua_setmetatable_t lua_setmetatable;
lua_setfenv_t lua_setfenv;
lua_gc_t lua_gc;
lua_error_t lua_error;
lua_next_t lua_next;
lua_concat_t lua_concat;
lua_getallocf_t lua_getallocf;
lua_setallocf_t lua_setallocf;

EXPORT void OnModuleSetup(stModuleContainer *pModuleContainer)
{
	LogPrintf = (LogPrintf_t)pModuleContainer->pLogPrintf;
	// Setup interfaces
	pLuaInterface = (CLuaInterface *)pModuleContainer->pLuaInterface;
	// Setup Lua functions
	lua_gettop = (lua_gettop_t)pModuleContainer->lua_gettop;
	lua_settop = (lua_settop_t)pModuleContainer->lua_settop;
	lua_pushvalue = (lua_pushvalue_t)pModuleContainer->lua_pushvalue;
	lua_remove = (lua_remove_t)pModuleContainer->lua_remove;
	lua_insert = (lua_insert_t)pModuleContainer->lua_insert;
	lua_replace = (lua_replace_t)pModuleContainer->lua_replace;
	lua_checkstack = (lua_checkstack_t)pModuleContainer->lua_checkstack;
	lua_xmove = (lua_xmove_t)pModuleContainer->lua_xmove;
	lua_isnumber = (lua_isnumber_t)pModuleContainer->lua_isnumber;
	lua_isstring = (lua_isstring_t)pModuleContainer->lua_isstring;
	lua_iscfunction = (lua_iscfunction_t)pModuleContainer->lua_iscfunction;
	lua_isuserdata = (lua_isuserdata_t)pModuleContainer->lua_isuserdata;
	lua_type = (lua_type_t)pModuleContainer->lua_type;
	lua_typename = (lua_typename_t)pModuleContainer->lua_typename;
	lua_equal = (lua_equal_t)pModuleContainer->lua_equal;
	lua_rawequal = (lua_rawequal_t)pModuleContainer->lua_rawequal;
	lua_lessthan = (lua_lessthan_t)pModuleContainer->lua_lessthan;
	lua_tonumber = (lua_tonumber_t)pModuleContainer->lua_tonumber;
	lua_tointeger = (lua_tointeger_t)pModuleContainer->lua_tointeger;
	lua_toboolean = (lua_toboolean_t)pModuleContainer->lua_toboolean;
	lua_tolstring = (lua_tolstring_t)pModuleContainer->lua_tolstring;
	lua_objlen = (lua_objlen_t)pModuleContainer->lua_objlen;
	lua_tocfunction = (lua_tocfunction_t)pModuleContainer->lua_tocfunction;
	lua_touserdata = (lua_touserdata_t)pModuleContainer->lua_touserdata;
	lua_tothread = (lua_tothread_t)pModuleContainer->lua_tothread;
	lua_topointer = (lua_topointer_t)pModuleContainer->lua_topointer;
	lua_pushnil = (lua_pushnil_t)pModuleContainer->lua_pushnil;
	lua_pushnumber = (lua_pushnumber_t)pModuleContainer->lua_pushnumber;
	lua_pushinteger = (lua_pushinteger_t)pModuleContainer->lua_pushinteger;
	lua_pushlstring = (lua_pushlstring_t)pModuleContainer->lua_pushlstring;
	lua_pushstring = (lua_pushstring_t)pModuleContainer->lua_pushstring;
	lua_pushvfstring = (lua_pushvfstring_t)pModuleContainer->lua_pushvfstring;
	lua_pushfstring = (lua_pushfstring_t)pModuleContainer->lua_pushfstring;
	lua_pushcclosure = (lua_pushcclosure_t)pModuleContainer->lua_pushcclosure;
	lua_pushboolean = (lua_pushboolean_t)pModuleContainer->lua_pushboolean;
	lua_pushlightuserdata = (lua_pushlightuserdata_t)pModuleContainer->lua_pushlightuserdata;
	lua_pushthread = (lua_pushthread_t)pModuleContainer->lua_pushthread;
	lua_gettable = (lua_gettable_t)pModuleContainer->lua_gettable;
	lua_getfield = (lua_getfield_t)pModuleContainer->lua_getfield;
	lua_rawget = (lua_rawget_t)pModuleContainer->lua_rawget;
	lua_rawgeti = (lua_rawgeti_t)pModuleContainer->lua_rawgeti;
	lua_createtable = (lua_createtable_t)pModuleContainer->lua_createtable;
	lua_newuserdata = (lua_newuserdata_t)pModuleContainer->lua_newuserdata;
	lua_getmetatable = (lua_getmetatable_t)pModuleContainer->lua_getmetatable;
	lua_getfenv = (lua_getfenv_t)pModuleContainer->lua_getfenv;
	lua_settable = (lua_settable_t)pModuleContainer->lua_settable;
	lua_setfield = (lua_setfield_t)pModuleContainer->lua_setfield;
	lua_rawset = (lua_rawset_t)pModuleContainer->lua_rawset;
	lua_rawseti = (lua_rawseti_t)pModuleContainer->lua_rawseti;
	lua_setmetatable = (lua_setmetatable_t)pModuleContainer->lua_setmetatable;
	lua_setfenv = (lua_setfenv_t)pModuleContainer->lua_setfenv;
	lua_gc = (lua_gc_t)pModuleContainer->lua_gc;
	lua_error = (lua_error_t)pModuleContainer->lua_error;
	lua_next = (lua_next_t)pModuleContainer->lua_next;
	lua_concat = (lua_concat_t)pModuleContainer->lua_concat;
	lua_getallocf = (lua_getallocf_t)pModuleContainer->lua_getallocf;
	lua_setallocf = (lua_setallocf_t)pModuleContainer->lua_setallocf;
}