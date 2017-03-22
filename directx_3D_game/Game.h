//=============================================================================
//
// �Q�[������ [Game.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
typedef enum
{
	GAME=0,
	PAUSE,
	MAX
}GAME_MODE;

#define LEG_MAX (6)
#define TARGET_MAX (6)
#define FIREBALL_MAX (5)

//=============================================================================
// �O���錾
//=============================================================================
class CRenderer;
class CPlayer;
class CGimmick;
class CFade;
class CField;
class CPause;
class CMotionModel;
class CNeedle;
class CTailBall;
class CCollision;
class CTarget;
class CMagma;
class CGoal;
class CCreateFire;
class CFireball;
class CLeg;

//=============================================================================
//Game�N���X
//=============================================================================
class CGame
{
	//���J�����o
	public:
		CGame();		//�R���X�g���N�^
		~CGame();		//�f�X�g���N�^

		HRESULT Init(CRenderer* pRenderer);		//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��

		static CField* GetField(void){return pMeshField;};		//�t�B�[���h�̃|�C���^�̎擾
		static CPlayer* GetPlayer(void){return m_pPlayer2;};	//���@�̃|�C���^�̎擾
		static CGimmick* GetGimmick(void){return m_pGimmick;};	//�M�~�b�N�̃|�C���^�̎擾
		static CMotionModel* GetMotionModel(void){return m_pMotion;};	//�M�~�b�N�̃|�C���^�̎擾
		static CNeedle* GetNeedle(void){return m_pNeedle;};			//
		static CTailBall* GetTailBall(void){return m_pTailBall;};	//
		static CCollision* GetCollision(void){return m_pCollision;};
		static CTarget* GetTarget(int num){return m_pTarget[num];};			//�t�F�[�h�̃|�C���^�̎擾
		static CGoal* GetGoal(void){return m_pGoal;}
		static CMagma* GetMagma(void){return m_pMagma;}

	//����J�����o
	private:
		static CPlayer* m_pPlayer2;				//���@�̃|�C���^
		static CGimmick* m_pGimmick;			//�M�~�b�N�̃|�C���^
		CFade* m_pFade;							//�t�F�[�h�̃|�C���^
		static CField* pMeshField;				//�t�B�[���h�m�|�C���^
		static CMagma* m_pMagma;
		static CRenderer* m_pRenderer;
		bool PauseFlag;							//�|�[�Y�t���O
		static GAME_MODE m_Phase;
		static GAME_MODE m_Nextphase;
		CPause* m_pPause;
		D3DXVECTOR3 ClearPos;
		static CMotionModel* m_pMotion;
		static CNeedle* m_pNeedle;
		static CTailBall* m_pTailBall;
		static CCollision* m_pCollision;
		static CTarget* m_pTarget[TARGET_MAX];
		static CGoal* m_pGoal;
		static CFireball* m_pFireball[FIREBALL_MAX];
		static CLeg* m_pLeg[LEG_MAX];




		static CCreateFire* m_pCreateFire;
		CCreateFire *lpFire;	//������N���X



};

#endif