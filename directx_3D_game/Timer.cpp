//=============================================================================
//
// �X�R�A���� [Score.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include"Score.h"
#include "Renderer.h"
#include "Timer.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CTimer::m_pTimer=NULL;
int CTimer::m_nTimer=NULL;
CNumber* CTimer::m_pNumber=NULL;
int Cnt=0;



//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTimer::CTimer(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_nTimer=0;
	m_pTimer=NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTimer::~CTimer(void)
{
	
}
//=============================================================================
// �X�R�A�̏�����
//=============================================================================
HRESULT CTimer::Init(CRenderer *pRenderer)
{
	m_pNumber=new CNumber[TIMER_DIGIT];

	for(int i=0;i<TIMER_DIGIT;i++)
	{
		m_pNumber[i].SetPos(m_Pos.x+(i*20),m_Pos.y,0.0f);
		m_pNumber[i].Init(pRenderer);
	}
	return S_OK;
}
//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CTimer::Uninit(void)
{
	for(int i=0;i<TIMER_DIGIT;i++)
	{
		m_pNumber[i].Uninit();
	}
	delete[] m_pNumber;
	CScene::Release();
}
//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CTimer::Update(void)
{
	Cnt++;
	if(Cnt==60)
	{
		AddTimer(1);
		Cnt=0;
	}
}

//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CTimer::Draw(void)
{
	for(int i=0;i<TIMER_DIGIT;i++)
	{
		m_pNumber[i].Draw();
	}

}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CTimer::AddTimer(int nValue)
{
	m_nTimer+=nValue;
	if(m_nTimer >= TIMER_MAX)
	{
		m_nTimer = TIMER_MAX;
	}
	if(m_nTimer < 0)
	{
		m_nTimer = 0;
	}
		for(int nCntPlace=0;nCntPlace<TIMER_DIGIT;nCntPlace++)
		{
			int nNumber;
			int num1,num2;
			num1 = (int)pow(10,(double)TIMER_DIGIT-nCntPlace);
			num2 = (int)pow(10,(double)TIMER_DIGIT-nCntPlace-1);
			if(nCntPlace == 0)
			{
				nNumber = m_nTimer / num2;
			}
			else
			{
				nNumber = m_nTimer % num1 / num2;
			}
			m_pNumber[nCntPlace].UpdateNumber(nNumber);
		}
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CTimer* CTimer::Create(float fPosX,float fPosY,CRenderer* m_pRenderer)
{
	CTimer *pTimer;
	//�C���X�^���X�̍쐬
	pTimer = new CTimer(OBJTYPE_TIMER);
	//���W�̐ݒ�
	pTimer->m_Pos = D3DXVECTOR3(fPosX,fPosY,0);
	//CEnemy��Init���Ăяo��
	pTimer->Init(m_pRenderer);
	
	m_pTimer=m_pRenderer;
	return pTimer;
}
