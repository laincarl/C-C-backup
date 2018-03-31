/**
* 程序名: Translation.cpp
* 功  能: 实现bmp格式灰度图片的平移，移出部分用白色填充
*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <windows.h>
#include<algorithm>
using namespace std;
BITMAPFILEHEADER bmpFileHeader;      //位图文件头
BITMAPINFOHEADER bmpInfoHeader;		 //位图信息头
RGBQUAD *pColorTable = new RGBQUAD[256];  //颜色表指针
unsigned char *pBmpData;             //图像数据指针
unsigned char *pNewBmpData;	         //平移后图像数据指针
unsigned char *pTemp, *pTemp1;		 //临时指针	
int width, height, imgSize;            //图像宽，高，实际大小,imgSize必须为4的倍数,bmp格式文件结构规定
int srcX[2], srcY[2], dstX[2], dstY[2]; //平移前后位置
/**
* 函数名: readBmp
* 参  数: bmpFileName--指向读入bmp文件的文件名指针
* 功  能: 读入一个bmp文件，获得相应数据
*/
bool readBmp(char *bmpFileName)
{
	FILE *fp = fopen(bmpFileName, "rb");    //以二进制读方式打开指定的图像文件
	if (NULL == fp)
	{
		printf("%s is not exist!", bmpFileName);
		return FALSE;
	}
	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);   //读取位图头信息放入bmpFileHeader,注:指针也相应移动
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);   //读取位图信息头放入bmpInfoHeader
	width = bmpInfoHeader.biWidth;							//宽
	height = bmpInfoHeader.biHeight;						//高
	fread(pColorTable, sizeof(RGBQUAD), 256, fp);				//读取颜色表放入pColorTable
	//	int bytePerLine = (bmpInfoHeader.biWidth * bmpInfoHeader.biBitCount + 31) / 32 * 4;
	pBmpData = new unsigned char[imgSize = bmpInfoHeader.biSizeImage];
	pNewBmpData = new unsigned char[imgSize];
	memset(pNewBmpData, (BYTE)255, sizeof(char)*imgSize);		//把新的图像信息用255(白色)填充，平移后没有图像的区域就是白色了
	fread(pBmpData, sizeof(char), bmpInfoHeader.biSizeImage, fp);	//读取图像信息放入pBmpData
	fclose(fp);                //记住要关闭文件
	return TRUE;

}

double tem[9] = { 1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0 };
void smooth()
{
	int height = bmpInfoHeader.biHeight;
	int width = bmpInfoHeader.biWidth;
	int imgSize = bmpInfoHeader.biSizeImage;
	int lineByte = (width * 8 + 31) / 32 * 4;  //每行像素所占字节数
	//处理是基于原图的，所以原图的数据不能改变，用pNewBmpData存储改变之后的数据
	memcpy(pNewBmpData, pBmpData, imgSize);   //把原图数据复制给pNewBmpData
	double sum;
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			sum = 0;    //清零
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j - 1)) * tem[0];   //该点左下角
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j)) * tem[1];		//下
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j + 1)) * tem[2];  //右下
			sum += (double)(*(pBmpData + i * lineByte + j - 1)) * tem[3];  //左
			sum += (double)(*(pBmpData + i * lineByte + j)) * tem[4];  //该点位置
			sum += (double)(*(pBmpData + i * lineByte + j + 1)) * tem[5];  //右
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j - 1)) * tem[6];  //左上
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j)) * tem[7];   //上
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j + 1)) * tem[8];  //右上
			*(pNewBmpData + i * lineByte + j) = (unsigned char)(sum / 16.0);
		}
	}
}
/**
* 函数名: medianFilter
* 功  能: 对图像进行水平中值滤波处理
*/
void medianFilter()
{
	int height = bmpInfoHeader.biHeight;
	int width = bmpInfoHeader.biWidth;
	int imgSize = bmpInfoHeader.biSizeImage;
	int lineByte = (width * 8 + 31) / 32 * 4;  //每行像素所占字节数
	//处理是基于原图的，所以原图的数据不能改变，用pNewBmpData存储改变之后的数据
	memcpy(pNewBmpData, pBmpData, imgSize);   //把原图数据复制给pNewBmpData
	unsigned char g[3];   //要取的三个点
	//注意边界点不处理，所以i从1到高度-2，j类似
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			g[0] = *(pBmpData + i * lineByte + j - 1);
			g[1] = *(pBmpData + i * lineByte + j);
			g[2] = *(pBmpData + i * lineByte + j + 1);
			sort(g, g + 3);   //排序
			*(pNewBmpData + i * lineByte + j) = g[1];
		}
	}
}
/**
* 函数名: writeBmp
* 功  能: 新建一个bmp文件,把平移后的图像信息写入，生成一个新的bmp
*/
void writeBmp()
{
	char writeBmpName[] = "new.bmp";
	FILE *fp = fopen(writeBmpName, "wb");   //以二进制写方式打开指定的图像文件
	if (NULL == fp)
	{
		cout << "file not exist!";
		return;
	}
	//写入BMP文件数据
	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	fwrite(pNewBmpData, sizeof(char), imgSize, fp);
	fclose(fp);
	//释放内存
	delete[]pColorTable;
	delete[]pNewBmpData;
	delete[]pBmpData;


}
/**
* 函数名: work
* 功  能: 处理
*/
void work()
{
	int x, y;
	char readBmpName[] = "003.bmp";
	if (!readBmp(readBmpName))
		printf("Bmp file reads faliure");
	//smooth();
	medianFilter();
	writeBmp();
}

int main()
{
	work();
	return 0;
}