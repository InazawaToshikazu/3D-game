#define _CRTDBG_MAP_ALLOC		//���������[�N�`�F�b�N
#include <stdlib.h>
#include <crtdbg.h>
//=============================================================================
//
// ���C������ [main.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "main.h"
#include "Renderer.h"
#include "Scene.h"
#include "Scene2D.h"
#include "Scene3D.h"
#include "SceneX.h"
#include "SceneBillboard.h"
#include "Manager.h"
#include "resource.h"
#include "CreateFire.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"������҂��҂��"				// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
#ifdef _DEBUG
int						g_nCountFPS = 0;			// FPS�J�E���^
#endif
CManager* pManager;


//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);		//���������[�N�`�F�b�N
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;


	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1)),	//exe�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		//MAKEINTRESOURCE(IDR_MENU1),			//���j���[
		CLASS_NAME,
		NULL
	};
	
	HWND hWnd;
	MSG msg;

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW&~(WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_THICKFRAME),
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						hInstance,
						NULL);
	
	pManager = new CManager;
	pManager->Init(hInstance,hWnd,TRUE);

	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	

	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);		// FPS�𑪒�
#endif
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				pManager->Update();

				// �`�揈��
				pManager->Draw();
				pManager->PhaseExchange();
				dwFrameCount++;
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	pManager->Uninit();
	delete pManager;

	timeEndPeriod(1);				// ����\��߂�

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	//PAINTSTRUCT ps;
	
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

		case VK_SPACE:

		//DWORD	dw;
		//g_pD3DDevice->GetRenderState( D3DRS_FOGENABLE, &dw );
		//if( dw == TRUE )
		//{
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //�t�H�O�FON��OFF
		//}
		//else
		//{
		//	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE); //�t�H�O�FOFF��ON
		//}
		//break;



	case WM_COMMAND:
		{
			int ID = LOWORD(wParam);
			switch(ID)
			{
				case ID_dialogue:
				{
					//HWND hDlg=CreateDialog((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),
					//						MAKEINTRESOURCE(IDD_DIALOG1),
					//						hWnd,
					//						DlgProc);
					//ShowWindow(hDlg,SW_SHOW);
				}
				break;
			}
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME ofn={0};		//0�ŏ�����

	int x=0,y=0,z=0;
	char DefDir[MAX_PATH];
	char OpenFileName[MAX_PATH]={0};
	GetCurrentDirectory(MAX_PATH,&DefDir[0]);		//�J�����g�f�B���N�g�����擾
	char DefDir2[MAX_PATH];
	char OpenFileName2[MAX_PATH]={0};
	GetCurrentDirectory(MAX_PATH,&DefDir2[0]);		//�J�����g�f�B���N�g�����擾

	//OPENFILENAME�̕K�v�Ȃ�ɒl������
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.hwndOwner=hWnd;
	ofn.lpstrInitialDir=&DefDir[0];
	ofn.lpstrFile=OpenFileName;
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFilter="���f���̃t�@�C��(*.x)\0*.x\0���ׂẴt�@�C��(*.*)\0*.*\0";		//�S�Ẵt�@�C�����I�[�v���Ώ�
	ofn.lpstrFileTitle="���f������";					//�_�C�A���O�^�C�g��
	ofn.Flags=OFN_FILEMUSTEXIST;


	switch(uMsg)
	{
		case WM_INITDIALOG:
		{
			return TRUE;
		}

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		case WM_COMMAND:
		{
			int ID = LOWORD(wParam);
			switch(ID)
			{
				case IDCLOSE:
					DestroyWindow(hWnd);
					break;

				case IDC_BUTTON1:
					char Buff[32];							//�����\���p
					//�e�L�X�g�{�b�N�X�ɓ��͂����ʒu�ɏo��
					GetDlgItemText(hWnd,IDC_X,Buff,30);		//����
					float x=(float)atof(Buff);		//����
					GetDlgItemText(hWnd,IDC_Y,Buff,30);		//����
					float y=(float)atof(Buff);		//����
					GetDlgItemText(hWnd,IDC_Z,Buff,30);		//����
					float z=(float)atof(Buff);		//����

					// ���f���̃t�@�C���I�[�v���_�C�A���O�\��
					if(GetOpenFileName(&ofn))
					{
						SetCurrentDirectory(&DefDir[0]);		//�J�����g�f�B���N�g����ݒ�
						//���f���̍쐬
						//CSceneX::Create((float)x,(float)y,(float)z,/*(CRenderer*)ofn.lpstrFile,(CRenderer*)ofn.lpstrFile,*/CManager::GetRenderer());
					}
					break;
			}
		}
	}
	return FALSE;
}




#ifdef _DEBUG
//=============================================================================
// FPS�\������
//=============================================================================
void CRenderer::DrawFPS(void)
{
	RECT rect={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	char aftr[256];
	wsprintf(&aftr[0],"FPS:%d\n",g_nCountFPS);
	m_pD3DFont->DrawText(NULL,&aftr[0],-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
}
#endif