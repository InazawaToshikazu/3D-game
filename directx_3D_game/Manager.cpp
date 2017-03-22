//=============================================================================
//
// ���C������ [Manager.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Camera.h"
#include "Light.h"
#include "Scene.h"
#include "Fade.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "Shadow.h"
#include "sound.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CManager::m_pRenderer=NULL;
CGame* CManager::m_pGame=NULL;
CTitle* CManager::m_pTitle=NULL;
CResult* CManager::m_pResult=NULL;
MODE CManager::m_Phase;
MODE CManager::m_NextPhase;
bool CManager::m_PauseFlag=false;
bool CManager::m_FadeFlag=false;
CCamera* CManager::m_pCamera=NULL;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_pRenderer = NULL;
	m_pGame=NULL;
	m_pTitle=NULL;
	m_pResult=NULL;
	m_Phase=MODE_TITLE;
	m_NextPhase=MODE_TITLE;
	m_PauseFlag=false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd,bool bWindow)
{
	//�C���^���X�쐬
	m_pRenderer = new CRenderer;
	m_pLight = new CLight;
	m_pCamera = new CCamera;


	//�T�E���h�̏�����
	InitSound(hWnd);

	//�L�[�{�[�h�̏�����
	InitKeyboard(hInstance,hWnd);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		return -1;
	}

	//���݂̃t�F�[�Y�Ǘ�
	switch(m_Phase)
	{
		//�^�C�g����
		case MODE_TITLE:
			m_pTitle= new CTitle;
			m_pTitle->Init(m_pRenderer);
			break;

		//�Q�[����
		case MODE_GAME:
			m_pGame= new CGame;
			m_pGame->Init(m_pRenderer);
			break;

		//���U���g��
		case MODE_RESULT:
			m_pResult= new CResult;
			m_pResult->Init(m_pRenderer);
			break;
	}

#ifdef _DEBUG
	m_pDebug = new CDebugProc;
	m_pDebug->Init();
#endif

	//�J�����̏�����
	m_pCamera->InitCamera(m_pRenderer);
	//���C�g�̏�����
	m_pLight->InitLight(m_pRenderer);
	

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{	
	//�L�[�{�[�h�̏I��
	UninitKeyboard();
	// �I������
	m_pDebug->Uninit();

#ifdef _DEBUG
	delete m_pDebug;
#endif

	//����
	delete m_pLight;
	delete m_pCamera;
	
	//���݂̃t�F�[�Y�Ǘ�
	switch(m_Phase)
	{
		//�^�C�g����
		case MODE_TITLE:
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle=NULL;
			break;

		//�Q�[����
		case MODE_GAME:
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame=NULL;
			break;

		//���U���g��
		case MODE_RESULT:
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult=NULL;
			break;
	}
	CScene::ReleaseAll();

	m_pRenderer->Uninit();

	//delete m_pRenderer;		//�K���Ō�


}
//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V
	UpdateKeyboard();

	//�J�����̍X�V
	m_pCamera->UpdateCamera();

	//���݂̃t�F�[�Y�Ǘ�
	switch(m_Phase)
	{
		//�^�C�g����
		case MODE_TITLE:
			m_pTitle->Update();
			break;

		//�Q�[����
		case MODE_GAME:
			m_pGame->Update();
			break;

		//���U���g��
		case MODE_RESULT:
			m_pResult->Update();
			break;
	}

	m_pRenderer->Update();		//�����͕K���Ō�
}
//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �J�����̐ݒu
	m_pCamera->SetCamera();

	m_pRenderer->Draw();
}

//=============================================================================
// �t�F�[�Y�̐؂�ւ�����
//=============================================================================
void CManager::PhaseExchange(void)
{
	//���̃t�F�[�Y�ƌ��݂̃t�F�[�Y���������
	if(m_NextPhase!=m_Phase)
	{
		//���݂̃t�F�[�Y�̔j��
		switch(m_Phase)
		{
			case MODE_TITLE:
				m_pTitle->Uninit();
				delete m_pTitle;
				m_pTitle=NULL;
				break;

			case MODE_GAME:
				m_pGame->Uninit();
				delete m_pGame;
				m_pGame=NULL;
				break;

			case MODE_RESULT:
				m_pResult->Uninit();
				delete m_pResult;
				m_pResult=NULL;
				break;
		}

	//���̃t�F�[�Y�𐶐��EInit
	switch(m_NextPhase)
	{
		case MODE_TITLE:
			m_pTitle= new CTitle;
			m_pTitle->Init(m_pRenderer);
			break;

		case MODE_GAME:
			m_pGame= new CGame;
			m_pGame->Init(m_pRenderer);
			break;

		case MODE_RESULT:
			m_pResult= new CResult;
			m_pResult->Init(m_pRenderer);
			break;

		case MODE_RESET:
			switch(m_Phase)
			{
				case MODE_TITLE:
					m_pTitle= new CTitle;
					m_pTitle->Init(m_pRenderer);
					m_NextPhase=m_Phase;
					break;

				case MODE_GAME:
					m_pGame= new CGame;
					m_pGame->Init(m_pRenderer);
					m_NextPhase=m_Phase;
					break;

				case MODE_RESULT:
					m_pResult= new CResult;
					m_pResult->Init(m_pRenderer);
					m_NextPhase=m_Phase;
					break;
			}
		}
	}
	m_Phase=m_NextPhase;
}

//=============================================================================
// �|�[�Y�t���O�̐ݒ�
//=============================================================================
void CManager::SetPauseFlag(bool PauseFlag)
{
	m_PauseFlag=PauseFlag;
	CScene::SetPauseFlag(m_PauseFlag);
	CCamera::SetPauseFlag(m_PauseFlag);
}