// zhong.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include "bmp.h"
#include "change.h"



int main()
{
	int size;
	int h,w;
	int i,j;
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	FILE *fin = fopen("lena.bmp","rb");
	if(fin == NULL)
	{
		printf("Error open!");
		return 0;
	}
	FILE *fout1 = fopen("girl11.bmp","wb");

	fread(&fileheader,sizeof(BITMAPFILEHEADER),1,fin);
	fread(&infoheader,sizeof(BITMAPINFOHEADER),1,fin); 
	Bmp A;
	change  C;
    w = A.getwidth(infoheader);
	h = A.getheight(infoheader);
	size = h*w;
	RGB *img = (RGB *)malloc(sizeof(RGB)*size);
	fread(img,sizeof(RGB),size,fin);                                   //ͼƬ���뵽��ά�����С�
    BYTE *R = (BYTE *)malloc(sizeof(BYTE)*size);
	BYTE *G = (BYTE *)malloc(sizeof(BYTE)*size);
	BYTE *B = (BYTE *)malloc(sizeof(BYTE)*size);
	for(i = 0;i<h;i++)
	{
		for(j = 0;j < w;j++)
		{
			*(R + i*w + j) = (img + i*w +j) ->R;
			*(G + i*w + j) = (img + i*w +j) ->G;
			*(B + i*w + j) = (img + i*w +j) ->B;
		}
	}

	RGB *img1 = (RGB *)malloc(sizeof(RGB)*size);

	short X1[BLOCK][BLOCK];
	short X2[BLOCK][BLOCK];
	short X3[BLOCK][BLOCK];
	double Y[BLOCK][BLOCK];
	short Z1[BLOCK][BLOCK];
	double Z2[BLOCK][BLOCK];
	short X0[BLOCK][BLOCK];

	int I,J;
	int count = 0;
	for(I = 0;I < h;)
	{
		for(J = 0;J<w;)
		{
			for(i = 0;i < BLOCK;i++)
			{
				for(j = 0;j < BLOCK;j++)
				{
					X1[i][j]	= *(R + (I+i)*w+J+j);
					X2[i][j]     =*(G + (I+i)*w+J+j);
					X3[i][j]    = *(B + (I+i)*w+J+j);
				}
			}
			//����R
			C.DCT(X1,Y);	
			C.LH(Y,Z1,Lhua);
			C.LR(Z1,Z2,Lhua);
			C.IDCT(Z2,X1);	
			for(i = 0;i < BLOCK;i++)
			{
				for(j = 0;j < BLOCK;j++)
				{
					(img1+(I+i)*w+J+j)->R = X1[i][j];
				}
			}
			//����G
			C.DCT(X2,Y);	
			C.LH(Y,Z1,Lhua);
			C.LR(Z1,Z2,Lhua);
			C.IDCT(Z2,X2);	
			for(i = 0;i < BLOCK;i++)
			{
				for(j = 0;j < BLOCK;j++)
				{
					(img1+(I+i)*w+J+j)->G = X2[i][j];
				}
			}
			//����B
			C.DCT(X3,Y);	
			C.LH(Y,Z1,Lhua);
			C.LR(Z1,Z2,Lhua);
			C.IDCT(Z2,X3);	
			for(i = 0;i < BLOCK;i++)
			{
				for(j = 0;j < BLOCK;j++)
				{
					(img1+(I+i)*w+J+j)->B = X3[i][j];
				}
			}
			count = count +1;						
			J = J + BLOCK;
		}
		I = I + BLOCK;
	}
	


	fwrite(&fileheader,sizeof(BITMAPFILEHEADER),1,fout1);
	fwrite(&infoheader,sizeof(BITMAPINFOHEADER),1,fout1);
	fwrite(img1,sizeof(RGB),size,fout1);


	fclose(fin);
	fclose(fout1);
	printf("��ʵ����ģ����DCT�任(jpgѹ������)�Ĺ���\n");
	printf("ԭͼ-��DCT-������-��������-������ͼ��\n");
	printf("�Ա�ԭͼ�ۿ�ʧ���,����ͼ����ԭͼ��ͬһ�ļ�����\n");
	getchar();
	return 0;
}

