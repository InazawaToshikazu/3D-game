//=============================================================================
//
// �h�[���\������ [Dome.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Renderer.h"
#include "Dome.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDome::CDome(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDome::~CDome()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CDome::Init(CRenderer *pRenderer,int SizeX,int SizeY,int NumWeight,int NumHigh)
{
	VERTEX_3D *pVtx;
	WORD *pIndex;		//�C���f�b�N�X�p
	int Cnt=0;			//�J�E���^
	m_pD3DDevice = pRenderer->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Rot=D3DXVECTOR3(0,0,0);
	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fSizeWeight=(float)SizeX;
	m_fSizeHigh=(float)SizeY;
	
	m_nNumWeight=NumWeight;
	m_nNumHigh=NumHigh;

	// �����_��
	m_nNumVertex = (m_nNumWeight+1)*(m_nNumHigh+1);
	// ���|���S����
	m_nNum = m_nNumWeight*m_nNumHigh*2+(m_nNumHigh-1)*4;
	// ���_�̑��C���f�b�N�X��
	m_nNumIndex = (m_nNumWeight+1)*(m_nNumHigh+1)+(m_nNumHigh-1)*(3+m_nNumWeight);

	//���_�o�b�t�@�̍쐬
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,D3DUSAGE_WRITEONLY,FVF_VERTEX_3D,D3DPOOL_MANAGED,&m_pD3DVtx,NULL)))
	{
		return E_FAIL;
	}
	//���b�N
	m_pD3DVtx->Lock(0,0,(void**)&pVtx,0);
	//���_���W�̐ݒ�
	for(int i=0;i<=m_nNumHigh;i++)
	{
		for(int j=0;j<=m_nNumWeight;j++)
		{
			m_Length=cosf(2.0f*D3DX_PI*i/4/m_nNumHigh)*SizeX;
			//���_���
			pVtx[i*(m_nNumHigh+1)+j].vtx=D3DXVECTOR3(cosf(2.0f*D3DX_PI*j/m_nNumWeight)*m_Length,
													sinf(2.0f*D3DX_PI*i/4/m_nNumHigh)*SizeX,
													sinf(2.0f*D3DX_PI*j/m_nNumWeight)*m_Length);

			//�@���x�N�g��
			pVtx[i*(m_nNumHigh+1)+j].nor=D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[i*(m_nNumHigh+1)+j].diffuse=D3DCOLOR_RGBA(0xff,0xff,0xff,255);
			//�e�N�X�`�����̐ݒ�
			float a=(float)j/(float)NumHigh;
			pVtx[i*(m_nNumHigh+1)+j].tex=D3DXVECTOR2((float)i/(float)m_nNumWeight,(float)j/(float)m_nNumHigh);
		}
	}
	//�e�N�X�`���̐ݒ�
	D3DXCreateTextureFromFile(m_pD3DDevice,"data/TEXTURE/sora2.jpg",&m_pD3DTex);
	//�A�����b�N
	m_pD3DVtx->Unlock();

	
	//�C���f�b�N�X����
	if(FAILED(m_pD3DDevice->CreateIndexBuffer(sizeof(DWORD)*m_nNumIndex,
												D3DUSAGE_WRITEONLY,
												D3DFMT_INDEX16,
												D3DPOOL_MANAGED,
												&m_pD3DIndex,
												NULL)))
	{
		return E_FAIL;
	}

	//�C���f�b�N�X�o�b�t�@�̐ݒ�
	m_pD3DIndex->Lock(0,0,(void**)&pIndex,0);
	int t = 0;
	int i = 0;
	for(int j = 0; j < m_nNumIndex; ++j)
	{
		// �k�ރ|���S��
		if(j == 2*(m_nNumWeight+1)+t*(2*(m_nNumWeight+1)+2))
		{
			pIndex[j] =  (i -1) + t*(m_nNumWeight+1);
			pIndex[j+1] = i + (t+1)*(m_nNumWeight+1);
			// �i�������
			j += 2;
			t++;
			i = 0;
		}
		// ��
		if(j % 2 == 0)
		{
			pIndex[j] = i + (t+1)*(m_nNumWeight+1);
		}
		// ��
		else
		{
			pIndex[j] = i + t*(m_nNumWeight+1);
			++i;
		}
	}

	//�A�����b�N
	m_pD3DIndex->Unlock();
	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void CDome::Uninit(void)
{
	if(m_pD3DVtx!=NULL)
	{
		m_pD3DVtx->Release();
		m_pD3DVtx=NULL;
	}
	if(m_pD3DIndex!=NULL)
	{
		m_pD3DIndex->Release();
		m_pD3DIndex=NULL;
	}
	if(m_pD3DTex!=NULL)
	{
		m_pD3DTex->Release();
		m_pD3DTex=NULL;
	}
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CDome::Update(void)
{

	m_Rot.y+=0.001f;

	this->SetPos(m_Pos.x,m_Pos.y,m_Pos.z);

}

//=============================================================================
// �`�揈��
//=============================================================================
void CDome::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate,mtxWorld;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, m_Scl.x, m_Scl.y, m_Scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	//��]�̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�̔��f
	D3DXMatrixTranslation(&mtxTranslate, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	//���[���h�}�g���b�N�X�̐ݒ�
	m_pD3DDevice -> SetTransform(D3DTS_WORLD, &mtxWorld);
	//���_�o�b�t�@���o�C���h
	m_pD3DDevice -> SetStreamSource(0, m_pD3DVtx, 0, sizeof(VERTEX_3D));
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice -> SetTexture(0, m_pD3DTex);
	//�C���f�b�N�X�����o�C���h
	m_pD3DDevice->SetIndices(m_pD3DIndex);
	//���_�t�H�[�}�b�g�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);
	//�|���S���̐ݒ�
	m_pD3DDevice -> DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNum);
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CDome* CDome::Create(float SizeX,float SizeZ,int NumX,int NumZ,float fPosX,float fPosY,float fPosZ,CRenderer* pRenderer)
{
	CDome *pDome;

	pDome=new CDome(OBJTYPE_DOME);
	//�������֐��Ăяo��
	pDome->Init(pRenderer,(int)SizeX,(int)SizeZ,NumX,NumZ);
	//���W�̐ݒ�
	pDome->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	//���W�ݒ�
	pDome->SetPos(fPosX,fPosY,fPosZ);
	return pDome;
}