/**
* ������: WorkBmp.cpp
* ��  ��: ��ȡ����ʾ24λBMPͼ��,����ͼ���������뵽ImageData.txt��
* 24λbmp����ͨ����ͼ�����е����Ϊ���ļ������п���ѡ��
* bmp�ļ��ŵ�����Ŀ¼��
*/
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <fstream>
using namespace std;
int biWidth;  //ͼ���
int biHeight;  //ͼ���
int biBitCount; //ͼ�����ͣ�ÿ����λ��
//RGBQUAD *pColorTable;  //��ɫ��ָ��
unsigned char *pBmpBuf;  //�洢ͼ������
int lineByte;         //ͼ������ÿ���ֽ���
/**
* ������: readBmp
* ��  ��: bmpName -- bmp�ļ���
* ��  ��: ����bmp�ļ�������ȡ��Ӧ����Ϣ
*/
bool readBmp(char *bmpName)
{
	FILE *fp;
	if ((fp = fopen(bmpName, "rb")) == NULL)  //�Զ����Ƶķ�ʽ���ļ�
	{
		cout << "The file " << bmpName << "was not opened" << endl;
		return FALSE;
	}
	if (fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_CUR))  //����BITMAPFILEHEADE
	{
		cout << "��תʧ��" << endl;
		return FALSE;
	}
	BITMAPINFOHEADER infoHead;
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);   //��fp�ж�ȡBITMAPINFOHEADER��Ϣ��infoHead��,ͬʱfp��ָ���ƶ�
	biWidth = infoHead.biWidth;
	biHeight = infoHead.biHeight;
	biBitCount = infoHead.biBitCount;
	lineByte = (biWidth*biBitCount / 8 + 3) / 4 * 4;   //lineByte����Ϊ4�ı���
	//24λbmpû����ɫ�����Ծ�ֱ�ӵ���ʵ�ʵ�λͼ���ݵ���ʼλ��
	pBmpBuf = new unsigned char[lineByte * biHeight];
	fread(pBmpBuf, sizeof(char), lineByte * biHeight, fp);
	fclose(fp);   //�ر��ļ�
	return TRUE;

}
/**
* ������: saveBmp
* ��  ��: bmpName -- bmp�ļ���
* ��  ��: ��bmpλͼ�ļ��������Ϣ��д���´������ļ���
*/
bool saveBmp(char *bmpName)
{
	FILE *fp;
	if ((fp = fopen(bmpName, "wb")) == NULL)   //�Զ�����д�뷽ʽ��
	{
		cout << "��ʧ��!" << endl;
		return FALSE;
	}
	//����BITMAPFILEHEADER����
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42;
	fileHead.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+lineByte * biHeight;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	//����BITMAPINFOHEADER����
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
	//д��
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(pBmpBuf, sizeof(char), lineByte * biHeight, fp);
	fclose(fp);    //�ر��ļ�
	return TRUE;


}
/**
* ������: work
* ��  ��: ����λͼ��Ϣ������λͼ���ݱ��浽ImageData�ļ���
*/
void work()
{
	char readFileName[] = "nv.BMP";   //����Ҫ������ļ���
	if (FALSE == readBmp(readFileName))
		cout << "readfile error!" << endl;
	//���ͼ�����Ϣ
	cout << "Width = " << biWidth << " Height = " << biHeight << " biBitCount=" << biBitCount << endl;
	ofstream outfile("ImageData.txt", ios::in | ios::trunc);
	if (!outfile)
	{
		cout << "open error" << endl;
		return;
	}
	int count = 0;
	//ͼ��������Ϣ�Ǵ����½ǰ��п�ʼ�洢��
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
	cout << "�ܵ�������:" << count / 3 << endl;

	char writeBmpName[] = "nvcpy.BMP";
	saveBmp(writeBmpName);
	delete[]pBmpBuf;  //�ͷ��ڴ�
}

int main()
{
	work();
	return 0;
}