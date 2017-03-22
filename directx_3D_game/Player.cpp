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
#include "Player.h"
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
#include "Effect.h"
#include "Collision.h"
#include "Goal.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define FIELD_WIDTH		(100.0f)		// �n�ʂ̕�
#define FIELD_HIGHT		(100.0f)		// �n�ʂ̏c
#define MODEL_ROT_SPEED				(0.05f)		//���f���̉�]���x
#define MODEL_SPEED_X				(1.7f)		//���f���̈ړ����x
#define MODEL_SPEED_Z				(1.3f)		//
#define MODEL_SPEED_Y				(0.05f)		//
#define MODEL_SPEED					(0.7f)		//

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CPlayer::m_pPlayer=NULL;
D3DXVECTOR3 Speed=D3DXVECTOR3(0.0f,0.0f,0.0f);
bool CPlayer::m_RotFlag;
CFade* CPlayer::m_pFade=NULL;
CPlayer* CPlayer::m_pFlag;
CPlayer* CPlayer::m_pPPlayer=NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_pPlayer=NULL;
	m_pSceneLink=NULL;
	m_pFlag=NULL;
	m_pFade=NULL;
	m_rotDestModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotDest=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BulletCnt=0;
	m_Mode=STATE_NORMAL;
	m_FrontVectol=D3DXVECTOR3(0.0f,0.0f,0.0f);
	TailShotFlag=false;
	m_DeadFlag=false;
	m_ClearFlag=false;
	m_JFlag=true;
	m_MoveFlag=false;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer(void)
{
	
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CPlayer* CPlayer::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CPlayer *pPlayer;
	//�C���X�^���X�̍쐬
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	//CEnemy��Init���Ăяo��
	pPlayer->Init(m_pRenderer);
	//���W�̐ݒ�
	pPlayer->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pPlayer->SetPos(fPosX,fPosY,fPosZ);
	m_pPlayer=m_pRenderer;
	return pPlayer;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(CRenderer *pRenderer)
{
	//���@���f���̎w��
	FileName="data/MODEL/player/sasori_body2.x";

	CSceneX::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CManager::GetCamera()->SetCameraMode(CCamera::MODE_THIRDPERSON);
	//���g�̃��\�[�X�̉��
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �x�N�g���v�Z
	float Vx = 0.0f;
	float Vz = 0.0f;
	float fDiffRotY = 0.0f;
	D3DXVECTOR3 Normal=D3DXVECTOR3(0.0f,1.0f,0.0f);
	//�W�����v�֘A
	float G=-0.2f;		//�d��
	float Power=5.0f;	//�オ���
	//�M�~�b�N�̔���֘A
	Vector2 VecLine,VecToTarget;
	D3DXVECTOR3 OffSet;
	D3DXVECTOR3 Target;
	float ModelHigh=10.0f;
	//�O�t���[���̃M�~�b�N�̍��W
	float GimmickUpPosOld;
	float GimmickUnderPosOld;
	CPlayer* pPlayer=CGame::GetPlayer();
	CGoal* pGoal = CGame::GetGoal();
	CCollision* pCollision = CGame::GetCollision();


	CScene* pGimmick;

	CScene* pSceneLinkOld=m_pSceneLink;
	m_pSceneLink=NULL;

	//�K���̏�ԊǗ�
	switch(m_Mode)
	{
		case STATE_NORMAL:
			Neutral();
			break;
		case STATE_SHOT:
			Shot();
			break;
		case STATE_RETURN:
			Return();
			break;
		case STATE_PULLED:
			Pulled();
			break;
		case STATE_DEAD:
			DeadDirection();
			break;
		case STATE_CLEAR:
			ClearDirection();
			break;
	}

	//���ʃx�N�g���̌v�Z
	m_FrontVectol.x=-sinf(m_Rot.y)*1.0f;
	m_FrontVectol.y=0;
	m_FrontVectol.z=-cos(m_Rot.y)*1.0f;

	//�e����
	//if(GetKeyboardTriger(DIK_Z))
	//{
	//	//�e�̐���
	//	CBullet::Create(m_Pos.x,m_Pos.y,m_Pos.z,m_pPlayer,m_Rot.y);
	//	CScore::AddScore(1);
	//	m_BulletCnt++;
	//}

	if( m_Mode == STATE_NORMAL)
	{
		//�W�����v
		if(GetKeyboardTriger(DIK_SPACE) && m_JFlag==false)
		{
			m_JFlag=true;
			PlaySound(SOUND_LABEL_JUMP);
			Speed.y=0;
			Speed.y+=Power;
		}
		if(m_Pos.y>CGame::GetField()->GetHeight(m_Pos,&Normal))
		{
			Speed.y+=G;
			
		}
		m_Pos.y+=Speed.y;
		//�n�ʂ̋N���Ƃ̂����蔻��
		if(m_Pos.y<CGame::GetField()->GetHeight(m_Pos,&Normal))
		{
			m_JFlag=false;
			m_Pos.y=CGame::GetField()->GetHeight(m_Pos,&Normal);
		}

		m_MoveFlag=false;
		//�O�i
		if(GetKeyboardPress(DIK_W))
		{
			m_Pos.x -=sinf(CCamera::GetRot().y)*MODEL_SPEED_Z;
			m_Pos.z -=cosf(CCamera::GetRot().y)*MODEL_SPEED_Z;
			//m_RotDest.y = CCamera::GetRot().y;
			m_RotFlag=true;
			//m_Pos.z+=MODEL_SPEED;
			m_MoveFlag=true;
		}

		//���
		else if(GetKeyboardPress(DIK_S))
		{
			//m_RotDest.y =D3DXToRadian(180)+CCamera::GetRot().y;
			m_RotFlag=true;
			m_Pos.x +=sinf(CCamera::GetRot().y)*MODEL_SPEED_Z;
			m_Pos.z +=cosf(CCamera::GetRot().y)*MODEL_SPEED_Z;
			m_MoveFlag=true;
		}
		//�E
		if(GetKeyboardPress(DIK_D))
		{
			//m_RotDest.y =CCamera::GetRot().y+D3DXToRadian(90);
			m_Rot.y+=0.05f;
			m_Pos.x +=sinf(CCamera::GetRot().y + D3DXToRadian(-90))*MODEL_SPEED_Y;
			m_Pos.z +=cosf(CCamera::GetRot().y + D3DXToRadian(-90))*MODEL_SPEED_Y;
			m_RotFlag=true;
			m_MoveFlag=true;

		}
		//��
		if(GetKeyboardPress(DIK_A))
		{
			//m_RotDest.y =CCamera::GetRot().y+D3DXToRadian(-90);
			m_Rot.y-=0.05f;
			m_Pos.x +=sinf(CCamera::GetRot().y+D3DXToRadian(90))*MODEL_SPEED_Y;
			m_Pos.z +=cosf(CCamera::GetRot().y+D3DXToRadian(90))*MODEL_SPEED_Y;
			m_RotFlag=true;
			m_MoveFlag=true;
		}
		else
		{
			m_RotFlag=false;
		}
		//// ����]
		//if(GetKeyboardPress(DIK_E))
		//{
		//	m_RotDest.y +=MODEL_ROT_SPEED;
		//	//�p�x����	
		//	if(m_RotDest.y > D3DX_PI)
		//	{
		//		m_RotDest.y -= D3DX_PI*2; 
		//	}
		//	if(m_RotDest.y < -D3DX_PI)
		//	{
		//		m_RotDest.y += D3DX_PI*2; 
		//	}
		//	//m_Flag=true;
		//}
		//
		//// �E��]
		//if(GetKeyboardPress(DIK_Q))
		//{
		//	m_RotDest.y-=MODEL_ROT_SPEED;
		//	//�p�x����	
		//	if(m_RotDest.y > D3DX_PI)
		//	{
		//		m_RotDest.y -= D3DX_PI*2; 
		//	}
		//	if(m_RotDest.y < -D3DX_PI)
		//	{
		//		m_RotDest.y += D3DX_PI*2; 
		//	}
		//	//m_Flag=true;
		//}
	}

	//fDiffRotY = m_RotDest.y - m_Rot.y;
	//���K��
	if(fDiffRotY > D3DX_PI)
	{
		fDiffRotY += -D3DX_PI * 2.0f;
	}
	else if(fDiffRotY < -D3DX_PI)
	{
		fDiffRotY += D3DX_PI * 2.0f;
	}

	m_Rot.y+=fDiffRotY*0.1f;
	//���K��
	if(m_Rot.y > D3DX_PI)
	{
		m_Rot.y += -D3DX_PI * 2.0f;
	}
	else if(m_Rot.y < -D3DX_PI)
	{
		m_Rot.y += D3DX_PI * 2.0f;
	}

	//�n��ɂ���������
	if(m_Pos.y < 30.0f && m_Mode!=STATE_DEAD)
	{
		PlaySound(SOUND_LABEL_DEATH);
		//m_Mode=STATE_DEAD;
		Speed.y=0;
		Speed.y+=Power+4;
	}
	
	//�S�[���ɒ������Ƃ�
	if(pCollision->SphereToSphere3D(pPlayer->GetPos(),10.0f,pGoal->GetPos(),10.0f)==true && m_Mode!=STATE_CLEAR)
	{
		PlaySound(SOUND_LABEL_CLEAR);
		m_Mode=STATE_CLEAR;
		Speed.y=0;
		Speed.y+=Power+4;
	
	}



	pGimmick=GetScene(OBJTYPE_GIMMICK);

	GimmickUpPosOld=pGimmick->GetPositionOld().y+ pGimmick->GetVertexMax().y;		//�O�t���[����
	GimmickUnderPosOld=pGimmick->GetPositionOld().y+ pGimmick->GetVertexMin().y;

	//�M�~�b�N�ɑ΂���v���C���[�̃I�t�Z�b�g�����߂�
	OffSet=m_Pos-pGimmick->GetPos();
	Target.x=pGimmick->GetPos().x+(cos(-pGimmick->GetRot().y)*
				OffSet.x+sin(-pGimmick->GetRot().y)*OffSet.z);
	Target.z=pGimmick->GetPos().z+(cos(-pGimmick->GetRot().y)*
				OffSet.z+sin(-pGimmick->GetRot().y)*OffSet.x);

	GimmickPos[0].x=pGimmick->GetPos().x + pGimmick->GetVertexMin().x;
	GimmickPos[0].z=pGimmick->GetPos().z + pGimmick->GetVertexMax().z;
	GimmickPos[1].x=pGimmick->GetPos().x + pGimmick->GetVertexMax().x;
	GimmickPos[1].z=pGimmick->GetPos().z + pGimmick->GetVertexMax().z;
	GimmickPos[2].x=pGimmick->GetPos().x + pGimmick->GetVertexMax().x;
	GimmickPos[2].z=pGimmick->GetPos().z + pGimmick->GetVertexMin().z;
	GimmickPos[3].x=pGimmick->GetPos().x + pGimmick->GetVertexMin().x;
	GimmickPos[3].z=pGimmick->GetPos().z + pGimmick->GetVertexMin().z;


	VecLine.x=GimmickPos[1].x-GimmickPos[0].x;
	VecLine.y=GimmickPos[1].z-GimmickPos[0].z;

	VecToTarget.x=Target.x-GimmickPos[0].x;
	VecToTarget.y=Target.z-GimmickPos[0].z;
	//���̔���
	if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y >=0.0f)
	{
		VecLine.x=GimmickPos[2].x-GimmickPos[1].x;
		VecLine.y=GimmickPos[2].z-GimmickPos[1].z;
		VecToTarget.x=Target.x-GimmickPos[1].x;
		VecToTarget.y=Target.z-GimmickPos[1].z;
		//�E�̔���
		if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y >=0.0f)
		{
			VecLine.x=GimmickPos[3].x-GimmickPos[2].x;
			VecLine.y=GimmickPos[3].z-GimmickPos[2].z;
			VecToTarget.x=Target.x-GimmickPos[2].x;
			VecToTarget.y=Target.z-GimmickPos[2].z;
			//��O�̔���
			if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y >=0.0f)
			{
				VecLine.x=GimmickPos[0].x-GimmickPos[3].x;
				VecLine.y=GimmickPos[0].z-GimmickPos[3].z;
				VecToTarget.x=Target.x-GimmickPos[3].x;
				VecToTarget.y=Target.z-GimmickPos[3].z;

				//���̔���
				if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y >=0.0f)
				{
					//�M�~�b�N�Ɣ͈͓��ɂ����ꍇ
					float GimmickUpPos=pGimmick->GetPos().y+pGimmick->GetVertexMax().y;			//�M�~�b�N�̏�ʂ̍���
					float GimmickUnderPos=pGimmick->GetPos().y+pGimmick->GetVertexMin().y;		//�M�~�b�N�̉��ʂ̍���

					if((GimmickUpPos>m_Pos.y && GimmickUpPosOld<=m_PosOld.y) || (GimmickUpPos<=m_PosOld.y && GimmickUpPos>m_Pos.y))
					{
						//�ォ��߂荞��
						//�v���C���[�̍��Ɛ̂̍������Đݒ�
						m_Pos.y=GimmickUpPos;
						m_PosOld.y=GimmickUpPos;
						m_pSceneLink=pGimmick;
						Speed.y=0;
					}
					else if(m_Pos.y>GimmickUnderPos && m_PosOld.y<=GimmickUnderPos)
					{
 						m_PosOld.y=GimmickUnderPos-ModelHigh;
						m_Pos.y=GimmickUnderPos-ModelHigh;
						Speed.y=0;
					}
				}
			}
		}
	}


	for(int i=0;i<4;i++)
	{
		VecLine.x=GimmickPos[(i+1)%4].x-GimmickPos[i].x;
		VecLine.y=GimmickPos[(i+1)%4].z-GimmickPos[i].z;
		VecToTarget.x=Target.x-GimmickPos[i].x;
		VecToTarget.y=Target.z-GimmickPos[i].z;

		if(VecLine.y*VecToTarget.x-VecLine.x*VecToTarget.y <0.0f)
		{
			//�͈͊O�������f

		}
	}
	
	CDebugProc::Print("\n�v���C���[�̍��W: (%f,%f,%f)\n" ,  m_Pos.x,m_Pos.y,m_Pos.z); 
	this->CSceneX::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
	CSceneX::Update();
	m_PosOld=m_Pos;

}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CSceneX::Draw();
}



