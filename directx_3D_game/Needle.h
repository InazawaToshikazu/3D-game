//=============================================================================
//
// ���@���f���\������ [Player.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _NEEDLE_H_
#define _NEEDLE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "SceneX.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ANGLE_LEFT	(D3DX_PI/2.0f)
#define ANGLE_RIGHT	(-D3DX_PI/2.0f)
#define ANGLE_FLONT	(D3DX_PI)
#define ANGLE_BACK	(0.0f)

//�O���錾
class CCollision;
class CRenderer;
class CTarget;
class CFade;
class CPlayer;

//=============================================================================
//CSceneX�N���X���p������CEnemy�N���X
//=============================================================================
class CNeedle:public CSceneX
{
	//���J�����o
	public:
		CNeedle(OBJTYPE nObjType,int nPriority=3);		//�R���X�g���N�^
		~CNeedle();										//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);			//������
		void Uninit(void);								//�I��
		void Update(void);								//�X�V
		void Draw(void);								//�`��

		static CNeedle* CNeedle::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);	//����

		void SetPosition(D3DXVECTOR3 Pos){m_PosDest = Pos;};								//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//��]�̎擾


		CScene* GetSceneLink(void){return m_pSceneLink;};		//�M�~�b�N�̃����N

		static bool GetRotFlag(void){return m_RotFlag;};			//��]�t���O�̎擾

		void AddRot(float x,float y,float z){m_Rot.x+=x;m_Rot.y+=y;m_Rot.z+=z;};			//��]�̐ݒ�

		static CFade* GetGFade(void){return m_pFade;};			//�t�F�[�h�̃|�C���^�̎擾

		int GetBulletCnt(void){return m_BulletCnt;};
		void SetBulletCnt(int i){m_BulletCnt=i;};

		bool GetHitFlag(void){return m_HitFlag;};
		void SetHitFlag(bool flag){m_HitFlag=flag;};

		void Shot(D3DXVECTOR3 vector);
		void Return(void);


	//����J�����o
	private:
		static CRenderer *m_pNeedle;			//�v���C���[�̃|�C���^


		CScene* m_pSceneLink;		//�M�~�b�N�Ƃ̃����N

		static CNeedle* m_pFlag;	//
		static CFade* m_pFade;		//�t�F�[�h�̃|�C���^

		bool m_Moving;							//���f���������Ă邩
		float m_fDiffRotY;
		bool m_JFlag;	//�W�����v�t���O

		// �X�s�[�h
		D3DXVECTOR3 m_speed;

		static bool m_RotFlag;		//��]�t���O
		int m_BulletCnt;

		D3DXVECTOR3 m_PosDest;					//�ړI�̌���

		CCollision* m_pCollision;
		CTarget* m_pTarget;
		CPlayer* m_pPlayer;

		bool m_HitFlag;
};

#endif

