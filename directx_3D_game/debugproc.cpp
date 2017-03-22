//=============================================================================
//
// �f�o�b�O���� [debugproc.cpp]
// Author : ���V
//=============================================================================
#include <stdio.h>
#include <stdarg.h>
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �ÓI�ϐ�
//=============================================================================
LPD3DXFONT CDebugProc::m_pD3DXFont = NULL;
char CDebugProc::m_aStr[1024] = {"\0"};
bool CDebugProc::m_bDisp = true;

//=============================================================================
// CDebugProc�R���X�g���N�^
//=============================================================================
CDebugProc::CDebugProc()
{
	// �o�b�t�@�N���A
	memset(m_aStr, 0, sizeof m_aStr);
}

//=============================================================================
// CDebugProc�f�X�g���N�^
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// ����������
//=============================================================================
void CDebugProc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���\���p�t�H���g��ݒ�
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pD3DXFont);
}

//=============================================================================
// �J������
//=============================================================================
void CDebugProc::Uninit(void)
{
	if(m_pD3DXFont != NULL)
	{// ���\���p�t�H���g�̊J��
		m_pD3DXFont->Release();
		m_pD3DXFont = NULL;
	}
}

//=============================================================================
// �������ݏ���
//=============================================================================
void CDebugProc::Print(char *fmt,...)
{
#ifdef _DEBUG
#if 0
	long *pParam;
	static char aBuf[256];

	pParam = (long*)&fmt;
	sprintf(aBuf, fmt, pParam[1], pParam[2], pParam[3], pParam[4],
									pParam[5], pParam[6], pParam[7], pParam[8],
									pParam[9], pParam[10], pParam[11], pParam[12]);
#else
	va_list list;
	char *pCur;
	char aBuf[256]={"\0"};
	char aWk[32];

	va_start(list, fmt);

	pCur = fmt;
	for( ; *pCur; ++pCur)
	{
		if(*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch(*pCur)
			{
			case 'd':
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				sprintf(aWk, "%f", va_arg(list, double));		// double�^�Ŏw��
				break;

			case 's':
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	va_end(list);

#endif
	if((strlen(m_aStr) + strlen(aBuf)) < sizeof m_aStr - 1)
	{
		strcat(m_aStr, aBuf);
	}
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	if(m_bDisp)
	{
		RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

		m_pD3DXFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

		// �o�b�t�@�N���A
		memset(m_aStr, 0, sizeof m_aStr);
	}
#endif
}

