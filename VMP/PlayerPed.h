/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: PlayerPed.h
-- Project: Client
-- Author(s): m0niSx
-- Description: PlayerPed handler header file
=============================================================*/

#ifndef PLAYERPED_H
#define PLAYERPED_H

#include "Entity.h"
#include "VPlayerPed.h"
#include "Task.h"
#include "GameUtils.h"

class CPlayerPed : public CEntity
{
	public:
		CPlayerPed(CVPlayerPed *pPlayerPed);
		~CPlayerPed();

		//////////////////////////////////////////////////////////////////////
		inline void SetHandler(CVPlayerPed *pPlayerPed)
		{
			// Set player ped pointer
			m_pPlayerPed = pPlayerPed;
			// Set entity pointer
			SetEntityHandler(reinterpret_cast<CVEntity *>(pPlayerPed));
		}
		inline CVPlayerPed *GetHandler() { return m_pPlayerPed; };

		//////////////////////////////////////////////////////////////////////
		float GetCurrentRotation() { return m_pPlayerPed ? m_pPlayerPed->fRotation : 0.0f; };
		void SetCurrentRotation(float fRotation) { m_pPlayerPed ? m_pPlayerPed->fRotation = fRotation : fRotation = 0.0f; };

		//////////////////////////////////////////////////////////////////////
		CVVehicleInfo *GetCurrentVehicle() { return (m_pPlayerPed && m_pPlayerPed->byteState == 5 ? m_pPlayerPed->pCurrentVehicle : NULL); };
		void SetCurrentVehicle(CVVehicleInfo *pVehicle) { m_pPlayerPed ? m_pPlayerPed->pCurrentVehicle = pVehicle : pVehicle = NULL; };

		//////////////////////////////////////////////////////////////////////
		template <typename T>
		T GetTarget() { return (m_pPlayerPed ? (T)m_pPlayerPed->pTarget : NULL); };

		//////////////////////////////////////////////////////////////////////
		void SetPedTask(CTask *pTask, eTaskPriority priority, bool bForceNewTask);
		void SetPedMouvementTask(CTask *pTask, int iPriority);
		void ClearTasks();

		//////////////////////////////////////////////////////////////////////
		CVWeapon *GetWeapon(BYTE byteSlot) { return (m_pPlayerPed ? &m_pPlayerPed->weapon[byteSlot] : NULL); };
		void SetWeapon(BYTE byteSlot, CVWeapon *pWeapon) { m_pPlayerPed ? memcpy(&m_pPlayerPed->weapon[byteSlot], pWeapon, sizeof(CVWeapon)) : pWeapon = NULL; };


	private:
		CVPlayerPed		*m_pPlayerPed;
};

#endif