//////////////////////////////
//	[CreateFire.cpp]		//
//	�����쐬����N���X		//
//////////////////////////////

#include "CreateFire.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//���̐F���i�[���Ă���e�[�u��
RGBTbl FirePal[256]={
{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{0,0,0},{0,0,0},{0,0,0},{0,0,0},
{1,0,0},{1,0,0},{1,0,0},{2,0,0},
{2,0,0},{2,0,0},{2,0,0},{2,0,0},
{3,0,0},{3,0,0},{3,0,0},{5,0,0},
{5,0,0},{6,0,0},{6,0,0},{6,0,0},
{7,0,0},{7,0,0},{7,0,0},{9,0,0},
{9,0,0},{9,0,0},{11,0,0},{11,0,0},
{11,0,0},{13,0,0},{13,0,0},{15,0,0},
{15,0,0},{15,0,0},{17,0,0},{17,0,0},
{17,0,0},{19,0,0},{19,0,0},{21,0,0},
{21,0,0},{21,0,0},{24,0,0},{24,0,0},
{24,0,0},{26,0,0},{26,0,0},{29,0,0},
{29,0,0},{32,0,0},{32,0,0},{34,0,0},
{34,0,0},{34,0,0},{38,0,0},{38,0,0},
{38,0,0},{41,0,0},{41,0,0},{44,0,0},
{44,0,0},{47,0,0},{47,0,0},{47,0,0},
{51,0,0},{51,0,0},{51,0,0},{54,0,0},
{54,0,0},{58,0,0},{58,0,0},{58,0,0},
{62,1,0},{62,1,0},{62,1,0},{66,1,0},
{66,1,0},{71,2,0},{71,2,0},{75,2,0},
{75,2,0},{80,2,0},{80,2,0},{84,2,0},
{84,2,0},{89,2,0},{89,3,0},{89,3,0},
{93,3,0},{93,3,0},{93,5,0},{98,5,0},
{98,5,0},{103,6,0},{103,6,0},{108,7,0},
{108,7,0},{113,7,0},{113,9,0},{118,9,0},
{118,9,0},{118,11,0},{123,11,0},{123,13,0},
{123,13,0},{129,15,0},{129,15,0},{134,17,0},
{134,17,0},{140,19,0},{140,19,0},{146,21,0},
{146,21,0},{146,24,0},{152,24,0},{152,26,0},
{152,26,0},{158,29,0},{158,29,0},{164,32,1},
{164,34,1},{170,34,1},{170,38,1},{170,41,1},
{176,44,2},{176,44,2},{176,47,2},{184,51,2},
{184,54,2},{191,58,2},{191,58,2},{197,62,2},
{197,66,3},{204,71,3},{204,75,3},{204,80,3},
{211,84,5},{211,84,5},{211,89,5},{218,93,5},
{218,98,6},{225,103,6},{225,108,6},{232,113,6},
{232,118,7},{232,123,7},{240,129,7},{240,134,9},
{240,140,9},{247,146,9},{247,152,11},{247,158,11},
{247,170,11},{247,176,13},{247,184,13},{255,191,15},
{255,197,15},{255,204,17},{255,211,17},{255,218,19},
{255,225,19},{255,232,21},{255,240,21},{255,247,24},
{255,247,29},{255,247,32},{255,247,34},{255,247,38},
{255,247,44},{255,255,47},{255,255,51},{255,255,58},
{255,255,62},{255,255,71},{255,255,75},{255,255,80},
{255,255,89},{255,255,93},{255,255,103},{255,255,108},
{255,255,113},{255,255,123},{255,255,129},{255,255,140},
{255,255,146},{255,255,152},{255,255,164},{255,255,170},
{255,255,184},{255,255,191},{255,255,197},{255,255,211},
{255,255,218},{255,255,225},{255,255,232},{255,255,240},
{255,255,247},{255,255,247},{255,255,247},{255,255,247},
{255,255,247},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255},
{255,255,255},{255,255,255},{255,255,255},{255,255,255}
};

//���q�̃f�[�^
int ParticleImg[12*12]={
	0,0,0,4,4,4,4,4,4,0,0,0,
	0,0,4,4,5,5,5,5,4,4,0,0,
	0,4,4,5,5,6,6,5,5,4,4,0,
	4,4,5,6,6,7,7,6,5,5,4,4,
	4,5,6,6,7,8,8,7,6,5,5,4,
	4,5,6,7,8,9,9,8,7,6,5,4,
	4,5,6,7,8,9,9,8,7,6,5,4,
	4,5,6,6,7,8,8,7,7,6,5,4,
	4,4,5,5,6,7,7,7,6,5,4,4,
	0,4,4,5,5,6,6,6,5,4,4,0,
	0,0,4,4,5,5,5,5,4,4,0,0,
	0,0,0,4,4,4,4,4,4,0,0,0,
};

