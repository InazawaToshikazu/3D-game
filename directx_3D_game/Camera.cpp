//=============================================================================
//
// �J�������� [Camera.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "main.h"
#include "Renderer.h"
#include "Camera.h"
#include "Input.h"
#include "Player.h"
#include "Manager.h"
#include "Game.h"
#include "Scene2D.h"
//=============================================================================
// �O���[�o���ϐ�u
//=============================================================================

//=============================================================================
// �}�N����`
//=============================================================================
D3DXMATRIX CCamera::m_mtxView;
D3DXVECTOR3 CCamera::m_rotCamera;		//�J�����̌����i��]�����j
CCamera* CCamera::m_pCamera;
bool CCamera::m_PauseFlag=false;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_posCameraP =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posCameraR =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_vecCameraV =D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_rotCamera  =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posCameraPDest =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posCameraRDest =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_zoom = D3DXVECTOR3(0.0f,10.0f,20.0f);
	m_pFont=NULL;
	//��ʕ����p
	m_viewport.X =0;
	m_viewport.Y =0;
	m_viewport.Width =SCREEN_WIDTH;
	m_viewport.Height =SCREEN_HEIGHT;
	m_viewport.MinZ =0.0f;
	m_viewport.MaxZ =1.0f;
	m_pCamera=NULL;
	m_Mode=MODE_THIRDPERSON;
	m_FirstPersonFlag=false;
	m_PauseFlag=false;
	m_pScene2D=NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// �J�����̏���������
