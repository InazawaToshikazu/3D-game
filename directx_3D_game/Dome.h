//=============================================================================
//
// Dome�\������ [Dome.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _DOME_H_
#define _DOME_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"

//�O���錾
class CRenderer;

//=============================================================================
//CScene�N���X���p������CDome�N���X
//=============================================================================
class CDome:public CScene
{
	//���J�����o
	public:
		CDome(OBJTYPE nObjType,int nPriority =3);			// �R���X�g���N�^
		~CDome();											// �f�X�g���N�^
		HRESULT Init(CRenderer *pRenderer){return S_OK;};	// ������
		HRESULT Init(CRenderer *pRenderer,int SizeX,int SizeY,int NumH,int NumW);	// ������

		void SetPos(float x,float y,float z){}
		void Uninit(void);					// �I��
		void Update(void);					// �X�V
		void Draw(void);					// �`��
		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};		//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};				//���W�̎擾
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;}				//��]�̎擾

		static CDome* Create(float SizeX,float SizeZ,int NumX,int NumZ,float fPosX,float fPosY,float fPosZ,CRenderer* pRenderer);

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̉�]�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̉�]�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	private:	// ����J
		// �����o�ϐ�
		LPDIRECT3DDEVICE9 m_pD3DDevice;			// �f�o�C�X
		LPDIRECT3DTEXTURE9 m_pD3DTex;		// �e�N�X�`���ւ̃|�C���^
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtx;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		LPDIRECT3DINDEXBUFFER9 m_pD3DIndex;

		D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
		D3DXVECTOR3 m_Pos;						// ���W
		D3DXVECTOR3 m_Rot;						// ����(��])
		D3DXVECTOR3 m_Scl;						// �傫��(�X�P�[��)

		int m_nNumIndex;			//���_�̑��C���f�b�N�X��
		int m_nNumWeight,m_nNumHigh;		//�u���b�N��
		int m_nNumVertex;			//�����_��
		int m_nNum;					//���|���S����
		float m_fSizeWeight,m_fSizeHigh;	//�u���b�N�T�C�Y
		float m_Length;

		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;



};

#endif