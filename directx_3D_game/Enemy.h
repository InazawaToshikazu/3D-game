//=============================================================================
//
// �G���f���\������ [Enemy.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "SceneX.h"

//=============================================================================
// �}�N����`
//=============================================================================


class CRenderer;
//=============================================================================
//CSceneX���p������CEnemy�N���X
//=============================================================================
class CEnemy:public CSceneX
{
	//���J�����o
	public:
		CEnemy(OBJTYPE nObjType,int nPriority =3);		//�R���X�g���N�^
		~CEnemy();										//�f�X�g���N�^
		HRESULT Init(CRenderer* m_pRenderer);			//������	
		void Uninit(void);								//�I��
		void Update(void);								//�X�V
		void Draw(void);								//�`��

		static CEnemy* CEnemy::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);		//����

	//����J�����o
	private:
		D3DXVECTOR3 m_Scl;
		static CSceneX *m_pSceneDummy;

};

#endif