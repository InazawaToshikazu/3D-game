//=============================================================================
//
// ���@���f���\������ [Player.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"
#include "SceneX.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ANGLE_LEFT	(D3DX_PI/2.0f)
#define ANGLE_RIGHT	(-D3DX_PI/2.0f)
#define ANGLE_FLONT	(D3DX_PI)
#define ANGLE_BACK	(0.0f)

//�O���錾
class CRenderer;
class CFade;

//=============================================================================
//CSceneX�N���X���p������CEnemy�N���X
//=============================================================================
class CPlayer:public CSceneX
{
	//���J�����o
	public:
		typedef enum
		{
			STATE_NORMAL,	//�ʏ�
			STATE_SHOT,		//���Ƃ�
			STATE_RETURN,	//�j���߂��Ă���
			STATE_PULLED,	//�j�ɂЂ��ς���
			STATE_DEAD,		//���S
			STATE_CLEAR		//�N���A
		}STATES;

		CPlayer(OBJTYPE nObjType,int nPriority=3);		//�R���X�g���N�^
		~CPlayer();										//�f�X�g���N�^

		HRESULT Init(CRenderer* m_pRenderer);			//������
		void Uninit(void);								//�I��
		void Update(void);								//�X�V
		void Draw(void);								//�`��

		static CPlayer* CPlayer::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);	//����

		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};								//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾

		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;}											//��]�̎擾

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾

		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

		CScene* GetSceneLink(void){return m_pSceneLink;};		//�M�~�b�N�̃����N

		static bool GetRotFlag(void){return m_RotFlag;};			//��]�t���O�̎擾

		void AddRot(float x,float y,float z){m_Rot.x+=x;m_Rot.y+=y;m_Rot.z+=z;};			//��]�̐ݒ�

		static CFade* GetGFade(void){return m_pFade;};			//�t�F�[�h�̃|�C���^�̎擾

		int GetBulletCnt(void){return m_BulletCnt;};

		static CPlayer* GetPlayer(void){return m_pPPlayer;};		//�t�B�[���h�̃|�C���^�̎擾
		void Neutral(void);
		void Shot(void);
		void Return(void);
		void Pulled(void);
		void DeadDirection(void);
		void ClearDirection(void);

		void SetFrontVectol(float x,float y,float z){m_FrontVectol.x=x;m_FrontVectol.y=y;m_FrontVectol.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetFrontVectol(void){return m_FrontVectol;};											//�O�t���̊p�x�̎擾

		int GetTailShotFlag(void){return TailShotFlag;};
		void SetTailShotFlag(bool flag){TailShotFlag=flag;};

		bool GetDeadFlag(){return m_DeadFlag;};
		bool GetClearFlag(){return m_ClearFlag;};

		bool GetMoveFlag(){return m_MoveFlag;};



	//����J�����o
	private:



		D3DXVECTOR3 m_rotDestModel;				//�ړI�̌���
		D3DXVECTOR3 m_Rot;						//���f���̌���
		D3DXVECTOR3 m_speedModel;				//���f���̃X�s�[�h
		D3DXVECTOR3 m_Pos;					//���f���̃X�s�[�h
		D3DXVECTOR3 m_RotDest;					//�ړI�̌���

		static CRenderer *m_pPlayer;			//�v���C���[�̃|�C���^
		static CPlayer* m_pPPlayer;

		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

		D3DXVECTOR3 m_PosOld;		//�O�t���̍��W
		D3DXVECTOR3 m_RotOld;		//�O�t���̊p�x

		D3DXVECTOR3 GimmickPos[4];	//�M�~�b�N��4���_�̍��W

		CScene* m_pSceneLink;		//�M�~�b�N�Ƃ̃����N

		static CPlayer* m_pFlag;	//
		static CFade* m_pFade;		//�t�F�[�h�̃|�C���^

		bool m_Moving;							//���f���������Ă邩
		float m_fDiffRotY;
		bool m_JFlag;	//�W�����v�t���O

		static bool m_RotFlag;		//��]�t���O
		int m_BulletCnt;
		STATES m_Mode;

		D3DXVECTOR3 m_FrontVectol;

		bool TailShotFlag;	//�K���̔��˃t���O


		bool m_DeadFlag;

		bool m_ClearFlag;

		bool m_MoveFlag;


};

#endif


////=============================================================================
////
//// ���@���f���\������ [Player.h]
//// Author : ���V�r�a
////
////=============================================================================
//#ifndef _PLAYER_H_
//#define _PLAYER_H_
//
////=============================================================================
//// �C���N���[�h
////=============================================================================
//#include "main.h"
//#include "Scene.h"
//#include "SceneX.h"
//
////=============================================================================
//// �}�N����`
////=============================================================================
//#define ANGLE_LEFT	(D3DX_PI/2.0f)
//#define ANGLE_RIGHT	(-D3DX_PI/2.0f)
//#define ANGLE_FLONT	(D3DX_PI)
//#define ANGLE_BACK	(0.0f)
//
//class CRenderer;
////=============================================================================
////CEnemy�N���X
////=============================================================================
//class CPlayer:public CSceneX
//{
//	public:
//		CPlayer(OBJTYPE nObjType,int nPriority=3);
//		~CPlayer();
//		HRESULT Init(CRenderer* m_pRenderer);
//		void Uninit(void);
//		void Update(void);
//		void Draw(void);
//		void Jump(void);
//		static CPlayer* CPlayer::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);
//		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};								//���W�̐ݒ�
//		D3DXVECTOR3 GetPos(void){return m_Pos;};										//���W�̎擾
//		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
//		D3DXVECTOR3 GetRot(void){return m_Rot;}											//��]�̎擾
//		static bool GetRotFlag(void){return m_Flag;};
//		static CPlayer* GetPlayer(void){return m_pFlag;};
//
//	private:
//		D3DXVECTOR3 m_rotDestModel;				//�ړI�̌���
//		bool m_Moving;							//���f���������Ă邩
//		float m_fDiffRotY;
//		D3DXVECTOR3 m_Rot;						//���f���̌���
//		D3DXVECTOR3 m_speedModel;				//���f���̃X�s�[�h
//		D3DXVECTOR3 m_Pos;						//���f���̃X�s�[�h
//		D3DXVECTOR3 m_RotDest;					//�ړI�̌���
//		static CRenderer *m_pPlayer;
//		//D3DXVECTOR3 m_Speed;
//		static bool m_Flag;
//		static CPlayer* m_pFlag;
//
//
//
//
//
//
//};
//
//#endif