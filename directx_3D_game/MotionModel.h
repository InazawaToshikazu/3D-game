//=============================================================================
//
// ���f���̓��� [MotionModel.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _MOTIONMODEL_H_
#define _MOTIONMODEL_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"
#include "Scene.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PART_MAX (6)	//�p�[�c�̍ő吔
#define KEY_MAX (3)		//�L�[�t���[���̍ő吔
#define MOVE_SPEED (0.5f)

struct KEY_DATA
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Scl;
	D3DXVECTOR3 Rot;
};

struct KEY_ANIME
{
	int Frame;				//���̃L�[�܂ł̃t���[����
	KEY_DATA Key[PART_MAX];
};

//�O���錾
class CRenderer;
class CSubModel;
class CScene3D;
class CPlayer;
class CScene;
class CFade;
//=============================================================================
//CMotionModel�N���X
//=============================================================================
class CMotionModel:public CScene
{
	public:
		CMotionModel(OBJTYPE nObjType,int nPriority=3);
		~CMotionModel();
		HRESULT Init(CRenderer* pRenderer);
		void Uninit(void);
		void Update(void);
		void Draw(void);
		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};

		void PartsInit(void);
		void DrawDebug(void);
		void WaitMotion(void);		//�ҋ@���[�V����
		void WaitMotion2(void);
		void RunningMotion(void);	//�����j���O���[�V����
		void PunchMotion(void);		//�p���`���[�V����
		void DownMotion(void);		//���ꃂ�[�V����

		static CMotionModel *CMotionModel::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);
		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};		//���W�̐ݒ�
		D3DXVECTOR3 GetPos(void){return m_Pos;};				//���W�̎擾
		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
		D3DXVECTOR3 GetRot(void){return m_Rot;}				//��]�̎擾
		void CMotionModel::WriteAnime(void);				//�A�j���̏����o��

		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾


		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾

		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};

	private:
		LPDIRECT3DDEVICE9 m_pDevice;
		D3DXVECTOR3 m_Rot;				//���f���̌���
		D3DXVECTOR3 m_Scl;				//���f���̑傫��
		D3DXVECTOR3 m_Pos;				//���f���̍��W
		D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X
		static CRenderer* m_pMotion;

		CSubModel* m_Part[PART_MAX];
		CSubModel* m_Part2[PART_MAX];

		int m_MotionKey;

		float m_MotionTime;
		int m_KeyMax;
		bool m_AnimLoopFlag;			//�A�j���[�V�����̃��[�v�t���O

		KEY_ANIME m_Anime[KEY_MAX];
		KEY_ANIME m_Anime2[KEY_MAX];

		void Linear(void);

		bool m_BlendFlag;		//���[�V�����u�����h�̃t���O

		float m_Ratios;		//�䗦

		int m_Key;
		bool m_PunchFlag;

		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
		D3DXVECTOR3 m_VtxMin;
		D3DXVECTOR3 m_VtxMax;

		D3DXVECTOR3 m_RotDest;					//�ړI�̌���


		D3DXVECTOR3 GimmickPos[4];	//�M�~�b�N��4���_�̍��W
		static CFade* m_pFade;		//�t�F�[�h�̃|�C���^
		static CPlayer* m_pFlag;	//
		CScene* m_pSceneLink;		//�M�~�b�N�Ƃ̃����N

		bool m_Moving;							//���f���������Ă邩
		float m_fDiffRotY;
		bool m_JFlag;	//�W�����v�t���O

		static bool m_RotFlag;		//��]�t���O
		int m_BulletCnt;

};

#endif
















