//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Fade.h"
#include "Renderer.h"
#include "Manager.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade(OBJTYPE nObjType,int nPriority):CScene2D(nObjType,nPriority)
{
	m_pD3DFadeTex = NULL;
	m_pD3DDevice=NULL;
	m_Mode = FADE_IN;
	m_aAlpha = 0;
	m_Time=0;
	m_Color.R=0;
	m_Color.G=0;
	m_Color.B=0;
	m_Color.A=0;
	m_Flag=false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{

}
//=============================================================================
// �t�F�[�h�̏�����
//=============================================================================
HRESULT CFade::Init(CRenderer *pRenderer)
{
	int i;
	m_pD3DDevice = pRenderer->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);


	m_aFadeVtx[0].vtx = D3DXVECTOR3(0,0,0.0f);
	m_aFadeVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH,0,0.0f);
	m_aFadeVtx[2].vtx = D3DXVECTOR3(0,SCREEN_HEIGHT,0.0f);
	m_aFadeVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	for(i=0;i<4;i++)
	{
		m_aFadeVtx[i].rhw=1.0f;
		m_aFadeVtx[i].diffuse = D3DCOLOR_RGBA(255,255,255,m_aAlpha);
	}

	m_aFadeVtx[0].tex=D3DXVECTOR2(0,0);
	m_aFadeVtx[1].tex=D3DXVECTOR2(1,0);
	m_aFadeVtx[2].tex=D3DXVECTOR2(0,1);
	m_aFadeVtx[3].tex=D3DXVECTOR2(1,1);

	return S_OK;
}
//=============================================================================
// �t�F�[�h�̏I������
//=============================================================================
void CFade::Uninit(void)
{
	if(m_pD3DFadeTex!=NULL)
	{
		m_pD3DFadeTex->Release();
		m_pD3DFadeTex= NULL;
	}
	CScene::Release();
}
//=============================================================================
// �t�F�[�h�̍X�V����
//=============================================================================
void CFade::Update(void)
{
	switch(m_Mode)
	{
		//�t�F�[�h�����Ă��Ȃ��Ƃ�
		case FADE_NONE:
			m_Flag=false;
			break;

		//�t�F�[�h�A�E�g���̏���
		case FADE_OUT:
			m_aAlpha+=m_RateAdd;		//�A���t�@�l�����Z
			if(m_aAlpha >= 255)
			{
				m_Mode=FADE_OUT_FINISH;
				m_aAlpha=255;
			}
			break;

		//�t�F�[�h�C�����I�������
		case FADE_IN_FINISH:
			m_Flag=false;
			break;

		//�t�F�[�h�C�����̏���
		case FADE_IN:
			m_aAlpha-=m_RateAdd;		//�A���t�@�l�����Z
			if(m_aAlpha <= 0)
			{
				m_Mode=FADE_NONE;
				m_aAlpha=0;
			}
			break;

		//�t�F�[�h�A�E�g���I�������
		case FADE_OUT_FINISH:
			
			break;

		case FADE_INFINITY:
			break;
	}

	for(int i=0;i<4;i++)
	{
		m_aFadeVtx[i].diffuse = D3DCOLOR_RGBA((int)m_Color.R,(int)m_Color.G,(int)m_Color.B,m_aAlpha);
	}

	CManager::SetFadeFlag(m_Flag);
}

//=============================================================================
// �t�F�[�h�̕`�揈��
//=============================================================================
void CFade::Draw(void)
{
	m_pD3DDevice->SetTexture(0,m_pD3DFadeTex);
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,&m_aFadeVtx[0],sizeof(VERTEX_2D));
}

//=============================================================================
// �t�F�[�h�̊J�n
//=============================================================================
void CFade::FadeStart(FADE Mode,int Time,COLOR Color)
{
	m_Time=Time;
	m_Mode=Mode;
	m_Color=Color;

	if(Mode==FADE_IN)
	{
		m_aAlpha=255;
		m_Flag=true;
	}

	if(Mode==FADE_OUT)
	{
		m_aAlpha=0;
		m_Flag=true;
	}
	if(Mode==FADE_INFINITY)
	{
		m_aAlpha=(int)m_Color.A;
		m_Flag=true;
	}
	if(Mode==FADE_NONE)
	{
		m_Flag=false;
	}

	m_RateAdd=255/m_Time;
	m_Color.A=m_aAlpha;
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CFade* CFade::Create(CRenderer *pRenderer)
{
	CFade *pFade = new CFade(OBJTYPE_FADE);

	pFade->Init(pRenderer);

	return pFade;
}