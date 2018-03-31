/**
* ������: Translation.cpp
* ��  ��: ʵ��bmp��ʽ�Ҷ�ͼƬ��ƽ�ƣ��Ƴ������ð�ɫ���
*/
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <windows.h>
#include<algorithm>
using namespace std;
BITMAPFILEHEADER bmpFileHeader;      //λͼ�ļ�ͷ
BITMAPINFOHEADER bmpInfoHeader;		 //λͼ��Ϣͷ
RGBQUAD *pColorTable = new RGBQUAD[256];  //��ɫ��ָ��
unsigned char *pBmpData;             //ͼ������ָ��
unsigned char *pNewBmpData;	         //ƽ�ƺ�ͼ������ָ��
unsigned char *pTemp, *pTemp1;		 //��ʱָ��	
int width, height, imgSize;            //ͼ����ߣ�ʵ�ʴ�С,imgSize����Ϊ4�ı���,bmp��ʽ�ļ��ṹ�涨
int srcX[2], srcY[2], dstX[2], dstY[2]; //ƽ��ǰ��λ��
/**
* ������: readBmp
* ��  ��: bmpFileName--ָ�����bmp�ļ����ļ���ָ��
* ��  ��: ����һ��bmp�ļ��������Ӧ����
*/
bool readBmp(char *bmpFileName)
{
	FILE *fp = fopen(bmpFileName, "rb");    //�Զ����ƶ���ʽ��ָ����ͼ���ļ�
	if (NULL == fp)
	{
		printf("%s is not exist!", bmpFileName);
		return FALSE;
	}
	fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);   //��ȡλͼͷ��Ϣ����bmpFileHeader,ע:ָ��Ҳ��Ӧ�ƶ�
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);   //��ȡλͼ��Ϣͷ����bmpInfoHeader
	width = bmpInfoHeader.biWidth;							//��
	height = bmpInfoHeader.biHeight;						//��
	fread(pColorTable, sizeof(RGBQUAD), 256, fp);				//��ȡ��ɫ�����pColorTable
	//	int bytePerLine = (bmpInfoHeader.biWidth * bmpInfoHeader.biBitCount + 31) / 32 * 4;
	pBmpData = new unsigned char[imgSize = bmpInfoHeader.biSizeImage];
	pNewBmpData = new unsigned char[imgSize];
	memset(pNewBmpData, (BYTE)255, sizeof(char)*imgSize);		//���µ�ͼ����Ϣ��255(��ɫ)��䣬ƽ�ƺ�û��ͼ���������ǰ�ɫ��
	fread(pBmpData, sizeof(char), bmpInfoHeader.biSizeImage, fp);	//��ȡͼ����Ϣ����pBmpData
	fclose(fp);                //��סҪ�ر��ļ�
	return TRUE;

}

double tem[9] = { 1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0 };
void smooth()
{
	int height = bmpInfoHeader.biHeight;
	int width = bmpInfoHeader.biWidth;
	int imgSize = bmpInfoHeader.biSizeImage;
	int lineByte = (width * 8 + 31) / 32 * 4;  //ÿ��������ռ�ֽ���
	//�����ǻ���ԭͼ�ģ�����ԭͼ�����ݲ��ܸı䣬��pNewBmpData�洢�ı�֮�������
	memcpy(pNewBmpData, pBmpData, imgSize);   //��ԭͼ���ݸ��Ƹ�pNewBmpData
	double sum;
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			sum = 0;    //����
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j - 1)) * tem[0];   //�õ����½�
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j)) * tem[1];		//��
			sum += (double)(*(pBmpData + (i - 1) * lineByte + j + 1)) * tem[2];  //����
			sum += (double)(*(pBmpData + i * lineByte + j - 1)) * tem[3];  //��
			sum += (double)(*(pBmpData + i * lineByte + j)) * tem[4];  //�õ�λ��
			sum += (double)(*(pBmpData + i * lineByte + j + 1)) * tem[5];  //��
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j - 1)) * tem[6];  //����
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j)) * tem[7];   //��
			sum += (double)(*(pBmpData + (i + 1) * lineByte + j + 1)) * tem[8];  //����
			*(pNewBmpData + i * lineByte + j) = (unsigned char)(sum / 16.0);
		}
	}
}
/**
* ������: medianFilter
* ��  ��: ��ͼ�����ˮƽ��ֵ�˲�����
*/
void medianFilter()
{
	int height = bmpInfoHeader.biHeight;
	int width = bmpInfoHeader.biWidth;
	int imgSize = bmpInfoHeader.biSizeImage;
	int lineByte = (width * 8 + 31) / 32 * 4;  //ÿ��������ռ�ֽ���
	//�����ǻ���ԭͼ�ģ�����ԭͼ�����ݲ��ܸı䣬��pNewBmpData�洢�ı�֮�������
	memcpy(pNewBmpData, pBmpData, imgSize);   //��ԭͼ���ݸ��Ƹ�pNewBmpData
	unsigned char g[3];   //Ҫȡ��������
	//ע��߽�㲻��������i��1���߶�-2��j����
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			g[0] = *(pBmpData + i * lineByte + j - 1);
			g[1] = *(pBmpData + i * lineByte + j);
			g[2] = *(pBmpData + i * lineByte + j + 1);
			sort(g, g + 3);   //����
			*(pNewBmpData + i * lineByte + j) = g[1];
		}
	}
}
/**
* ������: writeBmp
* ��  ��: �½�һ��bmp�ļ�,��ƽ�ƺ��ͼ����Ϣд�룬����һ���µ�bmp
*/
void writeBmp()
{
	char writeBmpName[] = "new.bmp";
	FILE *fp = fopen(writeBmpName, "wb");   //�Զ�����д��ʽ��ָ����ͼ���ļ�
	if (NULL == fp)
	{
		cout << "file not exist!";
		return;
	}
	//д��BMP�ļ�����
	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(pColorTable, sizeof(RGBQUAD), 256, fp);
	fwrite(pNewBmpData, sizeof(char), imgSize, fp);
	fclose(fp);
	//�ͷ��ڴ�
	delete[]pColorTable;
	delete[]pNewBmpData;
	delete[]pBmpData;


}
/**
* ������: work
* ��  ��: ����
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