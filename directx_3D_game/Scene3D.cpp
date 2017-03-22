//=============================================================================
//
// CScene3D [CScene3D.cpp]
// Author : ���V�r�a
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene3D.h"
#include "Renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FIELD_WIDTH		(100.0f)		// �n�ʂ̕�
#define FIELD_HIGHT		(100.0f)		// �n�ʂ̏c

CRenderer* CScene3D::m_pScene3D=NULL;			//3D�̃|�C���^


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene3D::CScene3D(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	// �����o�ϐ��̏�����
	m_pD3DDevice = NULL;
	m_pD3DTexture = NULL;
	m_pD3DVtxBuff = NULL;
	m_Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl = D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene3D::~CScene3D(void)
{
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CScene3D* CScene3D::Create(float fPosX,float fPosY,float fPosZ,float fSizeX,float fSizeY,float fSizeZ,CRenderer* m_pRenderer)
{
	/*CScene3D *pScene = new CScene3D(OBJTYPE_3D);

	pScene->Init(pRenderer);

	return pScene;
	*/

	//�C���X�^���X�̐���
	CScene3D *pScene= new CScene3D(OBJTYPE_3D);
	//CEnemy��Init���Ăяo��
	pScene->Init(m_pRenderer);
	//���W�̐ݒ�
	pScene->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pScene->SetPos(fPosX,fPosY,fPosZ);
	//�傫���̎w��
	pScene->m_Scl = D3DXVECTOR3(fSizeX,fSizeY,fSizeZ);
	pScene->SetPos(fSizeX,fSizeY,fSizeZ);

	m_pScene3D=m_pRenderer;
	return pScene;

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(CRenderer *pRenderer)
{
	VERTEX_3D *pVtx;
	m_pD3DDevice = pRenderer->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@�̐���
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}

	// �X�e�[�^�X�̏�����
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// �|���S���̐ݒ�
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
	//���_�̐ݒ�
	pVtx[0].vtx = D3DXVECTOR3(-FIELD_WIDTH/2, 0, FIELD_HIGHT/2);
	pVtx[1].vtx = D3DXVECTOR3(FIELD_WIDTH/2,  0, FIELD_HIGHT/2);
	pVtx[2].vtx = D3DXVECTOR3(-FIELD_WIDTH/2, 0, -FIELD_HIGHT/2);
	pVtx[3].vtx = D3DXVECTOR3(FIELD_WIDTH/2,  0, -FIELD_HIGHT/2);

	// �@���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	// �F�̐ݒ�
	pVtx[0].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	// ���_�̉摜�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0,0);
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);
	m_pD3DVtxBuff->Unlock();

	//�e�N�X�`��(�摜�t�@�C��)�̓ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,
							  "data/TEXTURE/magmas.jpg",
							  &m_pD3DTexture);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	// m_pD3DDevice�̉��
	if(m_pD3DDevice != NULL)
	{
		m_pD3DDevice = NULL;
	}

	// m_pD3DTexture�̉��
	if(m_pD3DTexture!= NULL)
	{
		m_pD3DTexture->Release();
		m_pD3DTexture = NULL;
	}

	// m_pD3DVtxBuff�̉��
	if(m_pD3DVtxBuff != NULL)
	{
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
	//// �E��]
	//if(CInputKeyboad::GetKeyboardRepeat(DIK_D))
	//{
		//m_Rot.y += 0.01f;
	//}
	//// ����]
	//if(CInputKeyboad::GetKeyboardRepeat(DIK_A))
	//{
	//	m_Rot.y -= 0.01f;
	//}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�X�P�[���̔��f
	D3DXMatrixScaling(&mtxScl, m_Scl.x, m_Scl.y, m_Scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	//��]�̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);

	//���[���h�}�g���b�N�X�̐ݒ�
	m_pD3DDevice -> SetTransform(D3DTS_WORLD, &m_mtxWorld);
	m_pD3DDevice -> SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	m_pD3DDevice -> SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	m_pD3DDevice -> SetTexture(0, m_pD3DTexture);
	m_pD3DDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
