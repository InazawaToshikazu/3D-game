//=============================================================================
//
// CScene3D [CScene3D.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"

//�O���錾
class CRenderer;

//=============================================================================
//CScene3D�N���X
//=============================================================================
class CScene3D:public CScene
{
	public:		// ���J

		CScene3D(OBJTYPE nObjType,int nPriority =3);			// �R���X�g���N�^
		~CScene3D();											// �f�X�g���N�^

		HRESULT Init(CRenderer *pRenderer);		// ������
		void Uninit(void);						// �I��
		void Update(void);						// �X�V
		void Draw(void);						// �`��

		static CScene3D* Create(float fPosX,float fPosY,float fPosZ,float fSizeX,float fSizeY,float fSizeZ,CRenderer* m_pRenderer);		//�I�u�W�F�N�g�̐���

		void SetPos(float x,float y,float z){}
		void SetScl(float x,float y,float z){m_Scl.x = x;m_Scl.y = y;m_Scl.z = z;};								//�傫���̐ݒ�

		void SetCamera(void);				// �J�����̐ݒ菈��
		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};		//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};				//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//��]�̎擾

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;}											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	private:	// ����J

		// �����o�ϐ�
		LPDIRECT3DDEVICE9 m_pD3DDevice;			// �f�o�C�X
		LPDIRECT3DTEXTURE9 m_pD3DTexture;		// �e�N�X�`���ւ̃|�C���^
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

		D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
		D3DXVECTOR3 m_Pos;						// �ʒu
		D3DXVECTOR3 m_Rot;						// ����(��])
		D3DXVECTOR3 m_Scl;						// �傫��(�X�P�[��)

		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
		static CRenderer *m_pScene3D;			//3D�̃|�C���^

};

#endif