//=============================================================================
// �v���C���[���ʏ��Ԃ̂Ƃ�
//=============================================================================
void CPlayer::Neutral(void)
{
	//�K���̍��W�Ɗp�x���擾
	CGame::GetNeedle()->SetPosition((D3DXVECTOR3(m_Pos.x,m_Pos.y+20,m_Pos.z)));
	CGame::GetNeedle()->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);

	//���݂̃J�����̃��[�h����l�̎��_�Ȃ�
	if(CManager::GetCamera()->GetCameraMode() == CCamera::MODE_FIRSTPERSON)
	{
		//m_Rot.y=-CManager::GetCamera()->GetRot().y;
		m_Mode = STATE_SHOT;		//��Ԃ�ύX
	}
}

//=============================================================================
// �ˌ���Ԃ̂Ƃ�
//=============================================================================
void CPlayer::Shot(void)
{
	//CCamera* pCamera;

	//G���������Ƃ��K���̔��˃t���O��false�Ȃ�
	if(GetKeyboardTriger(DIK_G) && TailShotFlag==false)
	{
		PlaySound(SOUND_LABEL_SHOT);
		//�J�����̌����ɐj���΂�
		CGame::GetNeedle()->Shot(CManager::GetCamera()->GetVecCamera());
		TailShotFlag=true;		//�K���̔��˃t���O��true�ɂ���
	}

	//���݂̃J�����̃��[�h���O�l�̎��_�Ȃ�
	if(CManager::GetCamera()->GetCameraMode() == CCamera::MODE_THIRDPERSON)
	{
		m_Mode = STATE_NORMAL;		//��Ԃ��m�[�}���ɂ���
		TailShotFlag=false;			//�K���̔��˃t���O��false�ɂ���
		CNeedle* pNeedle=CGame::GetNeedle();
		pNeedle->SetHitFlag(false);
	}
}

