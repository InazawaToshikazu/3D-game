//=============================================================================
//
// ���C������ [Manager.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Game.h"
#include "Renderer.h"
#include "Manager.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "SceneX.h"
#include "Enemy.h"
#include "MeshWall.h"
#include "CMeshField.h"
#include "Player.h"
#include "Cylinder.h"
#include "Dome.h"
#include "Gimmick.h"
#include "Fade.h"
#include "Input.h"
#include "Pause.h"
#include "Timer.h"
#include "Score.h"
#include "sound.h"
#include "Goal.h"
#include "Shadow.h"
#include "Enemy.h"
#include "MotionModel.h"
#include "TailBall.h"
#include "Needle.h"
#include "Collision.h"
#include "Target.h"
#include "Magma.h"
#include "Fireball.h"
#include "Collision.h"
#include "CreateFire.h"
#include "Leg.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CField* CGame::pMeshField=NULL;
CPlayer* CGame::m_pPlayer2=NULL;
CGimmick* CGame::m_pGimmick=NULL;
CRenderer* CGame::m_pRenderer=NULL;
CMotionModel* CGame::m_pMotion;
CNeedle* CGame::m_pNeedle=NULL;
CTailBall* CGame::m_pTailBall=NULL;
CCollision* CGame::m_pCollision=NULL;
CTarget* CGame::m_pTarget[]={NULL};
CMagma* CGame::m_pMagma=NULL;
CGoal* CGame::m_pGoal=NULL;
CFireball* CGame::m_pFireball[]={NULL};
CLeg* CGame::m_pLeg[]={NULL};


CCreateFire* CGame::m_pCreateFire=NULL;
CCreateFire Fire;

