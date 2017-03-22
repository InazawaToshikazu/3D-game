//=============================================================================
//
// �����e�N�X�`���A�j���[�V�������� [Explosion.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include"Explosion.h"
#include"Renderer.h"
#include "Camera.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	//�v���C���[�̍��W�����
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0,0,0);
	m_Scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_pD3DTex =NULL;
	m_pDevice=NULL;
	
	m_pD3DBuff=NULL;
	m_nCounterAnim=0;
	m_nPatternAnim=0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion(void)
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(CRenderer *m_pRenderer)
{
	m_pDevice = m_pRenderer->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	pRenderer = m_pRenderer;
	m_Scl = D3DXVECTOR3(15.0f,15.0f,15.0f);

	//���_���̐ݒ�
	//���_�o�b�t�A����
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pD3DBuff,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_3D *pVtx;
	m_pD3DBuff -> Lock(0,0,(void**)&pVtx,0);

	pVtx[0].vtx = D3DXVECTOR3(-1.0f,1.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(1.0f,1.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-1.0f,-1.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(1.0f,-1.0f,0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	for(int j=0;j<4;j++)
	{
		//pVtx[i].rhw=1.0f;
		pVtx[j].diffuse = D3DCOLOR_RGBA(255,100,0,255);
	}
	pVtx[0].tex=D3DXVECTOR2(0,0);
	pVtx[1].tex=D3DXVECTOR2(0.125,0);   
	pVtx[2].tex=D3DXVECTOR2(0,1);
	pVtx[3].tex=D3DXVECTOR2(0.125,1);	

			m_pD3DBuff->Unlock();
	
	

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(m_pDevice,"data/TEXTURE/explosion000.png",&m_pD3DTex);
	return S_OK;
}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void CExplosion::Uninit(void)
{	
	if(m_pD3DTex != NULL)
	{
		m_pD3DTex ->Release();
		m_pD3DTex = NULL;
	}

	if(m_pD3DBuff !=NULL)
	{
		m_pD3DBuff ->Release();
		m_pD3DBuff = NULL;
	}
	CScene::Release();
}
//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CExplosion::Update(void)
{
	m_nCounterAnim++;
	if(m_nCounterAnim == 5)
	{
		m_nPatternAnim++;
		//�A�j���[�V�����p�^�[���̐؂�ւ�
		switch(m_nPatternAnim)
		{
			case 0:
				TextureUpdate(0,0);
				break;
			case 1:
				TextureUpdate(0.125f,0);
 				break;
			case 2:
				TextureUpdate(0.25f,0);
				break;
			case 3:
				TextureUpdate(0.375f,0);
				break;
			case 4:
				TextureUpdate(0.5f,0);
				break;
			case 5:
				TextureUpdate(0.625f,0);
				break;
			case 6:
				TextureUpdate(0.75f,0);
				break;
			case 7:
				TextureUpdate(0.875f,0);
				m_nPatternAnim = 0;
				CExplosion::Uninit();
				break;
		}
	
		m_nCounterAnim = 0 ;
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	
	m_pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	mtxView = CCamera::GetMtxView();
	//�A���t���e�X�g
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF,100);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	
	//���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);													//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);				//�X�P�[���𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);		
	D3DXMatrixRotationYawPitchRoll(&mtxRot,0.0f,m_Rot.y,m_Rot.z);	//��]�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);	//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	m_pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);									//���[���h�}�g���b�N�X�̐ݒ�
	//�A���t�@�e�X�g
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF,0);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);
	//�`��
	
	m_pDevice->SetStreamSource(0,m_pD3DBuff,0,sizeof(VERTEX_3D));
	m_pDevice->SetTexture(0,m_pD3DTex);
	m_pDevice->SetFVF(FVF_VERTEX_3D);
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);			
	
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	
	m_pDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	//�A���t���e�X�g�n�e�e
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);

}

//=============================================================================
// �e�L�X�`���̕`�揈��
//=============================================================================
void CExplosion::TextureUpdate(float x,float y)
{
	VERTEX_3D *pVtx;

	m_pD3DBuff -> Lock(0,0,(void**)&pVtx,0);
	pVtx[0].tex=D3DXVECTOR2(x,y);
	pVtx[1].tex=D3DXVECTOR2(x+0.125f,y);
	pVtx[2].tex=D3DXVECTOR2(x,y+1);
	pVtx[3].tex=D3DXVECTOR2(x+0.125f,y+1);	
	m_pD3DBuff->Unlock();
}


//===========================================================================
// �I�u�W�F�N�g�쐬
//=============================================================================
CExplosion *CExplosion::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CExplosion *pExplosion;
	//�C���X�^���X�̐���
	pExplosion = new CExplosion(OBJTYPE_EXPLOSION);
	//���W�̐ݒ�
	pExplosion->SetPos(fPosX,fPosY,fPosZ);
	//������
	pExplosion->Init(m_pRenderer);
	return pExplosion;
}
