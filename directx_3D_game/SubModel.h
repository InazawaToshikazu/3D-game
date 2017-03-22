//=============================================================================
//
// ���C������ [SCENEX.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _SUBMODEL_H_
#define _SUBMODEL_H_

#include"Scene.h"

//�O���錾
class CRenderer;

//=============================================================================
//CSceneX�N���X
//=============================================================================
class CSubModel
{
	public:
		CSubModel(int nPriority =3);
		~CSubModel();
		HRESULT Init(CRenderer* m_pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		static CSubModel *CSubModel::Create(float fPosX,float fPosY,float fPosZ,char* FileName,CRenderer* m_pRenderer);
		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};
		void SetFileName(char* FileName){m_FileName=FileName;};
		void SetScl(float x,float y,float z){m_Scl.x=x;m_Scl.y=y;m_Scl.z=z;};
		void SetParent(CSubModel* Parent){m_Parent=Parent;};
		D3DXMATRIX GetWorld(){return m_mtxWorld;};
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//��]�̎擾

	private:
		LPDIRECT3DDEVICE9 pDevice;
		D3DXVECTOR3 m_Pos;
		D3DXVECTOR3 m_Rot;
		D3DXVECTOR3 m_Scl;
		LPD3DXMESH m_pD3DXMeshPlayer;		//���b�V�����̃|�C���^
		LPD3DXBUFFER m_D3DXBuffMatPlayer;	//�}�e���A�����ւ̃|�C���^
		DWORD m_nNumMatPlayer;				//�}�e���A�����̐�

		D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X

		char* m_FileName;

		CSubModel* m_Parent;



};

#endif