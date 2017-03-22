//=============================================================================
//
// �J�������� [Camera.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CAMERA_SPEED		(1.5f)//�J�����̑���
#define CAMERA_SPEED2		(1.5f)//�J�����̑���
#define CIRCLE_CAMERA		(3.0f)


class CScene2D;
//=============================================================================
//Camera�N���X
//=============================================================================
class CCamera
{
	//���J�����o
	public:
		typedef enum 
		{
			MODE_FIRSTPERSON,
			MODE_THIRDPERSON
		}MODE;

		CCamera();			//�R���X�g���N�^
		~CCamera();			//�f�X�g���N�^
		HRESULT InitCamera(CRenderer* pRenderer);					//������
		void UpdateCamera(void);									//�X�V
		void SetCamera(void);										//�J�����̃Z�b�g
		D3DXVECTOR3 GetRotCamera(void){return m_rotCamera;};		//�J�����̌����̎擾
		static D3DXMATRIX GetMtxView(void){return m_mtxView;};		//MtxView�̎擾
		void DrawRot(void);
		static D3DXVECTOR3 GetRot(void){return m_rotCamera;};		//�J�����̌����̎擾
		D3DXVECTOR3 GetRotDest(void){return m_posCameraPDest;};		//
		static CCamera* GetCamera(void){return m_pCamera;};			//
		static void SetPauseFlag(bool PauseFlag){m_PauseFlag=PauseFlag;};	//�|�[�Y�̐ݒ�
		static bool GetPauseFlag(void){return m_PauseFlag;};		//�|�[�Y�t���O�̎擾
		void FirstPersonCamera(void);
		void ThirdPersonCamera(void);

		void SetCameraMode(MODE Mode){m_Mode=Mode;};		//�O�t���̊p�x�̐ݒ�
		MODE GetCameraMode(void){return m_Mode;};

		void SetVecCamera(D3DXVECTOR3 Vector){m_VecCamera=Vector;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetVecCamera(void){return m_VecCamera;};


		// 

	//����J�����o
	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		D3DXVECTOR3 m_posCameraP;		//�J�����̎��_
		D3DXVECTOR3 m_posCameraR;		//�J�����̒��ӓ_
		D3DXVECTOR3 m_vecCameraV;		//�J�����̏�����x�N�g��
		static D3DXVECTOR3 m_rotCamera;	//�J�����̌����i��]�����j
		D3DXVECTOR3 m_rotCameraDest;	//�J�����̌����i��]�����j
		D3DXVECTOR3 m_posCameraPDest;	//�ړI�̎��_
		D3DXVECTOR3 m_posCameraRDest;	//�ړI�̒����_
		static D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
		D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
		D3DXVECTOR3 m_zoom;				//�Y�[���p
		D3DVIEWPORT9 m_viewport;		//��ʕ���
		LPD3DXFONT m_pFont;
		float m_fAngle;
		float m_fLength;
		float m_angle;
		float m_angleDest;
		float fDiffRotY;
		static CCamera* m_pCamera;
		static bool m_PauseFlag;		//�|�[�Y�t���O
		D3DXVECTOR3 m_Vec;
		MODE m_Mode;
		bool m_FirstPersonFlag;
		D3DXVECTOR3 m_VecCamera;		//�J�����̃x�N�g��
		CScene2D* m_pScene2D;


};

#endif 