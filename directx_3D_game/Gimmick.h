//=============================================================================
//
// �M�~�b�N�\������ [Gimmick.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _GIMMICK_H_
#define _GIMMICK_H_

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

//=============================================================================
//CScene�N���X���p������CGimmick�N���X
//=============================================================================
class CGimmick:public CSceneX
{
	//���J�����o
	public:
		CGimmick(OBJTYPE nObjType,int nPriority=3);		//�R���X�g���N�^
		~CGimmick();									//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);			//������
		void Uninit(void);								//�I��
		void Update(void);								//�X�V
		void Draw(void);								//�`��

		static CGimmick* Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);	//����

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};	//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};										//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};	//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};										//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		void SetScl(float x,float y,float z){m_Scl.x=x;m_Scl.y=y;m_Scl.z=z;};

		
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾

	//����J�����o
	private:
		D3DXVECTOR3 m_Pos;
		D3DXVECTOR3 m_Rot;			//�p�x
		D3DXVECTOR3 m_Scl;
		D3DXVECTOR3 m_PosOld;		//�O�t���̍��W
		D3DXVECTOR3 m_RotOld;		//�O�t���̊p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
		float Movex;
		float Movez;



};

#endif