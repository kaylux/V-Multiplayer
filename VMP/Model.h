/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VModel.h
-- Project: Client
-- Author(s): m0niSx
-- Description: models handler header file
=============================================================*/

#ifndef MODEL_H
#define MODEL_H

#include "VModel.h"

class CModel
{
	public:
		CModel(unsigned int uiModelIndex);
		~CModel();

		//////////////////////////////////////////////////////////////////////
		inline void SetHandler(CVModel *pModel)
		{
			// do we have a valid pointer ?
			if(pModel)
			{
				// Set model pointer
				m_pModel = pModel;
				// Set model hash
				m_dwModelHash = pModel->dwHash;
			}
		}
		inline CVModel *GetHandler() { return m_pModel; };

		////////////////////////////////////////////////////////////////
		inline unsigned int GetModelIndex() { return m_uiModelIndex; };
		inline void SetModelIndex(unsigned int uiModelIndex) 
		{ 
			// Set the model index
			m_uiModelIndex = uiModelIndex; 
			// Do we have a valid model index ?
			if(uiModelIndex)
				// Set the new model handler
				SetHandler(CGameUtils::GetModelInfoFromIndex(uiModelIndex));
			else
				m_pModel = NULL;
		};

		////////////////////////////////////////////////////////////////
		inline DWORD GetModelHash() { return m_dwModelHash; };
		inline void SetModelHash(DWORD dwModelHash) { m_dwModelHash = dwModelHash; };
		
		////////////////////////////////////////////////////////////////
		bool Load(bool bWaitForLoad);
		bool IsLoaded();
		void Unload();

	private:
		bool				m_bLoaded;
		unsigned int		m_uiModelIndex;
		DWORD				m_dwModelHash;
		CVModel				*m_pModel;

};

#endif