////=============================================================================
////
//// ���f���̓��� [MotionModel.h]
//// Author : ���V�r�a
////
////=============================================================================
//#ifndef _MOTIONMODEL_H_
//#define _MOTIONMODEL_H_
//
////=============================================================================
//// �C���N���[�h
////=============================================================================
//#include "main.h"
//#include "Scene.h"
////=============================================================================
//// �}�N����`
////=============================================================================
//#define PART_MAX (10)	//�p�[�c�̍ő吔
//#define KEY_MAX (3)		//�L�[�t���[���̍ő吔
//#define MOVE_SPEED (0.5f)
//
//struct KEY_DATA
//{
//	D3DXVECTOR3 Pos;
//	D3DXVECTOR3 Scl;
//	D3DXVECTOR3 Rot;
//};
//
//struct KEY_ANIME
//{
//	int Frame;				//���̃L�[�܂ł̃t���[����
//	KEY_DATA Key[PART_MAX];
//};
//
////�O���錾
//class CRenderer;
//class CSubModel;
//class CScene3D;
////=============================================================================
////CMotionModel�N���X
////=============================================================================
//class CMotionModel:public CScene
//{
//	public:
//		CMotionModel(OBJTYPE nObjType,int nPriority=3);
//		~CMotionModel();
//		HRESULT Init(CRenderer* pRenderer);
//		void Uninit(void);
//		void Update(void);
//		void Draw(void);
//		void SetPos(float x,float y,float z){m_Pos.x = x;m_Pos.y = y;m_Pos.z = z;};
//
//		void PartsInit(void);
//		void DrawDebug(void);
//		void WaitMotion(void);		//�ҋ@���[�V����
//		void WaitMotion2(void);
//		void RunningMotion(void);	//�����j���O���[�V����
//		void PunchMotion(void);		//�p���`���[�V����
//		void DownMotion(void);		//���ꃂ�[�V����
//
//		static CMotionModel *CMotionModel::Create(float fPosX,float fPosY,float fPosZ,CRenderer* m_pRenderer);
//		void SetPosition(D3DXVECTOR3 Pos){m_Pos = Pos;};		//���W�̐ݒ�
//		D3DXVECTOR3 GetPos(void){return m_Pos;};				//���W�̎擾
//		void SetRot(float x,float y,float z){m_Rot.x=x;m_Rot.y=y;m_Rot.z=z;};			//��]�̐ݒ�
//		D3DXVECTOR3 GetRot(void){return m_Rot;}				//��]�̎擾
//		void CMotionModel::WriteAnime(void);				//�A�j���̏����o��
//
//		void SetPositionOld(float x,float y,float z){m_PosOld.x=x;m_PosOld.y=y;m_PosOld.z=z;};		//�O�t���̍��W�̐ݒ�
//		D3DXVECTOR3 GetPositionOld(void){return m_PosOld;};											//�O�t���̍��W�̎擾
//
//		void SetRotitionOld(float x,float y,float z){m_RotOld.x=x;m_RotOld.y=y;m_RotOld.z=z;};		//�O�t���̊p�x�̐ݒ�
//		D3DXVECTOR3 GetRotitionOld(void){return m_RotOld;};											//�O�t���̊p�x�̎擾
//
//		D3DXVECTOR3 GetVertexMin(void){return m_VtxMin;};
//		D3DXVECTOR3 GetVertexMax(void){return m_VtxMax;};
//
//	private:
//		LPDIRECT3DDEVICE9 m_pDevice;
//		D3DXVECTOR3 m_Rot;				//���f���̌���
//		D3DXVECTOR3 m_Scl;				//���f���̑傫��
//		D3DXVECTOR3 m_Pos;				//���f���̍��W
//		D3DXMATRIX m_mtxWorld;			//���[���h�}�g���b�N�X
//		static CRenderer* m_pMotion;
//
//		CSubModel* m_Part[PART_MAX];
//		CSubModel* m_Part2[PART_MAX];
//
//		int m_MotionKey;
//
//		float m_MotionTime;
//		int m_KeyMax;
//		bool m_AnimLoopFlag;			//�A�j���[�V�����̃��[�v�t���O
//
//		KEY_ANIME m_Anime[KEY_MAX];
//		KEY_ANIME m_Anime2[KEY_MAX];
//
//		void Linear(void);
//
//		bool m_BlendFlag;		//���[�V�����u�����h�̃t���O
//
//		float m_Ratios;		//�䗦
//
//		int m_Key;
//		bool m_PunchFlag;
//
//		D3DXVECTOR3 m_PosOld;						//�|���S���̍��W
//		D3DXVECTOR3 m_RotOld;						//�|���S���̉�]�p�x
//		D3DXVECTOR3 m_VtxMin;
//		D3DXVECTOR3 m_VtxMax;
//
//};
//
//#endif