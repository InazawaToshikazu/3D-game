//=============================================================================
//
// �^�C�g������ [Title.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//�O���錾
class CRenderer;
class CCamera;
class CLight;
class CFade;
//=============================================================================
//CManager�N���X
//=============================================================================
class CTitle
{
	public:
		CTitle();
		~CTitle();
		HRESULT Init(CRenderer* pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);

	private:
		static CRenderer* m_pRenderer;
		CFade* m_pFade;
		VERTEX_2D m_aVtx[4];						//���_���i�[���[�N	
		LPDIRECT3DTEXTURE9  m_pD3DTex;
		LPDIRECT3DDEVICE9 m_pDevice;

};

#endif