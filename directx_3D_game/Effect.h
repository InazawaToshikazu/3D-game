//=============================================================================
//
// ���@���f���\������ [Player.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"


//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_MAX (100)

//�O���錾
class CRenderer;



//=============================================================================
//CSceneX�N���X���p������CEnemy�N���X
//=============================================================================
class CEffect:public CScene
{
	//���J�����o
	public:
		CEffect(OBJTYPE nObjType,int nPriority=3);		//�R���X�g���N�^
		~CEffect();										//�f�X�g���N�^

		HRESULT Init(CRenderer *pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		static CEffect* Create(int Red,int Green,int Blue,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};		//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//�p�x�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;};										//�p�x�̎擾

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	//����J�����o
	private:
		LPDIRECT3DTEXTURE9		m_pD3DTextureEffect;		// �e�N�X�`���ւ̃|�C���^
		LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuffEffect;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		LPDIRECT3DDEVICE9 m_pDevice;
		D3DXMATRIX m_mtxWorldeffect;				//���[���h�}�g���b�N�X
		
		D3DXVECTOR3 m_Pos;
		D3DXVECTOR3 m_Rot;
		D3DXVECTOR3 m_Scl;

		
		int m_EffectFlag;
		int m_EffectCnt;
		int m_EffectShow;

		CRenderer* m_pEffect;

		COLOR m_Color;

		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;



};

#endif


