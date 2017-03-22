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
#include "Renderer.h"
#include "SceneX.h"
#include "Input.h"
#include "Manager.h"
#include "CMeshField.h"
#include "Gimmick.h"
#include "Camera.h"
#include "Game.h"
#include "Player.h"
#include "Leg.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MODEL_ROT_SPEED				(0.05f)		//���f���̉�]���x
#define MODEL_SPEED_X				(1.7f)		//���f���̈ړ����x
#define MODEL_SPEED_Z				(4.0f)		//
#define MODEL_SPEED_Y				(0.1f)		//
#define MODEL_SPEED					(0.7f)		//

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CLeg::m_pLeg=NULL;
int CLeg::m_LegNum=0; 
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLeg::CLeg(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_rotDestModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotDest=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BulletCnt=0;
	m_pPlayer=NULL;
	m_Ratio=0.0f;
	m_State=0;
	m_Rotate=0.1f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLeg::~CLeg(void)
{
	
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CLeg* CLeg::Create(float Ratio,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CLeg *pLeg;
	//�C���X�^���X�̍쐬
	pLeg = new CLeg(OBJTYPE_LEG);

	//���W�̐ݒ�
	pLeg->SetRatio(Ratio);
	pLeg->m_State=m_LegNum;
	m_LegNum++;
	pLeg->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pLeg->SetPos(fPosX,fPosY,fPosZ);
		//CEnemy��Init���Ăяo��
	pLeg->Init(m_pRenderer);
	m_pLeg=m_pRenderer;
	return pLeg;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLeg::Init(CRenderer *pRenderer)
{
	//���@���f���̎w��
	FileName="data/MODEL/player/sasori_leg.x";

	switch(m_State)
	{
		case 0:
			FileName="data/MODEL/player/sasori_leg_l.x";
			m_Rot.z=D3DX_PI/4;
			break;
		case 1:
			FileName="data/MODEL/player/sasori_leg_l.x";
			m_Rot.z=0.0f;
			break;
		case 2:
			FileName="data/MODEL/player/sasori_leg_l.x";
			m_Rot.z=-D3DX_PI/4;
			break;
		case 3:
			FileName="data/MODEL/player/sasori_leg.x";
			m_Rot.z=D3DX_PI/4;
			break;
		case 4:
			FileName="data/MODEL/player/sasori_leg.x";
			m_Rot.z=0.0f;
			break;
		case 5:
			FileName="data/MODEL/player/sasori_leg.x";
			m_Rot.z=-D3DX_PI/4;
			break;


	}


	CSceneX::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLeg::Uninit(void)
{
	//���g�̃��\�[�X�̉��
	m_LegNum=0;
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLeg::Update(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();
	
	

	m_Rot.y=pPlayer->GetRot().y;

	switch(m_State)
	{
		case 0:	//���̂P�{��
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y+D3DX_PI*5/8)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y+D3DX_PI*5/8)*MODEL_SPEED_Z;
			break;
		case 1:	//���̂Q�{��
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y+D3DX_PI/2)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y+D3DX_PI/2)*MODEL_SPEED_Z;
			break;
		case 2:	//����3�{��
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y+D3DX_PI*3/8)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y+D3DX_PI*3/8)*MODEL_SPEED_Z;
			break;
		case 3:	//�E�̂P�{��
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y-D3DX_PI*5/8)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y-D3DX_PI*5/8)*MODEL_SPEED_Z;
			break;
		case 4:	//�E�̂Q�{��
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y-D3DX_PI/2)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y-D3DX_PI/2)*MODEL_SPEED_Z;
			break;
		case 5:	//�E��3�{��
			m_Pos.x =pPlayer->GetPos().x+sinf(CSceneX::m_Rot.y-D3DX_PI*3/8)*MODEL_SPEED_Z;
			m_Pos.z =pPlayer->GetPos().z+cosf(CSceneX::m_Rot.y-D3DX_PI*3/8)*MODEL_SPEED_Z;
			break;
	}
	if(pPlayer->GetMoveFlag() == true)
	{
			m_Rot.z += m_Rotate;
			
			if(m_Rot.z>D3DX_PI/4)
			{
				m_Rotate = -m_Rotate;
			}
			if(m_Rot.z<-D3DX_PI/4)
			{
				m_Rotate = -m_Rotate;
			}
	}

	m_Pos.y =pPlayer->GetPos().y;
	this->CSceneX::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
	CSceneX::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLeg::Draw(void)
{
	CSceneX::Draw();
}

