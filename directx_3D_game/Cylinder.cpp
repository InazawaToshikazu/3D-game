//=============================================================================
//
// �V�����_�[�\������ [Cylinder.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Renderer.h"
#include "Cylinder.h"
//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
float CCylinder::m_Lengthin[1];
int CCylinder::m_nCylinderNum=0;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCylinder::CCylinder(OBJTYPE nObjType,int nPriority):CScene(nObjType,nPriority)
{
	m_pD3DDevice=NULL;
	m_pD3DTex=NULL;
	m_pD3DVtx=NULL;
	m_pD3DIndex=NULL;
	m_nNumVertex=0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCylinder::~CCylinder()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CCylinder::Init(CRenderer *pRenderer,int SizeX,int SizeY,int NumWeight,int NumHigh)
{
	VERTEX_3D *pVtx;
	WORD *pIndex;		//�C���f�b�N�X�p
	int Cnt=0;

	m_pD3DDevice = pRenderer->GetDevice();	// �f�o�C�X�ւ̃|�C���^


	m_Rot=D3DXVECTOR3(0,0,0);
	m_Scl=D3DXVECTOR3(1.0f,1.0f,1.0f);

	m_fSizeWeight=(float)SizeX;
	m_fSizeHigh=(float)SizeY;
	m_nNumWeight=(int)NumWeight;
	m_nNumHigh=(int)NumHigh;

	// �����_��
	m_nNumVertex = (m_nNumWeight+1)*(m_nNumHigh+1);
	// ���|���S����
	m_nNum = m_nNumWeight*m_nNumHigh*2+(m_nNumHigh-1)*4;
	// ���_�̑��C���f�b�N�X��
	m_nNumIndex = (m_nNumWeight+1)*(m_nNumHigh+1)+(m_nNumHigh-1)*(3+m_nNumWeight);

	m_Length=D3DXVECTOR2(m_fSizeWeight,m_fSizeHigh);

	//���_�o�b�t�@�̍쐬
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
												D3DUSAGE_WRITEONLY,
												FVF_VERTEX_3D,
												D3DPOOL_MANAGED,
												&m_pD3DVtx,
												NULL)))
	{
		return E_FAIL;
	}

	m_pD3DVtx->Lock(0,0,(void**)&pVtx,0);

	//���_���W�̐ݒ�
	for(int i=0;i<=m_nNumHigh;i++)
	{
		for(int j=0;j<=m_nNumWeight;j++)
		{
			float Rot=2.0f*D3DX_PI*j/m_nNumWeight;
			pVtx[i*(m_nNumHigh+1)+j].vtx=D3DXVECTOR3(-cosf(Rot)*m_Length.x,m_Length.y*i,sinf(Rot)*m_Length.x);
			pVtx[i*(m_nNumHigh+1)+j].nor=D3DXVECTOR3(0.0f,1.0f,0.0f);
			pVtx[i*(m_nNumHigh+1)+j].diffuse=D3DCOLOR_RGBA(0xff,0xff,0xff,0xff);
			pVtx[i*(m_nNumHigh+1)+j].tex=D3DXVECTOR2((float)i/(float)m_nNumWeight,(float)j/(float)m_nNumHigh);
		}
	}
	m_pD3DVtx->Unlock();

	//�摜�t�@�C���̓ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,"data/TEXTURE/wall003.jpg",&m_pD3DTex);

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

	m_pD3DIndex->Lock(0,0,(void**)&pIndex,0);
	// i�st��
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
	m_pD3DIndex->Unlock();
	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void CCylinder::Uninit(void)
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
void CCylinder::Update(void)
{
	m_Rot.y+=0.002f;

}

//=============================================================================
// �`�揈��
//=============================================================================
void CCylinder::Draw(void)
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
//�I�u�W�F�N�g����
//float SizeX	���T�C�Y
//float SizeY	�c�T�C�Y
//int NumX		���̕�����
//int NumZ		�c�̕�����
//float fPosX	X���W
//float fPosY	Y���W
//flaot fPosZ	Z���W
//=============================================================================
CCylinder* CCylinder::Create(float SizeX,float SizeY,int NumX,int NumZ,float fPosX,float fPosY,float fPosZ,CRenderer* pRenderer)
{
	CCylinder *pCylinder;
	//�C���X�^���X�̐���
	pCylinder=new CCylinder(OBJTYPE_CYLINDER);
	//������
	pCylinder->Init(pRenderer,(int)SizeX,(int)SizeY,NumX,NumZ);
	pCylinder->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);

	pCylinder->SetPos(fPosX,fPosY,fPosZ);

	return pCylinder;
}