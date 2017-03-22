//=============================================================================
//
// �X�R�A���� [Score.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include"Score.h"
#include "Renderer.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CScore::m_pScore=NULL;
int CScore::m_nScore=NULL;
CNumber* CScore::m_pNumber=NULL;



//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScore::CScore(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pDevice=NULL;
	m_pD3DScoreVtxBuff=NULL;
	m_pD3DScore=NULL;
	m_nScore=0;
	m_pScore=NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScore::~CScore(void)
{
	
}
//=============================================================================
// �X�R�A�̏�����
//=============================================================================
HRESULT CScore::Init(CRenderer *pRenderer)
{
	//�X�R�A�̌������̃C���X�^���X�����
	m_pNumber=new CNumber[DIGIT];
	for(int i=0;i<DIGIT;i++)
	{
		m_pNumber[i].SetPos(m_Pos.x+(i*20),m_Pos.y,0.0f);
		m_pNumber[i].Init(pRenderer);
	}
	return S_OK;
}
//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CScore::Uninit(void)
{
	if(m_pD3DScore != NULL)
	{
		m_pD3DScore ->Release();
		m_pD3DScore = NULL;
	}
	if(m_pD3DScoreVtxBuff !=NULL)
	{
		m_pD3DScoreVtxBuff ->Release();
		m_pD3DScoreVtxBuff = NULL;
	}
	for(int i=0;i<DIGIT;i++)
	{
		m_pNumber[i].Uninit();
	}
	delete[] m_pNumber;
	CScene::Release();
}
//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CScore::Update(void)
{
}

//=============================================================================
// �X�R�A�̕`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for(int i=0;i<DIGIT;i++)
	{
		m_pNumber[i].Draw();
	}

}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore+=nValue;
	if(m_nScore >= SCORE_MAX)
	{
		m_nScore = SCORE_MAX;
	}
	if(m_nScore < 0)
	{
		m_nScore = 0;
	}
		for(int nCntPlace=0;nCntPlace<DIGIT;nCntPlace++)
		{
			int nNumber;
			int num1,num2;
			num1 = (int)pow(10,(double)DIGIT-nCntPlace);
			num2 = (int)pow(10,(double)DIGIT-nCntPlace-1);
			if(nCntPlace == 0)
			{
				nNumber = m_nScore / num2;
			}
			else
			{
				nNumber = m_nScore % num1 / num2;
			}
			m_pNumber[nCntPlace].UpdateNumber(nNumber);
		}
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CScore* CScore::Create(float fPosX,float fPosY,CRenderer* m_pRenderer)
{
	CScore *pScore;
	//�C���X�^���X�̍쐬
	pScore = new CScore(OBJTYPE_SCORE);
	//���W�̐ݒ�
	pScore->m_Pos = D3DXVECTOR3(fPosX,fPosY,0);
	//CEnemy��Init���Ăяo��
	pScore->Init(m_pRenderer);
	
	m_pScore=m_pRenderer;
	return pScore;
}
