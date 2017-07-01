#include "Main.h"


int TestFunction(lua_State *pVM)
{
	LogPrintf("the test helloworld function was called");
	return 1;
}