CCreateFire::CCreateFire()
{
	int i;

	OffScreenDC=NULL;
	OffScreenBMP=NULL;
	OffScreenoldBMP=NULL;

	for(i=0;i<MAX_PARTICLECOU;i++) ParticleDat[i].LifeCou=0;

	GravVal=9.8f;
}

CCreateFire::~CCreateFire()
{
	if(OffScreenDC){
		if(OffScreenBMP){
			SelectObject(OffScreenDC,OffScreenoldBMP);
			DeleteObject(OffScreenBMP);
			OffScreenBMP=NULL;
		}
		DeleteDC(OffScreenDC);
		OffScreenDC=NULL;
	}
}

//����ʂ��쐬
bool CCreateFire::CreateOffScreeen(int width,int height)
{
	int i;

	//�r�b�g�}�b�v���̊i�[
	struct{
		BITMAPINFOHEADER bmiH;	
		RGBQUAD rgbTbl[256];
		int rgbTblCount;
	} BmpInfo;

	width=(width+3) & 0xfffc;
	height=(height+3) & 0xfffc;

	//DIB��8bpp�Őݒ�
	memset(&BmpInfo.bmiH,0,sizeof(BITMAPINFOHEADER));
	BmpInfo.rgbTblCount=256;
	ZeroMemory(BmpInfo.rgbTbl,sizeof(RGBQUAD)*256);

	BmpInfo.bmiH.biSize=sizeof(BITMAPINFOHEADER);
	BmpInfo.bmiH.biWidth=width;
	BmpInfo.bmiH.biHeight=height;
	BmpInfo.bmiH.biPlanes=1;
	BmpInfo.bmiH.biBitCount=8;

	//�p���b�g��ݒ�
	for(i=0;i<256;i++){
		BmpInfo.rgbTbl[i].rgbRed=FirePal[i].R;
		BmpInfo.rgbTbl[i].rgbGreen=FirePal[i].G;
		BmpInfo.rgbTbl[i].rgbBlue=FirePal[i].B;
	}

	//DIB�̍쐬
	HDC ScreenDC=GetDC(0);
	OffScreenDC=CreateCompatibleDC(ScreenDC);
	if(OffScreenDC==NULL) return false;
	
	OffScreenBMP=CreateDIBSection(OffScreenDC,(BITMAPINFO *)&BmpInfo,
		DIB_RGB_COLORS,&lpOSBits,NULL,NULL);
	if(OffScreenBMP==NULL) return false;

	ReleaseDC(0,ScreenDC);

	OffScreenoldBMP=(HBITMAP)SelectObject(OffScreenDC,OffScreenBMP);
	SetDIBColorTable(OffScreenDC,0,256,BmpInfo.rgbTbl);

	ScrWidth=width;
	ScrHeight=height;

	return true;
}

//�p���b�g�̐F���擾����
bool CCreateFire::GetFirePal(int num,int *rR,int *rG,int *rB)
{
	if(num<0 || num>255) return false;

	if(rR) *rR=FirePal[num].R;
	if(rG) *rG=FirePal[num].G;
	if(rB) *rB=FirePal[num].B;

	return true;
}

//����������
bool CCreateFire::InitScreen(int width,int height)
{
	if(CreateOffScreeen(width,height)==false) return false;
	
	//���΂̒��S���W
	SetCenterPos(ScrWidth>>1,ScrHeight-40);

	return true;
}

//��ʂ��N���A
void CCreateFire::ClearScreen()
{
	BYTE *lpBits=(BYTE *)lpOSBits;
	
	memset((void *)lpBits,0,ScrWidth*ScrHeight);
}


//�摜��`�悷��i���{�Łj
//hdc ... �]�����HDC
//dx,dy.. �]����̕`��J�n�ʒu
//width*height ... �]������摜�T�C�Y
//sx,sy.. �]�����Ƃ̕`��J�n�ʒu
void CCreateFire::DrawImage(HDC hdc,int dx,int dy,int width,int height,int sx,int sy)
{
	int xx,yy;
	int bw,bh;

	if(OffScreenDC==NULL) return;

	bw=ScrWidth;
	bh=ScrHeight;
	if(sx>=bw || sy>=bh) return;
	xx=sx+width;
	yy=sy+height;
	if(xx>=bw) width=bw-sx;
	if(yy>=bh) height=bh-sy;

	//�摜�̓]��
	StretchBlt(hdc,dx,dy,width,height,OffScreenDC,sx,sy,width,height,SRCCOPY);
}

