#include"windows.h"//包含位图文件的文件头，信息头等信息
#include"stdio.h"
//定义几个全局的变量
unsigned char *pBmpBuf;//读入图像数据的指针
int bmpWidth;//图像的宽
int bmpHeight;//图像的高
int bmpclrused;//实际使用的颜色数

RGBQUAD *pColorTable;//颜色表指针
int biBitCount;//每个像素的位数 


//readBmp()函数用于读取位图数据
bool readBmp(char *bmpName)
{

	FILE *fp;//二进制方式打开制定的图像文件
	BITMAPINFOHEADER head;
	int lineByte;
	fp=fopen(bmpName,"rb");
	if(fp==0) 
		return 0;
	//跳过位图的文件头
	fseek(fp,sizeof(BITMAPFILEHEADER),0);
	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head之中
    
	fread(&head,sizeof(BITMAPINFOHEADER),1,fp);
	//获取图像高，宽，每个像素所占的位数信息
	bmpWidth=head.biWidth;
	bmpHeight=head.biHeight;
	biBitCount=head.biBitCount;
	bmpclrused=head.biClrUsed;
	//定义变量，计算图像每行像素所占的字节数
	lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	//灰度图像
	if(biBitCount==8)
	{
		pColorTable=new RGBQUAD[256];
		fread(pColorTable,sizeof(RGBQUAD),256,fp);
	}
	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf=new unsigned char[lineByte*bmpHeight];
	//读入数据
	fread(pBmpBuf,1,lineByte*bmpHeight,fp);
	fclose(fp);
	return 1;
}

//bmp文件的存盘用函数savebmp()
//char *bmpName文件名字及路径
//unsigned char *imgBuf待存盘的文图数据
//int wedth以像素为单位待存盘位图的宽
//int height
//int biBitCount每像素所占的位数
//RGBQUAD *pColorTable颜色表指针
//返回值0为失败，1为成功
bool saveBmp(char *bmpName,unsigned char *imgBuf,int width,int height,int biBitCount,RGBQUAD *pColorTable)
{
	if(!imgBuf)
		return 0;//位图数据指针为0，则没有数据传入
	int colorTablesize=0;//颜色表的大小
	if(biBitCount==8)
		colorTablesize=1024;//灰度图像颜色表大小为1024
	int lineByte=(width*biBitCount/8+3)/4*4;//每行所占的字节数
	//以二进制方式打开文件
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0) return 0;
	//申请位图文件头结构变量，填写文件头信息
	BITMAPFILEHEADER fileHead;
	fileHead.bfType=0x4D42;//bmp的类型
	fileHead.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTablesize+lineByte*height;
	fileHead.bfReserved1=0;
	fileHead.bfReserved2=0;
	//bfOffBits是图像文件前三个部分所需要的空间和
	fileHead.bfOffBits=54+colorTablesize;
	//写文件头进文件
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	//申请位图信息头结构变量，填写信息头信息
    BITMAPINFOHEADER head;
	head.biBitCount=biBitCount;
	head.biClrImportant=0;
	head.biClrUsed=0;
	head.biCompression=0;
	head.biHeight=height;
	head.biPlanes=1;
	head.biSize=40;
	head.biSizeImage=lineByte*height;
	head.biWidth=width;
	head.biXPelsPerMeter=0;
	head.biYPelsPerMeter=0;
	//写位图信息头进内存
	fwrite(&head,sizeof(BITMAPINFOHEADER),1,fp);
	//如果是灰度图像，有颜色表，需要写入文件
	if(biBitCount==8)
		fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	//写位图数据进文件
	fwrite(imgBuf,height*lineByte,1,fp);
	fclose(fp);
	return 1;
}

void main()
{
	char readpath[]="256tu.BMP";
	readBmp(readpath);
	BYTE r,g,b;
	int gray;

	//输出图像
	printf("width=%d\nheight=%d\nbiBitCount=%d\n",bmpWidth,bmpHeight,biBitCount);
	printf("biclrused=%d\n",bmpclrused);
	//循环变量i，j图像的坐标
	int i,j;
	//每行字节数
	int lineByte=(bmpWidth*biBitCount/8+3)/4*4;
    //将图像数据存盘
	int k;//当图像为彩色图像时，遍历每个像素的三个分量
	//将图像左下角1、4部分置成黑色
	if(biBitCount==8)//灰度图像
	{
	/*	for(i=0;i<bmpHeight/2;i++)
			for(j=0;j<bmpWidth/2;j++)
				*(pBmpBuf+i*lineByte+j)=0;*/
	}
	else if(biBitCount==24)
/*	{
	     for(i=0;i<bmpHeight/2;i++)
               for(j=0;j<bmpWidth/2;j++)
				   for(k=0;k<3;k++)
					   *(pBmpBuf+i*lineByte+j*3+k)=0;
	}*/
	//为24位图时，转换为灰度图像
	{
		for(i=0;i<bmpHeight;i++)
			for(j=0;j<bmpWidth;j++)
			{ b=*(pBmpBuf+i*lineByte+j*3+0);
			  g=*(pBmpBuf+i*lineByte+j*3+1);
			  r=*(pBmpBuf+i*lineByte+j*3+2);
              //gray=(r+g+b)/3;
			//	gray=100;
			  gray=0.3*r+0.59*g+0.11*b;
              *(pBmpBuf+i*lineByte+j*3+0)=(BYTE)gray;
			  *(pBmpBuf+i*lineByte+j*3+1)=(BYTE)gray;
			  *(pBmpBuf+i*lineByte+j*3+2)=(BYTE)gray;

			}
	}
	//改变灰度图像的颜色表蓝色分量的值
	//256色图像
	if(biBitCount==8)
	{
		for(i=0;i<256;i++)
		{
			gray=0.11*pColorTable[i].rgbBlue+0.3*pColorTable[i].rgbRed+0.59*pColorTable[i].rgbGreen;
			pColorTable[i].rgbBlue=(BYTE)gray;
			pColorTable[i].rgbRed=(BYTE)gray;
			pColorTable[i].rgbGreen=(BYTE)gray;
		}
	}
	char writepath[]="256色权值灰度.bmp";
	saveBmp(writepath,pBmpBuf,bmpWidth,bmpHeight,biBitCount,pColorTable);
	//清除换从去，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间
	delete []pBmpBuf;
	if(biBitCount==8)
		delete []pColorTable;
}
