//=============================================================================
//
// �n�ʏ��� [Explosion.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//======================================================
//�C���N���[�h
//======================================================
#include"main.h"
#include"Scene.h"

//======================================================
//�}�N����`
//======================================================


//�O���錾
class CRenderer;

//======================================================
//CScene�N���X���p������CExplosion�N���X
//=======================================================
class CExplosion:public CScene
{
	//���J�����o
	public:
		CExplosion(OBJTYPE nObjType,int nPriority=3);
		~CExplosion();
		HRESULT Init(CRenderer *m_pRenderer);				//���������̏�����
		void Update(void);					//���������̍X�V
		void Uninit(void);					//���������̏I��
		void Draw(void);					//���������̕`��

		void TextureUpdate(float x,float y);		//���������̃e�N�X�`���̐ݒ�
		void DeleteExplosion(void);					//���������̍폜

		void SetExplosionPosition(float PosX,float PosY,float PosZ);		//

		static CExplosion* Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);		//����

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};		//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//�p�x�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;};										//�p�x�̎擾

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};	//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};										//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};	//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};										//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	//����J�����o
	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		LPDIRECT3DTEXTURE9		m_pD3DTex;						// �e�N�X�`���ւ̃|�C���^
		LPDIRECT3DVERTEXBUFFER9 m_pD3DBuff;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		
		D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
		CRenderer* pRenderer;
		
		D3DXVECTOR3 m_Pos;			//���W
		D3DXVECTOR3 m_Rot;			//�p�x
		D3DXVECTOR3 m_Scl;			//�傫��

		int m_nCounterAnim;
		int m_nPatternAnim;

		
		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;
	



};
#endif
