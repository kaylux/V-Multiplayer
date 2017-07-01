/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Vehicle.h
-- Project: Server
-- Author(s): m0niSx
-- Description: Vehicle header file
=============================================================*/

#ifndef VEHICLE_H
#define VEHICLE_H

class CVehicle
{
	public:
		CVehicle(EntityId vehicleId, DWORD dwModel, CVector3 vecPosition);
		~CVehicle();

		void AddForPlayer(EntityId playerId);

		////////////////////////////////////////////////////////////////////////////
		inline void GetPosition(CVector3 &vecPosition) { memcpy(&vecPosition, &m_vecPosition, sizeof(CVector3)); };
		void SetPosition(CVector3 vecPosition);
		inline void GetMoveSpeed(CVector3 &vecMoveSpeed) { memcpy(&vecMoveSpeed, &m_vecMoveSpeed, sizeof(CVector3)); };
		void SetMoveSpeed(CVector3 vecMoveSpeed);
		inline void GetTurnSpeed(CVector3 &vecTurnSpeed) { memcpy(&vecTurnSpeed, &m_vecTurnSpeed, sizeof(CVector3)); };
		inline void SetTurnSpeed(CVector3 vecTurnSpeed) { memcpy(&m_vecTurnSpeed, &vecTurnSpeed, sizeof(CVector3)); };
		inline float GetRotation() { return m_fRotation; };
		inline void SetRotation(float fRotation) { m_fRotation = fRotation; };

		////////////////////////////////////////////////////////////////////////////
		inline EntityId GetDriverId() { return m_driverId; };
		inline void SetDriverId(EntityId playerId) { m_driverId = playerId; };

		inline EntityId GetPassengerId(BYTE byteSeatId) { return m_passengerId[byteSeatId]; };
		inline void SetPassengerId(BYTE byteSeatId, EntityId playerId) { m_passengerId[byteSeatId] = playerId; };

		////////////////////////////////////////////////////////////////////////////
		void StoreSync(RakNet::BitStream *pBitStream);
		void ProcessSync();

	private:
		EntityId		m_vehicleId;
		DWORD			m_dwModelId;
		float			m_fRotation;
		CVector3		m_vecPosition;
		CVector3		m_vecMoveSpeed;
		CVector3		m_vecTurnSpeed;
		EntityId		m_driverId;
		EntityId		m_passengerId[3];

};

#endif