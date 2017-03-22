//=============================================================================
//
// �e�\������ [Shadow.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

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

class CRenderer;
class CPlayer;
//=============================================================================
//CEnemy�N���X
//=============================================================================
class CShadow:public CSceneX
{
	public:
		CShadow(OBJTYPE nObjType,int nPriority=3);
		~CShadow();
		HRESULT Init(CRenderer* m_pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		static CShadow* CShadow::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);
		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};								//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//��]�̎擾




		
	private:
		D3DXVECTOR3 m_rotDestModel;				//�ړI�̌���
		bool m_Moving;							//���f���������Ă邩
		float m_fDiffRotY;
		D3DXVECTOR3 m_Rot;						//���f���̌���
		D3DXVECTOR3 m_speedModel;				//���f���̃X�s�[�h
		D3DXVECTOR3 m_Pos;						//���f���̃X�s�[�h
		D3DXVECTOR3 m_Scl;
		D3DXVECTOR3 m_RotDest;					//�ړI�̌���
		static CRenderer *m_pShadow;
		D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
		LPD3DXMESH m_pD3DXMesh;		//���b�V�����̃|�C���^
		LPD3DXBUFFER m_D3DXBuffMat;	//�}�e���A�����ւ̃|�C���^
		LPDIRECT3DDEVICE9 pDevice;
		DWORD m_nNumMat;				//�}�e���A�����̐�
		LPDIRECT3DVERTEXBUFFER9 m_pD3DBuff;		//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		static CPlayer* m_pPlayer;
		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x

		CScene* m_pSceneLink;		//�M�~�b�N�Ƃ̃����N

		D3DXVECTOR3 GimmickPos[4];	//�M�~�b�N��4���_�̍��W







};

#endif