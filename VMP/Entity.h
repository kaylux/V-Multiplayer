/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Entity.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Entity class header file
=============================================================*/

#ifndef ENTITY_H
#define ENTITY_H

#include "Model.h"
#include "VEntity.h"

class CEntity
{
	public:
		CEntity();
		~CEntity();
		
		///////////////////////////////////////////////////////////////////
		inline void SetEntityHandler(CVEntity *pEntity)
		{
			// do we have a valid pointer ?
			if(pEntity)
				// Set entity pointer
				m_pEntity = pEntity;
		}
		inline CVEntity *GetEntityHandler() { return m_pEntity; };

		///////////////////////////////////////////////////////////////////
		inline CModel *GetModelHandler() { return m_pModel; };
		inline void SetModelHandler(CModel *pModel) { m_pModel = pModel; };

		///////////////////////////////////////////////////////////////////
		void AddToWorld();
		void RemoveFromWorld();

		///////////////////////////////////////////////////////////////////
		void SetPosition(CVector3 vecPosition);
		void GetPosition(CVector3 &vecPosition);
		void SetMoveSpeed(CVector3 vecMoveSpeed);
		void GetMoveSpeed(CVector3 &vecMoveSpeed);
		void SetTurnSpeed(CVector3 vecTurnSpeed);
		void GetTurnSpeed(CVector3 &vecTurnSpeed);
		void SetModel(unsigned int uiModelIndex);
		DWORD GetPhysics();


	private:
		CVEntity				*m_pEntity;
		CModel					*m_pModel;
		
};

#endif