//���΂̒��S���W���w��
void CCreateFire::SetCenterPos(int sx, int sy)
{
	StPosX=sx;
	StPosY=sy;
}


//�P�^�[�����̉��̏������s��
//PtCou ... ���̎�̔�����
//PtLife .. ���̎����i1�`200�j
//sFlag ... ���͎������邩�ǂ���
//wind  ... ���͂ɂ��ړ���
void CCreateFire::MoveFire(int PtCou,int PtLife,bool sFlag,double wind)
{
	int i,x,y,iDat;
	PARTICLE *lpPt;
	double fx,fy,tim,gv,fv;

	if(lpOSBits==NULL) return;

	ClearScreen();	//�X�N���[���̃N���A

	//���q�̐���
	iDat=PtCou;
	lpPt=ParticleDat;
	for(i=0;i<MAX_PARTICLECOU;i++){
		if(!(lpPt->LifeCou)){
			lpPt->LifeCou=PtLife+(rand()&31);
			x=32-(rand()&63);	//���q�̐��������̉����x
			y=32+(rand()&31);	//���q�̐��������̉����x

			lpPt->fx=(float)x;
			lpPt->fy=(float)y;
			lpPt->sx=(float)(8-(rand()&15));
			lpPt->x=(lpPt->sx)+(float)StPosX;
			lpPt->y=lpPt->sy=(float)(StPosY+(rand()&3));
			(lpPt->DiffTime)=0.0f;	//�o�ߎ���
			(lpPt->Syusoku)=1.0f;	//�����W��
			iDat--;
			if(!iDat) break;
		}
		lpPt++;
	}

	fv=0.8f;		//���͌W��
	gv=GravVal*fv/2.0;

	//�������闱�q���ړ�������
	lpPt=ParticleDat;
	for(i=0;i<MAX_PARTICLECOU;i++){
		if((lpPt->LifeCou)>0){
			tim=lpPt->DiffTime;
			fx=(lpPt->sx)+tim*(lpPt->fx);
			fx=StPosX+fx*(lpPt->Syusoku);
			(lpPt->sx)+=(float)wind;
			fy=(lpPt->sy)-((lpPt->fy)*tim-(gv*tim*tim));
			(lpPt->x)=(float)fx;
			(lpPt->y)=(float)fy;
			(lpPt->LifeCou)--;
			(lpPt->DiffTime)+=0.04f;

			//���̒��S�Ɏ������邽�߂̌W��
			if(sFlag){
				if((lpPt->Syusoku)>0) (lpPt->Syusoku)-=0.015f;
			}

		} else {
			lpPt->LifeCou=0;
		}
		lpPt++;
	}


	//���q�̕`��
	lpPt=ParticleDat;
	for(i=0;i<MAX_PARTICLECOU;i++){
		if(!(lpPt->LifeCou)){
			lpPt++;
			continue;
		}

		x=(int)(lpPt->x);
		y=(int)(lpPt->y);

		if(x>=0 && x<ScrWidth && y>=0 && y<ScrHeight){
			iDat=ParticleDat[i].LifeCou;
			DrawParticle(x,y,iDat);
		}
		lpPt++;
	}
}

//���q��`�悷��
void CCreateFire::DrawParticle(int x,int y,int PCol)
{
	BYTE *lpBits=(BYTE *)lpOSBits;
	BYTE *lpBits2;
	int x1,y1,x2,y2;
	int xx,yy,col,iDat;
	int *lpImgPos;
	int ColTbl[10];

	x1=x-6;y1=y-6;
	x2=x+6;y2=y+6;

	if(x1<0 || x2>=ScrWidth) return;
	if(y1<0 || y2>=ScrHeight) return;

	PCol>>=1;
	for(x=0;x<10;x++){
		ColTbl[x]=(PCol*x)/10;
	}

	lpImgPos=ParticleImg;
	lpBits=lpBits+ScrWidth*(ScrHeight-y1-1)+x1;
	for(yy=y1;yy<y2;yy++){
		lpBits2=lpBits;
		for(xx=x1;xx<x2;xx++){
			col=ColTbl[*lpImgPos];		//���q��1�_�̐F
			iDat=*lpBits2;
			iDat+=col;
			if(iDat>255) iDat=255;
			*lpBits2=(BYTE)iDat;

			lpBits2++;
			lpImgPos++;
		}
		lpBits-=ScrWidth;
	}
}

