#include "Main.h"

/* ------------------------------------------------------ 
** OnModuleLoad - Called when the module is loaded

* Parameter 1: szModuleName - Module name that should be specified
* Parameter 2: pVM - Pointer to the lua VM
----------------------------------------------------- */
EXPORT bool OnModuleLoad(char *szModuleName, lua_State *pVM)
{
	// Print message
	LogPrintf("HelloWorld module is loaded 0x%x", pVM);
	// Set module name
	strcpy(szModuleName, "VMP HelloWorld");

	// Register functions
	lua_register(pVM, "helloworld", TestFunction);
	return true;
}

/* ------------------------------------------------------ 
** OnModuleUnLoad - Called when the module is unloaded

* No Parameters
----------------------------------------------------- */
EXPORT void OnModuleUnload()
{
	LogPrintf("HelloWorld module is unloaded");
}

/* ------------------------------------------------------ 
** OnScriptLoad - Called every time the script gets loaded

* Parameter 1: szScriptName - Script name thats getting loaded
----------------------------------------------------- */
EXPORT void OnScriptLoad(char *szScriptName)
{
	// Call a test function
	//CLuaArguments luaArguments;
	//GetLuaInterface()->CallEvent("onModuleEvent", NULL);
}

/* ------------------------------------------------------ 
** OnScriptUnload - Called every time the script gets unloaded

* Parameter 1: szScriptName - Script name thats getting unloaded
----------------------------------------------------- */
EXPORT void OnScriptUnload(char *szScriptName)
{

}

/* ------------------------------------------------------ 
** OnModulePulse - Called every time the server pulses

* No Parameters
----------------------------------------------------- */
EXPORT void OnModulePulse()
{

}