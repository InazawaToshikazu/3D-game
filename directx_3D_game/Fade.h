//=============================================================================
//
// Fade���� [Fade.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "Scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
//�t�F�[�h�̎��
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_IN_FINISH,
	FADE_OUT,
	FADE_OUT_FINISH,
	FADE_INFINITY,
	FADE_MAX
}FADE;


//�O���錾
class CRenderer;


//�K��Scene�J�ڂ̍ۂɎg���t�F�[�h�͈�ԍŌ�ɍX�V���邱��
//���Ȃ��ƃL�[�{�[�h���X�V����Ȃ��Ȃ�\������

//=============================================================================
// CScene2D���p������CFade�N���X
//=============================================================================
class CFade:public CScene2D
{
	//���J�����o
	public:
		CFade(OBJTYPE nObjType,int nPriority =7);							// �R���X�g���N�^
		~CFade();						// �f�X�g���N�^
		HRESULT Init(CRenderer *pRenderer);	// ������

		void SetPos(float x,float y,float z){}
		void Uninit(void);					// �I��
		void Update(void);					// �X�V
		void Draw(void);					// �`��

		void SetFade(FADE fade){m_Mode = fade;};		//�t�F�[�h�̐ݒ�
		FADE GetFade(void){return m_Mode;};				//�t�F�[�h�̏�Ԃ̎擾
		static CFade* Create(CRenderer *pRenderer);		//�I�u�W�F�N�g�̐���
		void FadeStart(FADE Mode,int Time,COLOR Color);				//�t�F�[�h�̊J�n

	//����J�����o
	private:
		LPDIRECT3DDEVICE9 m_pD3DDevice;			// �f�o�C�X
		VERTEX_2D m_aFadeVtx[4];
		LPDIRECT3DTEXTURE9 m_pD3DFadeTex;
		FADE m_Mode;							//���[�h
		int m_aAlpha;							//�A���t�@�l
		int m_Time;								//����
		COLOR m_Color;							//�F
		bool m_Flag;								//�t�F�[�h�t���O
		int m_RateAdd;
};

#endif