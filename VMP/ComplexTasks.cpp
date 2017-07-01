/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ComplexTasks.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Complex tasks handler source file
=============================================================*/

#include "Main.h"

extern CGame *pGame;

/* CComplexTask class

+ 0x0 = VFTable
+ 0x20 = (-1) - Unknown (pushed when calling the task setup function)
+ 0x24 = (-7) - Seat Id handler (argument 2)
+ 0x14 = 27 - Unknown
+ 0x1C / 0x30 / 0x31 / 0x32 / 0x33 = 0 - No idea
+ 0x2C = 3 - idk but maybe type ?
+ 0x3C = -2.0f - (argument 5)
+ 0x34 / byte_0x44 = 0
+ 0x38 = 8
+ 0x40 / 0x44 = 0
+ 0x4C = address D87708
+ 0x50 / 0x54 = (-1)
+ 0x58 = 0

+ 0x18 - Maybe pEnterVehicleTask ptr
		pEnterVehicleTaskPtr + 0x0 = pVehicle pointer

*/

/* CTaskComplexShootAt (Size = 0x38)

+ 0x0: VF Table
+ 0x14: A pointer to the clone
+ 0x20 .. 0x2C: shoot at vector
+ 0x30: some bool that got initialized to true (Clone func makes me think its bIsInitialized)


*/

CTask *CComplexTasks::CreateEnterVehicleTask(CVVehicleInfo *pVehicle, BYTE byteSeatId)
{
	// Make sure we have a valid vehicle pointer
	if(!pVehicle)
		return NULL;

	// Create the task
	CTask *pTask = new CTask();
	// Is the task successfully created ?
	if(pTask && pTask->IsCreated())
	{
		// Create the enter vehicle task
		CVTask *pTaskHandler = pTask->GetHandler();
		//int iUnknown = -7;
		float fUnknown = -2.0f;
		_asm
		{
			push 0
			push 0x20
			push 27
			push 0xFFFFFFF9
			push pVehicle
			mov ecx, pTaskHandler
			call CAddress::FUNC_CTask__CreateEnterVehicle
			mov pTaskHandler, eax
		}
		// Set the task handler
		pTask->SetHandler(pTaskHandler);
		// Return the task pointer
		return pTask;
	}
	return NULL;
}

CTask *CComplexTasks::CreateExitVehicleTask(CVVehicleInfo *pVehicle, int iExitMode)
{
	// Make sure we have a valid vehicle pointer
	if(!pVehicle)
		return NULL;

	// Create the task
	CTask *pTask = new CTask();
	// Is the task successfully created ?
	if(pTask && pTask->IsCreated())
	{
		// Create the enter vehicle task
		CVTask *pTaskHandler = pTask->GetHandler();
		_asm
		{
			push 0
			push 0
			push iExitMode
			push pVehicle
			mov ecx, pTaskHandler
			call CAddress::FUNC_CTask__CreateExitVehicle
			mov pTaskHandler, eax
		}
		// Set the task handler
		pTask->SetHandler(pTaskHandler);
		// Return the task pointer
		return pTask;
	}
	return NULL;
}