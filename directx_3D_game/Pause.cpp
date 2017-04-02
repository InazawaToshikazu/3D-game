//=============================================================================
//
// �|�[�Y���� [Pause.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Game.h"
#include "Renderer.h"
#include "Manager.h"
#include "Scene2D.h"
#include "Pause.h"
#include "Input.h"
#include "Fade.h"
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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPause::CPause()
{
	m_CurrentMenu=NONE;
	m_pMask=NULL;
	m_pReturnTitle=NULL;
	m_pReturnGame=NULL;
	m_pRetry=NULL;
	m_pArrow=NULL;
	m_Num=0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPause::~CPause()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(CRenderer* pRenderer)
{
	//�C���X�^���X�̍쐬
	m_pMask= new CFade(OBJTYPE_FADE,6);

	//�t�F�[�h�̏�����
	m_pMask->Init(pRenderer);

	COLOR Color;
	Color.R=0;
	Color.G=0;
	Color.B=0;
	Color.A=128;
	m_pMask->FadeStart(FADE_INFINITY,60,Color);

	//�摜�̐���
	m_pReturnTitle=CScene2D::Create(400,150,300,200,"data/TEXTURE/ReturnGame.png",pRenderer,6);
	m_pReturnGame=CScene2D::Create(400,300,300,200,"data/TEXTURE/ReturnTitle.png",pRenderer,6);
	m_pRetry=CScene2D::Create(400,450,300,200,"data/TEXTURE/Retry.png",pRenderer,6);
	m_pArrow=CScene2D::Create(200,150,100,100,"data/TEXTURE/Arrow2.png",pRenderer,6);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	m_pMask->Uninit();
	m_pReturnTitle->Uninit();
	m_pReturnGame->Uninit();
	m_pRetry->Uninit();
	m_pArrow->Uninit();

}
//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	D3DXVECTOR3 ArrowPos=m_pArrow->GetPos();

	//��ړ�
	if(GetKeyboardTriger(DIK_W))
	{
		//PlaySound(SOUND_LABEL_SELECT);
		m_pArrow->SetPos(ArrowPos.x,ArrowPos.y-150,ArrowPos.z);
		m_Num--;
	}
	//���ړ�
	if(GetKeyboardTriger(DIK_S))
	{
		//PlaySound(SOUND_LABEL_SELECT);
		m_pArrow->SetPos(ArrowPos.x,ArrowPos.y+150,ArrowPos.z);
		m_Num++;
	}
	//�J��Ԃ�����
	if(m_Num<0)
	{
		m_Num=2;
		m_pArrow->SetPos(ArrowPos.x,ArrowPos.y+300,ArrowPos.z);
	}
	if(m_Num>2)
	{
		m_Num=0;
		m_pArrow->SetPos(ArrowPos.x,ArrowPos.y-300,ArrowPos.z);
	}
	//����
	if(GetKeyboardTriger(DIK_RETURN))
	{
		//PlaySound(SOUND_LABEL_ENTER);
		m_CurrentMenu=(PAUSE_MENU)m_Num;
	}
	//�|�[�Y�I��
	if(GetKeyboardTriger(DIK_P))
	{
		m_CurrentMenu=RETURN_GAME;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{

}
