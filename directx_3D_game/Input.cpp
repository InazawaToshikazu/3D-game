//=============================================================================
//
// ���͏��� [input.cpp]
// Author : ���V�r�a
//
//=============================================================================
#include "input.h"
#include "Manager.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define KEY_ON (128)						// �L�[��������Ă���
#define START_REPEAT	(10)				// ���s�[�g�J�n�܂�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUT8 g_pDInput = NULL;	// DIRECTINPUT�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;	// �f�o�C�X�I�u�W�F�N�g�ւ̃|�C���^
BYTE g_aKeyState[256];				// �L�[�{�[�h������Ԃ��󂯎�郏�[�N
BYTE g_prevKeyState[256];			// �O��̃L�[���
int g_nCountRepeatKey[256];			// ���s�[�g�p�J�E���^
//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	// �L�[���̏�����
	for(int i = 0; i<256; i++)
	{
		g_aKeyState[i] = 0;
		g_prevKeyState[i] = 0;
		g_nCountRepeatKey[i] = 0;
	}


	// DirectInput�I�u�W�F�N�g�̍쐬
	if(g_pDInput == NULL)
	{
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL);

		if(FAILED(hr))
		{

			MessageBox(NULL, "DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���", "�x��" ,MB_OK);
			return hr;
		}
	}

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = g_pDInput -> CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);

	if(FAILED(hr))
	{
		MessageBox(NULL, "�f�o�C�X�I�u�W�F�N�g�̍쐬�Ɏ��s���܂���", "�x��" ,MB_OK);
		return hr;
	}


	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = g_pDIDevKeyboard -> SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hr))
	{
		MessageBox(NULL, "�f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���", "�x��" ,MB_OK);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = g_pDIDevKeyboard -> SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if(FAILED(hr))
	{
		MessageBox(NULL, "�������[�h�̐ݒ�Ɏ��s���܂���", "�x��" ,MB_OK);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDIDevKeyboard -> Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void UninitKeyboard(void)
{
	// DirectInput�I�u�W�F�N�g�̊J��
	if(g_pDInput != NULL)
	{
		g_pDInput -> Release();
		g_pDInput = NULL;
	}


	// �f�o�C�X�I�u�W�F�N�g�̊J��
	if(g_pDIDevKeyboard != NULL)
	{
		g_pDIDevKeyboard -> Acquire();
		g_pDIDevKeyboard -> Release();
		g_pDIDevKeyboard = NULL;
	}

}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[256];

	// �L�[���͂��擾
	if(SUCCEEDED(g_pDIDevKeyboard -> GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		// �L�[�{�[�h���̍쐬�A�ۑ�
		for(int nKey=0;nKey<256;nKey++)
		{
			// �O��̃L�[���i�[
			g_prevKeyState[nKey] =g_aKeyState[nKey];

			// ���݂̏�Ԃ��i�[
			g_aKeyState[nKey] =aKeyState[nKey];


			// ���s�[�g���̍쐬
			if(g_aKeyState[nKey] == KEY_ON)
			{
				// ���s�[�g�J�E���^
				g_nCountRepeatKey[nKey]++;
			}
			else
			{
				// �L�[�������ĂȂ���΃J�E���^0��
				g_nCountRepeatKey[nKey] =0;
			}

		}
	}
	else
	{
		g_pDIDevKeyboard ->Acquire();
	}

	if(CManager::GetFadeFlag()==true)
	{
		// �L�[���̏�����
		for(int i = 0; i<256; i++)
		{
			g_aKeyState[i] = 0;
			g_prevKeyState[i] = 0;
			g_nCountRepeatKey[i] = 0;
		}
	}
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	bool result = false;

	if(g_aKeyState[nKey] ==KEY_ON)
	{
		result = true;
	}

	return result;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool GetKeyboardTriger(int nKey)
{
	bool result = false;

	if(((g_aKeyState[nKey] ^g_prevKeyState[nKey]) &g_aKeyState[nKey]) ==KEY_ON)
	{
		result =true;
	}

	return result;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool GetKeyboardRepeat(int nKey)
{
	bool result =false;

	if(g_nCountRepeatKey[nKey] ==1 || g_nCountRepeatKey[nKey] >=START_REPEAT)
	{
		result = true;
	}

	return result;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	bool result =false;

	if(((g_prevKeyState[nKey] ^ g_aKeyState[nKey])&g_prevKeyState[nKey]) ==KEY_ON)
	{
		result =true;
	}

	return result;
}
