//=============================================================================
//
// ���C������ [Scene2D.cpp]
// Author :���V�r�a
//
//=============================================================================
#include"Scene2D.h"
#include"Renderer.h"


//=============================================================================
// �O���[�o���ϐ�
//=============================================================================


//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pD3DTex=NULL;
	m_pDevice=NULL;
	m_pD3DBuff=NULL;
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fLength=0.0f;
	m_fAngle=0.0f;	
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(CRenderer* m_pRenderer)
{
	//�f�o�C�X�̎擾
	m_pDevice = m_pRenderer->GetDevice();
	//�֐��̏����ݒ�
	/*m_rot.z = 0;
	m_pos.x = 0;
	m_pos.y = 0;*/
	m_fLength =  sqrtf(100*100+100*100);
	m_fAngle = atan2f(100,100);

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(m_pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,D3DUSAGE_WRITEONLY,FVF_VERTEX_2D,D3DPOOL_MANAGED,&m_pD3DBuff,NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *aVtx;
	m_pD3DBuff -> Lock(0,0,(void**)&aVtx,0);
	//���_�̐ݒ�
	aVtx[0].vtx = D3DXVECTOR3(m_Pos.x-m_Size.x*0.5f,m_Pos.y-m_Size.y*0.5f,0.0f);
	aVtx[1].vtx = D3DXVECTOR3(m_Pos.x+m_Size.x*0.5f,m_Pos.y-m_Size.y*0.5f,0.0f);
	aVtx[2].vtx = D3DXVECTOR3(m_Pos.x-m_Size.x*0.5f,m_Pos.y+m_Size.y*0.5f,0.0f);
	aVtx[3].vtx = D3DXVECTOR3(m_Pos.x+m_Size.x*0.5f,m_Pos.y+m_Size.y*0.5f,0.0f);

	aVtx[0].rhw=1.0f;
	aVtx[1].rhw=1.0f;
	aVtx[2].rhw=1.0f;
	aVtx[3].rhw=1.0f;

	//�F
	aVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	aVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	aVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	aVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);

	//�e�N�X�`�����W
	aVtx[0].tex=D3DXVECTOR2(0,0);
	aVtx[1].tex=D3DXVECTOR2(1,0);
	aVtx[2].tex=D3DXVECTOR2(0,1);
	aVtx[3].tex=D3DXVECTOR2(1,1);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(m_pDevice,TextureName,&m_pD3DTex);
	//���b�N
	m_pD3DBuff->Unlock();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
{	
	if(m_pD3DTex != NULL)
	{
		m_pD3DTex ->Release();
		m_pD3DTex = NULL;
	}
	if(m_pD3DBuff != NULL)
	{
		m_pD3DBuff ->Release();
		m_pD3DBuff = NULL;
	}
	CScene::Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{	
	//���_�̍X�V
	VERTEX_2D *aVtx;
	m_pD3DBuff -> Lock(0,0,(void**)&aVtx,0);
	aVtx[0].vtx = D3DXVECTOR3(m_Pos.x-m_Size.x*0.5f,m_Pos.y-m_Size.y*0.5f,0.0f);
	aVtx[1].vtx = D3DXVECTOR3(m_Pos.x+m_Size.x*0.5f,m_Pos.y-m_Size.y*0.5f,0.0f);
	aVtx[2].vtx = D3DXVECTOR3(m_Pos.x-m_Size.x*0.5f,m_Pos.y+m_Size.y*0.5f,0.0f);
	aVtx[3].vtx = D3DXVECTOR3(m_Pos.x+m_Size.x*0.5f,m_Pos.y+m_Size.y*0.5f,0.0f);

	/*g_aVtx[0].vtx = D3DXVECTOR3(m_pos.x-sinf(-m_rot.z+m_fAngle)*m_fLength,m_pos.y-cosf(-m_rot.z+m_fAngle)*m_fLength,0.0f);	
	g_aVtx[1].vtx = D3DXVECTOR3(m_pos.x+sinf(m_rot.z+m_fAngle)*m_fLength,m_pos.y-cosf(m_rot.z+m_fAngle)*m_fLength,0.0f);
	g_aVtx[2].vtx = D3DXVECTOR3(m_pos.x-sinf(m_rot.z+m_fAngle)*m_fLength,m_pos.y+cosf(m_rot.z+m_fAngle)*m_fLength,0.0f);
	g_aVtx[3].vtx = D3DXVECTOR3(m_pos.x+sinf(-m_rot.z+m_fAngle)*m_fLength,m_pos.y+cosf(-m_rot.z+m_fAngle)*m_fLength,0.0f);*/

	m_pD3DBuff->Unlock();

	/*for(int i=0;i<SCENE_MAX;i++)
	{
		g_rot+=0.01f;
		//���K��
		if(g_rot < -D3DX_PI || g_rot > D3DX_PI)
		{
			g_rot = -g_rot;
		}
		//��]�������Ăяo��
		if(i<2)
		{
			SetRot(D3DXVECTOR3(0,0,g_rot));
		}	
	}*/

}
//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	m_pDevice ->SetStreamSource(0,m_pD3DBuff,0,sizeof(VERTEX_2D));
	m_pDevice ->SetTexture(0,m_pD3DTex);
	m_pDevice ->SetFVF(FVF_VERTEX_2D);
	m_pDevice ->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}

//=============================================================================
// �N���G�C�g
//=============================================================================
CScene2D *CScene2D::Create(float fPosX,float fPosY,float fSizeX,float fSizeY,char* pTextureName,CRenderer* m_pRenderer,int nPriority)
{
	CScene2D *pScene2D;
	//�C���X�^���X�̐ݒ�
	pScene2D = new CScene2D(OBJTYPE_2D,nPriority);
	//�e�N�X�`���̎w��
	pScene2D->TextureName=pTextureName;
	//���W�̐ݒ�
	pScene2D->SetPos(fPosX,fPosY,0);
	//�傫���̐ݒ�
	pScene2D->SetSize(fSizeX,fSizeY,0);
	pScene2D->Init(m_pRenderer);

	return pScene2D;
}