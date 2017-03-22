//////////////////////////////
//	[CreateFire.h]			//
//	�����쐬����N���X		//
//	2000.03.05	Y.Yutaka	//
//////////////////////////////

#ifndef _CREATEFIRE_H
#define _CREATEFIRE_H

#include <windows.h>

typedef struct stRGBTbl{
	int R,G,B;
} RGBTbl;

#define MAX_PARTICLECOU	1000

class CCreateFire
{
private:

	HDC OffScreenDC;
	HBITMAP OffScreenBMP;
	void *lpOSBits;
	HBITMAP OffScreenoldBMP;
	int ScrWidth,ScrHeight;

	bool CreateOffScreeen(int width,int height);

	//���q�̃f�[�^
	typedef struct{
		float fx,fy;	//�͂̌����i�����x�j
		int LifeCou;	//�����܂ł̃J�E���g
		float sx,sy;	//���q�̊J�n�ʒu
		float x,y;		//���q�̈ʒu
		float DiffTime;	//�o�ߎ���
		float Syusoku;	//����X�������������邽�߂̌W��
	} PARTICLE;
	PARTICLE ParticleDat[MAX_PARTICLECOU];
	
	int StPosX,StPosY;	//���΂̒��S���W
	int StRenX,stRenY;	//���΂͈̔�
	double GravVal;		//�d�͒l�i�n���̏ꍇ�d�͉����x=9.8�j

	void DrawParticle(int x,int y,int col);	//���q��`�悷��

public:
	CCreateFire();
	~CCreateFire();

	//����������
	bool InitScreen(int width,int height);

	//�p���b�g�̐F���擾����
	bool GetFirePal(int num,int *rR,int *rG,int *rB);

	//�摜�̓]��
	void DrawImage(HDC hdc,int dx,int dy,int width,int height,int sx,int sy);

	//��ʂ��N���A
	void ClearScreen();

	//���΂̒��S���W���w��
	void SetCenterPos(int sx, int sy);

	//�P�^�[�����̉��̏������s��
	void MoveFire(int PtCou,int PtLife,bool sFlag,double wind);

};

#endif