int FireForce=800;	//���̋���
int FireLife=400;	//���̎���
bool sFlag=false;		//�����������邩�ǂ����̃t���O
double WindForce=0;	//���͂̋���
void OnDraw(HWND hwnd,HDC hdc);	//��ʂ̕`��
//���̃p�����[�^FirePara1=6;FirePara2=50;
int FirePara1=6,FirePara2=50;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	lpFire=NULL;
	pMeshField=NULL;
	m_pRenderer = NULL;
	PauseFlag=false;
	m_pPause=NULL;
	ClearPos=D3DXVECTOR3(605,50,-241);

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(CRenderer* pRenderer)
{

	m_pRenderer=pRenderer;

	//�C���^���X�쐬
	m_pFade = new CFade(OBJTYPE_FADE);

	m_pCollision = new CCollision();
	//�t�F�[�h�̏�����
	m_pFade->Init(pRenderer);
	COLOR Color;
	Color.R=255;
	Color.G=255;
	Color.B=255;
	Color.A=255;
	m_pFade->FadeStart(FADE_IN,60,Color);



	//2D�|���S��(�������)�쐬
	CScene2D::Create(100,100,200,200,"data/TEXTURE/sousa2.png",m_pRenderer);
	//�h�[���̐���
	CDome::Create(1200,1200,50,50,500,0,-600,pRenderer);
	//�V�����_�[�쐬
	//����
	CCylinder::Create(10,40,20,20,35,0,-88,pRenderer);
	//����
	CCylinder::Create(10,40,20,20,8.5,0,-995,pRenderer);
	//�E��
	CCylinder::Create(10,40,20,20,894,0,-30,pRenderer);
	//�E��
	CCylinder::Create(10,40,20,20,989,0,-993,pRenderer);

	//�t�B�[���h�쐬
	pMeshField=CField::Create(pRenderer,0,0,0);

		//�M�~�b�N(������)�쐬
	m_pGimmick=CGimmick::Create(894,60,-730,pRenderer);
	
	//�e�@�K���t�B�[���h�E�e�E�L�����̏��Ԃŕ`�悷��
	CShadow::Create(80,50,-962,m_pRenderer);

	//���@�쐬
	m_pPlayer2=CPlayer::Create(80,60,-962,pRenderer);			//����
	m_pTailBall=CTailBall::Create(0.2f,80,60,-952,pRenderer);	//�K���̋�
	m_pTailBall=CTailBall::Create(0.4f,80,60,-952,pRenderer);	//�K���̋�
	m_pTailBall=CTailBall::Create(0.6f,80,60,-952,pRenderer);	//�K���̋�
	m_pTailBall=CTailBall::Create(0.8f,80,60,-952,pRenderer);	//�K���̋�
	m_pNeedle=CNeedle::Create(150,100,-982,pRenderer);			//�j
	
	//��
	m_pLeg[0]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[1]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[2]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[3]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[4]=CLeg::Create(0.4f,83,60,-949,pRenderer);
	m_pLeg[5]=CLeg::Create(0.4f,83,60,-949,pRenderer);

	//�I
	m_pTarget[0] = CTarget::Create(300,80,-942,pRenderer);
	m_pTarget[1] = CTarget::Create(500,100,-442,pRenderer);
	m_pTarget[2] = CTarget::Create(500,150,-942,pRenderer);
	m_pTarget[3] = CTarget::Create(800,80,-942,pRenderer);
	m_pTarget[4] = CTarget::Create(700,80,-282,pRenderer);
	m_pTarget[5] = CTarget::Create(100,80,-42,pRenderer);


	//�G�쐬
	//CEnemy::Create(80,60,-962,pRenderer);

	//�S�[���̖ڈ�̃��f���쐬
	m_pGoal=CGoal::Create(605.5f,50.0f,-241.6f,pRenderer);

	//BGM�Đ�
	//PlaySound(SOUND_LABEL_GAME);

	m_pFireball[0]=CFireball::Create(1,586,150,-531,pRenderer);
	m_pFireball[1]=CFireball::Create(1,586,40,-531,pRenderer);
	m_pFireball[2]=CFireball::Create(0,586,40,-531,pRenderer);
	m_pFireball[3]=CFireball::Create(0,586,60,-531,pRenderer);
	m_pFireball[4]=CFireball::Create(2,586,20,-531,pRenderer);


	//�}�O�}�̐���
	m_pMagma=CMagma::Create(m_pRenderer->GetDevice(),300,30,200);

	//�^�C�}�[�̐���
	CTimer::Create(730,0,m_pRenderer);


	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{	
	//StopSound(SOUND_LABEL_GAME);

	if(m_pPause!=NULL)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause=NULL;
	}

	pMeshField=NULL;
	m_pPlayer2=NULL;
	m_pGimmick=NULL;
	m_pFade=NULL;
	
	
	m_pCollision=NULL;
	for(int i=0;i<LEG_MAX;i++)
	{
		m_pLeg[i]=NULL;
		m_pTarget[i]=NULL;
	}
	for(int i=0;i<FIREBALL_MAX;i++)
	{
		m_pFireball[i]=NULL;
	}
	m_pMagma=NULL;
	m_pRenderer=NULL;

	CScene::ReleaseAll();
	//delete pMeshField;
}
//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	//�t�F�[�h���I�������
	if(m_pFade->GetFade()==FADE_OUT_FINISH)
	{
		//�|�[�Y��Ԃ̎�
		if(m_pPause!=NULL)
		{
			//�|�[�Y���I����
			switch(m_pPause->GetMenu())
			{
				//�^�C�g���ɖ߂�
				case RETURN_TITLE:
					CManager::SetNextPhase(MODE_TITLE);
					break;

				//���g���C
				case RETRY:
					CManager::SetNextPhase(MODE_RESET);
					break;
			}
		}
		else
		{
			// �Q�[���I�[�o�[���N���A���t���O�Ŕ��f
			CManager::SetNextPhase(MODE_RESULT);
		}
		//�|�[�Y�t���O��false��
		CManager::SetPauseFlag(false);
	}
	//�����|�[�Y�t���O��true�Ȃ�
	if(CManager::GetPauseFlag()==true)
	{
		m_pPause->Update();
		//�|�[�Y����Q�[���̖߂�����
		if(m_pPause->GetMenu()==RETURN_GAME)
		{
			CManager::SetPauseFlag(false);
			m_pPause->Uninit();
			delete m_pPause;
			m_pPause=NULL;
		}
		else if((m_pPause->GetMenu()==RETURN_TITLE || m_pPause->GetMenu()==RETRY) && m_pFade->GetFade()==FADE_NONE)
		{
			COLOR Color;
			Color.R=255;
			Color.G=255;
			Color.B=255;
			Color.A=0;
			m_pFade->FadeStart(FADE_OUT,60,Color);
		}
		return;
	}
	//P�{�^���������ꂽ��
	if(GetKeyboardTriger(DIK_P))
	{
		CManager::SetPauseFlag(true);
		m_pPause= new CPause;
		m_pPause->Init(m_pRenderer);
	}

	CPlayer* pPlayer=CGame::GetPlayer();
	CGoal* pGoal = CGame::GetGoal();
	CCollision* pCollision = CGame::GetCollision();

	//�N���A����
	//�S�[���̍��W�ɒ�������
	if(pPlayer->GetClearFlag() == true && m_pFade->GetFade()==FADE_NONE)
	{
		COLOR Color;
		Color.R=255;
		Color.G=255;
		Color.B=255;
		Color.A=0;
		m_pFade->FadeStart(FADE_OUT,60,Color);
	}

	//�Q�[���I�[�o�[�̎�
	//�n��ɗ�������
	if(pPlayer->GetDeadFlag() == true && m_pFade->GetFade()==FADE_NONE)
	{
		COLOR Color;
		Color.R=255;
		Color.G=255;
		Color.B=255;
		Color.A=0;
		m_pFade->FadeStart(FADE_OUT,60,Color);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
		HDC hdc;
	PAINTSTRUCT ps;
	HWND hWnd;

	hdc=BeginPaint(hWnd,&ps);
	OnDraw(hWnd,hdc);			//��ʕ`��
	EndPaint(hWnd,&ps);
}
void OnDraw(HWND hwnd,HDC hdc)
{
	Fire.MoveFire(FireForce,FireLife,sFlag,WindForce);
	Fire.DrawImage(hdc,0,100,500,500,0,100);
}