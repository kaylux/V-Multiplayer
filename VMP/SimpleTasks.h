/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: SimpleTasks.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Simple tasks handler header file
=============================================================*/

#ifndef SIMPLETASKS_H
#define SIMPLETASKS_H

#include "Task.h"

class CSimpleTasks
{
	public:
		static CTask *CreateTaskSimpleMoveGoToPoint(CVector3 vecPoint, bool bSprint);

};

#endif
