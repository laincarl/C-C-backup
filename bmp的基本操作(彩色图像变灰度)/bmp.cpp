#include"windows.h"//����λͼ�ļ����ļ�ͷ����Ϣͷ����Ϣ
#include"stdio.h"
//���弸��ȫ�ֵı���
unsigned char *pBmpBuf;//����ͼ�����ݵ�ָ��
int bmpWidth;//ͼ��Ŀ�
int bmpHeight;//ͼ��ĸ�
int bmpclrused;//ʵ��ʹ�õ���ɫ��

RGBQUAD *pColorTable;//��ɫ��ָ��
int biBitCount;//ÿ�����ص�λ�� 


//readBmp()�������ڶ�ȡλͼ����
bool readBmp(char *bmpName)
{

	FILE *fp;//�����Ʒ�ʽ���ƶ���ͼ���ļ�
	BITMAPINFOHEADER head;
	int lineByte;
	fp=fopen(bmpName,"rb");
	if(fp==0) 
		return 0;
	//����λͼ���ļ�ͷ
	fseek(fp,sizeof(BITMAPFILEHEADER),0);
	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head֮��
    
	fread(&head,sizeof(BITMAPINFOHEADER),1,fp);
	//��ȡͼ��ߣ���ÿ��������ռ��λ����Ϣ
	bmpWidth=head.biWidth;
	bmpHeight=head.biHeight;
	biBitCount=head.biBitCount;
	bmpclrused=head.biClrUsed;
	//�������������ͼ��ÿ��������ռ���ֽ���
	lineByte=(bmpWidth * biBitCount/8+3)/4*4;
	//�Ҷ�ͼ��
	if(biBitCount==8)
	{
		pColorTable=new RGBQUAD[256];
		fread(pColorTable,sizeof(RGBQUAD),256,fp);
	}
	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	pBmpBuf=new unsigned char[lineByte*bmpHeight];
	//��������
	fread(pBmpBuf,1,lineByte*bmpHeight,fp);
	fclose(fp);
	return 1;
}

//bmp�ļ��Ĵ����ú���savebmp()
//char *bmpName�ļ����ּ�·��
//unsigned char *imgBuf�����̵���ͼ����
//int wedth������Ϊ��λ������λͼ�Ŀ�
//int height
//int biBitCountÿ������ռ��λ��
//RGBQUAD *pColorTable��ɫ��ָ��
//����ֵ0Ϊʧ�ܣ�1Ϊ�ɹ�
bool saveBmp(char *bmpName,unsigned char *imgBuf,int width,int height,int biBitCount,RGBQUAD *pColorTable)
{
	if(!imgBuf)
		return 0;//λͼ����ָ��Ϊ0����û�����ݴ���
	int colorTablesize=0;//��ɫ��Ĵ�С
	if(biBitCount==8)
		colorTablesize=1024;//�Ҷ�ͼ����ɫ���СΪ1024
	int lineByte=(width*biBitCount/8+3)/4*4;//ÿ����ռ���ֽ���
	//�Զ����Ʒ�ʽ���ļ�
	FILE *fp=fopen(bmpName,"wb");
	if(fp==0) return 0;
	//����λͼ�ļ�ͷ�ṹ��������д�ļ�ͷ��Ϣ
	BITMAPFILEHEADER fileHead;
	fileHead.bfType=0x4D42;//bmp������
	fileHead.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTablesize+lineByte*height;
	fileHead.bfReserved1=0;
	fileHead.bfReserved2=0;
	//bfOffBits��ͼ���ļ�ǰ������������Ҫ�Ŀռ��
	fileHead.bfOffBits=54+colorTablesize;
	//д�ļ�ͷ���ļ�
	fwrite(&fileHead,sizeof(BITMAPFILEHEADER),1,fp);
	//����λͼ��Ϣͷ�ṹ��������д��Ϣͷ��Ϣ
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
	//дλͼ��Ϣͷ���ڴ�
	fwrite(&head,sizeof(BITMAPINFOHEADER),1,fp);
	//����ǻҶ�ͼ������ɫ����Ҫд���ļ�
	if(biBitCount==8)
		fwrite(pColorTable,sizeof(RGBQUAD),256,fp);
	//дλͼ���ݽ��ļ�
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

	//���ͼ��
	printf("width=%d\nheight=%d\nbiBitCount=%d\n",bmpWidth,bmpHeight,biBitCount);
	printf("biclrused=%d\n",bmpclrused);
	//ѭ������i��jͼ�������
	int i,j;
	//ÿ���ֽ���
	int lineByte=(bmpWidth*biBitCount/8+3)/4*4;
    //��ͼ�����ݴ���
	int k;//��ͼ��Ϊ��ɫͼ��ʱ������ÿ�����ص���������
	//��ͼ�����½�1��4�����óɺ�ɫ
	if(biBitCount==8)//�Ҷ�ͼ��
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
	//Ϊ24λͼʱ��ת��Ϊ�Ҷ�ͼ��
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
	//�ı�Ҷ�ͼ�����ɫ����ɫ������ֵ
	//256ɫͼ��
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
	char writepath[]="256ɫȨֵ�Ҷ�.bmp";
	saveBmp(writepath,pBmpBuf,bmpWidth,bmpHeight,biBitCount,pColorTable);
	//�������ȥ��pBmpBuf��pColorTable��ȫ�ֱ��������ļ�����ʱ����Ŀռ�
	delete []pBmpBuf;
	if(biBitCount==8)
		delete []pColorTable;
}
