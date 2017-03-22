//=============================================================================
//
// ���@���f���\������ [Player.cpp]
// Author : ���V�r�a
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "Fireball.h"
#include "main.h"
#include "Effect.h"
#include "debugproc.h"
//#include "Renderer.h"


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
CFireball::CFireball(OBJTYPE nObjType,int nPriority):CSceneBillboard(nObjType,nPriority)
{
	m_Pos=D3DXVECTOR3(0.0f,0.0f,0.0f);		//���W
	m_Rot=D3DXVECTOR3(0.0f,0.0f,0.0f);		//�p�x
	m_Scl=D3DXVECTOR3(0.0f,0.0f,0.0f);		//�傫��
	m_Angle=D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFireball::~CFireball(void)
{
	
}

//=============================================================================
// �I�u�W�F�N�g�̐���
//=============================================================================
CFireball* CFireball::Create(int Pattern,float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer)
{
	CFireball *pFireball;
	//�C���X�^���X�̍쐬
	pFireball = new CFireball(OBJTYPE_FIREBALL);
	pFireball->m_Pattern=Pattern;
	//���W�̐ݒ�
	pFireball->m_Pos = D3DXVECTOR3(fPosX,fPosY,fPosZ);
	pFireball->SetPos(fPosX,fPosY,fPosZ);
	//CEnemy��Init���Ăяo��
	pFireball->Init(m_pRenderer);
	return pFireball;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFireball::Init(CRenderer *pRenderer)
{
	this->CSceneBillboard::SetSize(5,5,5);
	CSceneBillboard::Init(pRenderer);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFireball::Uninit(void)
{
	//���g�̃��\�[�X�̉��
	CSceneBillboard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFireball::Update(void)
{
	m_Angle.y+=0.01f;
	m_Angle.x+=0.01f;
	/*m_Pos.x = m_Pos.x+cosf(m_Angle.y)*50;
	m_Pos.y = m_Pos.y+cosf(m_Angle.x)*40;
	m_Pos.z = m_Pos.z+sinf(m_Angle.y)*50;

			m_posCameraR.x = m_posCameraP.x+cosf(m_rotCamera.y)*0.1f;
			m_posCameraR.y = m_posCameraP.y+cosf(m_rotCamera.x)*0.1f;
			m_posCameraR.z = m_posCameraP.z+sinf(m_rotCamera.y)*0.1f;

	m_Angle.x+=0.5f;
	m_Angle.y+=0.5f;
	m_Angle.z+=0.5f;*/

	//�e�ɃG�t�F�N�g���Z�b�g
	CEffect::Create(255,30,10,m_Pos.x,m_Pos.y,m_Pos.z,pRenderer);


	//m_Pos.y +=0.1f;
	switch(m_Pattern)
	{
		case 0:		//�݂����獶
			m_Pos.x = m_Pos.x+sinf(m_Angle.y)*0.5f;
			m_Pos.y = m_Pos.y+cosf(m_Angle.x)*3.5f;
		break;
		case 1://���������O
			m_Pos.z = m_Pos.z+sinf(m_Angle.y)*0.5f;
			m_Pos.y = m_Pos.y+cosf(m_Angle.x)*3.5f;
		break;
		case 2:		//������E
			m_Pos.x = m_Pos.x-sinf(m_Angle.y)*0.5f;
			m_Pos.y = m_Pos.y+cosf(m_Angle.x)*3.5f;
		break;
	}
	//m_Pos.z = m_Pos.z+sinf(m_Angle.y)*0.8f;



	//CDebugProc::Print("\n�e�̍��W: (%f %f %f)\n" , m_Pos.x,m_Pos.y,m_Pos.z );
	this->CSceneBillboard::SetPos(m_Pos.x,m_Pos.y,m_Pos.z);
	CSceneBillboard::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFireball::Draw(void)
{
		//������30�ȉ��ɂȂ��������
	if(m_Pos.y<30)
	{
		CSceneBillboard::Draw();
	}
	


}

