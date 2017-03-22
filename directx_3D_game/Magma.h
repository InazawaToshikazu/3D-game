//
//�߂����t�B�[���h
//

#ifndef _MAGMA_H_
#define _MAGMA_H_
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "Scene3D.h"
//=============================================================================
// �O���錾
//=============================================================================
class CRenderer;
class CScene3D;

//=============================================================================
// �N���X��`
//=============================================================================
class CMagma : public CScene3D
{
//=============================================================================
// ���J�����o
//=============================================================================
public:
	CMagma(OBJTYPE nObjType,int nPriority =3);										//�R���X�g���N�^
	~CMagma();										//�f�X�g���N�^
	HRESULT Init(LPDIRECT3DDEVICE9 device);			//������
	void Uninit();									//���
	void Update();									//�X�V
	void Draw();									//�`��
	void SetPosition(D3DXVECTOR3 pos){m_Pos = pos;};//accerer
	void SetPosition(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};//accerer
	void SetRot(D3DXVECTOR3 angle){m_Rot = angle;};	//accerer

	D3DXVECTOR3 GetRot(void){return m_Rot;};		//accerer
	D3DXVECTOR3 GetPosition(void){return m_Pos;};	//accerer

	static CMagma* Create(LPDIRECT3DDEVICE9 device,float fPosX,float fPosY,float fPosZ);	

	float GetHeight(D3DXVECTOR3 Pos,D3DXVECTOR3* pNormal);
	float GetHeightPolygon(const D3DXVECTOR3& P0,const D3DXVECTOR3& P1,const D3DXVECTOR3& P2,const D3DXVECTOR3& Pos,D3DXVECTOR3* pNormal);


//=============================================================================
// ����J�����o
//=============================================================================
private:
	void SetVertexPolygon();				//���W�ݒ�
	HRESULT InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);

	VERTEX_3D *n_pVtx;						//���W�\���̕ϐ�
	LPDIRECT3DDEVICE9 n_pD3DDevice;			//Device�I�u�W�F�N�g(�`��ɕK�v)
	LPDIRECT3DVERTEXBUFFER9 n_pD3DVtexBuff;	//Texture�I�u�W�F�N�g(�`��ɕK�v)
	LPDIRECT3DINDEXBUFFER9 n_pD3DIndexBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 n_pD3DTex;			//�e�N�X�`���p�ϐ�

	//���W�֌W
	D3DXVECTOR3 m_Pos;						//���W�ϐ�
	D3DXVECTOR3 m_Rot;						//�p�x�ϐ�
	D3DXVECTOR3 m_Scl;

	int n_nNumVertexIndex;					//���_�̑��C���f�b�N�X��

	int m_nNumBlockX; 			// �u���b�N��
	int m_nNumBlockZ;
	float m_fSizeBlockX;		// �u���b�N�T�C�Y
	float m_fSizeBlockZ;

	int m_nNumVertex;						// �����_��
	int m_nNumPolygon;						// ���|���S����

	int m_nNumVertexIndex;							// ���_�̑��C���f�b�N�X��

	//��]�p�ϐ�
	float n_fLength;						//��]�p�ϐ�
	float n_fAngle;							//��]�p�ϐ�
	// ���_���Z�b�g
	VERTEX_3D *pVtx;

	// ����
	float m_fWaterTime;

	float m_Rotate;

	// �F
	unsigned char m_Color;
	unsigned char m_ColorAdd;

};// class CWall
#endif

// EOF