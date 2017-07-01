/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VVehicleInfo.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game vehicle handler header file
=============================================================*/

#ifndef VVEHICLEINFO_H
#define VVEHICLEINFO_H

#include "VEntity.h"

#pragma pack(push, 1)
class CVVehicleInfo : public CVEntity
{
	public:
		// CVEntity								// 0x0000 - 0x0074
		PAD(pad0, 2684);						// 0x0074 - 0x0FA0
		void				*pDriver;			// 0x0FA0 - 0x0FA4
		void				*pPassenger[3];		// 0x0FA0 - 0x0FB6 // F6F = Vehicle Type (0x20 = police car)
		PAD(pad1, 4378);						// 0x0FB6 - 0x20D0

};
#pragma pack(pop)

#endif