//=============================================================================
// �K���̐j���߂��Ă���̂Ƃ�
//=============================================================================
void CPlayer::Return(void)
{

}

//=============================================================================
// �K���ɐj�Ɉ���������Ƃ�
//=============================================================================
void CPlayer::Pulled(void)
{
	D3DXVECTOR3 Dest;
	CNeedle* pNeedle=CGame::GetNeedle();

	Dest.x=(pNeedle->GetPos().x-m_Pos.x);
	m_Pos.x+=Dest.x*0.02f;

	Dest.y=(pNeedle->GetPos().y-m_Pos.y);
	m_Pos.y+=Dest.y*0.02f;

	Dest.z=(pNeedle->GetPos().z-m_Pos.z);
	m_Pos.z+=Dest.z*0.02f;

	CDebugProc::Print("\nDest: (%f,%f,%f)\n" ,  Dest.x,Dest.y,Dest.z);
	CDebugProc::Print("\nm_Pos: (%f,%f,%f)\n" ,  m_Pos.x,m_Pos.y,m_Pos.z);
	CDebugProc::Print("\n�K���̍��W: (%f,%f,%f)\n" ,  pNeedle->GetPos().x,pNeedle->GetPos().y,pNeedle->GetPos().z);
}

//���S���o
void CPlayer::DeadDirection(void)
{
	float G=-0.2f;		//�d��

	
	Speed.y+=G;
	CRenderer* pRenderer=CManager::GetRenderer();
	//���@�ɃG�t�F�N�g���Z�b�g
	CEffect::Create(255,30,10,m_Pos.x,m_Pos.y,m_Pos.z,pRenderer);
	CEffect::Create(100,30,10,m_Pos.x,m_Pos.y,m_Pos.z,pRenderer);
	m_Rot.x+=0.2f;

	if(m_Pos.y>0)
	{
		m_Pos.y+=Speed.y;
	}
	

	if(m_Pos.y<20)
	{
		m_DeadFlag=true;
	}
}

//�N���A���o
void CPlayer::ClearDirection(void)
{
	float G=-0.5f;		//�d��
	CPlayer* pPlayer=CGame::GetPlayer();
	CGoal* pGoal = CGame::GetGoal();
	CCollision* pCollision = CGame::GetCollision();

	Speed.y+=G;
	if(m_Pos.y>0)
	{
		m_Pos.y+=Speed.y;
	}

	if(m_Pos.y<53)
	{
		m_ClearFlag=true;
	}
}