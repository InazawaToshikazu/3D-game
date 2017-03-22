//=============================================================================
//
// �|�[�Y���� [Pause.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
//�|�[�Y���j���[
typedef enum
{
	RETURN_GAME=0,
	RETURN_TITLE,
	RETRY,
	NONE,
	PAUSE_MANU_MAX
}PAUSE_MENU;

// �O���錾
class CRenderer;
class CScene2D;
class CFade;

//=============================================================================
//Pause�N���X
//=============================================================================
class CPause
{
	//���J�����o
	public:
		CPause();		//�R���X�g���N�^
		~CPause();		//�f�X�g���N�^

		HRESULT Init(CRenderer* pRenderer);		//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��

		PAUSE_MENU GetMenu(void){return m_CurrentMenu;};	//

	//����J�����o
	private:
		CScene2D* m_pReturnTitle;		//�^�C�g���֖߂�
		CScene2D* m_pReturnGame;		//�Q�[���ɖ߂�
		CScene2D* m_pRetry;				//���g���C
		CScene2D* m_pArrow;				//���
		int m_Num;						//���Ԗڂ�
		CFade* m_pMask;
		PAUSE_MENU m_CurrentMenu;
};

#endif