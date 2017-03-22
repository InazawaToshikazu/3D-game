//=============================================================================
//
// ���[�V�������� [MotionModel.cpp]
// Author : ���V�r�a
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "MotionModel.h"
#include "Scene.h"
#include "SceneX.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "SubModel.h"
#include "Scene3D.h"

#include "Bullet.h"
#include "CMeshField.h"
#include "Gimmick.h"
#include "Camera.h"
#include "Game.h"
#include "Fade.h"
#include "Score.h"
#include "sound.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define ROT_SPEED  (0.01f)	//��]���x

CRenderer* CMotionModel::m_pMotion;
//D3DXVECTOR3 Speed=D3DXVECTOR3(0.0f,0.0f,0.0f);
bool CMotionModel::m_RotFlag;
CFade* CMotionModel::m_pFade=NULL;
CPlayer* CMotionModel::m_pFlag;


#define MODEL_ROT_SPEED				(0.05f)		//���f���̉�]���x
#define MODEL_SPEED_X				(1.7f)		//���f���̈ړ����x
#define MODEL_SPEED_Z				(1.7f)		//
#define MODEL_SPEED_Y				(0.1f)		//
#define MODEL_SPEED					(0.7f)		//


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMotionModel::CMotionModel(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pDevice=NULL;
	for(int i=0;i<PART_MAX;i++)
	{
		m_Part[i]=NULL;
		m_Part2[i]=NULL;
	}
	for(int i=0;i<KEY_MAX;i++)
	{
		m_Anime[i].Frame=60;
		m_Anime2[i].Frame=60;
	}

	m_pMotion=NULL;
	m_MotionKey=0;
	m_MotionTime=0.0f;
	m_KeyMax=KEY_MAX;


	m_AnimLoopFlag=false;
	m_BlendFlag=false;
	m_PunchFlag=false;
	m_Ratios=0.0f;
	m_Key=0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMotionModel::~CMotionModel(void)
{

}


//=============================================================================
// ����������
//=============================================================================
HRESULT CMotionModel::Init(CRenderer* pRenderer)
{
	m_pDevice=CManager::GetRenderer()->GetDevice();

	m_Part[0]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_body.x",pRenderer);			//����
	m_Part[1]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_tail1.x",pRenderer);			//�K��1

	m_Part[2]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_tail2.x",pRenderer);		//�K��1
	m_Part[3]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_tail3.x",pRenderer);		//�K��1

	m_Part[4]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_tail4.x",pRenderer);		//�K��1
	m_Part[5]=CSubModel::Create(500,70,-500,"data/MODEL/player/sasori_needle.x",pRenderer);		//�j

	/*m_Part[6]=CSubModel::Create(503,66,-500,"data/MODEL/leg_l.x",pRenderer);		//�j
	m_Part[7]=CSubModel::Create(497,66,-500,"data/MODEL/leg_r.x",pRenderer);		//�E��

	m_Part[8]=CSubModel::Create(503,62,-500,"data/MODEL/foot_l.x",pRenderer);		//������
	m_Part[9]=CSubModel::Create(497,62,-500,"data/MODEL/foot_r.x",pRenderer);		//�E����*/
	
	WaitMotion2();

	PartsInit();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMotionModel::Uninit(void)
{
	Release();
	for(int i=0;i<PART_MAX;i++)
	{
		//���g�̃��\�[�X�̉��
		if(m_Part[i]!=NULL)
		{
			m_Part[i]->Uninit();
			delete m_Part[i];
			m_Part[i] = nullptr;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CMotionModel::Update(void)
{
	bool flag=false;
	//�f�o�b�O�����\��
	DrawDebug();

	//���삷��p�[�c�̑I��
	if(GetKeyboardPress(DIK_0)){m_MotionKey=0;}		//����
	if(GetKeyboardPress(DIK_1)){m_MotionKey=1;}		//��
	if(GetKeyboardPress(DIK_2)){m_MotionKey=2;}		//���r
	if(GetKeyboardPress(DIK_3)){m_MotionKey=3;}		//�E�r
	if(GetKeyboardPress(DIK_4)){m_MotionKey=4;}		//����
	if(GetKeyboardPress(DIK_5)){m_MotionKey=5;}		//�E��
	//if(GetKeyboardPress(DIK_6)){m_MotionKey=6;}		//����
	//if(GetKeyboardPress(DIK_7)){m_MotionKey=7;}		//�E��
	//if(GetKeyboardPress(DIK_8)){m_MotionKey=8;}		//������
	//if(GetKeyboardPress(DIK_9)){m_MotionKey=9;}		//�E����

	//�I�������p�[�c�̍��W�Ɗp�x�̎擾
	D3DXVECTOR3 Pos=m_Part[m_MotionKey]->GetPos();
	D3DXVECTOR3 Rot=m_Part[m_MotionKey]->GetRot();

	//�ړ�
	//�E
	if(GetKeyboardPress(DIK_D))
	{
		Pos.x+=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}
	//��
	if(GetKeyboardPress(DIK_A))
	{
		Pos.x-=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}
	//�O
	if(GetKeyboardPress(DIK_W))
	{
		Pos.z+=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}

	//���
	if(GetKeyboardPress(DIK_S))
	{
		Pos.z-=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}
	//��
	if(GetKeyboardPress(DIK_O))
	{
		Pos.y+=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}

	//��
	if(GetKeyboardPress(DIK_L))
	{
		Pos.y-=MOVE_SPEED;
		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
	}
	//��]
	if(GetKeyboardPress(DIK_Z))
	{
		Rot.z+=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}
	//��]2
	if(GetKeyboardPress(DIK_X))
	{
		Rot.z-=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}

	//��]2
	if(GetKeyboardPress(DIK_C))
	{
		Rot.y-=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}
		//��]2
	if(GetKeyboardPress(DIK_V))
	{
		Rot.y+=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}
	//��]2
	if(GetKeyboardPress(DIK_B))
	{
		Rot.x+=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}
	if(GetKeyboardPress(DIK_N))
	{
		Rot.x-=ROT_SPEED;
		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
	}

	//���f���̉�]
	if(GetKeyboardPress(DIK_Z))
	{
		Rot.y-=ROT_SPEED;
		m_Part[0]->SetRot(Rot.x,Rot.y,Rot.z);
	}

	/*if(GetKeyboardTriger(DIK_F1)){m_MotionTime=0;}
	if(m_BlendFlag==false)
	{
		if(GetKeyboardTriger(DIK_F2))
		{
			WaitMotion();
			m_Key=m_MotionTime;
			m_MotionTime=0;

		}
		if(GetKeyboardTriger(DIK_F3)&&m_PunchFlag==false)
		{
			PunchMotion();
			m_Key=m_MotionTime;
			m_MotionTime=0;
		}
		if(GetKeyboardTriger(DIK_F4))
		{
			RunningMotion();
			m_Key=m_MotionTime;
			m_MotionTime=0;
		}		//�����j���O
		if(GetKeyboardTriger(DIK_F5))
		{
			DownMotion();
			m_Key=m_MotionTime;
			m_MotionTime=0;
		}			//����
	}

	int i = (int)m_MotionTime;  // i �ɑS�̃A�j�����Ԃ̐�����������
	if( i > m_KeyMax - 2 ){i = m_KeyMax - 2;}
	float dt = 1.0f / m_Anime[i].Frame;
	if(m_BlendFlag==false)
	{
		for(int j = 0; j < PART_MAX; j++)
		{
			D3DXVECTOR3 KeyRot,KeyRot2;
			KeyRot.x=(m_Anime[i+1].Key[j].Rot.x - m_Anime[i].Key[j].Rot.x);
			KeyRot.y=(m_Anime[i+1].Key[j].Rot.y - m_Anime[i].Key[j].Rot.y);
			KeyRot.z=(m_Anime[i+1].Key[j].Rot.z - m_Anime[i].Key[j].Rot.z);

			//���K��
			if(KeyRot.x > D3DX_PI)
			{
				KeyRot.x -= D3DX_PI*2; 
			}
			if(KeyRot.x < -D3DX_PI)
			{
				KeyRot.x += D3DX_PI*2; 
			}
			if(KeyRot.y > D3DX_PI)
			{
				KeyRot.y -= D3DX_PI*2; 
			}
			if(KeyRot.y < -D3DX_PI)
			{
				KeyRot.y += D3DX_PI*2; 
			}
			if(KeyRot.z > D3DX_PI)
			{
				KeyRot.z -= D3DX_PI*2; 
			}
			if(KeyRot.z < -D3DX_PI)
			{
				KeyRot.z += D3DX_PI*2; 
			}


			//���`���
			// trans x ���
			m_Pos.x= m_Anime[i].Key[j].Pos.x +											//�O�̃L�[�t���[���ʒu
								(m_Anime[i+1].Key[j].Pos.x - m_Anime[i].Key[j].Pos.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - i);								//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			// trans y ���
			m_Pos.y = m_Anime[i].Key[j].Pos.y +											//�O�̃L�[�t���[���ʒu
								(m_Anime[i+1].Key[j].Pos.y - m_Anime[i].Key[j].Pos.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			// trans z ���
			m_Pos.z = m_Anime[i].Key[j].Pos.z +											//�O�̃L�[�t���[���ʒu
								(m_Anime[i+1].Key[j].Pos.z - m_Anime[i].Key[j].Pos.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			// scale x ��� 
			m_Scl.x = m_Anime[i].Key[j].Scl.x +											//�O�̃L�[�t���[���ʒu
								(m_Anime[i+1].Key[j].Scl.x - m_Anime[i].Key[j].Scl.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			// scale y ���
			m_Scl.y = m_Anime[i].Key[j].Scl.y +											//�O�̃L�[�t���[���ʒu
								(m_Anime[i+1].Key[j].Scl.y - m_Anime[i].Key[j].Scl.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			// scale z ���
			m_Scl.z = m_Anime[i].Key[j].Scl.z +											//�O�̃L�[�t���[���ʒu
								(m_Anime[i+1].Key[j].Scl.z - m_Anime[i].Key[j].Scl.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			// rotation ���
			m_Rot.x = m_Anime[i].Key[j].Rot.x +											//�O�̃L�[�t���[���ʒu
									KeyRot.x											//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
			// rotation ��� 
			m_Rot.y = m_Anime[i].Key[j].Rot.y +											//�O�̃L�[�t���[���ʒu
									KeyRot.y											//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊���������		// rotation ��� 
			m_Rot.z = m_Anime[i].Key[j].Rot.z +											//�O�̃L�[�t���[���ʒu
									KeyRot.z											//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
				//��Ōv�Z�������l��ݒ肷��
			m_Part[j]->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
			//m_Part[j]->SetScl(m_Scl.x,m_Scl.y,m_Scl.z);
			m_Part[j]->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
	

		}
	}
	else
	{
		Linear();
	}

		
		


		//��
		if(GetKeyboardPress(DIK_W))
		{
			Pos.z+=MOVE_SPEED;
			m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
			if(GetKeyboardTriger(DIK_W))
			{
				RunningMotion();
			}
		}
		//�E
		if(GetKeyboardPress(DIK_D))
		{
			Pos.x+=MOVE_SPEED;
			m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
		}
		//��
		if(GetKeyboardPress(DIK_S))
		{
			Pos.z-=MOVE_SPEED;
			m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
		}
		//��
		if(GetKeyboardPress(DIK_A))
		{
			Pos.x-=MOVE_SPEED;
			m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
		}

		if(GetKeyboardPress(DIK_Z))
		{
			Rot.y-=MOVE_SPEED;
			m_Part[0]->SetRot(Rot.x,Rot.y,Rot.z);

		}*/
		
	


	
	/*if(m_BlendFlag==false)
	{
		m_MotionTime += dt;
	}
	if( m_MotionTime > m_KeyMax - 1.0f )
	{
		m_MotionTime = m_KeyMax - 1.0f;
		if(m_AnimLoopFlag==true)
		{
			m_MotionTime=0;
		}
		else
		{
			WaitMotion();
		}
	}*/
	
	for(int i=0;i<PART_MAX;i++)
	{
		m_Part[i]->Update();
	}
	//CDebugProc::Print("(%f)\n" , m_MotionTime);


}

//=============================================================================
// �`�揈��
//=============================================================================
void CMotionModel::Draw(void)
{
	/*
	// key & frame �\��
	int Key = (int)m_MotionTime;  // i �ɑS�̃A�j�����Ԃ̐�����������

	if( Key > m_KeyMax - 2 ){Key = m_KeyMax - 2;}

	float dt = 1.0f / m_Anime[Key].Frame;
	float rest = m_MotionTime - Key;
	int Frame = rest / dt;
	CDebugProc::Print("\nKey:%d  frame:%d\n" ,Key,Frame);
	*/

	for(int i=0;i<PART_MAX;i++)
	{
		m_Part[i]->Draw();
	}
}
//=============================================================================
// �o�C���h�|�[�Y
//=============================================================================
void CMotionModel::PartsInit(void)
{
	// �f�[�^������ �K��1
	m_Part[1]->SetPos(0.0f,23.0f,45.0f);
	m_Part[1]->SetParent(m_Part[0]);

	// part ����
	m_Part[0]->SetPos(500.0f,70.0f,-500.0f);
	m_Part[0]->SetParent(NULL);

	//part2�K��2
	m_Part[2]->SetPos(0.0f,10.0f,15.0f); 
	 // �d�v�@�e�o�^
	m_Part[2]->SetParent(m_Part[1]);


	// part �K��3
	m_Part[3]->SetPos(0.0f,20.0f,0.0f);
	// �d�v�@�e�o�^
	m_Part[3]->SetParent(m_Part[2]);


	//����K��4
	m_Part[4]->SetPos(0.0f,18.0f,-8.0f);
	// �d�v�@�e�o�^
	m_Part[4]->SetParent(m_Part[3]);

	// �j
	m_Part[5]->SetPos(500.0f,70.0f,-520.0f);
	// �d�v�@�e�o�^
	m_Part[5]->SetParent(NULL);

	//����
	//m_Part[6]->SetPos(4.0f,-1.0f,0.0f);
	//
	//// �d�v�@�e�o�^
	//m_Part[6]->SetParent(m_Part[0]);
	//
	////�E��
	//m_Part[7]->SetPos(-4.0f,-1.0f,0.0f);
	//
	//// �d�v�@�e�o�^
	//m_Part[7]->SetParent(m_Part[0]);
	//
	////������
	//m_Part[8]->SetPos(0.0f,-12.0f,0.0f);
	//
	//// �d�v�@�e�o�^
	//m_Part[8]->SetParent(m_Part[6]);
	//
	////�E����
	//m_Part[9]->SetPos(0.0f,-12.0f,0.0f);
	//
	//// �d�v�@�e�o�^
	//m_Part[9]->SetParent(m_Part[7]);
}
//=============================================================================
// �N���G�C�g
//=============================================================================
CMotionModel *CMotionModel::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CMotionModel *pObje;
	//�C���X�^���X�̍쐬
	pObje = new CMotionModel(OBJTYPE_MOTIONMODEL);
	//SceneX�̏�����
	pObje->Init(m_pRenderer);
	//���W�̐ݒ�
	pObje->SetPos(fPosX,fPosY,fPosZ);
	return pObje;
}
//=============================================================================
//�f�o�b�O�����̕\��
//=============================================================================
void CMotionModel::DrawDebug(void)
{
	CDebugProc::Print("\n0���� : (%f,%f,%f)\n", m_Part[0]->GetPos().x,m_Part[0]->GetPos().y,m_Part[0]->GetPos().z);
	CDebugProc::Print("1�K��1 : (%f,%f,%f)\n"   ,  m_Part[1]->GetPos().x,m_Part[1]->GetPos().y,m_Part[1]->GetPos().z);
	CDebugProc::Print("2�K��2 : (%f,%f,%f)\n" ,  m_Part[2]->GetPos().x,m_Part[2]->GetPos().y,m_Part[2]->GetPos().z);
	CDebugProc::Print("3�K��3 : (%f,%f,%f)\n" ,  m_Part[3]->GetPos().x,m_Part[3]->GetPos().y,m_Part[3]->GetPos().z);
	CDebugProc::Print("4�K��4 : (%f,%f,%f)\n" ,  m_Part[4]->GetPos().x,m_Part[4]->GetPos().y,m_Part[4]->GetPos().z);
	CDebugProc::Print("5�j : (%f,%f,%f)\n" ,  m_Part[5]->GetPos().x,m_Part[5]->GetPos().y,m_Part[5]->GetPos().z);

	/*CDebugProc::Print("\n0���� : (%f,%f,%f)\n", m_Part[0]->GetRot().x,m_Part[0]->GetRot().y,m_Part[0]->GetRot().z);
	CDebugProc::Print("1�� : (%f,%f,%f)\n"   ,  m_Part[1]->GetRot().x,m_Part[1]->GetRot().y,m_Part[1]->GetRot().z);
	CDebugProc::Print("2���r : (%f,%f,%f)\n" ,  m_Part[2]->GetRot().x,m_Part[2]->GetRot().y,m_Part[2]->GetRot().z);
	CDebugProc::Print("3�E�r : (%f,%f,%f)\n" ,  m_Part[3]->GetRot().x,m_Part[3]->GetRot().y,m_Part[3]->GetRot().z);
	CDebugProc::Print("4���� : (%f,%f,%f)\n" ,  m_Part[4]->GetRot().x,m_Part[4]->GetRot().y,m_Part[4]->GetRot().z);
	CDebugProc::Print("5�E�� : (%f,%f,%f)\n" ,  m_Part[5]->GetRot().x,m_Part[5]->GetRot().y,m_Part[5]->GetRot().z);
	CDebugProc::Print("6���� : (%f,%f,%f)\n" ,  m_Part[6]->GetRot().x,m_Part[6]->GetRot().y,m_Part[6]->GetRot().z);
	CDebugProc::Print("7�E�� : (%f,%f,%f)\n" ,  m_Part[7]->GetRot().x,m_Part[7]->GetRot().y,m_Part[7]->GetRot().z);
	CDebugProc::Print("8���� : (%f,%f,%f)\n" ,  m_Part[8]->GetRot().x,m_Part[8]->GetRot().y,m_Part[8]->GetRot().z);
	CDebugProc::Print("9�E�� : (%f,%f,%f)\n" ,  m_Part[9]->GetRot().x,m_Part[9]->GetRot().y,m_Part[9]->GetRot().z);
	*/

	CDebugProc::Print("\n������@:WASD:���s�ړ�\nOL:�㏸���~\nZ����]:��XZ\nY����]:C��V\n" );
	CDebugProc::Print("�J��������:��������\n�㏸���~�FI��K\nF1:�f�[�^�̏�������" );
	CDebugProc::Print("\n�J��������FN,M" );
	CDebugProc::Print("\nF2:�ҋ@\n\F3:�p���`\nF4�F����\nF5:����" );

}


//=============================================================================
//�ҋ@���[�V�����̕\��
//=============================================================================
void CMotionModel::WaitMotion2(void)
{		
	m_AnimLoopFlag=true;
	//�ҋ@���[�V����
	// part ����
	m_Anime[0].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime[0].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
	m_Anime[0].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
	// part 4�E�r
	m_Anime[0].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime[0].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
	//����
	m_Anime[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime[0].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime[0].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime[0].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	// part ����
	m_Anime[1].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime[1].Key[0].Rot=D3DXVECTOR3(-0.05f,-0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime[1].Key[1].Rot=D3DXVECTOR3(-0.14f,0.0f,0.0f);
	//part2���r
	m_Anime[1].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,0.0f);
	m_Anime[1].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.439f);
	// part 4�E�r
	m_Anime[1].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime[1].Key[3].Rot=D3DXVECTOR3(0.14f,-0.07f,1.39f);
	//����
	m_Anime[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime[1].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime[1].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	//�ҋ@���[�V����
	// part ����
	m_Anime[2].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime[2].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
	m_Anime[2].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
	// part 4�E�r
	m_Anime[2].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime[2].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
	//����
	m_Anime[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime[2].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime[2].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

}

//=============================================================================
//�ҋ@���[�V�����̕\��
//=============================================================================
void CMotionModel::WaitMotion(void)
{		
	m_AnimLoopFlag=true;
	//�ҋ@���[�V����
	// part ����
	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
	// part 4�E�r
	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
	//����
	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	// part ����
	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(-0.05f,-0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(-0.14f,0.0f,0.0f);
	//part2���r
	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,0.0f);
	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.439f);
	// part 4�E�r
	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.14f,-0.07f,1.39f);
	//����
	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	//�ҋ@���[�V����
	// part ����
	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
	// part 4�E�r
	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
	//����
	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_BlendFlag=true;

}
//=============================================================================
//�p���`���[�V�����̕\��
//=============================================================================
void CMotionModel::PunchMotion(void)
{
	//m_PunchFlag=true;
	m_AnimLoopFlag=false;
	//�p���`���[�V����
	// part ����
	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,12.0f,0.0f);
	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,-1.18f);
	// part 4�E�r
	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,1.16f);
	//����
	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

		// part ����
	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(0.0f,-0.17f,0.0f);
	// �f�[�^������ ��
	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.0f,-0.05f,-1.14f);
	// part 4�E�r
	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,-3.3f);
	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.0f,-1.55f,-0.11f);
	//����
	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,1.53f,0.03f);
	// �E��
	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(-0.22f,0.0f,0.0f);
	//�E��
	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.74f,0.08f,0.0f);
	//������
	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.49f,0.0f);
	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-9.8f,7.5f);
	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.30f,0.30f);

		//�p���`���[�V����
	// part ����
	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,12.0f,0.0f);
	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.0f,0.0f,-1.18f);
	// part 4�E�r
	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.0f,0.0f,1.16f);
	//����
	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	m_BlendFlag=true;
	//m_PunchFlag=false;
}
//=============================================================================
//�����j���O���[�V�����̕\��
//=============================================================================
void CMotionModel::RunningMotion(void)
{
	m_AnimLoopFlag=true;
	//�����j���O���[�V����
	// part ����
	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.96f,0.07f,-1.27f);
	// part 4�E�r
	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-8.1f,13.5f,-2.4f);
	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(-3.75f,0.09f,-1.27f);
	//����
	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
	// �E��
	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,-0.02f);
	//����
	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(-0.36f,0.0f,0.0f);
	//�E��
	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,-0.6f);
	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.87f,0.0f,0.0f);
	//������
	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
	//�E����
	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);

	//�����j���O���[�V����
	// part ����
	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(9.6f,12.0f,-2.4f);
	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(-0.74f,-0.28f,-1.29f);
	// part 4�E�r
	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-8.1f,12.5f,-0.3f);
	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(-2.23f,0.2f,-1.27f);
	//����
	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
	// �E��
	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,0.02f);
	//����
	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.61f,0.0f,0.0f);
	//�E��
	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(-0.8f,0.0f,0.0f);
	//������
	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
	//�E����
	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);

	
	// part ����
	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �f�[�^������ ��
	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.96f,0.07f,-1.27f);
	// part 4�E�r
	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-8.1f,13.5f,-2.4f);
	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(-3.75f,0.09f,-1.27f);
	//����
	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
	// �E��
	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,-0.02f);
	//����
	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(-0.36f,0.0f,0.0f);
	//�E��
	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,-0.6f);
	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.87f,0.0f,0.0f);
	//������
	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
	//�E����
	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);
		m_BlendFlag=true;

}
//=============================================================================
//���ꃂ�[�V�����̕\��
//=============================================================================
void CMotionModel::DownMotion(void)
{
	m_AnimLoopFlag=false;
	//���ꃂ�[�V����
	// part ����
	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,76.5f,-476.0f);
	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.929f,0.02f,0.0f);
	// �f�[�^������ ��
	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//part2���r
	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
	// part 4�E�r
	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,0.0f);
	//����
	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-9.0f,0.0f);
	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	// part ����
	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,59.0f,-476.0f);
	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(1.5f,0.002f,0.0f);
	// �f�[�^������ ��
	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,23.5f,2.5f);
	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(-0.12f,1.07f,-0.03f);
	//part2���r
	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
	// part 4�E�r
	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
	//����
	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);

	
	// part ����
	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,59.5f,-476.0f);
	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(1.5f,-0.02f,0.0f);
	// �f�[�^������ ��
	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(-30.0f,23.5f,2.5f);
	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(-0.12f,2.08f,0.0f);
	//part2���r
	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
	// part 4�E�r
	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,0.0f);
	//����
	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	// �E��
	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//����
	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E��
	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//������
	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	//�E����
	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_BlendFlag=true;

}
//=============================================================================
// �A�j�������o��
//=============================================================================
void CMotionModel::WriteAnime(void)
{
	int i = (int)m_MotionTime;  // i �ɑS�̃A�j�����Ԃ̐�����������
	if( i > m_KeyMax - 2 ){i = m_KeyMax - 2;}
	float dt = 1.0f / m_Anime[i].Frame;

	FILE *fp;
	fp = fopen("data.txt","a+");
	if( fp==NULL )
	return;

	fprintf(fp,"// key data\n");
	fprintf(fp,"\t{ 60,\t// frame count\n");

	fprintf(fp,"\t\t{\n");

	for (int j = 0; j < PART_MAX; j++)
	{
		fprintf(fp,"\t\t\t// part %d\n",i);
		fprintf(fp,"\t\t\t{ D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// trans\n",m_Anime[i].Key[j].Pos.x,m_Anime[i].Key[j].Pos.y,m_Anime[i].Key[j].Pos.z);
		fprintf(fp,"\t\t\t  D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// scale\n",m_Anime[i].Key[j].Scl.x,m_Anime[i].Key[j].Scl.y,m_Anime[i].Key[j].Scl.z);
		fprintf(fp,"\t\t\t  D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// rotation\n",m_Anime[i].Key[j].Rot.x,m_Anime[i].Key[j].Rot.y,m_Anime[i].Key[j].Rot.z);
		fprintf(fp,"\t\t\t},\n");
	}
	fprintf(fp,"\t\t}\n");
	fprintf(fp,"\t},\t// end of key\n");

	fclose(fp);
}



