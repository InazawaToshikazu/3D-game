//=============================================================================
//
// ���C������ [Renderer.h]
// Author : ���V�r�a
//
//=============================================================================
#include "main.h"
#include "debugproc.h"


//=============================================================================
// �}�N����`
//=============================================================================
#define SCENE_MAX (5)

//�O���錾
class CScene;
class CLight;
class CCamera;

//=============================================================================
//CRenderer�N���X
//=============================================================================
class CRenderer
{
	//���J�����o
	public:
		CRenderer();		//�R���X�g���N�^
		~CRenderer();		//�f�X�g���N�^

		HRESULT Init(HWND hWmd,BOOL bWindow);	//������
		void Uninit(void);						//�I��
		void Update(void);						//�X�V
		void Draw(void);						//�`��

		void AddScene(CScene* pScenes);			//Scene�̒ǉ�

		LPDIRECT3DDEVICE9 GetDevice(void){return m_pD3DDevice;};	// �f�o�C�X�̎擾

	//����J�����o
	private:
		void DrawFPS(void);
		LPDIRECT3D9 m_pD3D;
		LPDIRECT3DDEVICE9 m_pD3DDevice;
		LPD3DXFONT m_pD3DFont;

		float m_rot;

		CScene* m_apScenes[SCENE_MAX];

		int m_nCountScene;		//Scene�̃J�E���g
};
