
//=============================================================================
//
// ���b�V���n�ʂ̏��� [MeshField.cpp]
// Author : ���V�r�a
//=============================================================================
#include "MeshWall.h"
#include "Input.h"
#include "Renderer.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEX_SIZE_X		(10)			// �e�N�X�`���̃T�C�Y�̓|���S����
#define TEX_SIZE_Z		(10)			// �e�N�X�`���̃T�C�Y�̓|���S���c

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshWall::CMeshWall(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pDevice=NULL;
	m_pD3DTextureField=NULL;
	m_pD3DVtxBuffField=NULL;
	m_pD3DIndexBuffField=NULL;
	m_rot =D3DXVECTOR3(0,0,0);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshWall::~CMeshWall(void)
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshWall::Init(CRenderer *pRenderer)
{
	m_pDevice = pRenderer->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	//�T�C�Y�ƕ������̐ݒ�
	m_nNumBlockX = WALL_NUM_BLOCK_X;
	m_nNumBlockZ = WALL_NUM_BLOCK_Z;
	m_fSizeBlockX = WALL_SIZE_BLOCK_X;
	m_fSizeBlockZ = WALL_SIZE_BLOCK_Z;

	// �����_��
	m_nNumVertex = (m_nNumBlockX+1)*(m_nNumBlockZ+1);

	// ���|���S����
	m_nNumPolygon = m_nNumBlockX*m_nNumBlockZ*2+(m_nNumBlockZ-1)*4;

	// ���_�̑��C���f�b�N�X��
	//				���_��							  +	�k�ރ|���S��������		+ �_�u���Ă�_
	// (nNumBlockX+1)*(nNumBlockZ+1) +  (nNumBlockZ-1)*4		+(nNumBlockX-1)*(nNumBlockZ-1)
	m_nNumVertexIndex = (m_nNumBlockX+1)*(m_nNumBlockZ+1)+(m_nNumBlockZ-1)*(3+m_nNumBlockX);

	// ���_���̃Z�b�g
	if(FAILED(InitMeshFieldVerTex(m_nNumBlockX, m_nNumBlockZ, m_fSizeBlockX, m_fSizeBlockZ)))
	{
		MessageBox(NULL, "InitVerTex():���_���̏������Ɏ��s���܂���", "�x��" ,MB_OK);
		return E_FAIL;
	}

	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshWall::Uninit(void)
{
	// �e�N�X�`���̊J��
	if(m_pD3DTextureField != NULL)
	{
		m_pD3DTextureField -> Release();
		m_pD3DTextureField = NULL;
	}

	// ���_�o�b�t�@���
	if(m_pD3DVtxBuffField != NULL)
	{
		m_pD3DVtxBuffField -> Release();
		m_pD3DVtxBuffField = NULL;
	}

	// ���_�C���f�b�N�X�o�b�t�@���
	if(m_pD3DIndexBuffField != NULL)
	{
		m_pD3DIndexBuffField -> Release();
		m_pD3DIndexBuffField = NULL;
	}
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshWall::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshWall::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	

	//���[���h�g�����X�t�H�[��
	D3DXMatrixIdentity(&m_mtxWorldField);
	D3DXMatrixScaling(&mtxScl,1.0f,1.0f,1.0f);					//�X�P�[���𔽉f
	D3DXMatrixMultiply(&m_mtxWorldField,&m_mtxWorldField,&mtxScl);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_Trans.x,m_Trans.y,m_Trans.z);
	D3DXMatrixMultiply(&m_mtxWorldField,&m_mtxWorldField,&mtxTranslate);
	//��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.x,m_rot.y,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldField,&m_mtxWorldField,&mtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,-m_Trans.x,m_Trans.y,-m_Trans.z);
	D3DXMatrixMultiply(&m_mtxWorldField,&m_mtxWorldField,&mtxTranslate);
	// ���[���h�ݒ��K������
	m_pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorldField);

	//�f�[�^��n��(�o�C���h)
	m_pDevice->SetStreamSource(0,m_pD3DVtxBuffField,0,sizeof(VERTEX_3D));
	// �C���f�b�N�X�o�b�t�@���o�C���h
	m_pDevice->SetIndices(m_pD3DIndexBuffField); 

	//FVF�̐ݒ�
	m_pDevice->SetFVF(FVF_VERTEX_3D);	
	//�e�N�X�`���̐ݒ�
	m_pDevice->SetTexture(0,m_pD3DTextureField);

	// ��ł���ɕς���
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
									0,
									0,
									m_nNumVertex,						//�����_��
									0,
									m_nNumPolygon);						//�`�悷��v���V�e�C�u��

}
	

