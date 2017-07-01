/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Player.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Player header file
=============================================================*/

#ifndef PLAYER_H
#define PLAYER_H

#include <Common.h>

enum eSyncType
{
	SYNC_TYPE_ONFOOT,
	SYNC_TYPE_INVEHICLE
};

class CPlayer
{
	public:
		CPlayer(EntityId playerId, char *szName, CVector3 vecSpawnPosition);
		~CPlayer();

		////////////////////////////////////////////////////////////////////////////
		inline bool IsSpawned() { return m_bSpawned; };
		inline void GetName(char *szName) { strcpy(szName, m_szName); };
		void SetName(char *szName);
		inline EntityId GetVehicleId() { return m_vehicleId; };
		inline BYTE GetSeatId() { return m_byteSeatId; };
		inline CVector3 *GetPosition() { return (&m_vecPosition); };
		void SetPosition(CVector3 vecPosition);
		void SetMoveSpeed(CVector3 vecMoveSpeed);

		////////////////////////////////////////////////////////////////////////////
		void SpawnForPlayer(EntityId playerId);
		void SpawnForWorld();
		inline void SetSpawnPosition(CVector3 vecPosition) { memcpy(&m_vecSpawnPosition, &vecPosition, sizeof(CVector3)); };
		inline CVector3 *GetSpawnPosition() { return (&m_vecSpawnPosition); };

		////////////////////////////////////////////////////////////////////////////
		inline ePlayerState GetState() { return m_state; };
		void SetState(ePlayerState state);

		////////////////////////////////////////////////////////////////////////////
		void StoreSync(RakNet::BitStream *pBitStream);
		void StoreVehicleSync(RakNet::BitStream *pBitStream);
		void ProcessSync(eSyncType type);

		////////////////////////////////////////////////////////////////////////////
		EntityId GetNearestVehicle();
		void EnterVehicle(bool bPassenger);
		void ExitVehicle();
		void VehicleEntryComplete();
		void VehicleExitComplete();
		void PutInVehicle(EntityId vehicleId, BYTE byteSeatId);
		void RemoveFromVehicle();

	private:
		EntityId		m_playerId;
		char			m_szName[MAX_NAME_LENGTH];
		bool			m_bSpawned;
		unsigned int	m_uiModelId;
		CVector3		m_vecSpawnPosition;
		ePlayerState	m_state;
		CVector3		m_vecPosition;
		float			m_fRotation;
		CVector3		m_vecMoveSpeed;
		EntityId		m_vehicleId;
		BYTE			m_byteSeatId;
		EntityId		m_enterVehicleId;
		BYTE			m_byteEnterSeatId;

};

#endif