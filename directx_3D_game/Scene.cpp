//=============================================================================
//
// ���C������ [Scene.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "Scene.h"
#include "Renderer.h"

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
CScene* CScene::m_pTop[LIST_NUM];
CScene* CScene::m_pCur[LIST_NUM];
bool CScene::m_PauseFlag=false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(OBJTYPE ObjType,int nPriority)
{
	m_bDelete=false;
	//�����Ȃ��Ƃ�
	if(m_pTop[nPriority] ==NULL && m_pCur[nPriority] ==NULL)
	{
		m_pTop[nPriority] =this;
		m_pCur[nPriority] =this;
		m_pPrev =NULL;
		m_pNext =NULL;
	}
	//��������Ƃ�
	else
	{
		m_pCur[nPriority] ->m_pNext=this;
		m_pPrev = m_pCur[nPriority];
		m_pCur[nPriority] = this;
		m_pNext = NULL;
	}
	m_nPriority =nPriority;
	m_ObjType=ObjType;

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// �����[�X
//=============================================================================
void CScene::Release(void)
{
	//�폜�t���O�𗧂Ă�
	m_bDelete=true;
}

//=============================================================================
// �X�V
//=============================================================================
void CScene::UpdateAll(void)
{
	CScene *pScene;


	for(int i=0;i<LIST_NUM;i++)
	{
		pScene = m_pTop[i];

		if(m_PauseFlag==true && i<6)
		{
			continue;	//for��������΂�
		}

		while(1)
		{
			//pScene�̒��ɉ��������Ă�����
			if(pScene)
			{
				CScene *pScene2 =pScene->m_pNext;
				if(!pScene->m_bDelete)
				{
					pScene->Update();
				}
				
				//�폜�t���O�������Ă�����
				if(pScene->m_bDelete)
				{
					pScene->UnlinkList();		//���X�g���Ȃ���
					delete pScene;				//�f���[�g
				}
				pScene = pScene2;
			}
			else
			{
				break;
			}
		}
	}
}


//=============================================================================
// �`��
//=============================================================================
void CScene::DrawAll(void)
{
	CScene *pScene;
	for(int i=0;i<LIST_NUM;i++)
	{
		pScene =m_pTop[i];
		while(1)
		{
			//pScene�̒��ɉ��������Ă�����
			if(pScene)
			{
				pScene->Draw();
				pScene = pScene->m_pNext;
			}
			//pScene�̒�����Ȃ�
			else
			{
				break;
			}
		}
	}
}

//=============================================================================
// �����[�X�I�[��
//=============================================================================
void CScene::ReleaseAll(void)
{
	CScene *pScene;
	for(int i=0;i<LIST_NUM;i++)
	{
		pScene = m_pTop[i];

		while(1)
		{
			//pScene�̒��ɂȂɂ������Ă�����
			if(pScene)
			{
				pScene->Uninit();
				//�폜�t���O�������Ă�����
				if(pScene->m_bDelete)
				{
					pScene->UnlinkList();		//���X�g���Ȃ���
					delete pScene;				//�f���[�g
				}
				pScene = m_pTop[i];
			}
			//pScene����Ȃ�
			else
			{
				break;
			}
		}
	}
}

//=============================================================================
// UnlinkList
//=============================================================================
void CScene::UnlinkList(void)
{
	// ��݂̂̎�
	if(this->m_pPrev == NULL && this->m_pNext == NULL)
	{
		m_pTop[m_nPriority] = NULL;
		m_pCur[m_nPriority] = NULL;
	}

	// �擪�������ꍇ
	else if(this->m_pPrev == NULL && this->m_pNext !=NULL)
	{
		m_pTop[m_nPriority] = this->m_pNext;
		this->m_pNext ->m_pPrev = NULL;
	}
	// ���Ԃ̏���
	else if(this->m_pPrev != NULL && this->m_pNext != NULL)
	{
		this->m_pPrev->m_pNext = this->m_pNext;
		this->m_pNext->m_pPrev = this->m_pPrev;
	}
	// �Ō����������
	else if(this->m_pNext ==NULL && this->m_pPrev != NULL)
	{
		m_pCur[m_nPriority] = this->m_pPrev;
		this->m_pPrev ->m_pNext = NULL;
	}
}


D3DXVECTOR3 CScene::CrossProduct(D3DXVECTOR3 Vector1,D3DXVECTOR3 Vector2,D3DXVECTOR3 Vector3)
{
	D3DXVECTOR3 VecLine,VecToTarget,Vec1;

	VecLine=Vector2-Vector1;
	VecToTarget=Vector3-Vector1;
	//�O�ς̎Z�o
	D3DXVec3Cross(&Vec1,&VecLine,&VecToTarget);
	return Vec1;
}


CScene* CScene::GetScene(OBJTYPE Obj)
{
	CScene *pScene;
	for(int i=0;i<LIST_NUM;i++)
	{
		pScene = m_pTop[i];
		while(1)
		{
			//pScene�̒��ɉ��������Ă�����
			if(pScene)
			{
				if(pScene->GetObjType()==Obj)
				{
					return pScene;
				}
				pScene = pScene->m_pNext;
			}
			else
			{
				break;
			}
		}
	}
	return pScene;

}