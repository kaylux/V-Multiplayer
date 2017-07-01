/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: SimpleTasks.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Simple tasks handler source file
=============================================================*/

#include "Main.h"

extern CGame		*pGame;

/* CTaskComplexGoToCoords:

+ 0x0 .. 0x10 - CTask
+ 0x1C - (-1) initial value and (-1)
+ 0x18 - Move type handler (0 for type 0 & 1 / 1 for type 2 / 2.0f for type 3 / 3.0f for type 4)
+ 0x20 .. 0x28 = vecPoint
+ 0x2C = vecPoint.fUnknown
+ 0x30 = 0.5f (arg 3)
+ 0x34 = 2.0f (arg 4)
+ 0x38 = 2.0f (in the code)
+ 0x3C = 4 (move type maybe)

*/

CTask *CSimpleTasks::CreateTaskSimpleMoveGoToPoint(CVector3 vecPoint, bool bSprint)
{
	// Create the task
	CTask *pTask = new CTask();
	// Is the task successfully created ?
	if(pTask && pTask->IsCreated())
	{
		// Get the task handler
		CVTask *pTaskHandler = pTask->GetHandler();
		// Get the moving type
		int iMoveType = 0;
		if(bSprint)
			iMoveType = 4;
		else
			iMoveType = 3;

		// Create the GTA vector pointer
		CVGTAVector *pvecPoint = new CVGTAVector(vecPoint);
		float fUnk = 0.5f;
		// Create the goto point task
		_asm
		{
			push 0
			push fUnk
			push pvecPoint
			push 0
			push iMoveType
			mov ecx, pTaskHandler
			call CAddress::FUNC_CTaskSimpleMoveGoToPoint__Constructor
			mov pTaskHandler, eax
		}
		// Set the task handler
		pTask->SetHandler(pTaskHandler);
		// Return the task pointer
		return pTask;
	}
	// Return Invalid
	return NULL;
}
