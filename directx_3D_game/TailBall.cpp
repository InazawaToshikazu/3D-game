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
#include "Player.h"
#include "Needle.h"
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
CRenderer* CTailBall::m_pTailBall=NULL;
bool CTailBall::m_RotFlag;
CFade* CTailBall::m_pFade=NULL;
CTailBall* CTailBall::m_pFlag;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTailBall::CTailBall(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_pTailBall=NULL;
	m_pSceneLink=NULL;
	m_pFlag=NULL;
	m_pFade=NULL;
	m_rotDestModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotDest=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BulletCnt=0;
	m_pNeedle=NULL;
	m_pPlayer=NULL;
	m_Ratio=0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTailBall::~CTailBall(void)
{
	
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CTailBall* CTailBall::Create(float Ratio,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CTailBall *pTailBall;
	//�C���X�^���X�̍쐬
	pTailBall = new CTailBall(OBJTYPE_TAILBALL);
	//CEnemy��Init���Ăяo��
	pTailBall->Init(m_pRenderer);
	//���W�̐ݒ�
	pTailBall->SetRatio(Ratio);
	pTailBall->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pTailBall->SetPos(fPosX,fPosY,fPosZ);
	m_pTailBall=m_pRenderer;
	return pTailBall;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTailBall::Init(CRenderer *pRenderer)
{
	//���@���f���̎w��
	FileName="data/MODEL/player/sasori_Tail1.x";

	CSceneX::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTailBall::Uninit(void)
{
	//���g�̃��\�[�X�̉��
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTailBall::Update(void)
{
	D3DXVECTOR3 VecToNeedle;	//�j�Ɍ������x�N�g��

	VecToNeedle=CGame::GetNeedle()->GetPos()-CGame::GetPlayer()->GetPos();
	m_Pos=CGame::GetPlayer()->GetPos()+(VecToNeedle*m_Ratio);

	CSceneX::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTailBall::Draw(void)
{

	CSceneX::Draw();


}

