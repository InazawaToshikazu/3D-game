//=============================================================================
//
// �X�e���V�����g�����e�̕\������ [Shadow.cpp]
// Author : ���V�r�a
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Shadow.h"
#include "Renderer.h"
#include "SceneX.h"
#include "Input.h"
#include "Bullet.h"
#include "Manager.h"
#include "CMeshField.h"
#include "Player.h"
#include "Game.h"
#include "MotionModel.h"
#include "Magma.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define FIELD_WIDTH		(100.0f)		// �n�ʂ̕�
#define FIELD_HIGHT		(100.0f)		// �n�ʂ̏c
#define MODEL_ROT_SPEED				(0.01f)		//���f���̉�]���x
#define MODEL_SPEED_X				(1.7f)		//���f���̈ړ����x
#define MODEL_SPEED_Z				(1.7f)		//���f���̈ړ����x
#define MODEL_SPEED_Y				(0.1f)		//���f���̈ړ����x
#define MODEL_SPEED					(0.5f)		//���f���̈ړ����x

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CRenderer* CShadow::m_pShadow=NULL;
CPlayer* CShadow::m_pPlayer=NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CShadow::CShadow(OBJTYPE nObjType,int nPriority):CSceneX(nObjType,nPriority)
{
	m_rotDestModel = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl =D3DXVECTOR3(0.0f,0.0f,0.0f);
	pDevice =NULL;
	m_nNumMat =NULL;
	m_D3DXBuffMat =NULL;
	m_pD3DXMesh =NULL;
	m_pD3DBuff=NULL;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CShadow::~CShadow(void)
{
	
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CShadow* CShadow::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CShadow *pShadow;
	//�C���X�^���X�̍쐬
	pShadow = new CShadow(OBJTYPE_SHADOW);
	pShadow->SetFileName("data/MODEL/shadow000.x");
	//CEnemy��Init���Ăяo��
	pShadow->Init(m_pRenderer);
	//���W�̐ݒ�
	pShadow->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pShadow->SetPos(fPosX,fPosY,fPosZ);
	m_pShadow=m_pRenderer;
	return pShadow;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShadow::Init(CRenderer *pRenderer)
{
	pDevice=pRenderer->GetDevice();
	//�e���f���̎w��
	FileName="data/MODEL/shadow000.x";
	m_Scl=D3DXVECTOR3(0.5f,1.0f,0.5f);
	//�w�t�@�C����ǂݍ���
	if(FAILED(D3DXLoadMeshFromX("data/MODEL/shadow000.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&m_D3DXBuffMat,NULL,&m_nNumMat,&m_pD3DXMesh)))
	{
		MessageBox(NULL, "�e��X�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B", "�x��", MB_OK);
		return E_FAIL;
	}

	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_pD3DBuff,NULL)))
	{
		return E_FAIL;
	}

	//��ʂ����ς��̍��|���S�����o���ݒ�
	VERTEX_2D *g_aVtx;
	m_pD3DBuff -> Lock(0,0,(void**)&g_aVtx,0);
	//���_�̐ݒ�
	g_aVtx[0].vtx = D3DXVECTOR3(0,0,0.0f);
	g_aVtx[1].vtx = D3DXVECTOR3(SCREEN_WIDTH,0,0.0f);
	g_aVtx[2].vtx = D3DXVECTOR3(0,SCREEN_HEIGHT,0.0f);
	g_aVtx[3].vtx = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);

	g_aVtx[0].rhw=1.0f;
	g_aVtx[1].rhw=1.0f;
	g_aVtx[2].rhw=1.0f;
	g_aVtx[3].rhw=1.0f;

	//�F
	g_aVtx[0].diffuse = D3DCOLOR_RGBA(0,0,0,180);
	g_aVtx[1].diffuse = D3DCOLOR_RGBA(0,0,0,180);
	g_aVtx[2].diffuse = D3DCOLOR_RGBA(0,0,0,180);
	g_aVtx[3].diffuse = D3DCOLOR_RGBA(0,0,0,180);

	//�e�N�X�`�����W
	g_aVtx[0].tex=D3DXVECTOR2(0,0);
	g_aVtx[1].tex=D3DXVECTOR2(1,0);
	g_aVtx[2].tex=D3DXVECTOR2(0,1);
	g_aVtx[3].tex=D3DXVECTOR2(1,1);

	m_pD3DBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShadow::Uninit(void)
{
	//���g�̃��\�[�X�̉��
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CShadow::Update(void)
{
	// �x�N�g���v�Z
	float Vx = 0.0f;
	float Vz = 0.0f;
	float fDiffRotY = 0.0f;
	D3DXVECTOR3 Normal=D3DXVECTOR3(0.0f,1.0f,0.0f);
	//�M�~�b�N�̔���֘A
	Vector2 VecLine,VecToTarget;
	D3DXVECTOR3 OffSet;
	D3DXVECTOR3 Target;
	float ModelHigh=10.0f;
	//�O�t���[���̃M�~�b�N�̍��W
	float GimmickUpPosOld;
	float GimmickUnderPosOld;

	CScene* pGimmick;

	CScene* pSceneLinkOld=m_pSceneLink;
	m_pSceneLink=NULL;

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
					}
					else if(m_Pos.y>GimmickUnderPos && m_PosOld.y<=GimmickUnderPos)
					{
 						m_PosOld.y=GimmickUnderPos-ModelHigh;
						m_Pos.y=GimmickUnderPos-ModelHigh;
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
	this->CSceneX::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	this->CSceneX::SetRot(m_Rot.x,m_Rot.y,m_Rot.z);

	CSceneX::Update();
	m_PosOld=m_Pos;


	//�e�ƃv���C���[�̍��W�𓯊�
	CPlayer* pPlayer=CGame::GetPlayer();
	//CMotionModel* pMotion=CGame::GetMotionModel();
	m_Pos.x=pPlayer->GetPos().x;
	m_Pos.z=pPlayer->GetPos().z;
	//m_Pos=pPlayer->GetPos();
	//m_Pos=pMotion->GetPos();
	//CDebugProc::Print("\n�e�̍��W: (%f,%f,%f)\n" ,  m_Pos.x,m_Pos.y,m_Pos.z);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShadow::Draw(void)
{
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;


	//���[���h�}�g���b�N�X
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.y,m_Rot.x,m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);
	//���݃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�X�e���V���̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);					//�X�e���V����L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);					//Z�o�b�t�@�ւ̏������݂𖳌�
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0x00000000);			//�J���[�o�b�t�@�ւ̏������ݖ���

	//DrawSubset�̑O�ɏ���
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);			//�S�č��i
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g���i�EZ�e�X�g���i��0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_INCR);		//�X�e���V���e�X�g���i�EZ�e�X�g�s���i��1
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g�s���i��0
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);					//�J�����O���t�ɂ���
	pD3DXMat = (D3DXMATERIAL*)m_D3DXBuffMat->GetBufferPointer();
	for(int nCntMat = 0;nCntMat<(signed)m_nNumMat;nCntMat++)
	{
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		pDevice->SetTexture(0,0);
		m_pD3DXMesh->DrawSubset(nCntMat);
	}

	pDevice->SetRenderState(D3DRS_STENCILREF,0x01);						//�X�e���V���Q�ƒl��1�ɂ���
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_GREATEREQUAL);		//�X�e���V���l��1�ȏ�ō��i
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);		//�X�e���V���e�X�g���i�EZ�e�X�g���i��+=1
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g���i�EZ�e�X�g�s���i��0
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g�s���i��0
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);				//�J�����O�����Ƃɖ߂�
	for(int nCntMat = 0;nCntMat<(signed)m_nNumMat;nCntMat++)
	{
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		pDevice->SetTexture(0,0);
		m_pD3DXMesh->DrawSubset(nCntMat);
	}
	
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_STENCILREF,0x02);						//�X�e���V���Q�ƒl��2�ɂ���
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);			//�X�e���V���l��2�ō��i
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);		//�X�e���V���e�X�g���i�EZ�e�X�g���i�����̂܂�
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);		//�X�e���V���e�X�g���i�EZ�e�X�g�s���i�����̂܂�
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_KEEP);		//�X�e���V���e�X�g�s���i�����̂܂�
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);				//�J�����O�����Ƃɖ߂�
	
	
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,(D3DCOLORWRITEENABLE_RED   |
													D3DCOLORWRITEENABLE_GREEN |
													D3DCOLORWRITEENABLE_BLUE  |
													D3DCOLORWRITEENABLE_ALPHA ));
	//��ʂ����ς���2D�������̍��|���S����`��
	pDevice ->SetStreamSource(0,m_pD3DBuff,0,sizeof(VERTEX_2D));
	pDevice ->SetFVF(FVF_VERTEX_2D);
	pDevice ->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
	//��Еt��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);		//�X�e���V����L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);		//Z�o�b�t�@�ւ̏������݂𖳌�

}
