#include <CONIO.H>    
#include <STDLIB.H>    
#include <STDIO.H>    
#include <MATH.H>   
#include <MALLOC.H> 
#include <string.h>

typedef unsigned char BYTE;   
typedef unsigned short WORD;   
typedef unsigned long DWORD;   
   
/****  The file header of bmp file 位图文件头*****/
#include <pshpack2.h> //This file turns 2 byte packing of structures on, then sizeof(BITMAPFILEHEADER)=14, otherwise sizeof(BITMAPFILEHEADER)=16
typedef struct tagBITMAPFILEHEADER {   
    WORD bfType;   
    DWORD bfSize;   
    WORD bfReserved1;   
    WORD bfReserved2;
    DWORD bfoffBits;                                                
} BITMAPFILEHEADER; 
#include <poppack.h> //This file turns packing of structures off 
   
/****  The information header of bmp file 位图信息头*****/
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
   
/****  The RGB data of bmp file 图像RGB数据*****/
typedef struct tagRGBDATA{   
    BYTE rgbBlue;       
    BYTE rgbGreen; 
	BYTE rgbRed;   
} RGBDATA; 

int main(int argc, char *argv[])
{
	system("color F0");
	RGBDATA *bmpData=NULL;	//图像数据指针
	FILE *fp, *fq;				//BMP文件指针
	long i,j,k;
	long width=112;			//图像宽度
	long height=113;		//图像高度
	long dataSize=width*height;
	BITMAPFILEHEADER bmfHeader;   
	BITMAPINFOHEADER bmiHeader; 

	if(argc<2)
	{
		printf("\n    请指定您要生成的BMP文件名！\n");
		printf("\n    方法1：在cmd窗口输入： yinzhang  xxxx.bmp　后回车执行！\n");
		printf("\n    方法2：在VC的工程设置中添加参数： xxxx.bmp　后编译运行！\n");
		exit(0);
	}		

    //第一步：用命令行中给出的文件名新建一BMP文件，此时还是一个空文件
	if((fp=fopen(argv[1], "wb+"))==NULL)
	{
		printf("Cannot open BMP file!");
		exit(0);
	}


	//第二步：置文件头数据并写入BMP文件
	bmfHeader.bfType=0x4d42;
	bmfHeader.bfSize=14+40+width*height*3;
	bmfHeader.bfReserved1=0;
	bmfHeader.bfReserved2=0;
	bmfHeader.bfoffBits=0x36;
    fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	//第三步：置信息头数据并写入BMP文件
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
	
	//第四步：置图像RGB数据并写入BMP文件
	//分配足够内存，让bmpData指向这块内存，用于存放图像各象素点的RGB分量值
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

	printf("\n    恭喜您！BMP文件已经成功生成！\n");
	printf("\n    请在当前目录下查看生成的BMP文件%s\n\n",argv[1]);

	free(bmpData);	
	bmpData=NULL;	
	fclose(fp);		
}


