//=============================================================================
//
// ���C������ [SceneBillboard.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _SCENEBillBOARD_H_
#define _SCENEBILLBOARD_H_


#include"Scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_MAX (50)

//�O���錾
class CRenderer;

//=============================================================================
//CScene�N���X���p������CSceneBillboard�N���X
//=============================================================================
class CSceneBillboard:public CScene
{
	//���J�����o
	public:
		CSceneBillboard(OBJTYPE nObjType,int nPriority =3);		//�R���X�g���N�^
		~CSceneBillboard();										//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);		//������
		void Uninit(void);							//�I��
		void Update(void);							//�X�V
		void Draw(void);							//�`��

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

		void SetSize(float x,float y,float z){m_Scl.x=x;m_Scl.y=y;m_Scl.z=z;};		//�O�t���̍��W�̐ݒ�

	//����J�����o
	private:
		CRenderer* pRenderer;
		LPDIRECT3DDEVICE9 pDevice;
		LPDIRECT3DTEXTURE9  m_pD3DTex;
		LPDIRECT3DVERTEXBUFFER9 m_pD3DBuff;		//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		D3DXMATRIX m_mtxWorldBullet;			//���[���h�}�g���b�N�X

		D3DXVECTOR3 m_Pos;		//���W
		D3DXVECTOR3 m_Rot;		//�p�x
		D3DXVECTOR3 m_Scl;		//�傫��

		float m_fLength;
		float m_fAngle;

		CSceneBillboard *m_pBillboard;

		float SpeedX;							//X�����x
		float SpeedZ;							//Z�����x
		bool BulletFlag;						//�g�p�t���O

		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

};

#endif