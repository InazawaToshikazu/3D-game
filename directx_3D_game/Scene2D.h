//=============================================================================
//
// ���C������ [Scene2D.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include"Scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SCENE_2D (5)

//�O���錾
class CRenderer;

//=============================================================================
//CScene�N���X���p������CScene2D�N���X
//=============================================================================
class CScene2D:public CScene
{
	//���J�����o
	public:
		CScene2D(OBJTYPE nObjType,int nPriority =3);		//�R���X�g���N�^
		~CScene2D();										//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);		//������
		void Uninit(void);							//�I��
		void Update(void);							//�X�V
		void Draw(void);							//�`��

		static CScene2D* Create(float fPosX,float fPosY,float fSizeX,float fSizeY,char* TextureName,CRenderer* m_pRenderer,int nPriority =3);

		void SetSize(float x,float y,float z){m_Size.x=x;m_Size.y=y;m_Size.z=z;};

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//���W�̑��
		D3DXVECTOR3 GetPos(void){return m_Pos;};									//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};	//��]�p�x�̑��
		D3DXVECTOR3 GetRot(void){return m_Rot;};								//��]�p�x�̎擾

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		char* TextureName;

	//����J�����o
	private:
		LPDIRECT3DDEVICE9 m_pDevice;				//�f�o�C�X
		LPDIRECT3DTEXTURE9  m_pD3DTex;			//�e�N�X�`���ւ̃|�C���^
		LPDIRECT3DVERTEXBUFFER9 m_pD3DBuff;		//���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		D3DXVECTOR3 m_Pos;						//�|���S���̍��W
		D3DXVECTOR3 m_Size;						//�|���S���̃T�C�Y
		D3DXVECTOR3 m_Rot;						//�|���S���̉�]�p�x
		float m_fLength;						//���S���W�ƒ��_�ւ̋���
		float m_fAngle;							//���S���W�ƒ��_�ւ̊p�x
		D3DXVECTOR3 m_PosOld;					//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;					//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

};

#endif