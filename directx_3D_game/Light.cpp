//=============================================================================
//
// ���C�g���� [Light.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Light.h"
#include "Renderer.h"


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{


}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{

}


//=============================================================================
// ���C�g�̏�����
//=============================================================================
HRESULT CLight::InitLight(CRenderer* pRenderer)
{
	m_pDevice = pRenderer->GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXVECTOR3 vecDir;

	//���C�g�P
	ZeroMemory(&m_aLight[0],sizeof(D3DLIGHT9));		//������
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	vecDir = D3DXVECTOR3(-1.0f,-1.0f,1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction,&vecDir);
	m_pDevice->SetLight(0,&m_aLight[0]);
	m_pDevice->LightEnable(0,TRUE);

	//���C�g2
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	vecDir = D3DXVECTOR3(1.0f,1.0f,-1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction,&vecDir);
	m_pDevice->SetLight(1,&m_aLight[1]);
	m_pDevice->LightEnable(1,TRUE);

	//���C�g3
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	vecDir = D3DXVECTOR3(-1.0f,1.0f,-1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[2].Direction,&vecDir);
	m_pDevice->SetLight(2,&m_aLight[2]);
	m_pDevice->LightEnable(2,TRUE);
	

	return S_OK;
}
