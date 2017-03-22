//=============================================================================
//
// �X�R�A���� [Score.h]
// Author : ���V�r�a
//
//=============================================================================
#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include"Scene.h"
#include "Number.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define SCORE_MAX	(99999)		//�J���X�g
#define DIGIT		(5)			//����
//�O���錾
class CRenderer;
class CNumber;
//=============================================================================
//CScore�N���X
//=============================================================================
class CScore:public CScene
{
	//���J�����o
	public:
		CScore(OBJTYPE nObjType,int nPriority=3);		//�R���X�g���N�^	
		~CScore();										//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);		//������
		void Uninit(void);							//�I��
		void Update(void);							//�X�V
		void Draw(void);							//�`��

		static CScore* Create(float fPosX,float fPosY,CRenderer* m_pRenderer);		//����

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};		//���W�̑��
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};		//��]�p�x�̑��
		D3DXVECTOR3 GetRot(void){return m_Rot;};									//��]�p�x�̎擾

		static void AddScore(int nValue);						//�X�R�A�̉��Z

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̍��W�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		static int GetScore(void){return m_nScore;};		//�X�R�A�̎擾

	//����J�����o
	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		D3DXVECTOR3 m_Pos;						//�|���S���̍��W
		D3DXVECTOR3 m_Rot;						//�|���S���̉�]�p�x
		float m_fLength;						//���S���W�ƒ��_�ւ̋���
		float m_fAngle;							//���S���W�ƒ��_�ւ̊p�x
		LPDIRECT3DVERTEXBUFFER9 m_pD3DScoreVtxBuff;
		LPDIRECT3DTEXTURE9 m_pD3DScore;

		static int m_nScore;		//�X�R�A

		static CRenderer* m_pScore;		//�X�R�A�̃|�C���^
		static CNumber* m_pNumber;		//�i���o�[�̃|�C���^
		
		D3DXVECTOR3 m_PosOld;						//�O�t���̍��W
		D3DXVECTOR3 m_RotOld;						//�O�t���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

};

#endif
