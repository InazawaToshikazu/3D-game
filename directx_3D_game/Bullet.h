//=============================================================================

// �e�̏��� [Bullet.h]
// Author : ���V�r�a

//=============================================================================
#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "SceneBillboard.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_MAX (50)

//�O���錾
class CRenderer;

//=============================================================================
//CSceneBillboard�N���X���p������Bullet�N���X
//=============================================================================
class CBullet:public CSceneBillboard
{
	//���J�����o
	public:
		CBullet(OBJTYPE nObjType,int nPriority =3);
		~CBullet();
		HRESULT Init(CRenderer* m_pRenderer);		//������
		void Uninit(void);							//�I��
		void Update(void);							//�X�V
		void Draw(void);							//�`��
		static CBullet *CBullet::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer,float dir);		//����

	//����J�����o
	private:
		LPDIRECT3DDEVICE9 m_pD3DDevice;
		CRenderer* pRenderer;
		D3DXVECTOR3 m_Pos;			//���W
		D3DXVECTOR3 m_Rot;			//�p�x
		D3DXVECTOR3 m_Scl;			//�傫��
		float SpeedX;				//X�����x
		float SpeedZ;				//Z�����x
		float Direction;
		D3DXVECTOR3 WallPos[4];
	

};

#endif