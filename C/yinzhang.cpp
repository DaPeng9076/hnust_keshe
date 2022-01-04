#include <CONIO.H>    
#include <STDLIB.H>    
#include <STDIO.H>    
#include <MATH.H>   
#include <MALLOC.H> 
#include <string.h>

typedef unsigned char BYTE;   
typedef unsigned short WORD;   
typedef unsigned long DWORD;   
   
/****  The file header of bmp file λͼ�ļ�ͷ*****/
#include <pshpack2.h> //This file turns 2 byte packing of structures on, then sizeof(BITMAPFILEHEADER)=14, otherwise sizeof(BITMAPFILEHEADER)=16
typedef struct tagBITMAPFILEHEADER {   
    WORD bfType;   
    DWORD bfSize;   
    WORD bfReserved1;   
    WORD bfReserved2;
    DWORD bfoffBits;                                                
} BITMAPFILEHEADER; 
#include <poppack.h> //This file turns packing of structures off 
   
/****  The information header of bmp file λͼ��Ϣͷ*****/
typedef struct tagBITMAPINFOHEADER {   
    DWORD biSize;   
    DWORD biWidth;   
    DWORD biHeight;   
    WORD  biPlanes;   
    WORD  biBitCount;      
    DWORD biCompress;
    DWORD biSizeImage;   
    DWORD biXPeIsPerMeter;   
    DWORD biYPeIsPerMeter;   
    DWORD biCIrUsed;   
    DWORD biClrImprotant;   
} BITMAPINFOHEADER;   
   
/****  The RGB data of bmp file ͼ��RGB����*****/
typedef struct tagRGBDATA{   
    BYTE rgbBlue;       
    BYTE rgbGreen; 
	BYTE rgbRed;   
} RGBDATA; 

int main(int argc, char *argv[])
{
	system("color F0");
	RGBDATA *bmpData=NULL;	//ͼ������ָ��
	FILE *fp, *fq;				//BMP�ļ�ָ��
	long i,j,k;
	long width=112;			//ͼ����
	long height=113;		//ͼ��߶�
	long dataSize=width*height;
	BITMAPFILEHEADER bmfHeader;   
	BITMAPINFOHEADER bmiHeader; 

	if(argc<2)
	{
		printf("\n    ��ָ����Ҫ���ɵ�BMP�ļ�����\n");
		printf("\n    ����1����cmd�������룺 yinzhang  xxxx.bmp����س�ִ�У�\n");
		printf("\n    ����2����VC�Ĺ�����������Ӳ����� xxxx.bmp����������У�\n");
		exit(0);
	}		

    //��һ�������������и������ļ����½�һBMP�ļ�����ʱ����һ�����ļ�
	if((fp=fopen(argv[1], "wb+"))==NULL)
	{
		printf("Cannot open BMP file!");
		exit(0);
	}


	//�ڶ��������ļ�ͷ���ݲ�д��BMP�ļ�
	bmfHeader.bfType=0x4d42;
	bmfHeader.bfSize=14+40+width*height*3;
	bmfHeader.bfReserved1=0;
	bmfHeader.bfReserved2=0;
	bmfHeader.bfoffBits=0x36;
    fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	//������������Ϣͷ���ݲ�д��BMP�ļ�
	bmiHeader.biSize=40;
	bmiHeader.biWidth=width;
	bmiHeader.biHeight=height;
	bmiHeader.biPlanes=1;
	bmiHeader.biBitCount=24;
	bmiHeader.biCompress=0;
	bmiHeader.biSizeImage=width*height*3;
	bmiHeader.biXPeIsPerMeter=0;
	bmiHeader.biYPeIsPerMeter=0;
	bmiHeader.biCIrUsed=0;
	bmiHeader.biClrImprotant=0;
    fwrite(&bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	
	//���Ĳ�����ͼ��RGB���ݲ�д��BMP�ļ�
	//�����㹻�ڴ棬��bmpDataָ������ڴ棬���ڴ��ͼ������ص��RGB����ֵ
	if((fq=fopen("xp.txt", "r"))==NULL){
		printf("Cannot open BMP file!");
		exit(0);
	}
	if((bmpData=(RGBDATA*)malloc(width*height*3))==NULL){
		printf("bmpData memory malloc error!");
	}

	char a[113][113];
	for(i=0;i<113;i++)
	   for(j=0;j<113;j++){
	   	  fscanf(fq,"%c",&a[i][j]);
	   }
	fclose(fq);
	
	for(i=0;i<113;i++){
		for(j=0;j<113;j++){
			k=(height-i-1)*width + j;
			if(a[i][j]=='X'||i<=2||j<=2||i>=height-3||j>=width-3){
				bmpData[k].rgbBlue=0;
				bmpData[k].rgbGreen=0;
				bmpData[k].rgbRed=255;
			}
			else if(a[i][j]=='_'){
				bmpData[k].rgbBlue=255;
				bmpData[k].rgbGreen=255; 
				bmpData[k].rgbRed=255;
			}
		}
	}
	fwrite(bmpData,sizeof(RGBDATA),dataSize,fp);

	printf("\n    ��ϲ����BMP�ļ��Ѿ��ɹ����ɣ�\n");
	printf("\n    ���ڵ�ǰĿ¼�²鿴���ɵ�BMP�ļ�%s\n\n",argv[1]);

	free(bmpData);	
	bmpData=NULL;	
	fclose(fp);		
}


