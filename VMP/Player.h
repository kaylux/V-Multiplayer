/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Player.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Player class header file
=============================================================*/

#ifndef PLAYER_H
#define PLAYER_H

#include "PlayerPed.h"
#include "PlayerInfo.h"
#include "Blip.h"
#include <Common.h>

class CPlayer
{
	public:
		CPlayer(bool bLocal, EntityId playerId, char *szPlayerName);
		~CPlayer();
		
		////////////////////////////////////////////////////////////////////////////
		inline void SetId(EntityId playerId) { m_playerId = playerId; };
		inline EntityId GetId() { return m_playerId; };
		
		////////////////////////////////////////////////////////////////////////////
		inline void SetName(char *szName) { strcpy(m_szPlayerName, szName); };
		inline void GetName(char *szName) { strcpy(szName, m_szPlayerName); };

		////////////////////////////////////////////////////////////////////////////
		inline void SetGameId(BYTE byteGameId) { m_byteGameId = byteGameId; };
		inline BYTE GetGameId() { return m_byteGameId; };
		
		////////////////////////////////////////////////////////////////////////////
		void Create();
		void Spawn(unsigned int uiModelIndex);
		void SetModel(unsigned int uiModelIndex);
		void Destroy();

		////////////////////////////////////////////////////////////////////////////
		inline void SetPlayerPed(CPlayerPed *pPlayerPed)
		{
			// do we have a valid pointer ?
			if(pPlayerPed)
				// Set player ped pointer
				m_pPlayerPed = pPlayerPed;
		}
		inline CPlayerPed *GetPlayerPed() { return m_pPlayerPed; };

		////////////////////////////////////////////////////////////////////////////
		inline void SetPlayerInfo(CPlayerInfo *pPlayerInfo)
		{
			// do we have a valid pointer ?
			if(pPlayerInfo)
				// Set player ped pointer
				m_pPlayerInfo = pPlayerInfo;
		}
		inline CPlayerInfo *GetPlayerInfo() { return m_pPlayerInfo; }; 

		////////////////////////////////////////////////////////////////////////////
		inline void SetBlip(CBlip *pBlip)
		{
			// do we have a valid pointer ?
			if(pBlip)
				// Set blip pointer
				m_pBlip = pBlip;
		}
		inline CBlip *GetBlip() { return m_pBlip; }; 

		////////////////////////////////////////////////////////////////////////////
		inline void SetTask(CTask *pTask)
		{
			// do we have a valid pointer ?
			if(pTask)
				// Set task pointer
				m_pTask = pTask;
		}
		inline CTask *GetTask() { return m_pTask; }; 

		////////////////////////////////////////////////////////////////////////////
		void Sync(RakNet::BitStream *pBitStream);
		void Interpolate();
		void Process();
		void HandleTaskDestroy();

		////////////////////////////////////////////////////////////////////////////
		inline ePlayerState GetState() { return m_state; };
		inline void SetState(ePlayerState state) { m_state = state; };

		////////////////////////////////////////////////////////////////////////////
		EntityId GetNearestVehicle();
		void HandleVehicleEntryAndExit(bool bPassenger);
		void ProcessVehicleEntryAndExit();
		void EnterVehicle(EntityId vehicleId, BYTE byteSeatId);
		void ExitVehicle(EntityId vehicleId);
		void PutInVehicle(EntityId vehicleId, BYTE byteSeatId);
		void RemoveFromVehicle();

		////////////////////////////////////////////////////////////////////////////
		inline EntityId GetVehicleId() { return m_vehicleId; };
		inline BYTE GetSeatId() { return m_byteSeatId; };

		////////////////////////////////////////////////////////////////////////////
		void AttachBlip();
		void DetachBlip();


	private:
		bool					m_bLocal;
		EntityId				m_playerId;
		BYTE					m_byteGameId;
		char					m_szPlayerName[MAX_NAME_LENGTH];
		ePlayerState			m_state;
		CPlayerPed				*m_pPlayerPed;
		CPlayerInfo				*m_pPlayerInfo;
		CBlip					*m_pBlip;
		CTask					*m_pTask;
		CVector3				m_vecInterpolation;
		CVector3				m_vecLastSyncPosition;
		EntityId				m_vehicleId;
		BYTE					m_byteSeatId;
		EntityId				m_enterVehicleId;
		BYTE					m_byteEnterSeatId;
		bool					m_bEnteringVehicle;
		bool					m_bExitingVehicle;
		
};

#endif