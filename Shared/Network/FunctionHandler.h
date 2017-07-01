/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: FunctionsHandler.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: RPC functions handler header file
=============================================================*/

#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

#include <BitStream.h>
#include "FunctionsIdentifiers.h"
#include "SenderInfo.h"

// A type definition of the server functions callback
typedef void (*RPCFunction_t)(RakNet::BitStream *pBitStream, CSenderInfo *pSenderInfo);

class CFunctionHandler
{
	public:
		CFunctionHandler();
		~CFunctionHandler();


		void RegisterFunction(RPCFunction_t pfnFunction, eRPCFunctions functionID)
		{
			// Get free function slot
			BYTE byteId = GetFreeFunctionSlot();
			if(byteId != 255)
			{
				// Store func name
				m_functionId[byteId] = functionID;
				// Store func
				m_pfnFunction[byteId] = pfnFunction;
				// Increase functions count
				m_byteFuncs++;
			}
		};

		RPCFunction_t GetFunctionAddressFromId(eRPCFunctions functionId);

	private:
		BYTE				GetFreeFunctionSlot();

		// Functions variables
		RPCFunction_t		m_pfnFunction[MAX_FUNCTIONS];
		BYTE				m_byteFuncs;
		eRPCFunctions		m_functionId[MAX_FUNCTIONS];

};

#endif