void CMotionModel::Linear(void)
{
	int k = (int)m_MotionTime;  // k �ɑS�̃A�j�����Ԃ̐�����������
	if( k > m_KeyMax - 2 ){k = m_KeyMax - 2;}
	for(int l = 0; l < PART_MAX; l++)
	{
		D3DXVECTOR3 KeyRot,KeyRot2;
		KeyRot.x=(m_Anime[m_Key+1].Key[l].Rot.x - m_Anime[m_Key].Key[l].Rot.x);
		KeyRot.y=(m_Anime[m_Key+1].Key[l].Rot.y - m_Anime[m_Key].Key[l].Rot.y);
		KeyRot.z=(m_Anime[m_Key+1].Key[l].Rot.z - m_Anime[m_Key].Key[l].Rot.z);
		KeyRot2.x=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
		KeyRot2.y=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
		KeyRot2.z=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);

		if(KeyRot.x > D3DX_PI)
		{
			KeyRot.x -= D3DX_PI*2; 
		}
		if(KeyRot.x < -D3DX_PI)
		{
			KeyRot.x += D3DX_PI*2; 
		}

		if(KeyRot.y > D3DX_PI)
		{
			KeyRot.y -= D3DX_PI*2; 
		}
		if(KeyRot.y < -D3DX_PI)
		{
			KeyRot.y += D3DX_PI*2; 
		}

		if(KeyRot.z > D3DX_PI)
		{
			KeyRot.z -= D3DX_PI*2; 
		}
		if(KeyRot.z < -D3DX_PI)
		{
			KeyRot.z += D3DX_PI*2; 
		}
		//2����
		if(KeyRot2.x > D3DX_PI)
		{
			KeyRot2.x -= D3DX_PI*2; 
		}
		if(KeyRot2.x < -D3DX_PI)
		{
			KeyRot2.x += D3DX_PI*2; 
		}

		if(KeyRot2.y > D3DX_PI)
		{
			KeyRot2.y -= D3DX_PI*2; 
		}
		if(KeyRot2.y < -D3DX_PI)
		{
			KeyRot2.y += D3DX_PI*2; 
		}

		if(KeyRot2.z > D3DX_PI)
		{
			KeyRot2.z -= D3DX_PI*2; 
		}
		if(KeyRot2.z < -D3DX_PI)
		{
			KeyRot2.z += D3DX_PI*2; 
		}


		//���`���
		m_Pos.x= (m_Anime[m_Key].Key[l].Pos.x +												//�O�̃L�[�t���[���ʒu
							(m_Anime[m_Key+1].Key[l].Pos.x - m_Anime[m_Key].Key[l].Pos.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
								* (m_MotionTime - k))*(1.0-m_Ratios);								//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// trans y ���
		m_Pos.y = (m_Anime[m_Key].Key[l].Pos.y +											//�O�̃L�[�t���[���ʒu
							(m_Anime[m_Key+1].Key[l].Pos.y - m_Anime[m_Key].Key[l].Pos.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(1.0-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// trans z ���
		m_Pos.z = (m_Anime[m_Key].Key[l].Pos.z +											//�O�̃L�[�t���[���ʒu
							(m_Anime[m_Key+1].Key[l].Pos.z - m_Anime[m_Key].Key[l].Pos.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(1.0-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// scale x ��� 
		m_Scl.x = (m_Anime[m_Key].Key[l].Scl.x +											//�O�̃L�[�t���[���ʒu
							(m_Anime[m_Key+1].Key[l].Scl.x - m_Anime[m_Key].Key[l].Scl.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(1.0-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// scale y ���
		m_Scl.y = (m_Anime[m_Key].Key[l].Scl.y +											//�O�̃L�[�t���[���ʒu
							(m_Anime[m_Key+1].Key[l].Scl.y - m_Anime[m_Key].Key[l].Scl.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(1.0-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// scale z ���
		m_Scl.z = (m_Anime[m_Key].Key[l].Scl.z +											//�O�̃L�[�t���[���ʒu
							(m_Anime[m_Key+1].Key[l].Scl.z - m_Anime[m_Key].Key[l].Scl.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(1.0-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
									
		// Rotatkon ���
		m_Rot.x = (m_Anime[m_Key].Key[l].Rot.x +											//�O�̃L�[�t���[���ʒu
									KeyRot.x												//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(1.0-m_Ratios);					//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// Rotatkon ��� 
		m_Rot.y = (m_Anime[m_Key].Key[l].Rot.y +											//�O�̃L�[�t���[���ʒu
									KeyRot.y												//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(1.0-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// Rotatkon ��� 
		m_Rot.z = (m_Anime[m_Key].Key[l].Rot.z +											//�O�̃L�[�t���[���ʒu
									KeyRot.z												//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(1.0-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������

		//2�Ԗ�
		// trans x ���
		m_Pos.x+= (m_Anime2[0].Key[l].Pos.x +											//�O�̃L�[�t���[���ʒu
							(m_Anime2[0+1].Key[l].Pos.x - m_Anime2[0].Key[l].Pos.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
								* (m_MotionTime - k))*(m_Ratios);								//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// trans y ���
		m_Pos.y+= (m_Anime2[0].Key[l].Pos.y +											//�O�̃L�[�t���[���ʒu
							(m_Anime2[0+1].Key[l].Pos.y - m_Anime2[0].Key[l].Pos.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// trans z ���
		m_Pos.z += (m_Anime2[0].Key[l].Pos.z +											//�O�̃L�[�t���[���ʒu
							(m_Anime2[0+1].Key[l].Pos.z - m_Anime2[0].Key[l].Pos.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// scale x ��� 
		m_Scl.x+= (m_Anime2[0].Key[l].Scl.x +											//�O�̃L�[�t���[���ʒu
							(m_Anime2[0+1].Key[l].Scl.x - m_Anime2[0].Key[l].Scl.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// scale y ���
		m_Scl.y+= (m_Anime2[0].Key[l].Scl.y +											//�O�̃L�[�t���[���ʒu
							(m_Anime2[0+1].Key[l].Scl.y - m_Anime2[0].Key[l].Scl.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// scale z ���
		m_Scl.z += (m_Anime2[0].Key[l].Scl.z +											//�O�̃L�[�t���[���ʒu
							(m_Anime2[0+1].Key[l].Scl.z - m_Anime2[0].Key[l].Scl.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
									
		// Rotatkon ���
		m_Rot.x+= (m_Anime2[0].Key[l].Rot.x +											//�O�̃L�[�t���[���ʒu
									KeyRot2.x													//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// Rotatkon ��� 
		m_Rot.y+= (m_Anime2[0].Key[l].Rot.y +											//�O�̃L�[�t���[���ʒu
									KeyRot2.y													//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
		// Rotatkon ��� 
		m_Rot.z += (m_Anime2[0].Key[l].Rot.z +											//�O�̃L�[�t���[���ʒu
									KeyRot2.z											//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������

		//��Ōv�Z�������l��ݒ肷��
		m_Part[l]->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
		//m_Part[l]->SetScl(m_Scl.x,m_Scl.y,m_Scl.z);
		m_Part[l]->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);

	}

	m_Ratios+=0.02f;
	if(m_Ratios>=1.0f)
	{
		m_Ratios=0.0f;
		m_BlendFlag=false;
		for(int i=0;i<KEY_MAX;i++)
		{
			m_Anime[i]=m_Anime2[i];
		}
	}
	//CDebugProc::Print("�䗦�F(%f)\n" , m_Ratios);

}























////=============================================================================
////
//// ���[�V�������� [MotionModel.cpp]
//// Author : ���V�r�a
////
////=============================================================================
//
////=============================================================================
//// �C���N���[�h
////=============================================================================
//#include <stdio.h>
//#include "main.h"
//#include "MotionModel.h"
//#include "Scene.h"
//#include "SceneX.h"
//#include "Manager.h"
//#include "Renderer.h"
//#include "Input.h"
//#include "SubModel.h"
//#include "Scene3D.h"
////=============================================================================
//// �}�N����`
////=============================================================================
//#define ROT_SPEED  (0.01f)	//��]���x
//
//CRenderer* CMotionModel::m_pMotion;
//
////=============================================================================
//// �O���[�o���ϐ�
////=============================================================================
//
////=============================================================================
//// �R���X�g���N�^
////=============================================================================
//CMotionModel::CMotionModel(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
//{
//	m_pDevice=NULL;
//	for(int i=0;i<PART_MAX;i++)
//	{
//		m_Part[i]=NULL;
//		m_Part2[i]=NULL;
//	}
//	for(int i=0;i<KEY_MAX;i++)
//	{
//		m_Anime[i].Frame=60;
//		m_Anime2[i].Frame=60;
//	}
//
//	m_pMotion=NULL;
//	m_MotionKey=0;
//	m_MotionTime=0.0f;
//	m_KeyMax=KEY_MAX;
//
//
//	m_AnimLoopFlag=false;
//	m_BlendFlag=false;
//	m_PunchFlag=false;
//	m_Ratios=0.0f;
//	m_Key=0;
//}
//
////=============================================================================
//// �f�X�g���N�^
////=============================================================================
//CMotionModel::~CMotionModel(void)
//{
//
//}
//
//
////=============================================================================
//// ����������
////=============================================================================
//HRESULT CMotionModel::Init(CRenderer* pRenderer)
//{
//	m_pDevice=CManager::GetRenderer()->GetDevice();
//
//	m_Part[0]=CSubModel::Create(500,66,-500,"data/MODEL/body.x",pRenderer);			//����
//	m_Part[1]=CSubModel::Create(500,70,-500,"data/MODEL/head.x",pRenderer);			//��
//
//	m_Part[2]=CSubModel::Create(505,70,-500,"data/MODEL/arm_l.x",pRenderer);		//���r
//	m_Part[3]=CSubModel::Create(497,70,-500,"data/MODEL/arm_r.x",pRenderer);		//�E�r
//
//	m_Part[4]=CSubModel::Create(511,70,-500,"data/MODEL/hand_l.x",pRenderer);		//����
//	m_Part[5]=CSubModel::Create(492,70,-500,"data/MODEL/hand_r.x",pRenderer);		//�E��
//
//	m_Part[6]=CSubModel::Create(503,66,-500,"data/MODEL/leg_l.x",pRenderer);		//����
//	m_Part[7]=CSubModel::Create(497,66,-500,"data/MODEL/leg_r.x",pRenderer);		//�E��
//
//	m_Part[8]=CSubModel::Create(503,62,-500,"data/MODEL/foot_l.x",pRenderer);		//������
//	m_Part[9]=CSubModel::Create(497,62,-500,"data/MODEL/foot_r.x",pRenderer);		//�E����
//	
//	WaitMotion2();
//
//	PartsInit();
//
//	return S_OK;
//}
//
////=============================================================================
//// �I������
////=============================================================================
//void CMotionModel::Uninit(void)
//{
//	Release();
//	for(int i=0;i<PART_MAX;i++)
//	{
//		//���g�̃��\�[�X�̉��
//		if(m_Part[i]!=NULL)
//		{
//			m_Part[i]->Uninit();
//			delete m_Part[i];
//			m_Part[i] = nullptr;
//		}
//	}
//}
//
////=============================================================================
//// �X�V����
////=============================================================================
//void CMotionModel::Update(void)
//{
//	bool flag=false;
//	//�f�o�b�O�����\��
//	DrawDebug();
//
//	//���삷��p�[�c�̑I��
//	/*if(GetKeyboardPress(DIK_0)){m_MotionKey=0;}		//����
//	if(GetKeyboardPress(DIK_1)){m_MotionKey=1;}		//��
//	if(GetKeyboardPress(DIK_2)){m_MotionKey=2;}		//���r
//	if(GetKeyboardPress(DIK_3)){m_MotionKey=3;}		//�E�r
//	if(GetKeyboardPress(DIK_4)){m_MotionKey=4;}		//����
//	if(GetKeyboardPress(DIK_5)){m_MotionKey=5;}		//�E��
//	if(GetKeyboardPress(DIK_6)){m_MotionKey=6;}		//����
//	if(GetKeyboardPress(DIK_7)){m_MotionKey=7;}		//�E��
//	if(GetKeyboardPress(DIK_8)){m_MotionKey=8;}		//������
//	if(GetKeyboardPress(DIK_9)){m_MotionKey=9;}		//�E����
//	*/
//
//	//�I�������p�[�c�̍��W�Ɗp�x�̎擾
//	D3DXVECTOR3 Pos=m_Part[m_MotionKey]->GetPos();
//	D3DXVECTOR3 Rot=m_Part[m_MotionKey]->GetRot();
//
//	//�ړ�
//	//�E
//	/*if(GetKeyboardPress(DIK_D))
//	{
//		Pos.x+=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//	//��
//	if(GetKeyboardPress(DIK_A))
//	{
//		Pos.x-=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//	//�O
//	if(GetKeyboardPress(DIK_W))
//	{
//		Pos.z+=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//
//	//���
//	if(GetKeyboardPress(DIK_S))
//	{
//		Pos.z-=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//	//��
//	if(GetKeyboardPress(DIK_O))
//	{
//		Pos.y+=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//
//	//��
//	if(GetKeyboardPress(DIK_L))
//	{
//		Pos.y-=MOVE_SPEED;
//		m_Part[m_MotionKey]->SetPos(Pos.x,Pos.y,Pos.z);
//	}
//	//��]
//	if(GetKeyboardPress(DIK_Z))
//	{
//		Rot.z+=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//	//��]2
//	if(GetKeyboardPress(DIK_X))
//	{
//		Rot.z-=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//
//	//��]2
//	if(GetKeyboardPress(DIK_C))
//	{
//		Rot.y-=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//		//��]2
//	if(GetKeyboardPress(DIK_V))
//	{
//		Rot.y+=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//	//��]2
//	if(GetKeyboardPress(DIK_B))
//	{
//		Rot.x+=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//	if(GetKeyboardPress(DIK_N))
//	{
//		Rot.x-=ROT_SPEED;
//		m_Part[m_MotionKey]->SetRot(Rot.x,Rot.y,Rot.z);
//	}*/
//
//	//���f���̉�]
//	if(GetKeyboardPress(DIK_Z))
//	{
//		Rot.y-=ROT_SPEED;
//		m_Part[0]->SetRot(Rot.x,Rot.y,Rot.z);
//	}
//
//	if(GetKeyboardTriger(DIK_F1)){m_MotionTime=0;}
//	if(m_BlendFlag==false)
//	{
//		if(GetKeyboardTriger(DIK_F2))
//		{
//			WaitMotion();
//			m_Key=(int)m_MotionTime;
//			m_MotionTime=0;
//
//		}
//		if(GetKeyboardTriger(DIK_F3)&&m_PunchFlag==false)
//		{
//			PunchMotion();
//			m_Key=(int)m_MotionTime;
//			m_MotionTime=0;
//		}
//		if(GetKeyboardTriger(DIK_F4))
//		{
//			RunningMotion();
//			m_Key=(int)m_MotionTime;
//			m_MotionTime=0;
//		}		//�����j���O
//		if(GetKeyboardTriger(DIK_F5))
//		{
//			DownMotion();
//			m_Key=(int)m_MotionTime;
//			m_MotionTime=0;
//		}			//����
//	}
//
//	int i = (int)m_MotionTime;  // i �ɑS�̃A�j�����Ԃ̐�����������
//	if( i > m_KeyMax - 2 ){i = m_KeyMax - 2;}
//	float dt = 1.0f / m_Anime[i].Frame;
//	if(m_BlendFlag==false)
//	{
//		for(int j = 0; j < PART_MAX; j++)
//		{
//			D3DXVECTOR3 KeyRot,KeyRot2;
//			KeyRot.x=(m_Anime[i+1].Key[j].Rot.x - m_Anime[i].Key[j].Rot.x);
//			KeyRot.y=(m_Anime[i+1].Key[j].Rot.y - m_Anime[i].Key[j].Rot.y);
//			KeyRot.z=(m_Anime[i+1].Key[j].Rot.z - m_Anime[i].Key[j].Rot.z);
//
//			//���K��
//			if(KeyRot.x > D3DX_PI)
//			{
//				KeyRot.x -= D3DX_PI*2; 
//			}
//			if(KeyRot.x < -D3DX_PI)
//			{
//				KeyRot.x += D3DX_PI*2; 
//			}
//			if(KeyRot.y > D3DX_PI)
//			{
//				KeyRot.y -= D3DX_PI*2; 
//			}
//			if(KeyRot.y < -D3DX_PI)
//			{
//				KeyRot.y += D3DX_PI*2; 
//			}
//			if(KeyRot.z > D3DX_PI)
//			{
//				KeyRot.z -= D3DX_PI*2; 
//			}
//			if(KeyRot.z < -D3DX_PI)
//			{
//				KeyRot.z += D3DX_PI*2; 
//			}
//
//
//			//���`���
//			// trans x ���
//			m_Pos.x= m_Anime[i].Key[j].Pos.x +											//�O�̃L�[�t���[���ʒu
//								(m_Anime[i+1].Key[j].Pos.x - m_Anime[i].Key[j].Pos.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - i);								//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//			// trans y ���
//			m_Pos.y = m_Anime[i].Key[j].Pos.y +											//�O�̃L�[�t���[���ʒu
//								(m_Anime[i+1].Key[j].Pos.y - m_Anime[i].Key[j].Pos.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//			// trans z ���
//			m_Pos.z = m_Anime[i].Key[j].Pos.z +											//�O�̃L�[�t���[���ʒu
//								(m_Anime[i+1].Key[j].Pos.z - m_Anime[i].Key[j].Pos.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//			// scale x ��� 
//			m_Scl.x = m_Anime[i].Key[j].Scl.x +											//�O�̃L�[�t���[���ʒu
//								(m_Anime[i+1].Key[j].Scl.x - m_Anime[i].Key[j].Scl.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//			// scale y ���
//			m_Scl.y = m_Anime[i].Key[j].Scl.y +											//�O�̃L�[�t���[���ʒu
//								(m_Anime[i+1].Key[j].Scl.y - m_Anime[i].Key[j].Scl.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//			// scale z ���
//			m_Scl.z = m_Anime[i].Key[j].Scl.z +											//�O�̃L�[�t���[���ʒu
//								(m_Anime[i+1].Key[j].Scl.z - m_Anime[i].Key[j].Scl.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//			// rotation ���
//			m_Rot.x = m_Anime[i].Key[j].Rot.x +											//�O�̃L�[�t���[���ʒu
//									KeyRot.x											//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//			// rotation ��� 
//			m_Rot.y = m_Anime[i].Key[j].Rot.y +											//�O�̃L�[�t���[���ʒu
//									KeyRot.y											//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//										* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊���������		// rotation ��� 
//			m_Rot.z = m_Anime[i].Key[j].Rot.z +											//�O�̃L�[�t���[���ʒu
//									KeyRot.z											//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - i);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//				//��Ōv�Z�������l��ݒ肷��
//			m_Part[j]->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
//			//m_Part[j]->SetScl(m_Scl.x,m_Scl.y,m_Scl.z);
//			m_Part[j]->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
//		}
//	}
//	else
//	{
//		Linear();
//	}
//
//	//��
//	if(GetKeyboardPress(DIK_W))
//	{
//		Pos.z+=MOVE_SPEED;
//		
//		if(GetKeyboardTriger(DIK_W))
//		{
//			RunningMotion();
//		}
//	}
//	//�E
//	if(GetKeyboardPress(DIK_D))
//	{
//		Pos.x+=MOVE_SPEED;
//		if(GetKeyboardTriger(DIK_D))
//		{
//			RunningMotion();
//		}
//	}
//	//��
//	if(GetKeyboardPress(DIK_S))
//	{
//		Pos.z-=MOVE_SPEED;
//		if(GetKeyboardTriger(DIK_S))
//		{
//			RunningMotion();
//		}
//	}
//	//��
//	if(GetKeyboardPress(DIK_A))
//	{
//		Pos.x-=MOVE_SPEED;
//		if(GetKeyboardTriger(DIK_A))
//		{
//			RunningMotion();
//		}
//	}
//
//	if(GetKeyboardPress(DIK_Z))
//	{
//		Rot.y-=MOVE_SPEED;
//
//	}
//	CDebugProc::Print("\n(%f,%f,%f)\n" , Pos.x, Pos.y, Pos.z);
//	
//	if(m_BlendFlag==false)
//	{
//		m_MotionTime += dt;
//	}
//	if( m_MotionTime > m_KeyMax - 1.0f )
//	{
//		m_MotionTime = m_KeyMax - 1.0f;
//		if(m_AnimLoopFlag==true)
//		{
//			m_MotionTime=0;
//		}
//		else
//		{
//			WaitMotion();
//		}
//	}
//	
//	for(int i=0;i<PART_MAX;i++)
//	{
//		m_Part[i]->Update();
//	}
//	//CDebugProc::Print("(%f)\n" , m_MotionTime);
//	//���W�̍X�V
//	m_Part[0]->SetPos(Pos.x,Pos.y,Pos.z);
//
//}
//
////=============================================================================
//// �`�揈��
////=============================================================================
//void CMotionModel::Draw(void)
//{
//	/*
//	// key & frame �\��
//	int Key = (int)m_MotionTime;  // i �ɑS�̃A�j�����Ԃ̐�����������
//
//	if( Key > m_KeyMax - 2 ){Key = m_KeyMax - 2;}
//
//	float dt = 1.0f / m_Anime[Key].Frame;
//	float rest = m_MotionTime - Key;
//	int Frame = rest / dt;
//	CDebugProc::Print("\nKey:%d  frame:%d\n" ,Key,Frame);
//	*/
//
//	for(int i=0;i<PART_MAX;i++)
//	{
//		m_Part[i]->Draw();
//	}
//}
////=============================================================================
//// �o�C���h�|�[�Y
////=============================================================================
//void CMotionModel::PartsInit(void)
//{
//	// �f�[�^������ ��
//	m_Part[1]->SetPos(0.0f,15.0f,0.0f);
//	m_Part[1]->SetParent(m_Part[0]);
//
//	// part ����
//	m_Part[0]->SetPos(500.0f,70.0f,-500.0f);
//	m_Part[0]->SetParent(NULL);
//
//	//part2���r
//	m_Part[2]->SetPos(7.5f,12.0f,0.0f); 
//	 // �d�v�@�e�o�^
//	m_Part[2]->SetParent(m_Part[0]);
//
//
//	// part 4�E�r
//	m_Part[3]->SetPos(-7.5f,12.0f,0.0f);
//	// �d�v�@�e�o�^
//	m_Part[3]->SetParent(m_Part[0]);
//
//
//	//����
//	m_Part[4]->SetPos(10.0f,0.0f,0.0f);
//	// �d�v�@�e�o�^
//	m_Part[4]->SetParent(m_Part[2]);
//
//	// �E��
//	m_Part[5]->SetPos(-10.0f,0.0f,0.0f);
//
//	// �d�v�@�e�o�^
//	m_Part[5]->SetParent(m_Part[3]);
//
//	//����
//	m_Part[6]->SetPos(4.0f,-1.0f,0.0f);
//
//	// �d�v�@�e�o�^
//	m_Part[6]->SetParent(m_Part[0]);
//
//	//�E��
//	m_Part[7]->SetPos(-4.0f,-1.0f,0.0f);
//
//	// �d�v�@�e�o�^
//	m_Part[7]->SetParent(m_Part[0]);
//
//	//������
//	m_Part[8]->SetPos(0.0f,-12.0f,0.0f);
//
//	// �d�v�@�e�o�^
//	m_Part[8]->SetParent(m_Part[6]);
//
//	//�E����
//	m_Part[9]->SetPos(0.0f,-12.0f,0.0f);
//
//	// �d�v�@�e�o�^
//	m_Part[9]->SetParent(m_Part[7]);
//}
////=============================================================================
//// �N���G�C�g
////=============================================================================
//CMotionModel *CMotionModel::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
//{
//	CMotionModel *pObje;
//	//�C���X�^���X�̍쐬
//	pObje = new CMotionModel(OBJTYPE_MOTIONMODEL);
//	//SceneX�̏�����
//	pObje->Init(m_pRenderer);
//	//���W�̐ݒ�
//	pObje->SetPos(fPosX,fPosY,fPosZ);
//	return pObje;
//}
////=============================================================================
////�f�o�b�O�����̕\��
////=============================================================================
//void CMotionModel::DrawDebug(void)
//{
//	/*CDebugProc::Print("\n0���� : (%f,%f,%f)\n", m_Part[0]->GetPos().x,m_Part[0]->GetPos().y,m_Part[0]->GetPos().z);
//	CDebugProc::Print("1�� : (%f,%f,%f)\n"   ,  m_Part[1]->GetPos().x,m_Part[1]->GetPos().y,m_Part[1]->GetPos().z);
//	CDebugProc::Print("2���r : (%f,%f,%f)\n" ,  m_Part[2]->GetPos().x,m_Part[2]->GetPos().y,m_Part[2]->GetPos().z);
//	CDebugProc::Print("3�E�r : (%f,%f,%f)\n" ,  m_Part[3]->GetPos().x,m_Part[3]->GetPos().y,m_Part[3]->GetPos().z);
//	CDebugProc::Print("4���� : (%f,%f,%f)\n" ,  m_Part[4]->GetPos().x,m_Part[4]->GetPos().y,m_Part[4]->GetPos().z);
//	CDebugProc::Print("5�E�� : (%f,%f,%f)\n" ,  m_Part[5]->GetPos().x,m_Part[5]->GetPos().y,m_Part[5]->GetPos().z);
//	CDebugProc::Print("6���� : (%f,%f,%f)\n" ,  m_Part[6]->GetPos().x,m_Part[6]->GetPos().y,m_Part[6]->GetPos().z);
//	CDebugProc::Print("7�E�� : (%f,%f,%f)\n" ,  m_Part[7]->GetPos().x,m_Part[7]->GetPos().y,m_Part[7]->GetPos().z);
//	CDebugProc::Print("8���� : (%f,%f,%f)\n" ,  m_Part[8]->GetPos().x,m_Part[8]->GetPos().y,m_Part[8]->GetPos().z);
//	CDebugProc::Print("9�E�� : (%f,%f,%f)\n" ,  m_Part[9]->GetPos().x,m_Part[9]->GetPos().y,m_Part[9]->GetPos().z);
//
//	CDebugProc::Print("\n0���� : (%f,%f,%f)\n", m_Part[0]->GetRot().x,m_Part[0]->GetRot().y,m_Part[0]->GetRot().z);
//	CDebugProc::Print("1�� : (%f,%f,%f)\n"   ,  m_Part[1]->GetRot().x,m_Part[1]->GetRot().y,m_Part[1]->GetRot().z);
//	CDebugProc::Print("2���r : (%f,%f,%f)\n" ,  m_Part[2]->GetRot().x,m_Part[2]->GetRot().y,m_Part[2]->GetRot().z);
//	CDebugProc::Print("3�E�r : (%f,%f,%f)\n" ,  m_Part[3]->GetRot().x,m_Part[3]->GetRot().y,m_Part[3]->GetRot().z);
//	CDebugProc::Print("4���� : (%f,%f,%f)\n" ,  m_Part[4]->GetRot().x,m_Part[4]->GetRot().y,m_Part[4]->GetRot().z);
//	CDebugProc::Print("5�E�� : (%f,%f,%f)\n" ,  m_Part[5]->GetRot().x,m_Part[5]->GetRot().y,m_Part[5]->GetRot().z);
//	CDebugProc::Print("6���� : (%f,%f,%f)\n" ,  m_Part[6]->GetRot().x,m_Part[6]->GetRot().y,m_Part[6]->GetRot().z);
//	CDebugProc::Print("7�E�� : (%f,%f,%f)\n" ,  m_Part[7]->GetRot().x,m_Part[7]->GetRot().y,m_Part[7]->GetRot().z);
//	CDebugProc::Print("8���� : (%f,%f,%f)\n" ,  m_Part[8]->GetRot().x,m_Part[8]->GetRot().y,m_Part[8]->GetRot().z);
//	CDebugProc::Print("9�E�� : (%f,%f,%f)\n" ,  m_Part[9]->GetRot().x,m_Part[9]->GetRot().y,m_Part[9]->GetRot().z);
//	*/
//
//	CDebugProc::Print("\n������@:WASD:���s�ړ�\nOL:�㏸���~\nZ����]:��XZ\nY����]:C��V\n" );
//	CDebugProc::Print("�J��������:��������\n�㏸���~�FI��K\nF1:�f�[�^�̏�������" );
//	CDebugProc::Print("\n�J��������FN,M" );
//	CDebugProc::Print("\nF2:�ҋ@\n\F3:�p���`\nF4�F����\nF5:����" );
//
//}
//
//
////=============================================================================
////�ҋ@���[�V�����̕\��
////=============================================================================
//void CMotionModel::WaitMotion2(void)
//{		
//	m_AnimLoopFlag=true;
//	//�ҋ@���[�V����
//	// part ����
//	m_Anime[0].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime[0].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
//	m_Anime[0].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
//	// part 4�E�r
//	m_Anime[0].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime[0].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
//	//����
//	m_Anime[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime[0].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime[0].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime[0].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	// part ����
//	m_Anime[1].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime[1].Key[0].Rot=D3DXVECTOR3(-0.05f,-0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime[1].Key[1].Rot=D3DXVECTOR3(-0.14f,0.0f,0.0f);
//	//part2���r
//	m_Anime[1].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,0.0f);
//	m_Anime[1].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.439f);
//	// part 4�E�r
//	m_Anime[1].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime[1].Key[3].Rot=D3DXVECTOR3(0.14f,-0.07f,1.39f);
//	//����
//	m_Anime[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime[1].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime[1].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	//�ҋ@���[�V����
//	// part ����
//	m_Anime[2].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime[2].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
//	m_Anime[2].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
//	// part 4�E�r
//	m_Anime[2].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime[2].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
//	//����
//	m_Anime[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime[2].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime[2].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//}
//
////=============================================================================
////�ҋ@���[�V�����̕\��
////=============================================================================
//void CMotionModel::WaitMotion(void)
//{		
//	m_AnimLoopFlag=true;
//	//�ҋ@���[�V����
//	// part ����
//	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
//	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
//	// part 4�E�r
//	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
//	//����
//	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	// part ����
//	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(-0.05f,-0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(-0.14f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,0.0f);
//	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.439f);
//	// part 4�E�r
//	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.14f,-0.07f,1.39f);
//	//����
//	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	//�ҋ@���[�V����
//	// part ����
//	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(502.0f,74.8f,-500.0f);
//	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(9.5f,15.0f,2.0f);
//	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.14f,-0.01f,-1.56f);
//	// part 4�E�r
//	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-9.5f,14.0f,2.0f);
//	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.25f,-0.07f,1.49f);
//	//����
//	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,0.0f,0.0f);
//	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,0.5f,0.0f);
//	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	m_BlendFlag=true;
//
//}
////=============================================================================
////�p���`���[�V�����̕\��
////=============================================================================
//void CMotionModel::PunchMotion(void)
//{
//	//m_PunchFlag=true;
//	m_AnimLoopFlag=false;
//	//�p���`���[�V����
//	// part ����
//	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
//	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,12.0f,0.0f);
//	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,-1.18f);
//	// part 4�E�r
//	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,1.16f);
//	//����
//	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
//	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
//	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
//	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//		// part ����
//	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
//	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(0.0f,-0.17f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.0f,-0.05f,-1.14f);
//	// part 4�E�r
//	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,-3.3f);
//	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.0f,-1.55f,-0.11f);
//	//����
//	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,1.53f,0.03f);
//	// �E��
//	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(-0.22f,0.0f,0.0f);
//	//�E��
//	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
//	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.74f,0.08f,0.0f);
//	//������
//	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.49f,0.0f);
//	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-9.8f,7.5f);
//	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.30f,0.30f);
//
//		//�p���`���[�V����
//	// part ����
//	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,74.8f,-500.0f);
//	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,12.0f,0.0f);
//	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.0f,0.0f,-1.18f);
//	// part 4�E�r
//	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.0f,0.0f,1.16f);
//	//����
//	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
//	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
//	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-12.0f,0.0f);
//	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	m_BlendFlag=true;
//	//m_PunchFlag=false;
//}
////=============================================================================
////�����j���O���[�V�����̕\��
////=============================================================================
//void CMotionModel::RunningMotion(void)
//{
//	m_AnimLoopFlag=true;
//	//�����j���O���[�V����
//	// part ����
//	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
//	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.96f,0.07f,-1.27f);
//	// part 4�E�r
//	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-8.1f,13.5f,-2.4f);
//	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(-3.75f,0.09f,-1.27f);
//	//����
//	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
//	// �E��
//	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
//	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,-0.02f);
//	//����
//	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(-0.36f,0.0f,0.0f);
//	//�E��
//	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,-0.6f);
//	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.87f,0.0f,0.0f);
//	//������
//	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
//	//�E����
//	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);
//
//	//�����j���O���[�V����
//	// part ����
//	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
//	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(9.6f,12.0f,-2.4f);
//	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(-0.74f,-0.28f,-1.29f);
//	// part 4�E�r
//	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-8.1f,12.5f,-0.3f);
//	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(-2.23f,0.2f,-1.27f);
//	//����
//	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
//	// �E��
//	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
//	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,0.02f);
//	//����
//	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.61f,0.0f,0.0f);
//	//�E��
//	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,0.0f);
//	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(-0.8f,0.0f,0.0f);
//	//������
//	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
//	//�E����
//	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);
//
//	
//	// part ����
//	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,70.0f,-500.0f);
//	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.96f,0.07f,-1.27f);
//	// part 4�E�r
//	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-8.1f,13.5f,-2.4f);
//	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(-3.75f,0.09f,-1.27f);
//	//����
//	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(-0.02f,1.2f,-0.01f);
//	// �E��
//	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,-0.3f);
//	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.07f,1.43f,-0.02f);
//	//����
//	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,-1.0f,0.0f);
//	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(-0.36f,0.0f,0.0f);
//	//�E��
//	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,-1.0f,-0.6f);
//	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.87f,0.0f,0.0f);
//	//������
//	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(1.48f,0.0f,0.0f);
//	//�E����
//	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-9.89f,0.0f);
//	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.8f,0.0f,0.0f);
//		m_BlendFlag=true;
//
//}
////=============================================================================
////���ꃂ�[�V�����̕\��
////=============================================================================
//void CMotionModel::DownMotion(void)
//{
//	m_AnimLoopFlag=false;
//	//���ꃂ�[�V����
//	// part ����
//	m_Anime2[0].Key[0].Pos=D3DXVECTOR3(500.0f,76.5f,-476.0f);
//	m_Anime2[0].Key[0].Rot=D3DXVECTOR3(0.929f,0.02f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[0].Key[1].Pos=D3DXVECTOR3(0.0f,15.0f,0.0f);
//	m_Anime2[0].Key[1].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//part2���r
//	m_Anime2[0].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
//	// part 4�E�r
//	m_Anime2[0].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[0].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,0.0f);
//	//����
//	m_Anime2[0].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime2[0].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[0].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[0].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
//	m_Anime2[0].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime2[0].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
//	m_Anime2[0].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime2[0].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[0].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[0].Key[9].Pos=D3DXVECTOR3(0.0f,-9.0f,0.0f);
//	m_Anime2[0].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	// part ����
//	m_Anime2[1].Key[0].Pos=D3DXVECTOR3(500.0f,59.0f,-476.0f);
//	m_Anime2[1].Key[0].Rot=D3DXVECTOR3(1.5f,0.002f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[1].Key[1].Pos=D3DXVECTOR3(0.0f,23.5f,2.5f);
//	m_Anime2[1].Key[1].Rot=D3DXVECTOR3(-0.12f,1.07f,-0.03f);
//	//part2���r
//	m_Anime2[1].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[1].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
//	// part 4�E�r
//	m_Anime2[1].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[1].Key[3].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
//	//����
//	m_Anime2[1].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime2[1].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[1].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[1].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
//	m_Anime2[1].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime2[1].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
//	m_Anime2[1].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime2[1].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[1].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[1].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[1].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//
//	
//	// part ����
//	m_Anime2[2].Key[0].Pos=D3DXVECTOR3(500.0f,59.5f,-476.0f);
//	m_Anime2[2].Key[0].Rot=D3DXVECTOR3(1.5f,-0.02f,0.0f);
//	// �f�[�^������ ��
//	m_Anime2[2].Key[1].Pos=D3DXVECTOR3(-30.0f,23.5f,2.5f);
//	m_Anime2[2].Key[1].Rot=D3DXVECTOR3(-0.12f,2.08f,0.0f);
//	//part2���r
//	m_Anime2[2].Key[2].Pos=D3DXVECTOR3(7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[2].Rot=D3DXVECTOR3(0.14f,0.0f,0.0f);
//	// part 4�E�r
//	m_Anime2[2].Key[3].Pos=D3DXVECTOR3(-7.5f,12.0f,0.0f);
//	m_Anime2[2].Key[3].Rot=D3DXVECTOR3(0.25f,0.0f,0.0f);
//	//����
//	m_Anime2[2].Key[4].Pos=D3DXVECTOR3(10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[4].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	// �E��
//	m_Anime2[2].Key[5].Pos=D3DXVECTOR3(-10.0f,0.0f,0.0f);
//	m_Anime2[2].Key[5].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//����
//	m_Anime2[2].Key[6].Pos=D3DXVECTOR3(4.0f,1.5f,0.0f);
//	m_Anime2[2].Key[6].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E��
//	m_Anime2[2].Key[7].Pos=D3DXVECTOR3(-4.0f,1.5f,0.0f);
//	m_Anime2[2].Key[7].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//������
//	m_Anime2[2].Key[8].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[2].Key[8].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	//�E����
//	m_Anime2[2].Key[9].Pos=D3DXVECTOR3(0.0f,-10.0f,0.0f);
//	m_Anime2[2].Key[9].Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
//	m_BlendFlag=true;
//
//}
////=============================================================================
//// �A�j�������o��
////=============================================================================
//void CMotionModel::WriteAnime(void)
//{
//	int i = (int)m_MotionTime;  // i �ɑS�̃A�j�����Ԃ̐�����������
//	if( i > m_KeyMax - 2 ){i = m_KeyMax - 2;}
//	float dt = 1.0f / m_Anime[i].Frame;
//
//	FILE *fp;
//	fp = fopen("data.txt","a+");
//	if( fp==NULL )
//	return;
//
//	fprintf(fp,"// key data\n");
//	fprintf(fp,"\t{ 60,\t// frame count\n");
//
//	fprintf(fp,"\t\t{\n");
//
//	for (int j = 0; j < PART_MAX; j++)
//	{
//		fprintf(fp,"\t\t\t// part %d\n",i);
//		fprintf(fp,"\t\t\t{ D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// trans\n",m_Anime[i].Key[j].Pos.x,m_Anime[i].Key[j].Pos.y,m_Anime[i].Key[j].Pos.z);
//		fprintf(fp,"\t\t\t  D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// scale\n",m_Anime[i].Key[j].Scl.x,m_Anime[i].Key[j].Scl.y,m_Anime[i].Key[j].Scl.z);
//		fprintf(fp,"\t\t\t  D3DXECTOR3(%.4ff,%.4ff,%.4ff),\t// rotation\n",m_Anime[i].Key[j].Rot.x,m_Anime[i].Key[j].Rot.y,m_Anime[i].Key[j].Rot.z);
//		fprintf(fp,"\t\t\t},\n");
//	}
//	fprintf(fp,"\t\t}\n");
//	fprintf(fp,"\t},\t// end of key\n");
//
//	fclose(fp);
//}
//
//
//
//void CMotionModel::Linear(void)
//{
//	int k = (int)m_MotionTime;  // k �ɑS�̃A�j�����Ԃ̐�����������
//	if( k > m_KeyMax - 2 ){k = m_KeyMax - 2;}
//	for(int l = 0; l < PART_MAX; l++)
//	{
//		D3DXVECTOR3 KeyRot,KeyRot2;
//		KeyRot.x=(m_Anime[m_Key+1].Key[l].Rot.x - m_Anime[m_Key].Key[l].Rot.x);
//		KeyRot.y=(m_Anime[m_Key+1].Key[l].Rot.y - m_Anime[m_Key].Key[l].Rot.y);
//		KeyRot.z=(m_Anime[m_Key+1].Key[l].Rot.z - m_Anime[m_Key].Key[l].Rot.z);
//		KeyRot2.x=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
//		KeyRot2.y=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
//		KeyRot2.z=(m_Anime2[0+1].Key[l].Rot.z - m_Anime2[0].Key[l].Rot.z);
//
//		if(KeyRot.x > D3DX_PI)
//		{
//			KeyRot.x -= D3DX_PI*2; 
//		}
//		if(KeyRot.x < -D3DX_PI)
//		{
//			KeyRot.x += D3DX_PI*2; 
//		}
//
//		if(KeyRot.y > D3DX_PI)
//		{
//			KeyRot.y -= D3DX_PI*2; 
//		}
//		if(KeyRot.y < -D3DX_PI)
//		{
//			KeyRot.y += D3DX_PI*2; 
//		}
//
//		if(KeyRot.z > D3DX_PI)
//		{
//			KeyRot.z -= D3DX_PI*2; 
//		}
//		if(KeyRot.z < -D3DX_PI)
//		{
//			KeyRot.z += D3DX_PI*2; 
//		}
//		//2����
//		if(KeyRot2.x > D3DX_PI)
//		{
//			KeyRot2.x -= D3DX_PI*2; 
//		}
//		if(KeyRot2.x < -D3DX_PI)
//		{
//			KeyRot2.x += D3DX_PI*2; 
//		}
//
//		if(KeyRot2.y > D3DX_PI)
//		{
//			KeyRot2.y -= D3DX_PI*2; 
//		}
//		if(KeyRot2.y < -D3DX_PI)
//		{
//			KeyRot2.y += D3DX_PI*2; 
//		}
//
//		if(KeyRot2.z > D3DX_PI)
//		{
//			KeyRot2.z -= D3DX_PI*2; 
//		}
//		if(KeyRot2.z < -D3DX_PI)
//		{
//			KeyRot2.z += D3DX_PI*2; 
//		}
//
//
//		//���`���
//		m_Pos.x= (m_Anime[m_Key].Key[l].Pos.x +												//�O�̃L�[�t���[���ʒu
//							(m_Anime[m_Key+1].Key[l].Pos.x - m_Anime[m_Key].Key[l].Pos.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//								* (m_MotionTime - k))*(1.0f-m_Ratios);								//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// trans y ���
//		m_Pos.y = (m_Anime[m_Key].Key[l].Pos.y +											//�O�̃L�[�t���[���ʒu
//							(m_Anime[m_Key+1].Key[l].Pos.y - m_Anime[m_Key].Key[l].Pos.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// trans z ���
//		m_Pos.z = (m_Anime[m_Key].Key[l].Pos.z +											//�O�̃L�[�t���[���ʒu
//							(m_Anime[m_Key+1].Key[l].Pos.z - m_Anime[m_Key].Key[l].Pos.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// scale x ��� 
//		m_Scl.x = (m_Anime[m_Key].Key[l].Scl.x +											//�O�̃L�[�t���[���ʒu
//							(m_Anime[m_Key+1].Key[l].Scl.x - m_Anime[m_Key].Key[l].Scl.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// scale y ���
//		m_Scl.y = (m_Anime[m_Key].Key[l].Scl.y +											//�O�̃L�[�t���[���ʒu
//							(m_Anime[m_Key+1].Key[l].Scl.y - m_Anime[m_Key].Key[l].Scl.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// scale z ���
//		m_Scl.z = (m_Anime[m_Key].Key[l].Scl.z +											//�O�̃L�[�t���[���ʒu
//							(m_Anime[m_Key+1].Key[l].Scl.z - m_Anime[m_Key].Key[l].Scl.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//									
//		// Rotatkon ���
//		m_Rot.x = (m_Anime[m_Key].Key[l].Rot.x +											//�O�̃L�[�t���[���ʒu
//									KeyRot.x												//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(1.0f-m_Ratios);					//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// Rotatkon ��� 
//		m_Rot.y = (m_Anime[m_Key].Key[l].Rot.y +											//�O�̃L�[�t���[���ʒu
//									KeyRot.y												//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// Rotatkon ��� 
//		m_Rot.z = (m_Anime[m_Key].Key[l].Rot.z +											//�O�̃L�[�t���[���ʒu
//									KeyRot.z												//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(1.0f-m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//
//		//2�Ԗ�
//		// trans x ���
//		m_Pos.x+= (m_Anime2[0].Key[l].Pos.x +											//�O�̃L�[�t���[���ʒu
//							(m_Anime2[0+1].Key[l].Pos.x - m_Anime2[0].Key[l].Pos.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//								* (m_MotionTime - k))*(m_Ratios);								//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// trans y ���
//		m_Pos.y+= (m_Anime2[0].Key[l].Pos.y +											//�O�̃L�[�t���[���ʒu
//							(m_Anime2[0+1].Key[l].Pos.y - m_Anime2[0].Key[l].Pos.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// trans z ���
//		m_Pos.z += (m_Anime2[0].Key[l].Pos.z +											//�O�̃L�[�t���[���ʒu
//							(m_Anime2[0+1].Key[l].Pos.z - m_Anime2[0].Key[l].Pos.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// scale x ��� 
//		m_Scl.x+= (m_Anime2[0].Key[l].Scl.x +											//�O�̃L�[�t���[���ʒu
//							(m_Anime2[0+1].Key[l].Scl.x - m_Anime2[0].Key[l].Scl.x)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// scale y ���
//		m_Scl.y+= (m_Anime2[0].Key[l].Scl.y +											//�O�̃L�[�t���[���ʒu
//							(m_Anime2[0+1].Key[l].Scl.y - m_Anime2[0].Key[l].Scl.y)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// scale z ���
//		m_Scl.z += (m_Anime2[0].Key[l].Scl.z +											//�O�̃L�[�t���[���ʒu
//							(m_Anime2[0+1].Key[l].Scl.z - m_Anime2[0].Key[l].Scl.z)	//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//									
//		// Rotatkon ���
//		m_Rot.x+= (m_Anime2[0].Key[l].Rot.x +											//�O�̃L�[�t���[���ʒu
//									KeyRot2.x													//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// Rotatkon ��� 
//		m_Rot.y+= (m_Anime2[0].Key[l].Rot.y +											//�O�̃L�[�t���[���ʒu
//									KeyRot2.y													//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//		// Rotatkon ��� 
//		m_Rot.z += (m_Anime2[0].Key[l].Rot.z +											//�O�̃L�[�t���[���ʒu
//									KeyRot2.z											//�O�̃L�[�t���[���Ǝ��̃L�[�t���[���̍���
//									* (m_MotionTime - k))*(m_Ratios);							//�ɑS�̃A�j�����Ԃ̏����_�ȉ��̊�����������
//
//		//��Ōv�Z�������l��ݒ肷��
//		m_Part[l]->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
//		//m_Part[l]->SetScl(m_Scl.x,m_Scl.y,m_Scl.z);
//		m_Part[l]->SetRot(m_Rot.x,m_Rot.y,m_Rot.z);
//
//	}
//
//	m_Ratios+=0.02f;
//	if(m_Ratios>=1.0f)
//	{
//		m_Ratios=0.0f;
//		m_BlendFlag=false;
//		for(int i=0;i<KEY_MAX;i++)
//		{
//			m_Anime[i]=m_Anime2[i];
//		}
//	}
//	//CDebugProc::Print("�䗦�F(%f)\n" , m_Ratios);
//
//}