//=============================================================================
// ���_���̏���������
//=============================================================================
HRESULT CMeshWall::InitMeshFieldVerTex(int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ)
{

	// �z��ԍ�
	int nNum = 0;

	// ���_���v�Z�p
	float fPosX,fPosY, fPosZ;
	double dTexU, dTexV;

	// i�st��
	int t = 0;
	int i = 0;

	// ���_���Z�b�g
	VERTEX_3D *pVtx;

	// �C���f�b�N�X���̃Z�b�g
	WORD *pIndex;

	// ���_�o�b�t�@�������m�ہI�i������Y�ꂸ�Ɂj
	if(FAILED(m_pDevice -> CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffField,
											NULL)))
	{
		return E_FAIL;
	}
	
	// index�o�b�t�@�������m�ہI�i������Y�ꂸ�Ɂj
	if(FAILED(m_pDevice -> CreateIndexBuffer(sizeof(WORD)*m_nNumVertexIndex,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pD3DIndexBuffField,
											NULL)))
	{
		return E_FAIL;
	}

	//���b�N
	m_pD3DVtxBuffField -> Lock(0, 0, (void**)&pVtx, 0);

	// i�st��ɒ��_�ݒ�
	for(i = 0; i <= nNumBlockZ; i++)
	{
		dTexU = 0;
		dTexV = (double)i/TEX_SIZE_Z;
		for(t = 0; t <= nNumBlockX; t++)
		{
			nNum = i * (nNumBlockX+1) + t;
			fPosX = m_pos.x + (fSizeBlockX * t);
//			fPosX = (float)fSizeBlockX * (-nNumBlockX/2 + t);
			fPosY = m_pos.y - (fSizeBlockZ * i);
//			fPosZ = (float) fSizeBlockZ * (nNumBlockZ/2 - i);
			fPosZ=m_pos.z;
			dTexU = (double)-t/TEX_SIZE_X;

			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosY, fPosZ);		// �������ɂ��邱�ƂŁA�e�Ȃǂ����ꂢ�ɏo��
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// ���v��1.0f�ɂȂ�悤�ɂ��Ȃ��ƃ_��
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(200, 200, 200, 255);
			//pVtx[nNum].tex = D3DXVECTOR2((float)dTexU, (float)dTexV);
			pVtx[nNum].tex = D3DXVECTOR2(t*1.0f,i*1.0f);
		}
	}
	
	// �A�����b�N
	m_pD3DVtxBuffField -> Unlock();

	// ���b�N
	m_pD3DIndexBuffField -> Lock(0, 0, (void**)&pIndex, 0);

	// i�st��
	i=0;
	t=0;

	for(int j = 0; j < m_nNumVertexIndex; ++j)
	{

		// �k�ރ|���S��
//		if(j == 2*(nNumBlockX+1)+t*(2*(nNumBlockX+1)+2))
		if(j == 2*(nNumBlockX+1)+t*(2*(nNumBlockX+1)+2))
		{
			pIndex[j] =  (i -1) + t*(nNumBlockX+1);
//			pIndex[j+1] = nNumBlockX+1 + i + t*(nNumBlockX+1);
			pIndex[j+1] = i + (t+1)*(nNumBlockX+1);

			// �i�������
			j += 2;
			t++;
			i = 0;
		}

		// ��
		if(j % 2 == 0)
		{
			pIndex[j] = i + (t+1)*(nNumBlockX+1);

		}
		// ��
		else
		{
			pIndex[j] = i + t*(nNumBlockX+1);
			++i;
		}
	}
	
	// �A�����b�N
	m_pD3DIndexBuffField -> Unlock();

	// �e�N�X�`���ǂݍ���
	if(FAILED(D3DXCreateTextureFromFile(m_pDevice, "./data/TEXTURE/a.jpg", &m_pD3DTextureField)))
	{
		// �ǂݍ��ݎ��s
		MessageBox(NULL,
				"InitField:�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���",
				"�x��",
				MB_OK);

		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// ���S����w�[�܂ł̋�����Ԃ�
//=============================================================================
float CMeshWall::GetFieldLengthX(void)
{
	return (float)m_nNumBlockX*m_fSizeBlockX/2;
}

//=============================================================================
// ���S����Z�[�܂ł̋�����Ԃ�
//=============================================================================
float CMeshWall::GetFieldLengthZ(void)
{
	return (float)m_nNumBlockZ*m_fSizeBlockZ/2;
}



//=============================================================================
// �I�u�W�F�N�g�̐���
//Pos  ���W
//Rot  �p�x
//Translate  
//
//=============================================================================
CMeshWall* CMeshWall::Create(CRenderer *pRenderer,float PosX,float PosY,float PosZ,float RotX,float RotY,float RotZ,float TranslateX,float TranslateY,float TranslateZ)
{
	//�C���X�^���X�̐���
	CMeshWall *pScene = new CMeshWall(OBJTYPE_MESHWALL);
	//���W�̐ݒ�
	pScene->SetPos(PosX,PosY,PosZ);
	pScene->SetTrans(TranslateX,TranslateY,TranslateZ);
	//�p�x�̐ݒ�
	pScene->SetRot(RotX,RotY,RotZ);
	//������
	pScene->Init(pRenderer);

	return pScene;
}

