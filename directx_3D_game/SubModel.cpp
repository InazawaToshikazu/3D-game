//=============================================================================
//
// ���C������ [SceneX.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Renderer.h"
#include "SubModel.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSubModel::CSubModel(int nPriority)
{
	pDevice =NULL;
	m_nNumMatPlayer =NULL;
	m_D3DXBuffMatPlayer =NULL;
	m_pD3DXMeshPlayer =NULL;
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl=D3DXVECTOR3(0.5f,0.5f,0.5f);
	m_Rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSubModel::~CSubModel()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSubModel::Init(CRenderer* m_pRenderer)
{
	pDevice = m_pRenderer->GetDevice();

	//�w�t�@�C����ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(m_FileName,D3DXMESH_SYSTEMMEM,pDevice,NULL,&m_D3DXBuffMatPlayer,NULL,&m_nNumMatPlayer,&m_pD3DXMeshPlayer)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B", "�x��", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CSubModel::Uninit(void)
{
	//���g�̃��\�[�X�̉��
	if(m_pD3DXMeshPlayer!=NULL)
	{
		m_pD3DXMeshPlayer->Release();
		m_pD3DXMeshPlayer= NULL;
	}
	if(m_D3DXBuffMatPlayer!=NULL)
	{
		m_D3DXBuffMatPlayer->Release();
		m_D3DXBuffMatPlayer= NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CSubModel::Update(void)
{	
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSubModel::Draw(void)
{
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxParent;
	
	if(m_Parent!=NULL)
	{
		mtxParent=m_Parent->GetWorld();
	}
	else
	{
		D3DXMatrixIdentity(&mtxParent);
	}
	
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
	//�e������
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxParent);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);
	//���݃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	
	pD3DXMat = (D3DXMATERIAL*)m_D3DXBuffMatPlayer->GetBufferPointer();
	for(int nCntMat = 0;nCntMat<(signed)m_nNumMatPlayer;nCntMat++)
	{
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);
		pDevice->SetTexture(0,0);
		m_pD3DXMeshPlayer->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);
}


//=============================================================================
// �N���G�C�g
//=============================================================================
CSubModel *CSubModel::Create(float fPosX,float fPosY,float fPosZ,char* FilePath,CRenderer* m_pRenderer)
{
	CSubModel *pObje;
	//�C���X�^���X�̍쐬
	pObje = new CSubModel();
	pObje->m_FileName=FilePath;
	//SceneX�̏�����
	pObje->Init(m_pRenderer);
	//���W�̐ݒ�
	pObje->SetPos(fPosX,fPosY,fPosZ);
	return pObje;
}