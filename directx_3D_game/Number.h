//=============================================================================
//
// �����\������ [Number.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene2D.h"
//=============================================================================
// �}�N����`
//=============================================================================


// �O���錾
class CRenderer;

//=============================================================================
//CNumber�N���X
//=============================================================================
class CNumber
{
	//���J�����o
	public:
		CNumber();		//�R���X�g���N�^
		~CNumber();		//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);		//������
		void Uninit(void);							//�I��
		void Update(void);							//�X�V
		void Draw(void);							//�`��

		static CNumber* Create(float fPosX,float fPosY,CRenderer* m_pRenderer);		//����

		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//���W�̑��
		D3DXVECTOR3 GetPos(void){return m_Pos;};									//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};		//��]�p�x�̑��
		D3DXVECTOR3 GetRot(void){return m_Rot;};									//��]�p�x�̎擾

		void UpdateNumber(int nNumber);					//�����̍X�V
		void SetNumber(int Num){m_Number = Num;};

	//����J�����o
	private:
		D3DXVECTOR3 m_Pos;						//�|���S���̍��W
		D3DXVECTOR3 m_Rot;						//�|���S���̉�]�p�x

		CRenderer *m_pNumber;					//�����̃|�C���^
		LPDIRECT3DVERTEXBUFFER9 m_pD3DNumberVtxBuff;
		LPDIRECT3DTEXTURE9 m_pD3DNumber;
		LPDIRECT3DDEVICE9 m_pDevice;
		int m_Number;

};

#endif

