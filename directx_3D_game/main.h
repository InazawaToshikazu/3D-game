//=============================================================================
//
// ���C������ [main.h]
// Author : ���V�r�a
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#include "xaudio2.h"

#define DIRECTINPUT_VERSION (0x0800)		// �x���΍��p
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ON			(1)
#define OFF			(0)

// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(800)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(600)				// �E�C���h�E�̍���

// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

//	�|���S���̃J�����O
typedef enum
{
	CULL_CW = 0, CULL_CCW, CULL_MAX
}CULLING;

typedef struct
{
	float x;
	float y;
}Vector2;

//�J���[�\����
struct COLOR
{
	int R;		//Red
	int G;		//Green
	int B;		//Blue
	int A;		//Alpha
};

//#ifdef _DEBUG
//#ifndef DBG_NEW
//#define DBG NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
//#define new _NEW
//#define DBG_NEW new
//#endif
//#endif		//_DEBUG

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


#endif


/*
�����邱��

������̃��f���ɓ���������
�@�����킿��킿�Ⴓ����
�@�r�𓮂���
�@�K���𓮂���


�X�e�[�W�������ƊȒP�ɂ���


�}�O�}�������ƃ}�O�}���ۂ�


�e���f���ƃM�~�b�N�̕`�揇�����ւ���Ɖe���M�~�b�N�̏�ɂł邩��



������@������ƂȂ����Q�T�ڂ�CMeshField��InitMeshFieldVerTex�̒���
�x�N�g���������NorMap�Ɋi�[���Ă���Ƃ���Ŏ~�܂�

*/