//=============================================================================
//
// ���@���f���\������ [Player.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _LEG_H_
#define _LEG_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "SceneX.h"

//=============================================================================
// �}�N����`
//=============================================================================

//�O���錾
class CRenderer;
class CFade;
class CNeedle;
class CPlayer;
//=============================================================================
//CSceneX�N���X���p������CEnemy�N���X
//=============================================================================
class CLeg:public CSceneX
{
	//���J�����o
	public:
		CLeg(OBJTYPE nObjType,int nPriority=3);		//�R���X�g���N�^
		~CLeg();										//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);			//������
		void Uninit(void);								//�I��
		void Update(void);								//�X�V
		void Draw(void);								//�`��

		static CLeg* CLeg::Create(float Ratio,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);	//����

		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};								//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//��]�̎擾

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		CScene* GetSceneLink(void){return m_pSceneLink;};		//�M�~�b�N�̃����N

		static bool GetRotFlag(void){return m_RotFlag;};			//��]�t���O�̎擾

		void AddRot(float x,float y,float z){m_Rot.x+=x;m_Rot.y+=y;m_Rot.z+=z;};			//��]�̐ݒ�


		int GetBulletCnt(void){return m_BulletCnt;};

		void SetRatio(float Ratio){m_Ratio=Ratio;};		//�O�t���̍��W�̐ݒ�


	//����J�����o
	private:
		D3DXVECTOR3 m_rotDestModel;				//�ړI�̌���
		D3DXVECTOR3 m_Rot;						//���f���̌���
		D3DXVECTOR3 m_speedModel;				//���f���̃X�s�[�h
		D3DXVECTOR3 m_Pos;					//���f���̃X�s�[�h
		D3DXVECTOR3 m_RotDest;					//�ړI�̌���


		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

		D3DXVECTOR3 m_PosOld;		//�O�t���̍��W
		D3DXVECTOR3 m_RotOld;		//�O�t���̊p�x

		D3DXVECTOR3 GimmickPos[4];	//�M�~�b�N��4���_�̍��W

		CScene* m_pSceneLink;		//�M�~�b�N�Ƃ̃����N


		bool m_Moving;							//���f���������Ă邩
		float m_fDiffRotY;

		static bool m_RotFlag;		//��]�t���O
		int m_BulletCnt;

		CPlayer* m_pPlayer;

		float m_Ratio;
		static CRenderer *m_pLeg;			//�v���C���[�̃|�C���^
		int m_State;
		static int m_LegNum;
		float m_Rotate;
};

#endif

