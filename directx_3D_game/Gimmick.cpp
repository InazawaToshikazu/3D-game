//=============================================================================
//
// �M�~�b�N�\������ [Gimmick.cpp]
// Author : ���V�r�a
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Gimmick.h"
#include "Renderer.h"
#include "SceneX.h"
#include "Input.h"
#include "Player.h"
#include "Manager.h"
#include "debugproc.h"
#include "Game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE_SPEED					(1.3f)		//�M�~�b�N�̈ړ����x
#define ROT_SPEED					(0.01f)		//�M�~�b�N�̉�]���x

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGimmick::CGimmick(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PosOld=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PosOld=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotOld=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxMin=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_VtxMax=D3DXVECTOR3(0.0f,0.0f,0.0f);
	Movex=MOVE_SPEED;
	Movez=MOVE_SPEED;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGimmick::~CGimmick(void)
{
	
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CGimmick* CGimmick::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CGimmick *pGimmick;
	//�C���X�^���X�̍쐬
	pGimmick = new CGimmick(OBJTYPE_GIMMICK);
	//CEnemy��Init���Ăяo��
	pGimmick->Init(m_pRenderer);
	//���W�̐ݒ�
	pGimmick->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pGimmick->SetPos(fPosX,fPosY,fPosZ);

	return pGimmick;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGimmick::Init(CRenderer *pRenderer)
{
	//X�t�@�C���̎w��
	FileName="data/MODEL/b.x";

	CSceneX::Init(pRenderer);

	//m_VtxMin=D3DXVECTOR3(-80.0f,-2.0f,-80.0f);
	//m_VtxMax=D3DXVECTOR3(80.0f,2.0f,80.0f);
	
	m_VtxMin=D3DXVECTOR3(-30.0f,-2.0f,-37.0f);
	m_VtxMax=D3DXVECTOR3(30.0f,2.0f,37.0f);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGimmick::Uninit(void)
{
	//���g�̃��\�[�X�̉��
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGimmick::Update(void)
{
	//�M�~�b�N�̎����ړ�
	m_Pos.z+=Movez;
	//m_Pos.x+=Movex;
	////�͈͊O�ɍs�����甽�]
	//if(m_Pos.z<=-1000.0f || m_Pos.z>=-50.0f)
	//{
	//	Movez=-Movez;
	//}
	////
	//if(m_Pos.x>=1000.0f || m_Pos.x<=20.0f)
	//{
	//	Movex=-Movex;
	//}

	//�ړ��̐���
	if(m_Pos.z < -753 || m_Pos.z > -400)
	{
		Movez=-Movez;
	}

	//CDebugProc::Print("\n�M�~�b�N�̍��W: (%f,%f,%f)\n" ,  m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
	

	CPlayer* pPlayer=CGame::GetPlayer();
	if(pPlayer!=NULL)
	{
		if(pPlayer->GetSceneLink()==this)
		{
			//�����N���Ă���
			D3DXVECTOR3 RotDest,Offset,PlayerPos,PlayerRot,OffsetRot,GimmickMove;
			PlayerPos=pPlayer->GetPos();
			PlayerRot=pPlayer->GetRot();
			//CDebugProc::Print("\n�ړ��O�v���C��[�̍��W: (%f,%f,%f)\n" ,  PlayerPos.x,PlayerPos.y,PlayerPos.z);
			//��]�̍������Z�o
			RotDest=m_Rot-m_RotOld;

			//���K��
			if(RotDest.y > D3DX_PI)
			{
				RotDest.y += -D3DX_PI * 2.0f;
			}
			else if(RotDest.y < -D3DX_PI)
			{
				RotDest.y += D3DX_PI * 2.0f;
			}

			//�I�t�Z�b�g�̎Z�o
			Offset=PlayerPos-m_Pos;

			//�I�t�Z�b�g�̉�]
			OffsetRot.x=cos(RotDest.y)*Offset.x+sin(RotDest.y)*Offset.z;
			OffsetRot.z=cos(RotDest.y)*Offset.z-sin(RotDest.y)*Offset.x;

			//�V�v���C���[���W
			PlayerPos.x=m_Pos.x+OffsetRot.x;
			PlayerPos.z=m_Pos.z+OffsetRot.z;

			//�M�~�b�N�̈ړ���
			GimmickMove=m_Pos-m_PosOld;

			//�V�v���C���[���W
			PlayerPos.x+=GimmickMove.x;
			PlayerPos.y=m_Pos.y+m_VtxMax.y;
			PlayerPos.z+=GimmickMove.z;
			//CDebugProc::Print("\n�����݂��ړ������̍��W: (%f,%f,%f)\n" ,  GimmickMove.x,GimmickMove.y,GimmickMove.z);
			//CDebugProc::Print("\n�ړ���v���C��[�̍��W: (%f,%f,%f)\n" ,  PlayerPos.x,PlayerPos.y,PlayerPos.z);

			//�e���𔽉f
			pPlayer->CPlayer::SetPosition(PlayerPos);
			pPlayer->SetPositionOld(PlayerPos.x,PlayerPos.y,PlayerPos.z);
			pPlayer->AddRot(0,RotDest.y,0);
		}
	}

	m_PosOld=m_Pos;
	m_RotOld=m_Rot;
	CSceneX::Update();

}

//=============================================================================
// �`�揈��
//=============================================================================
void CGimmick::Draw(void)
{
	CSceneX::Draw();
}