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

#include "Manager.h"

#include "Camera.h"
#include "Game.h"
#include "Effect.h"

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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_EffectFlag=0;
	m_EffectCnt=0;
	m_pD3DVtxBuffEffect=NULL;
	m_EffectShow=0;

	m_pD3DTextureEffect=NULL;


}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect(void)
{
	
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CEffect* CEffect::Create(int Red,int Green,int Blue,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CEffect *pEffect;
	//�C���X�^���X�̍쐬
	pEffect = new CEffect(OBJTYPE_EFFECT);

	//���W�̐ݒ�
	pEffect->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pEffect->m_Color.R=Red;
	pEffect->m_Color.G=Green;
	pEffect->m_Color.B=Blue;
	pEffect->m_Color.A=255;	
	//CEnemy��Init���Ăяo��
	pEffect->Init(m_pRenderer);
	pEffect->m_pEffect=m_pRenderer;
	return pEffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(CRenderer *pRenderer)
{
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();
	m_pDevice = CManager::GetRenderer() ->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	//���_���̐ݒ�
	//���_�o�b�t�A����
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pD3DVtxBuffEffect,NULL)))
	{
		return E_FAIL;
	}
	VERTEX_3D *pVtx;
	m_pD3DVtxBuffEffect -> Lock(0,0,(void**)&pVtx,0);

	pVtx[0].vtx = D3DXVECTOR3(-10.0f,10.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(10.0f,10.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-10.0f,-10.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(10.0f,-10.0f,0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
	for(int j=0;j<4;j++)
	{
		pVtx[j].diffuse = D3DCOLOR_RGBA(m_Color.R,m_Color.G,m_Color.B,m_Color.A);
	}
	pVtx[0].tex=D3DXVECTOR2(0,0);
	pVtx[1].tex=D3DXVECTOR2(1,0);
	pVtx[2].tex=D3DXVECTOR2(0,1);
	pVtx[3].tex=D3DXVECTOR2(1,1);	
	m_pD3DVtxBuffEffect->Unlock();
	m_EffectFlag = ON;
	m_EffectCnt = 0;

	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(m_pDevice,"data/TEXTURE/shadow000.jpg",&m_pD3DTextureEffect);
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	if(m_pD3DTextureEffect !=NULL)
	{
		m_pD3DTextureEffect ->Release();
		m_pD3DTextureEffect = NULL;
	}
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{

	//	VERTEX_3D *pVtx;
	//	m_pD3DVtxBuffEffect -> Lock(0,0,(void**)&pVtx,0);
	//
	//	m_pD3DVtxBuffEffect->Unlock();


	//�G�t�F�N�g�̏����鑁��
	//�ǂ�ǂ񏬂������Ă���
	m_Scl.x-=0.08f;
	m_Scl.y-=0.08f;
	m_Scl.z-=0.08f;

	//0.1��菬�����Ȃ�����������͍�����30�ȉ��ɂȂ��������
	if(m_Scl.x<= 0.1f || m_Pos.y<30)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^	
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxView;
	mtxView = CCamera::GetMtxView();

	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_ALWAYS);
	//�v���C���[

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldeffect);
	D3DXMatrixInverse(&m_mtxWorldeffect,NULL,&mtxView);
	m_mtxWorldeffect._41 = 0.0f;
	m_mtxWorldeffect._42 = 0.0f;
	m_mtxWorldeffect._43 = 0.0f;

	D3DXMatrixScaling(&mtxScl,m_Scl.x,m_Scl.y,m_Scl.z);					//�X�P�[���𔽉f
	D3DXMatrixMultiply(&m_mtxWorldeffect,&m_mtxWorldeffect,&mtxScl);		
	
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_Rot.x,m_Rot.y,m_Rot.z);		//��]�𔽉f
	D3DXMatrixMultiply(&m_mtxWorldeffect,&m_mtxWorldeffect,&mtxRot);
	D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);		//�ʒu�𔽉f
	D3DXMatrixMultiply(&m_mtxWorldeffect,&m_mtxWorldeffect,&mtxTranslate);
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorldeffect);										//���[���h�}�g���b�N�X�̐ݒ�

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	//�|���S���̕`��	
	pDevice->SetStreamSource(0,m_pD3DVtxBuffEffect,0,sizeof(VERTEX_3D));
	pDevice->SetTexture(0,m_pD3DTextureEffect);
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//�e�|���S���̕`��
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
}

