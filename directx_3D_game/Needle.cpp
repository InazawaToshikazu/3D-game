//=============================================================================
//
// ���@���f���\������ [Player.cpp]
// Author : ���V�r�a
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "TailBall.h"
#include "Renderer.h"
#include "SceneX.h"
#include "Input.h"
#include "Bullet.h"
#include "Manager.h"
#include "CMeshField.h"
#include "Gimmick.h"
#include "Camera.h"
#include "Game.h"
#include "Fade.h"
#include "Score.h"
#include "sound.h"
#include "Needle.h"
#include "Collision.h"
#include "Target.h"
#include "Player.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define FIELD_WIDTH		(100.0f)		// �n�ʂ̕�
#define FIELD_HIGHT		(100.0f)		// �n�ʂ̏c
#define MODEL_ROT_SPEED				(0.05f)		//���f���̉�]���x
#define MODEL_SPEED_X				(1.7f)		//���f���̈ړ����x
#define MODEL_SPEED_Z				(1.7f)		//
#define MODEL_SPEED_Y				(0.1f)		//
#define MODEL_SPEED					(0.7f)		//

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CNeedle::m_pNeedle=NULL;
bool CNeedle::m_RotFlag;
CFade* CNeedle::m_pFade=NULL;
CNeedle* CNeedle::m_pFlag;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNeedle::CNeedle(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_pNeedle=NULL;
	m_pSceneLink=NULL;
	m_pFlag=NULL;
	m_pFade=NULL;
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BulletCnt=0;
	m_speed = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PosDest=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pTarget=NULL;
	m_HitFlag=false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNeedle::~CNeedle(void)
{
	
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CNeedle* CNeedle::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CNeedle *pNeedle;
	//�C���X�^���X�̍쐬
	pNeedle = new CNeedle(OBJTYPE_NEEDLE);
	//CEnemy��Init���Ăяo��
	pNeedle->Init(m_pRenderer);
	//���W�̐ݒ�
	pNeedle->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pNeedle->SetPos(fPosX,fPosY,fPosZ);
	m_pNeedle=m_pRenderer;
	return pNeedle;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CNeedle::Init(CRenderer *pRenderer)
{
	//�K���̐j���f���̎w��
	FileName="data/MODEL/player/sasori_needle.x";

	CSceneX::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNeedle::Uninit(void)
{
	//���g�̃��\�[�X�̉��
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CNeedle::Update(void)
{
	m_BulletCnt++;
	if(m_BulletCnt < 10)
	{
		m_PosDest += m_speed;
	}
	if(m_HitFlag==false)
	{
		m_Pos+=(m_PosDest-m_Pos)*0.1;
	}

	CCollision *pCollision = CGame::GetCollision();
	CPlayer *pPlayer = CGame::GetPlayer();

	for(int i=0;i<6;i++)
	{
		CTarget *target = CGame::GetTarget(i);		//�I�̃|�C���^�̎擾
		//�j�ƓI�̓����蔻��
		if(pCollision->SphereToSphere3D(m_Pos,3.0f,target->GetPos(),17.0f) && pPlayer->GetTailShotFlag()==true)
		{
			m_BulletCnt=30;
			CDebugProc::Print("\n�q�b�g\n");		//�f�o�b�O�����\��
			m_HitFlag=true;
			break;
		}
		else
		{
			if(m_BulletCnt==30 && m_HitFlag==false)		//�J�E���g��30�ł��t���O��false�Ȃ�
			{
				pPlayer->Neutral();						//�v���C���[�̏�Ԃ�ʏ�ɖ߂�
				pPlayer->SetTailShotFlag(false);		//���˃t���O�̐ݒ�
			}
		}
	}
	if(m_HitFlag==true)
	{
		pPlayer->Pulled();	//���������ꍇ�͐j�Ɉ���������֐����Ă�
	}





	CSceneX::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CNeedle::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// �j�̔��ˊ֐�
//=============================================================================
void CNeedle::Shot(D3DXVECTOR3 vector)
{
	m_speed = vector;
	m_BulletCnt = 0;
}

void CNeedle::Return(void)
{

}