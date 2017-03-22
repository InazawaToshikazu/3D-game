//=============================================================================
//
// �X�R�A���� [Score.h]
// Author : ���V�r�a
//
//=============================================================================
#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include"Scene.h"
#include "Number.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define TIMER_MAX	(999)		//�J���X�g
#define TIMER_DIGIT	  (3)			//����
//�O���錾
class CRenderer;
class CNumber;
//=============================================================================
//CScene2D�N���X
//=============================================================================
class CTimer:public CScene
{
	public:
		CTimer(OBJTYPE nObjType,int nPriority=3);
		~CTimer();
		HRESULT Init(CRenderer* m_pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};
		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};
		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};
		static int GetTime(void){return m_nTimer;};
		static CTimer* Create(float fPosX,float fPosY,CRenderer* m_pRenderer);
		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};	//���W�̑��
		D3DXVECTOR3 GetPos(void){return m_Pos;};		//���W�̎擾
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};	//��]�p�x�̑��
		D3DXVECTOR3 GetRot(void){return m_Rot;};		//��]�p�x�̎擾
		static void AddTimer(int nValue);						//�X�R�A�̉��Z




	private:
		D3DXVECTOR3 m_Pos;						//�|���S���̍��W
		D3DXVECTOR3 m_Rot;						//�|���S���̉�]�p�x
		static int m_nTimer;
		static CRenderer *m_pTimer;
		static CNumber* m_pNumber;
		
		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

};

#endif