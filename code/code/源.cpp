/**
* 程序名: WorkBmp.cpp
* 功  能: 读取和显示24位BMP图像,并把图像数据输入到ImageData.txt中
* 24位bmp可以通过画图程序中的另存为的文件类型中可以选择
* bmp文件放到工程目录下
*/
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <fstream>
using namespace std;
int biWidth;  //图像宽
int biHeight;  //图像高
int biBitCount; //图像类型，每像素位数
//RGBQUAD *pColorTable;  //颜色表指针
unsigned char *pBmpBuf;  //存储图像数据
int lineByte;         //图像数据每行字节数
/**
* 函数名: readBmp
* 参  数: bmpName -- bmp文件名
* 功  能: 读入bmp文件，并获取相应的信息
*/
bool readBmp(char *bmpName)
{
	FILE *fp;
	if ((fp = fopen(bmpName, "rb")) == NULL)  //以二进制的方式打开文件
	{
		cout << "The file " << bmpName << "was not opened" << endl;
		return FALSE;
	}
	if (fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_CUR))  //跳过BITMAPFILEHEADE
	{
		cout << "跳转失败" << endl;
		return FALSE;
	}
	BITMAPINFOHEADER infoHead;
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);   //从fp中读取BITMAPINFOHEADER信息到infoHead中,同时fp的指针移动
	biWidth = infoHead.biWidth;
	biHeight = infoHead.biHeight;
	biBitCount = infoHead.biBitCount;
	lineByte = (biWidth*biBitCount / 8 + 3) / 4 * 4;   //lineByte必须为4的倍数
	//24位bmp没有颜色表，所以就直接到了实际的位图数据的起始位置
	pBmpBuf = new unsigned char[lineByte * biHeight];
	fread(pBmpBuf, sizeof(char), lineByte * biHeight, fp);
	fclose(fp);   //关闭文件
	return TRUE;

}
/**
* 函数名: saveBmp
* 参  数: bmpName -- bmp文件名
* 功  能: 将bmp位图文件的相关信息，写入新创建的文件中
*/
bool saveBmp(char *bmpName)
{
	FILE *fp;
	if ((fp = fopen(bmpName, "wb")) == NULL)   //以二进制写入方式打开
	{
		cout << "打开失败!" << endl;
		return FALSE;
	}
	//设置BITMAPFILEHEADER参数
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+lineByte * biHeight;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	//设置BITMAPINFOHEADER参数
	BITMAPINFOHEADER infoHead;
	infoHead.biSize = 40;
	infoHead.biWidth = biWidth;
	infoHead.biHeight = biHeight;
	infoHead.biPlanes = 1;
	infoHead.biBitCount = biBitCount;
	infoHead.biCompression = BI_RGB;
	infoHead.biSizeImage = lineByte * biHeight;
	infoHead.biXPelsPerMeter = 0;
	infoHead.biYPelsPerMeter = 0;
	infoHead.biClrUsed = 0;
	infoHead.biClrImportant = 0;
	//写入
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(pBmpBuf, sizeof(char), lineByte * biHeight, fp);
	fclose(fp);    //关闭文件
	return TRUE;


}
/**
* 函数名: work
* 功  能: 处理位图信息，并将位图数据保存到ImageData文件中
*/
void work()
{
	char readFileName[] = "nv.BMP";   //定义要读入的文件名
	if (FALSE == readBmp(readFileName))
		cout << "readfile error!" << endl;
	//输出图像的信息
	cout << "Width = " << biWidth << " Height = " << biHeight << " biBitCount=" << biBitCount << endl;
	ofstream outfile("ImageData.txt", ios::in | ios::trunc);
	if (!outfile)
	{
		cout << "open error" << endl;
		return;
	}
	int count = 0;
	//图像数据信息是从左下角按行开始存储的
	for (int i = 0; i < biHeight; i++)
	{
		for (int j = 0; j < biWidth; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				int temp = *(pBmpBuf + i * lineByte + j + k);
				count++;
				outfile << temp << " ";
				if (count % 8 == 0)
				{
					outfile << endl;
				}
			}
		}
	}
	cout << "总的像素数:" << count / 3 << endl;

	char writeBmpName[] = "nvcpy.BMP";
	saveBmp(writeBmpName);
	delete[]pBmpBuf;  //释放内存
}

int main()
{
	work();
	return 0;
}