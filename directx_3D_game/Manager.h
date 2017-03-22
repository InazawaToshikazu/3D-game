//=============================================================================
//
// �}�l�[�W������ [CManager.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//�Q�[���̃��[�h
typedef enum
{
	MODE_TITLE,		//�^�C�g�����
	MODE_GAME,		//�Q�[�����
	MODE_RESULT,	//���U���g���
	MODE_GAMEOVER,	//�Q�[���I�[�o�[���
	MODE_RESET
}MODE;


//�O���錾
class CRenderer;
class CField;
class CCamera;
class CLight;
class CPlayer;
class CGimmick;
class CDebugProc;
class CFade;
class CGame;
class CTitle;
class CResult;

//=============================================================================
//CManager�N���X
//=============================================================================
class CManager
{
	//���J�����o
	public:
		CManager();		//�R���X�g���N�^
		~CManager();	//�f�X�g���N�^

		HRESULT Init(HINSTANCE hInstance,HWND hWnd,bool bWindow);		//������
		void Uninit(void);												//�I��
		void Update(void);												//�X�V
		void Draw(void);												//�`��

		static CRenderer* GetRenderer(void){return m_pRenderer;};		//Renderer�̃|�C���^�̎擾

		static void SetNextPhase(MODE mode){m_NextPhase=mode;};			//���[�h�̐ݒ�
		static MODE GetNextPhase(void){return m_NextPhase;};			//���[�h�̎擾

		static MODE GetPhase(void){return m_Phase;};			//���[�h�̎擾

		static void SetPauseFlag(bool PauseFlag);						//�|�[�Y�̐ݒ�
		static bool GetPauseFlag(void){return m_PauseFlag;};			//�|�[�Y�̎擾

		void PhaseExchange(void);										//�t�F�[�Y�̐؂�ւ�

		static void SetFadeFlag(bool FadeFlag){m_FadeFlag=FadeFlag;};	//�t�F�[�h�t���O�̐ݒ�
		static bool GetFadeFlag(void){return m_FadeFlag;}				//�t�F�[�h�t���O�̎擾

		static CCamera* GetCamera(void){return m_pCamera;};

	//����J�����o
	private:
		static CRenderer* m_pRenderer;
		CFade* m_pFade;				//�t�F�[�h�̃|�C���^
		static CGame* m_pGame;		//�Q�[����ʂ̃|�C���^
		static CTitle* m_pTitle;	//�^�C�g����ʂ̃|�C���^
		static CResult* m_pResult;	//���U���g��ʂ̃|�C���^

		CLight* m_pLight;			//���C�g�̃|�C���^
		//CCamera* m_pCamera;			//�J�����̃|�C���^
		CDebugProc* m_pDebug;		//�f�o�b�O�\���̃|�C���^

		static MODE m_Phase;		//���݂̃t�F�[�Y
		static MODE m_NextPhase;	//���̃t�F�[�Y
		static bool m_PauseFlag;	//�|�[�Y�t���O
		static bool m_FadeFlag;		//�t�F�[�h�t���O
		static CCamera* m_pCamera;

};

#endif