//=============================================================================
HRESULT CCamera::InitCamera(CRenderer* pRenderer)
{

	m_pDevice = pRenderer->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	m_posCameraP = D3DXVECTOR3(500.0f,200.0f,-650.0f);
	m_posCameraR = D3DXVECTOR3(500.0f,100.0f,-500.0f);
	m_vecCameraV = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_rotCamera  = D3DXVECTOR3(-D3DX_PI/2,0.0f,0.0f);
	m_rotCameraDest  = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posCameraPDest = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posCameraRDest = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_zoom = D3DXVECTOR3(0.0f,10.0f,20.0f);
	m_fAngle = -D3DX_PI/2;
	m_angle = 0.0f;
	m_angleDest = 0.0f;
	fDiffRotY = 0.0f;
	//��ʕ����p
	m_viewport.X = 0;
	m_viewport.Y = 0;
	m_viewport.Width = SCREEN_WIDTH;
	m_viewport.Height = SCREEN_HEIGHT;
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ =1.0f;
	
	return S_OK;
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::UpdateCamera(void)
{
	CRenderer* pRenderer=CManager::GetRenderer();
	
	////���f���̈ʒu����Z�����Ɉ�苗��
	//m_posCameraPDest.x =CManager::GetPlayer()->GetPos().x - cosf(m_rotCamera.y) *200.0f;
	//m_posCameraPDest.y =CManager::GetPlayer()->GetPos().y + 130;
	//m_posCameraPDest.z =CManager::GetPlayer()->GetPos().z - sinf(m_rotCamera.y) * 200.0f;
	//

	////���f���̑O���̈ʒu
	//m_posCameraRDest.x =CManager::GetPlayer()->GetPos().x/*-sinf(CManager::GetPlayer()->GetRot().y)*/;
	//m_posCameraRDest.y =CManager::GetPlayer()->GetPos().y;
	//m_posCameraRDest.z =CManager::GetPlayer()->GetPos().z/*-cosf(CManager::GetPlayer()->GetPos().y)*/;

	//if(CPlayer::GetPlayer()->GetRotFlag()==false)
	//{
	//	m_rotCamera = CManager::GetPlayer()->GetRot();
	//	 
	//	m_posCameraP.x += (m_posCameraPDest.x - m_posCameraP.x)*0.04f;
	//	m_posCameraP.y += (m_posCameraPDest.y - m_posCameraP.y)*0.04f;
	//	m_posCameraP.z += (m_posCameraPDest.z - m_posCameraP.z)*0.04f;
	//}
	//else
	//{
	//	m_posCameraP.x = CManager::GetPlayer()->GetPos().x- cosf(m_rotCamera.y) *200.0f;
	//	m_posCameraP.y = CManager::GetPlayer()->GetPos().y+130.0f;
	//	m_posCameraP.z = CManager::GetPlayer()->GetPos().z- sinf(m_rotCamera.y) * 200.0f;
	//}

	//m_posCameraR.x += ( m_posCameraRDest.x - m_posCameraR.x ) * 1.0f;
	//m_posCameraR.y += ( m_posCameraRDest.y - m_posCameraR.y ) * 1.0f;
	//m_posCameraR.z += ( m_posCameraRDest.z - m_posCameraR.z ) * 1.0f;

	////�p�x����	
	//if(m_rotCamera.y > D3DX_PI)
	//{
	//	m_rotCamera.y -= D3DX_PI*2; 
	//}
	//if(m_rotCamera.y < -D3DX_PI)
	//{
	//	m_rotCamera.y += D3DX_PI*2; 
	//}
	//
	//if(m_fAngle > D3DX_PI*2)
	//{
	//	m_fAngle -= D3DX_PI*2; 
	//}
	//if(m_fAngle < 0)
	//{
	//	m_fAngle += D3DX_PI*2;
	//}

	switch(m_Mode)
	{
		case MODE_FIRSTPERSON:

			FirstPersonCamera();
			break;

		case MODE_THIRDPERSON:
			ThirdPersonCamera();
			break;
	}

	if(CManager::GetPhase()==MODE_GAME)
	{
		if(GetKeyboardTriger(DIK_Y) && m_Mode == MODE_THIRDPERSON)
		{
			m_Mode=MODE_FIRSTPERSON;
			//���_�����
			m_posCameraP=CGame::GetPlayer()->GetPos()+CGame::GetPlayer()->GetFrontVectol();

			CPlayer* pPlayer=CGame::GetPlayer();
			m_rotCamera.y=-pPlayer->GetRot().y-D3DX_PI/2;

			m_posCameraR.x = m_posCameraP.x+cosf(m_rotCamera.y)*0.1f;
			//m_posCameraR.y = m_posCameraP.y+cosf(m_rotCamera.x)*0.1f;
			m_posCameraR.y = pPlayer->GetPos().y;
			m_posCameraR.z = m_posCameraP.z+sinf(m_rotCamera.y)*0.1f;

			m_pScene2D=CScene2D::Create(400,280,200,200,"data/TEXTURE/aim.png",pRenderer);

			//�����_�����
			//m_posCameraR.x = CGame::GetPlayer()->GetPos().x+CGame::GetPlayer()->GetFrontVectol().x*50.0f;
			//m_posCameraR.y = CGame::GetPlayer()->GetPos().y+CGame::GetPlayer()->GetFrontVectol().y;
			//m_posCameraR.z = CGame::GetPlayer()->GetPos().z+CGame::GetPlayer()->GetFrontVectol().z*50.0f;


			//m_FirstPersonFlag=true;
		}
		else if(GetKeyboardTriger(DIK_Y) && m_Mode == MODE_FIRSTPERSON)
		{
			m_Mode=MODE_THIRDPERSON;
			CGame::GetPlayer()->Neutral();
			m_pScene2D->Uninit();
			//m_FirstPersonFlag=true;
		}
	}
	/*if(CManager::GetPhase()==MODE_GAME && m_FirstPersonFlag==true)
	{
		if(GetKeyboardTriger(DIK_Y))
		{
			ThirdPersonCamera();
			m_FirstPersonFlag=false;
		}
	}*/


}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	//pDevice = m_pRenderer->GetDevice();	
	
	D3DXMatrixIdentity(&m_mtxView);								//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixLookAtLH(&m_mtxView,&m_posCameraP,&m_posCameraR,&m_vecCameraV);
	m_pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);				//�r���[�}�g���b�N�X�̐ݒ�

	m_pDevice->SetViewport(&m_viewport);							//��ʕ���

	D3DXMatrixIdentity(&m_mtxProjection);						//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,D3DX_PI/4,SCREEN_WIDTH/(float)SCREEN_HEIGHT,10.0f,10000.0f);
	m_pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
}


