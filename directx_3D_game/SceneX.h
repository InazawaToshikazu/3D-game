//=============================================================================
//
// ���C������ [SCENEX.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include"Scene.h"

//�O���錾
class CRenderer;

//=============================================================================
//CSceneX�N���X
//=============================================================================
class CSceneX:public CScene
{
	//���J�����o
	public:
		CSceneX(OBJTYPE nObjType,int nPriority =3);		//�R���X�g���N�^
		~CSceneX();										//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);		//������
		void Uninit(void);							//�I��
		void Update(void);							//�X�V
		void Draw(void);							//�`��

		static CSceneX *CSceneX::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);		//����

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};		//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};									//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//�p�x�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;};									//�p�x�̎擾

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		void SetFileName(char* FileName){m_FileName=FileName;};

		char *FileName;

	//����J�����o
	private:
		LPDIRECT3DDEVICE9 pDevice;
		//LPDIRECT3DTEXTURE9  g_pD3DTex;
		//LPDIRECT3DVERTEXBUFFER9 g_pD3DBuff;
		/*float g_fLength;
		float g_fAngle;*/
		
		LPD3DXMESH m_pD3DXMeshPlayer;		//���b�V�����̃|�C���^
		LPD3DXBUFFER m_D3DXBuffMatPlayer;	//�}�e���A�����ւ̃|�C���^
		DWORD m_nNumMatPlayer;				//�}�e���A�����̐�

		D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X


		D3DXVECTOR3 m_PosDest;		//�ړI�̎��_
		D3DXVECTOR3 m_RotDest;		//�ړI�̌���
		//�t���O
		bool m_PlayerMove;
		int m_ShootCnt;

		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

		char* m_FileName;

protected:
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Rot;			//���f���̌���
	D3DXVECTOR3 m_Scl;			//���f���̑傫��


};

#endif