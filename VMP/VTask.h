/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VTask.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game task handler header file
=============================================================*/

#ifndef VTASK_H
#define VTASK_H

#include <SharedUtility.h>
#include "VVehicleInfo.h"

class CTaskVFTable
{
	public:
};

#pragma pack(push, 1)
class CVTask
{
	public:
		CTaskVFTable		*pVFTable;			// 0x0000 - 0x0004
		CVTask				*pParent;			// 0x0004 - 0x0008
		CVTask				*pSubTask;			// 0x0008 - 0x000C
		DWORD				dwState;			// 0x000C - 0x0010 (1 = running / 2 = aborted)
		PAD(pad0, 4);							// 0x0010 - 0x0014
};
#pragma pack(pop)

#pragma pack(push, 1)
class CVComplexTask : public CVTask
{
	public:
		// CTask								// 0x0000 - 0x0010
		// TODO: Verify the size (probably not the same as CVTask)
};
#pragma pack(pop)

#pragma pack(push, 1)
class CVTaskComplexGoToCoords : public CVComplexTask
{
	public:
		// CTask								// 0x0000 - 0x0010	
		PAD(pad0, 8);							// 0x0010 - 0x0018
		float		fMoveType;					// 0x0018 - 0x001C  (Move type handler (0 for type 0 & 1 / 1 for type 2 / 2.0f for type 3 / 3.0f for type 4) )
		PAD(pad1, 4);							// 0x001C - 0x0020
		CVector3	vecPoint;					// 0x0020 - 0x002C
		float		fPointUnknown;				// 0x002C - 0x0030 (4th memeber or CGtaVector)
		float		fUnknown1;					// 0x0030 - 0x0034 (seems to be 0.5f)
		float		fUnknown2;					// 0x0034 - 0x0038 (seems to be 2.0f)
		float		fUnknown3;					// 0x0038 - 0x003C (seems to be 2.0f)
		int			iType;						// 0x003C - 0x0040 (task type?)
		// TODO; Find size?
};
#pragma pack(pop)

#endif