/*
//=============================================================================
// �J�����̌������擾
//=============================================================================
D3DXVECTOR3 CRenderer::GetRotCamera(void)
{
	D3DXVECTOR3 RotCamera = D3DXVECTOR3(m_rotCamera.x, m_rotCamera.y, m_rotCamera.z);

	return RotCamera;
}*/

//=============================================================================
// �f�o�b�O���\��
//=============================================================================
void CCamera::DrawRot(void)
{
	int X, Y, Z, Len, Rad, Ang;
	int cX, cY, cZ;
	double a;
	X = (int)m_posCameraR.x;
	Y = (int)m_posCameraR.y;
	Z = (int)m_posCameraR.z;
	cX = (int)m_posCameraP.x;
	cY = (int)m_posCameraP.y;
	cZ = (int)m_posCameraP.z;
	a = (X-cX)*(X-cX)+(Y-cY)*(Y-cY)+(Z-cZ)*(Z-cZ);
	Len = (int)sqrt(a);
	Rad = (int)(m_rotCamera.y*180/D3DX_PI);
	//Ang = (int)(m_fangCamera*180/D3DX_PI);

	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	RECT rect1 = {0, 120, SCREEN_WIDTH, SCREEN_HEIGHT};
	RECT rect2 = {0, 300, SCREEN_WIDTH, SCREEN_HEIGHT};
	RECT rect3 = {0, 420, SCREEN_WIDTH, SCREEN_HEIGHT};
	RECT rect4 = {0, 80, SCREEN_WIDTH, SCREEN_HEIGHT};
	char stra[256];
	char strb[256];
	char strc[256];
	char strd[256];
	char stre[256];

	wsprintf(stra, "�J����x:%3d �J����y:%3d �J����z:%3d\n�����_x:%3d �����_y:%3d �����_z:%3d\n\n�����F%d Rot�F%d Ang�F%d", cX, cY, cZ, X, Y, Z, Len, Rad, Ang);
	wsprintf(strb, "---- ���_���� ----\n�O�ړ��FW\n��ړ��FS\n���ړ��FA\n�E�ړ��FD\n��ړ��FY\n���ړ��FN\n������FZ\n�E����FC\n");
	wsprintf(strc, "---- �����_���� ----\n��ړ��FT\n���ړ��FB\n������FQ\n�E����FE\n");
	wsprintf(strd, "---- �ԑ��� ----\n�O�ړ��F��\n��ړ��F��\n���ړ��F��\n�E�ړ��F��\n������FLSHIFT\n�E����FRSHIFT\n\n�������FP\n");
	
	//if(m_AutoFlag){ wsprintf(stre, "�J�������[�h�ؑցFM  ���݃��[�h�FAuto \n�J������w���(�Î~���j�FK");}
	//else			{ wsprintf(stre, "�J�������[�h�ؑցFM  ���݃��[�h�FManual");}
	
	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, stra, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x99));
	m_pFont->DrawText(NULL, strb, -1, &rect1, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x99));
	m_pFont->DrawText(NULL, strc, -1, &rect2, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x99));
	m_pFont->DrawText(NULL, strd, -1, &rect3, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x99));
	m_pFont->DrawText(NULL, stre, -1, &rect4, DT_LEFT, D3DCOLOR_ARGB(0xff, 0x00, 0xff, 0x99));
}

