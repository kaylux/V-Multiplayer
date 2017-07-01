/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VWeapon.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game weapons handler header file
=============================================================*/

#ifndef VWEAPON_H
#define VWEAPON_H

#pragma pack(push, 1)
class CVWeapon
{
	public:
		DWORD		dwWeaponType;			// 0x0000 - 0x0004 (12 = melee) TODO: Create enumeration for this when we have weapon sync
		PAD(pad0, 8);						// 0x0004 - 0x000C

};
#pragma pack(pop)

#endif