/*������̐K���U�����I�ɓ���������t�b�N�V���b�g�݂�����
�Ђ����Ƃ��E�E�E*/

//=============================================================================
//
// �ړI�n�̃��f���\������ [Goal.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _TARGET_H_
#define _TARGET_H_

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
class CRenderer;
class CFade;

//=============================================================================
//CSceneX�N���X���p������CEnemy�N���X
//=============================================================================
class CTarget:public CSceneX
{
	//���J�����o
	public:
		CTarget(OBJTYPE nObjType,int nPriority=3);		//�R���X�g���N�^
		~CTarget();										//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);			//������
		void Uninit(void);								//�I��
		void Update(void);								//�X�V
		void Draw(void);								//�`��

		static CTarget* CTarget::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);	//����

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


		void AddRot(float x,float y,float z){m_Rot.x+=x;m_Rot.y+=y;m_Rot.z+=z;};			//��]�̐ݒ�

		static CFade* GetGFade(void){return m_pFade;};			//�t�F�[�h�̃|�C���^�̎擾

		


	//����J�����o
	private:
		D3DXVECTOR3 m_rotDestModel;				//�ړI�̌���
		D3DXVECTOR3 m_Rot;						//���f���̌���
		D3DXVECTOR3 m_Pos;				//���f���̃X�s�[�h
		D3DXVECTOR3 m_RotDest;					//�ړI�̌���


		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

		D3DXVECTOR3 m_PosOld;		//�O�t���̍��W
		D3DXVECTOR3 m_RotOld;		//�O�t���̊p�x

		D3DXVECTOR3 GimmickPos[4];	//�M�~�b�N��4���_�̍��W

		CScene* m_pSceneLink;		//�M�~�b�N�Ƃ̃����N
		static CRenderer *m_pTarget;			//�ړI�n�̃|�C���^
		static CFade* m_pFade;		//�t�F�[�h�̃|�C���^
};

#endif