void CCamera::FirstPersonCamera(void)
{
	
	m_VecCamera = m_posCameraR - m_posCameraP;		//�J�����̌����̃x�N�g��
	CPlayer* pPlayer=CGame::GetPlayer();

	if(GetKeyboardPress(DIK_W) && m_rotCamera.x<D3DX_PI/2)
	{
		//m_rotCamera.x+=0.05f;
		m_rotCamera.x+=0.02f;

	}
	if(GetKeyboardPress(DIK_A))
	{
		m_rotCamera.y += 0.02f;
		// �����_�ύX�i�J�����̈ʒu�𒆐S��)
		//m_posCameraR.x = m_posCameraP.x-cosf(m_rotCamera.y+0.1f)*0.1f;
		//m_posCameraR.z = m_posCameraP.z-sinf(m_rotCamera.y+0.1f)*0.1f;
		//m_posCameraR.x-=sinf(m_rotCamera.y)*1.f;
		//m_posCameraR.z-=cosf(m_rotCamera.y)*1.f;
		//m_posCameraR.x+=0.7f;
		//m_posCameraR.z+=0.7f;
	}
	if(GetKeyboardPress(DIK_S) && m_rotCamera.x>-D3DX_PI/2)
	{
		m_rotCamera.x-=0.01f;
		//m_rotCamera.x-=0.05f;
	}
	if(GetKeyboardPress(DIK_D))
	{
		m_rotCamera.y -= 0.01f;
		//m_posCameraR.x = m_posCameraP.x+cosf(m_rotCamera.y+0.1f)*0.1f;
		//m_posCameraR.z = m_posCameraP.z+sinf(m_rotCamera.y+0.1f)*0.1f;
		//m_posCameraR.x+=sinf(m_rotCamera.y)*1.f;
		//m_posCameraR.z+=cosf(m_rotCamera.y)*1.f;
		//m_posCameraR.x-=0.7f;
		//m_posCameraR.z-=0.7f;

	}

	//�p�x����	
	if(m_rotCamera.y > D3DX_PI)
	{
		m_rotCamera.y -= D3DX_PI*2; 
	}
	if(m_rotCamera.y < -D3DX_PI)
	{
		m_rotCamera.y += D3DX_PI*2; 
	}
	//�p�x����	
	if(m_rotCamera.x > D3DX_PI)
	{
		m_rotCamera.x -= D3DX_PI*2; 
	}
	if(m_rotCamera.x < -D3DX_PI)
	{
		m_rotCamera.x += D3DX_PI*2; 
	}


	//CDebugProc::Print("\nCAMERA�̍��W: (%f)\n" ,  m_rotCamera.x);

	//CDebugProc::Print("\nCAMERA�̍��W: (%f,%f,%f)\n" ,  m_posCameraP.x,m_posCameraP.y,m_posCameraP.z);

	m_posCameraP=pPlayer->GetPos();

	m_posCameraR.x = m_posCameraP.x+cosf(m_rotCamera.y)*50;
	m_posCameraR.y = m_posCameraP.y+sinf(m_rotCamera.x)*50;
	m_posCameraR.z = m_posCameraP.z+sinf(m_rotCamera.y)*50;

	CDebugProc::Print("\nposCameraR.y�̍��W: (%f)\n" ,  m_rotCamera.x);

}

void CCamera::ThirdPersonCamera(void)
{
	if(CGame::GetPlayer()!=NULL)
	{
		m_rotCamera = CGame::GetPlayer()->GetRot();
		//�p�x���� 
		if(m_rotCamera.y > D3DX_PI)
		{
			m_rotCamera.y -= D3DX_PI*2; 
		}
		if(m_rotCamera.y < -D3DX_PI)
		{
			m_rotCamera.y += D3DX_PI*2; 
		}
		


		////���f���̈ʒu����Z�����Ɉ�苗��
		m_posCameraPDest.x =CGame::GetPlayer()->GetPos().x + sinf(m_rotCamera.y) *200.0f;
		m_posCameraPDest.y =CGame::GetPlayer()->GetPos().y + 130;
		m_posCameraPDest.z =CGame::GetPlayer()->GetPos().z + cosf(m_rotCamera.y) * 200.0f;

		m_posCameraP.x += (m_posCameraPDest.x - m_posCameraP.x)*0.4f;
		m_posCameraP.y += (m_posCameraPDest.y - m_posCameraP.y)*0.4f;
		m_posCameraP.z += (m_posCameraPDest.z - m_posCameraP.z)*0.4f;

		m_posCameraR.x = CGame::GetPlayer()->GetPos().x;
		m_posCameraR.y = CGame::GetPlayer()->GetPos().y;
		m_posCameraR.z = CGame::GetPlayer()->GetPos().z;


		if(m_fAngle > D3DX_PI*2)
		{
			m_fAngle -= D3DX_PI*2; 
		}
		if(m_fAngle < 0)
		{
			m_fAngle += D3DX_PI*2;
		}

	}
}