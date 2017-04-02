//=============================================================================
//
// ���U���g���� [Result.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Result.h"
#include "Renderer.h"
#include "Manager.h"
#include "Input.h"
#include "Scene.h"
#include "Fade.h"
#include "Manager.h"
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
CRenderer* CResult::m_pRenderer;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_pDevice=NULL;
	m_pD3DTex=NULL;
	m_pRenderer = NULL;
	m_pFade=NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(CRenderer* pRenderer)
{
	//�f�o�C�X�̎擾
	m_pDevice = pRenderer->GetDevice();

	//�C���^���X�쐬
	m_pFade = new CFade(OBJTYPE_FADE);

	//PlaySound(SOUND_LABEL_RESULT);

	//�t�F�[�h�̏�����
	m_pFade->Init(pRenderer);
	COLOR Color;
	Color.R=255;
	Color.G=255;
	Color.B=255;
	Color.A=255;
	m_pFade->FadeStart(FADE_IN,60,Color);

	//���U���g��ʂ̃e�N�X�`��
	CScene2D::Create(400,300,800,600,"data/TEXTURE/result.png",pRenderer);




	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{	
	//StopSound(SOUND_LABEL_RESULT);

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
void CResult::Update(void)
{
	//���񂽁[�L�[�Ń^�C�g����
	if(GetKeyboardTriger(DIK_RETURN))
	{
		COLOR Color;
		Color.R=255;
		Color.G=255;
		Color.B=255;
		Color.A=0;
		m_pFade->FadeStart(FADE_OUT,60,Color);
	}
	if(m_pFade->GetFade()==FADE_OUT_FINISH)
	{
		CManager::SetNextPhase(MODE_TITLE);
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
	m_pDevice->SetTexture(0,m_pD3DTex);
	m_pDevice->SetFVF(FVF_VERTEX_2D);
	m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,
									  2,
									  &m_aVtx[0],
									  sizeof(VERTEX_2D));

}