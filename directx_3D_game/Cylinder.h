//=============================================================================
//
// �V�����_�[�\������ [Cylinder.cpp]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "Scene.h"

//=============================================================================
//CScene���p������CCylinder�N���X
//=============================================================================
class CCylinder :public CScene
{
	//���J�����o
	public:
		CCylinder(OBJTYPE nObjType,int nPriority =3);		//�R���X�g���N�^
		~CCylinder();										//�f�X�g���N�^
		HRESULT Init(CRenderer *pRenderer){return S_OK;};	// ������
		HRESULT Init(CRenderer *pRenderer,int SizeX,int SizeY,int NumW,int NumH);
		void Uninit(void);									//�I��
		void Update(void);									//�X�V
		void Draw(void);									//�`��

		static CCylinder* Create(float SizeX,float SizeZ,int NumX,int NumZ,float fPosX,float fPosY,float fPosZ,CRenderer* pRenderer);

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//���W�̑��
		D3DXVECTOR3 GetPos(void){return m_Pos;};									//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};		//��]�p�x�̑��
		D3DXVECTOR3 GetRot(void){return m_Rot;};									//��]�p�x�̎擾

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};


	//����J�����o
	private:
		LPDIRECT3DDEVICE9 m_pD3DDevice;
		LPDIRECT3DTEXTURE9 m_pD3DTex;
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtx;
		LPDIRECT3DINDEXBUFFER9 m_pD3DIndex;

		D3DXVECTOR3 m_Pos;		//���W
		D3DXVECTOR3 m_Rot;		//��]
		D3DXVECTOR3 m_Scl;		//�傫��

		int m_nNumIndex;
		int m_nNumWeight,m_nNumHigh;		//�����ƍ���
		int m_nNumVertex;
		int m_nNum;
		float m_fSizeWeight,m_fSizeHigh;	//���T�C�Y�Əc�T�C�Y
		D3DXVECTOR2 m_Length;
		static float m_Lengthin[1];
		static int m_nCylinderNum;

		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;





		
};








#endif