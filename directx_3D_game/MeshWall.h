//=============================================================================

// ���b�V���E�H�[���̏��� [MeshWall.h]
// Author : ���V�r�a

//=============================================================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WALL_NUM_BLOCK_X		(100)		//���̃u���b�N��
#define WALL_NUM_BLOCK_Z		(3)		//�c�̃u���b�N��
#define WALL_SIZE_BLOCK_X		(10)			//���̃u���b�N�T�C�Y
#define WALL_SIZE_BLOCK_Z		(10)			//�c�̃u���b�N�T�C�Y


//=============================================================================
// CScene�N���X���p������MeshWall�N���X
//=============================================================================
class CMeshWall:public CScene
{
	//���J�����o
	public:
		CMeshWall(OBJTYPE nObjType,int nPriority =3);		//�R���X�g���N�^
		~CMeshWall();										//�f�X�g���N�^

		HRESULT Init(CRenderer *pRenderer);		//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��

		static CMeshWall* CMeshWall::Create(CRenderer *pRenderer,float PosX,float PosY,float PosZ,float RotX,float RotY,float RotZ,float TranslateX,float TranslateY,float TranslateZ);

		void SetPos(float x,float y,float z){m_pos.x=x;m_pos.y=y;m_pos.z=z;};		//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_pos;};									//���W�̎擾

		void SetRot(float x,float y,float z){m_rot.x=x;m_rot.y=y;m_rot.z=z;};		//�p�x�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_rot;};									//�p�x�̎擾

		void SetTrans(float x,float y,float z){m_Trans.x=x;m_Trans.y=y;m_Trans.z=z;};		//���s�ړ�

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		HRESULT InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ);
		float GetFieldLengthX(void);			// ���S����w�[�܂�
		float GetFieldLengthZ(void);			// ���S����Z�[�܂�

	//����J�����o
	private:
		LPDIRECT3DTEXTURE9 m_pD3DTextureField;			// �e�N�X�`���ւ̃|�C���^
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffField;		// ���_�o�b�t�@�ւ̃|�C���^
		
		LPDIRECT3DINDEXBUFFER9 m_pD3DIndexBuffField;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		int m_nNumVertexIndex;							// ���_�̑��C���f�b�N�X��
		D3DXMATRIX m_mtxWorldField;			// ���[���h�}�g���b�N�X
		D3DXVECTOR3 m_pos;					// �ʒu
		D3DXVECTOR3 m_rot;					// ����
		D3DXVECTOR3 m_Trans;					//

		int m_nNumBlockX, m_nNumBlockZ;			// �u���b�N��
		int m_nNumVertex;						// �����_��
		int m_nNumPolygon;						// ���|���S����
		float m_fSizeBlockX, m_fSizeBlockZ;		// �u���b�N�T�C�Y
		LPDIRECT3DDEVICE9 m_pDevice;

		
		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
		
};


#endif
