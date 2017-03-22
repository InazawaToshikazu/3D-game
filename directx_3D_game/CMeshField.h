//=============================================================================

// ���b�V���t�B�[���h���� [MeshField.h]
// Author : ���V�r�a

//=============================================================================


#ifndef _CFIELD_H_
#define _CFIELD_H_
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene3D.h"

//=============================================================================
// �O���錾
//=============================================================================
class CRenderer;
class CScene3D;

//=============================================================================
// CScene���p������MeshField�N���X
//=============================================================================
class CField : public CScene
{
	// ���J�����o
	public:
		CField(OBJTYPE nObjType,int nPriority =3);		//�R���X�g���N�^
		~CField();										//�f�X�g���N�^
		HRESULT Init(CRenderer* pRenderer);				//������
		void Uninit();									//���
		void Update();									//�X�V
		void Draw();									//�`��
		void SetPosition(D3DXVECTOR3 pos){m_Pos = pos;};//accerer
		void SetPosition(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};//accerer
		void SetRot(D3DXVECTOR3 angle){m_Rot = angle;};	//accerer
		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//���W�̑��
		D3DXVECTOR3 GetPos(void){return m_Pos;};		//���W�̎擾
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};	//��]�p�x�̑��
	
		D3DXVECTOR3 GetRot(void){return m_Rot;};		//accerer
		D3DXVECTOR3 GetPosition(void){return m_Pos;};	//accerer
	
		static CField* Create(CRenderer* pRenderer,float fPosX,float fPosY,float fPosZ);	//����
	
		float GetHeight(D3DXVECTOR3 Pos,D3DXVECTOR3* pNormal);
		float GetHeightPolygon(const D3DXVECTOR3& P0,const D3DXVECTOR3& P1,const D3DXVECTOR3& P2,const D3DXVECTOR3& Pos,D3DXVECTOR3* pNormal);
		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};
		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};
		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};
	
	//=============================================================================
	// ����J�����o
	//=============================================================================
	private:
		void SetVertexPolygon();				//���W�ݒ�
		HRESULT InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
	
		VERTEX_3D *m_pVtx;						//���W�\���̕ϐ�
		LPDIRECT3DDEVICE9 m_pD3DDevice;			//Device�I�u�W�F�N�g(�`��ɕK�v)
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtexBuff;	//Texture�I�u�W�F�N�g(�`��ɕK�v)
		LPDIRECT3DINDEXBUFFER9 m_pD3DIndexBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		LPDIRECT3DTEXTURE9 m_pD3DTex;			//�e�N�X�`���p�ϐ�
	
		//���W�֌W
		D3DXVECTOR3 m_Pos;				//���W
		D3DXVECTOR3 m_Rot;				//�p�x
		D3DXVECTOR3 m_Scl;				//�傫��
	
		int m_nNumVertexIndex;			//���_�̑��C���f�b�N�X��
	
		int m_nNumBlockX; 				//���̃u���b�N��
		int m_nNumBlockZ;				//�c�̃u���b�N��
		float m_fSizeBlockX;			//���̃u���b�N�T�C�Y
		float m_fSizeBlockZ;			//�c�̃u���b�N�T�C�Y
	
		int m_nNumVertex;				// �����_��
		int m_nNumPolygon;				// ���|���S����
	
		//int m_nNumVertexIndex;			// ���_�̑��C���f�b�N�X��
	
		//��]�p�ϐ�
		float n_fLength;						//��]�p�ϐ�
		float n_fAngle;							//��]�p�ϐ�
		// ���_���Z�b�g
		VERTEX_3D *pVtx;
	
		D3DXVECTOR3 m_PosOld;					//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;					//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
	
};// class CWall
#endif

// EOF