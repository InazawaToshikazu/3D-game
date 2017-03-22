//=============================================================================
//
// �^�C�g������ [Title.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Title.h"
#include "Input.h"
#include "Game.h"
#include "Renderer.h"
#include "Manager.h"
#include "Scene2D.h"
#include "Fade.h"
#include "sound.h"
#include "TitleLogo.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CTitle::m_pRenderer;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_pD3DTex=NULL;
	m_pDevice=NULL;
	m_pRenderer = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
	 
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init(CRenderer* pRenderer)
{
	//�f�o�C�X�̎擾
	m_pDevice = pRenderer->GetDevice();
	//�C���^���X�쐬
	m_pFade = new CFade(OBJTYPE_FADE);

	//�t�F�[�h�̏�����
	m_pFade->Init(pRenderer);
	COLOR Color;
	Color.R=255;
	Color.G=255;
	Color.B=255;
	Color.A=255;
	m_pFade->FadeStart(FADE_IN,60,Color);

	CScene2D::Create(400,300,800,600,"data/TEXTURE/sasori.jpg",pRenderer);
	CTitleLogo::Create(400,100,500,300,"data/TEXTURE/TitleLogo.png",pRenderer);

	PlaySound(SOUND_LABEL_TITLE);


	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	StopSound(SOUND_LABEL_TITLE);

	//�e�N�X�`���̉��
	if(m_pD3DTex != NULL)
	{
		m_pD3DTex ->Release();
		m_pD3DTex = NULL;
	}
	CScene::ReleaseAll();
}
//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	if(GetKeyboardTriger(DIK_RETURN))
	{
		PlaySound(SOUND_LABEL_ENTER);
		COLOR Color;
		Color.R=255;
		Color.G=255;
		Color.B=255;
		Color.A=0;
		m_pFade->FadeStart(FADE_OUT,60,Color);

	}
	if(m_pFade->GetFade()==FADE_OUT_FINISH)
	{
		CManager::SetNextPhase(MODE_GAME);
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	m_pDevice->SetTexture(0,m_pD3DTex);
	m_pDevice->SetFVF(FVF_VERTEX_2D);		
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
									  2,
									  &m_aVtx[0],
									  sizeof(VERTEX_2D));

}