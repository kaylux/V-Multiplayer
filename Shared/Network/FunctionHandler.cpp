/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: FunctionsHandler.cpp
-- Project: Shared
-- Author(s): m0niSx
-- Description: RPC functions handler source file
=============================================================*/

#include "FunctionHandler.h"

CFunctionHandler::CFunctionHandler()
{
	// Reset functions count
	m_byteFuncs = 0;
	// Reset functions values
	for(BYTE i = 0; i < MAX_FUNCTIONS; i++)
		m_pfnFunction[i] = NULL;
}

CFunctionHandler::~CFunctionHandler()
{
	// Reset values
	m_byteFuncs = 0;
}

BYTE CFunctionHandler::GetFreeFunctionSlot()
{
	// If the actual number is above or equal to the limit then return invalid
	if(m_byteFuncs >= MAX_FUNCTIONS)
		return 255;

	// Loop through the functions
	for(BYTE i = 0; i < MAX_FUNCTIONS; i++)
	{
		// If the function is not registred then return the id
		if(!m_pfnFunction[i])
			return i;
	}
	// Return invalid
	return 255;
}

RPCFunction_t CFunctionHandler::GetFunctionAddressFromId(eRPCFunctions functionId)
{
	// Loop through the functions
	for(BYTE i = 0; i < MAX_FUNCTIONS; i++)
	{
		// If the function id is equal for what we're searching
		if(functionId == m_functionId[i])
			return m_pfnFunction[i];
	}
	// Return invalid
	return NULL;
}

