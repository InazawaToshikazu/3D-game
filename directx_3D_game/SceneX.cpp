//=============================================================================
//
// ���C������ [SceneX.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "SceneX.h"
#include "Renderer.h"
#include "Input.h"
#include "Enemy.h"
//=============================================================================
// �O���[�o���ϐ�
//=============================================================================


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSceneX::CSceneX(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	pDevice =NULL;
	m_nNumMatPlayer =NULL;
	m_D3DXBuffMatPlayer =NULL;
	m_pD3DXMeshPlayer =NULL;
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PosDest =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_RotDest =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_PlayerMove =false;
	m_ShootCnt =0;

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneX::Init(CRenderer* m_pRenderer)
{
	pDevice = m_pRenderer->GetDevice();

	//�v���C���[�X�e�[�^�X������
	m_Pos =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot =D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Scl =D3DXVECTOR3(0.2f,0.2f,0.2f);
	
	m_PosDest = D3DXVECTOR3(m_Pos.x,m_Pos.y,m_Pos.z);

	//�w�t�@�C����ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(FileName,D3DXMESH_SYSTEMMEM,pDevice,NULL,&m_D3DXBuffMatPlayer,NULL,&m_nNumMatPlayer,&m_pD3DXMeshPlayer)))
	{
		MessageBox(NULL, "X�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B", "�x��", MB_OK);
		return E_FAIL;
	}
	m_PlayerMove = false;
	m_ShootCnt = 0;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CSceneX::Uninit(void)
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
	CScene::Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CSceneX::Update(void)
{	
	////BackSpace�L�[�������ꂽ��
	//if(GetKeyboardPress(DIK_BACK))
	//{
	//	//CSceneX��Uninit���Ă�
	//	CSceneX::Uninit();
	//}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSceneX::Draw(void)
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
CSceneX *CSceneX::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CSceneX *pSceneX;
	//�C���X�^���X�̍쐬
	pSceneX = new CSceneX(OBJTYPE_X);
	//SceneX�̏�����
	pSceneX->Init(m_pRenderer);
	//���W�̐ݒ�
	pSceneX->SetPos(fPosX,fPosY,fPosZ);
	return pSceneX;
}