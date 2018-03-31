#include <dos.h> /*DOS�ӿں���*/
#include <math.h> /*��ѧ�����Ķ���*/
#include <conio.h> /*��Ļ��������*/
#include <stdio.h> /*I/O����*/
#include <stdlib.h> /*�⺯��*/
#include <stdarg.h> /*�������Ȳ�����*/
#include <graphics.h> /*ͼ�κ���*/
#include <string.h> /*�ַ�������*/
#include <ctype.h> /*�ַ���������*/
#define UP 0x48 /*������Ƽ�*/
#define DOWN 0x50 /*������Ƽ�*/
#define LEFT 0x4b /*������Ƽ�*/
#define RIGHT 0x4d /*������Ƽ�*/
#define ENTER 0x0d /*�س���*/
void *rar; /*ȫ�ֱ�����������ͼ��*/
struct palettetype palette; /*ʹ�õ�ɫ����Ϣ*/
int GraphDriver; /* ͼ���豸����*/
int GraphMode; /* ͼ��ģʽֵ*/
int ErrorCode; /* �������*/
int MaxColors; /* ������ɫ�������ֵ*/
int MaxX, MaxY; /* ��Ļ�����ֱ���*/
double AspectRatio; /* ��Ļ�����ر�*/
void drawboder(void); /*���߿���*/
void initialize(void); /*��ʼ������*/
void computer(void); /*���������㺯��*/
void changetextstyle(int font, int direction, int charsize); /*�ı��ı���ʽ����*/
void mwindow(char *header); /*���ں���*/
int specialkey(void); /*��ȡ���������*/
int arrow(); /*���ü�ͷ��꺯��*/
/*������*/
int main()
{
	initialize();/* ����ϵͳ����ͼ��ģʽ */
	computer(); /*���м����� */
	closegraph();/*ϵͳ�ر�ͼ��ģʽ�����ı�ģʽ*/
	return(0); /*��������*/
}
/* ����ϵͳ����ͼ��ģʽ */
void initialize(void)
{
	int xasp, yasp; /* ���ڶ�x��y�����ݺ��*/
	GraphDriver = DETECT; /* �Զ������ʾ��*/
	initgraph(&GraphDriver, &GraphMode, "");
	/*��ʼ��ͼ��ϵͳ*/
	ErrorCode = graphresult(); /*����ʼ�����*/
	if (ErrorCode != grOk) /*�����ʼ��ʱ���ִ���*/
	{
		printf("Graphics System Error: %s\n",
			grapherrormsg(ErrorCode)); /*��ʾ�������*/
		exit(1); /*�˳�*/
	}
	getpalette(&palette); /* �������Ϣ*/
	MaxColors = getmaxcolor() + 1; /* ��ȡ��ɫ�����ֵ*/
	MaxX = getmaxx(); /* ����Ļ�ߴ� */
	MaxY = getmaxy(); /* ����Ļ�ߴ� */
	getaspectratio(&xasp, &yasp); /* �����ݺ�ȵ�������*/
	AspectRatio = (double)xasp / (double)yasp;/* �����ݺ��ֵ*/
}
/*����������*/
void computer(void)
{
	struct viewporttype vp; /*�����ӿ����ͱ���*/
	int color, height, width;
	int x, y, x0, y0, i, j, v, m, n, act, flag = 1;
	float num1 = 0, num2 = 0, result; /*�������ͼ���������*/
	char cnum[5], str2[20] = { "" }, c, temp[20] = { "" };
	char str1[] = "1230.456+-789*/Qc=^%";/* �����ַ����ڰ�ťͼ������ʾ�ķ��� */
	mwindow("Calculator"); /* ��ʾ������ */
	color = 7; /*���û���ɫֵ*/
	getviewsettings(&vp); /* ��ȡ��ǰ���ڵĴ�С*/
	width = (vp.right + 1) / 10; /* ���ð�ť��� */
	height = (vp.bottom - 10) / 10; /*���ð�ť�߶� */
	x = width / 2; /*����x������ֵ*/
	y = height / 2; /*����y������ֵ*/
	setfillstyle(SOLID_FILL, color + 3);
	bar(x + width * 2, y, x + 7 * width, y + height);
	/*��һ����ά��������ʾ�������ͽ��*/
	setcolor(color + 3); /*���õ�����ɫ�߿���*/
	rectangle(x + width * 2, y, x + 7 * width, y + height);
	/*��һ�����α߿���*/
	setcolor(RED); /*������ɫΪ��ɫ*/
	outtextxy(x + 3 * width, y + height / 2, "0."); /*����ַ���"0."*/
	x = 2 * width - width / 2; /*����x������ֵ*/
	y = 2 * height + height / 2; /*����y������ֵ*/
	for (j = 0; j<4; ++j) /*����ť*/
	{
		for (i = 0; i<5; ++i)
		{
			setfillstyle(SOLID_FILL, color);
			setcolor(RED);
			bar(x, y, x + width, y + height); /*��һ��������*/
			rectangle(x, y, x + width, y + height);
			sprintf(str2, "%c", str1[j * 5 + i]);
			/*���ַ����浽str2��*/
			outtextxy(x + (width / 2), y + height / 2, str2);
			x = x + width + (width / 2); /*�ƶ�������*/
		}
		y += (height / 2) * 3; /* �ƶ�������*/
		x = 2 * width - width / 2; /*��λ������*/
	}
	x0 = 2 * width;
	y0 = 3 * height;
	x = x0;
	y = y0;
	gotoxy(x, y); /*�ƶ���굽x,yλ��*/
	arrow(); /*��ʾ���*/
	putimage(x, y, rar, XOR_PUT);
	m = 0;
	n = 0;
	strcpy(str2, ""); /*����str2Ϊ�մ�*/
	while ((v = specialkey()) != 45) /*��ѹ��Alt+x���������򣬷���ִ�������ѭ��*/
	{
		while ((v = specialkey()) != ENTER) /*��ѹ�¼����ǻس�ʱ*/
		{
			putimage(x, y, rar, XOR_PUT); /*��ʾ���ͼ��*/
			if (v == RIGHT) /*���Ƽ�ͷʱ��λ�ü���*/
			if (x >= x0 + 6 * width)
				/*������ƣ��Ƶ�β�����ƶ���������ַ�λ��*/
			{
				x = x0;
				m = 0;
			}
			else
			{
				x = x + width + width / 2;
				m++;
			} /*�������Ƶ���һ���ַ�λ��*/
			if (v == LEFT) /*���Ƽ�ͷʱ��λ�ü���*/
			if (x <= x0)
			{
				x = x0 + 6 * width;
				m = 4;
			} /*����Ƶ�ͷ�������ƣ����ƶ������ұ��ַ�λ��*/
			else
			{
				x = x - width - width / 2;
				m--;
			} /*�������Ƶ�ǰһ���ַ�λ��*/
			if (v == UP) /*���Ƽ�ͷʱ��λ�ü���*/
			if (y <= y0)
			{
				y = y0 + 4 * height + height / 2;
				n = 3;
			} /*����Ƶ�ͷ�������ƣ����ƶ������±��ַ�λ��*/
			else
			{
				y = y - height - height / 2;
				n--;
			} /*�����Ƶ��ϱ�һ���ַ�λ��*/
			if (v == DOWN) /*���Ƽ�ͷʱ��λ�ü���*/
			if (y >= 7 * height)
			{
				y = y0;
				n = 0;
			} /*����Ƶ�β�������ƣ����ƶ������ϱ��ַ�λ��*/
			else
			{
				y = y + height + height / 2;
				n++;
			} /*�����Ƶ��±�һ���ַ�λ��*/
			putimage(x, y, rar, XOR_PUT); /*���µ�λ����ʾ����ͷ*/
		}
		c = str1[n * 5 + m]; /*���ַ����浽����c��*/
		if (isdigit(c) || c == '.') /*�ж��Ƿ������ֻ�С����*/
		{
			if (flag == -1) /*�����־Ϊ-1������Ϊ����*/
			{
				strcpy(str2, "-"); /*���������ӵ��ַ�����*/
				flag = 1;
			} /*����־ֵ�ָ�Ϊ1*/
			sprintf(temp, "%c", c); /*���ַ����浽�ַ�������temp��*/
			strcat(str2, temp); /*��temp�е��ַ������ӵ�str2��*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, str2); /*��ʾ�ַ���*/
		}
		if (c == '+')
		{
			num1 = atof(str2); /*����һ��������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 1; /*������ӷ���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '-')
		{
			if (strcmp(str2, "") == 0) /*���str2Ϊ�գ�˵���Ǹ��ţ������Ǽ���*/
				flag = -1; /*���ø�����־*/
			else
			{
				num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
				strcpy(str2, ""); /*��str2���*/
				act = 2; /*�����������־ֵ*/
				setfillstyle(SOLID_FILL, color + 3);
				bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
				outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
			}
		}
		if (c == '*')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 3; /*������˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '/')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 4; /*�����������־ֵ*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '^')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 5; /*������˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '%')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 6; /*������ģ����˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '=')
		{
			num2 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			switch (act) /*����������ż���*/
			{
			case 1:result = num1 + num2; break; /*���ӷ�*/
			case 2:result = num1 - num2; break; /*������*/
			case 3:result = num1*num2; break; /*���˷�*/
			case 4:result = num1 / num2; break; /*������*/
			case 5:result = pow(num1, num2); break; /*��x��y�η�*/
			case 6:result = fmod(num1, num2); break; /*��ģ����*/
			}
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*���ǽ����*/
			sprintf(temp, "%f", result); /*��������浽temp��*/
			outtextxy(5 * width, height, temp); /*��ʾ���*/
		}
		if (c == 'c')
		{
			num1 = 0; /*��������������λ0�����ű�־Ϊ1*/
			num2 = 0;
			flag = 1;
			strcpy(str2, ""); /*��str2���*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*���ǽ����*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == 'Q')exit(0); /*���ѡ����q�س��������������*/
	}
	putimage(x, y, rar, XOR_PUT); /*���˳�֮ǰ��ȥ����ͷ*/
	return; /*����*/
}
/*���ں���*/
void mwindow(char *header)
{
	int height;
	cleardevice(); /* ���ͼ����Ļ */
	setcolor(MaxColors - 1); /* ���õ�ǰ��ɫΪ��ɫ*/
	setviewport(20, 20, MaxX / 2, MaxY / 2, 1); /* �����ӿڴ�С */
	height = textheight("H"); /* ��ȡ�����ı���С */
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);/*�����ı���ʽ*/
	settextjustify(CENTER_TEXT, TOP_TEXT);/*�����ַ����з�ʽ*/
	outtextxy(MaxX / 4, 2, header); /*�������*/
	setviewport(20, 20 + height + 4, MaxX / 2 + 4, MaxY / 2 + 20, 1); /*�����ӿڴ�С*/
	drawboder(); /*���߿�*/
}
void drawboder(void) /*���߿�*/
{
	struct viewporttype vp; /*�����ӿ����ͱ���*/
	setcolor(MaxColors - 1); /*���õ�ǰ��ɫΪ��ɫ */
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);/*���û��߷�ʽ*/
	getviewsettings(&vp);/*����ǰ�ӿ���Ϣװ��vp��ָ�Ľṹ��*/
	rectangle(0, 0, vp.right - vp.left, vp.bottom - vp.top); /*�����α߿�*/
}
/*������ͼ�κ���*/
int arrow()
{
	int size;
	int raw[] = { 4, 4, 4, 8, 6, 8, 14, 16, 16, 16, 8, 6, 8, 4, 4, 4 }; /*������������*/
	setfillstyle(SOLID_FILL, 2); /*�������ģʽ*/
	fillpoly(8, raw); /*����һ����ͷ*/
	size = imagesize(4, 4, 16, 16); /*����ͼ���С*/
	rar = malloc(size); /*�����ڴ�����*/
	getimage(4, 4, 16, 16, rar); /*��Ź���ͷͼ��*/
	putimage(4, 4, rar, XOR_PUT); /*��ȥ����ͷͼ��*/
	return 0;
}
/*��������*/
int specialkey(void)
{
	int key;
	while (bioskey(1) == 0); /*�ȴ���������*/
	key = bioskey(0); /*��������*/
	key = key & 0xff ? key & 0xff : key >> 8; /*ֻȡ�������ɨ��ֵ������Ϊ0*/
	return(key); /*���ؼ�ֵ*/
}




��TC�����С�����������������Ŷ
���䣺 #include <dos.h> /*DOS�ӿں���*/
#include <math.h> /*��ѧ�����Ķ���*/
#include <conio.h> /*��Ļ��������*/
#include <stdio.h> /*I/O����*/
#include <stdlib.h> /*�⺯��*/
#include <stdarg.h> /*�������Ȳ�����*/
#include <graphics.h> /*ͼ�κ���*/
#include <string.h> /*�ַ�������*/
#include <ctype.h> /*�ַ���������*/
#define UP 0x48 /*������Ƽ�*/
#define DOWN 0x50 /*������Ƽ�*/
#define LEFT 0x4b /*������Ƽ�*/
#define RIGHT 0x4d /*������Ƽ�*/
#define ENTER 0x0d /*�س���*/
void *rar; /*ȫ�ֱ�����������ͼ��*/
struct palettetype palette; /*ʹ�õ�ɫ����Ϣ*/
int GraphDriver; /* ͼ���豸����*/
int GraphMode; /* ͼ��ģʽֵ*/
int ErrorCode; /* �������*/
int MaxColors; /* ������ɫ�������ֵ*/
int MaxX, MaxY; /* ��Ļ�����ֱ���*/
double AspectRatio; /* ��Ļ�����ر�*/
void drawboder(void); /*���߿���*/
void initialize(void); /*��ʼ������*/
void computer(void); /*���������㺯��*/
void changetextstyle(int font, int direction, int charsize); /*�ı��ı���ʽ����*/
void mwindow(char *header); /*���ں���*/
int specialkey(void); /*��ȡ���������*/
int arrow(); /*���ü�ͷ��꺯��*/
/*������*/
int main()
{
	initialize();/* ����ϵͳ����ͼ��ģʽ */
	computer(); /*���м����� */
	closegraph();/*ϵͳ�ر�ͼ��ģʽ�����ı�ģʽ*/
	return(0); /*��������*/
}
/* ����ϵͳ����ͼ��ģʽ */
void initialize(void)
{
	int xasp, yasp; /* ���ڶ�x��y�����ݺ��*/
	GraphDriver = DETECT; /* �Զ������ʾ��*/
	initgraph(&GraphDriver, &GraphMode, "");
	/*��ʼ��ͼ��ϵͳ*/
	ErrorCode = graphresult(); /*����ʼ�����*/
	if (ErrorCode != grOk) /*�����ʼ��ʱ���ִ���*/
	{
		printf("Graphics System Error: %s\n",
			grapherrormsg(ErrorCode)); /*��ʾ�������*/
		exit(1); /*�˳�*/
	}
	getpalette(&palette); /* �������Ϣ*/
	MaxColors = getmaxcolor() + 1; /* ��ȡ��ɫ�����ֵ*/
	MaxX = getmaxx(); /* ����Ļ�ߴ� */
	MaxY = getmaxy(); /* ����Ļ�ߴ� */
	getaspectratio(&xasp, &yasp); /* �����ݺ�ȵ�������*/
	AspectRatio = (double)xasp / (double)yasp;/* �����ݺ��ֵ*/
}
/*����������*/
void computer(void)
{
	struct viewporttype vp; /*�����ӿ����ͱ���*/
	int color, height, width;
	int x, y, x0, y0, i, j, v, m, n, act, flag = 1;
	float num1 = 0, num2 = 0, result; /*�������ͼ���������*/
	char cnum[5], str2[20] = { "" }, c, temp[20] = { "" };
	char str1[] = "1230.456+-789*/Qc=^%";/* �����ַ����ڰ�ťͼ������ʾ�ķ��� */
	mwindow("Calculator"); /* ��ʾ������ */
	color = 7; /*���û���ɫֵ*/
	getviewsettings(&vp); /* ��ȡ��ǰ���ڵĴ�С*/
	width = (vp.right + 1) / 10; /* ���ð�ť��� */
	height = (vp.bottom - 10) / 10; /*���ð�ť�߶� */
	x = width / 2; /*����x������ֵ*/
	y = height / 2; /*����y������ֵ*/
	setfillstyle(SOLID_FILL, color + 3);
	bar(x + width * 2, y, x + 7 * width, y + height);
	/*��һ����ά��������ʾ�������ͽ��*/
	setcolor(color + 3); /*���õ�����ɫ�߿���*/
	rectangle(x + width * 2, y, x + 7 * width, y + height);
	/*��һ�����α߿���*/
	setcolor(RED); /*������ɫΪ��ɫ*/
	outtextxy(x + 3 * width, y + height / 2, "0."); /*����ַ���"0."*/
	x = 2 * width - width / 2; /*����x������ֵ*/
	y = 2 * height + height / 2; /*����y������ֵ*/
	for (j = 0; j<4; ++j) /*����ť*/
	{
		for (i = 0; i<5; ++i)
		{
			setfillstyle(SOLID_FILL, color);
			setcolor(RED);
			bar(x, y, x + width, y + height); /*��һ��������*/
			rectangle(x, y, x + width, y + height);
			sprintf(str2, "%c", str1[j * 5 + i]);
			/*���ַ����浽str2��*/
			outtextxy(x + (width / 2), y + height / 2, str2);
			x = x + width + (width / 2); /*�ƶ�������*/
		}
		y += (height / 2) * 3; /* �ƶ�������*/
		x = 2 * width - width / 2; /*��λ������*/
	}
	x0 = 2 * width;
	y0 = 3 * height;
	x = x0;
	y = y0;
	gotoxy(x, y); /*�ƶ���굽x,yλ��*/
	arrow(); /*��ʾ���*/
	putimage(x, y, rar, XOR_PUT);
	m = 0;
	n = 0;
	strcpy(str2, ""); /*����str2Ϊ�մ�*/
	while ((v = specialkey()) != 45) /*��ѹ��Alt+x���������򣬷���ִ�������ѭ��*/
	{
		while ((v = specialkey()) != ENTER) /*��ѹ�¼����ǻس�ʱ*/
		{
			putimage(x, y, rar, XOR_PUT); /*��ʾ���ͼ��*/
			if (v == RIGHT) /*���Ƽ�ͷʱ��λ�ü���*/
			if (x >= x0 + 6 * width)
				/*������ƣ��Ƶ�β�����ƶ���������ַ�λ��*/
			{
				x = x0;
				m = 0;
			}
			else
			{
				x = x + width + width / 2;
				m++;
			} /*�������Ƶ���һ���ַ�λ��*/
			if (v == LEFT) /*���Ƽ�ͷʱ��λ�ü���*/
			if (x <= x0)
			{
				x = x0 + 6 * width;
				m = 4;
			} /*����Ƶ�ͷ�������ƣ����ƶ������ұ��ַ�λ��*/
			else
			{
				x = x - width - width / 2;
				m--;
			} /*�������Ƶ�ǰһ���ַ�λ��*/
			if (v == UP) /*���Ƽ�ͷʱ��λ�ü���*/
			if (y <= y0)
			{
				y = y0 + 4 * height + height / 2;
				n = 3;
			} /*����Ƶ�ͷ�������ƣ����ƶ������±��ַ�λ��*/
			else
			{
				y = y - height - height / 2;
				n--;
			} /*�����Ƶ��ϱ�һ���ַ�λ��*/
			if (v == DOWN) /*���Ƽ�ͷʱ��λ�ü���*/
			if (y >= 7 * height)
			{
				y = y0;
				n = 0;
			} /*����Ƶ�β�������ƣ����ƶ������ϱ��ַ�λ��*/
			else
			{
				y = y + height + height / 2;
				n++;
			} /*�����Ƶ��±�һ���ַ�λ��*/
			putimage(x, y, rar, XOR_PUT); /*���µ�λ����ʾ����ͷ*/
		}
		c = str1[n * 5 + m]; /*���ַ����浽����c��*/
		if (isdigit(c) || c == '.') /*�ж��Ƿ������ֻ�С����*/
		{
			if (flag == -1) /*�����־Ϊ-1������Ϊ����*/
			{
				strcpy(str2, "-"); /*���������ӵ��ַ�����*/
				flag = 1;
			} /*����־ֵ�ָ�Ϊ1*/
			sprintf(temp, "%c", c); /*���ַ����浽�ַ�������temp��*/
			strcat(str2, temp); /*��temp�е��ַ������ӵ�str2��*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, str2); /*��ʾ�ַ���*/
		}
		if (c == '+')
		{
			num1 = atof(str2); /*����һ��������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 1; /*������ӷ���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '-')
		{
			if (strcmp(str2, "") == 0) /*���str2Ϊ�գ�˵���Ǹ��ţ������Ǽ���*/
				flag = -1; /*���ø�����־*/
			else
			{
				num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
				strcpy(str2, ""); /*��str2���*/
				act = 2; /*�����������־ֵ*/
				setfillstyle(SOLID_FILL, color + 3);
				bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
				outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
			}
		}
		if (c == '*')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 3; /*������˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '/')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 4; /*�����������־ֵ*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '^')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 5; /*������˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '%')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 6; /*������ģ����˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '=')
		{
			num2 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			switch (act) /*����������ż���*/
			{
			case 1:result = num1 + num2; break; /*���ӷ�*/
			case 2:result = num1 - num2; break; /*������*/
			case 3:result = num1*num2; break; /*���˷�*/
			case 4:result = num1 / num2; break; /*������*/
			case 5:result = pow(num1, num2); break; /*��x��y�η�*/
			case 6:result = fmod(num1, num2); break; /*��ģ����*/
			}
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*���ǽ����*/
			sprintf(temp, "%f", result); /*��������浽temp��*/
			outtextxy(5 * width, height, temp); /*��ʾ���*/
		}
		if (c == 'c')
		{
			num1 = 0; /*��������������λ0�����ű�־Ϊ1*/
			num2 = 0;
			flag = 1;
			strcpy(str2, ""); /*��str2���*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*���ǽ����*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == 'Q')exit(0); /*���ѡ����q�س��������������*/
	}
	putimage(x, y, rar, XOR_PUT); /*���˳�֮ǰ��ȥ����ͷ*/
	return; /*����*/
}
/*���ں���*/
void mwindow(char *header)
{
	int height;
	cleardevice(); /* ���ͼ����Ļ */
	setcolor(MaxColors - 1); /* ���õ�ǰ��ɫΪ��ɫ*/
	setviewport(20, 20, MaxX / 2, MaxY / 2, 1); /* �����ӿڴ�С */
	height = textheight("H"); /* ��ȡ�����ı���С */
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);/*�����ı���ʽ*/
	settextjustify(CENTER_TEXT, TOP_TEXT);/*�����ַ����з�ʽ*/
	outtextxy(MaxX / 4, 2, header); /*�������*/
	setviewport(20, 20 + height + 4, MaxX / 2 + 4, MaxY / 2 + 20, 1); /*�����ӿڴ�С*/
	drawboder(); /*���߿�*/
}
void drawboder(void) /*���߿�*/
{
	struct viewporttype vp; /*�����ӿ����ͱ���*/
	setcolor(MaxColors - 1); /*���õ�ǰ��ɫΪ��ɫ */
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);/*���û��߷�ʽ*/
	getviewsettings(&vp);/*����ǰ�ӿ���Ϣװ��vp��ָ�Ľṹ��*/
	rectangle(0, 0, vp.right - vp.left, vp.bottom - vp.top); /*�����α߿�*/
}
/*������ͼ�κ���*/
int arrow()
{
	int size;
	int raw[] = { 4, 4, 4, 8, 6, 8, 14, 16, 16, 16, 8, 6, 8, 4, 4, 4 }; /*������������*/
	setfillstyle(SOLID_FILL, 2); /*�������ģʽ*/
	fillpoly(8, raw); /*����һ����ͷ*/
	size = imagesize(4, 4, 16, 16); /*����ͼ���С*/
	rar = malloc(size); /*�����ڴ�����*/
	getimage(4, 4, 16, 16, rar); /*��Ź���ͷͼ��*/
	putimage(4, 4, rar, XOR_PUT); /*��ȥ����ͷͼ��*/
	return 0;
}
/*��������*/
int specialkey(void)
{
	int key;
	while (bioskey(1) == 0); /*�ȴ���������*/
	key = bioskey(0); /*��������*/
	key = key & 0xff ? key & 0xff : key >> 8; /*ֻȡ�������ɨ��ֵ������Ϊ0*/
	return(key); /*���ؼ�ֵ*/
}



��TC���У������ɣ�
���䣺 #include <dos.h> /*DOS�ӿں���*/
#include <math.h> /*��ѧ�����Ķ���*/
#include <conio.h> /*��Ļ��������*/
#include <stdio.h> /*I/O����*/
#include <stdlib.h> /*�⺯��*/
#include <stdarg.h> /*�������Ȳ�����*/
#include <graphics.h> /*ͼ�κ���*/
#include <string.h> /*�ַ�������*/
#include <ctype.h> /*�ַ���������*/
#define UP 0x48 /*������Ƽ�*/
#define DOWN 0x50 /*������Ƽ�*/
#define LEFT 0x4b /*������Ƽ�*/
#define RIGHT 0x4d /*������Ƽ�*/
#define ENTER 0x0d /*�س���*/
void *rar; /*ȫ�ֱ�����������ͼ��*/
struct palettetype palette; /*ʹ�õ�ɫ����Ϣ*/
int GraphDriver; /* ͼ���豸����*/
int GraphMode; /* ͼ��ģʽֵ*/
int ErrorCode; /* �������*/
int MaxColors; /* ������ɫ�������ֵ*/
int MaxX, MaxY; /* ��Ļ�����ֱ���*/
double AspectRatio; /* ��Ļ�����ر�*/
void drawboder(void); /*���߿���*/
void initialize(void); /*��ʼ������*/
void computer(void); /*���������㺯��*/
void changetextstyle(int font, int direction, int charsize); /*�ı��ı���ʽ����*/
void mwindow(char *header); /*���ں���*/
int specialkey(void); /*��ȡ���������*/
int arrow(); /*���ü�ͷ��꺯��*/
/*������*/
int main()
{
	initialize();/* ����ϵͳ����ͼ��ģʽ */
	computer(); /*���м����� */
	closegraph();/*ϵͳ�ر�ͼ��ģʽ�����ı�ģʽ*/
	return(0); /*��������*/
}
/* ����ϵͳ����ͼ��ģʽ */
void initialize(void)
{
	int xasp, yasp; /* ���ڶ�x��y�����ݺ��*/
	GraphDriver = DETECT; /* �Զ������ʾ��*/
	initgraph(&GraphDriver, &GraphMode, "");
	/*��ʼ��ͼ��ϵͳ*/
	ErrorCode = graphresult(); /*����ʼ�����*/
	if (ErrorCode != grOk) /*�����ʼ��ʱ���ִ���*/
	{
		printf("Graphics System Error: %s\n",
			grapherrormsg(ErrorCode)); /*��ʾ�������*/
		exit(1); /*�˳�*/
	}
	getpalette(&palette); /* �������Ϣ*/
	MaxColors = getmaxcolor() + 1; /* ��ȡ��ɫ�����ֵ*/
	MaxX = getmaxx(); /* ����Ļ�ߴ� */
	MaxY = getmaxy(); /* ����Ļ�ߴ� */
	getaspectratio(&xasp, &yasp); /* �����ݺ�ȵ�������*/
	AspectRatio = (double)xasp / (double)yasp;/* �����ݺ��ֵ*/
}
/*����������*/
void computer(void)
{
	struct viewporttype vp; /*�����ӿ����ͱ���*/
	int color, height, width;
	int x, y, x0, y0, i, j, v, m, n, act, flag = 1;
	float num1 = 0, num2 = 0, result; /*�������ͼ���������*/
	char cnum[5], str2[20] = { "" }, c, temp[20] = { "" };
	char str1[] = "1230.456+-789*/Qc=^%";/* �����ַ����ڰ�ťͼ������ʾ�ķ��� */
	mwindow("Calculator"); /* ��ʾ������ */
	color = 7; /*���û���ɫֵ*/
	getviewsettings(&vp); /* ��ȡ��ǰ���ڵĴ�С*/
	width = (vp.right + 1) / 10; /* ���ð�ť��� */
	height = (vp.bottom - 10) / 10; /*���ð�ť�߶� */
	x = width / 2; /*����x������ֵ*/
	y = height / 2; /*����y������ֵ*/
	setfillstyle(SOLID_FILL, color + 3);
	bar(x + width * 2, y, x + 7 * width, y + height);
	/*��һ����ά��������ʾ�������ͽ��*/
	setcolor(color + 3); /*���õ�����ɫ�߿���*/
	rectangle(x + width * 2, y, x + 7 * width, y + height);
	/*��һ�����α߿���*/
	setcolor(RED); /*������ɫΪ��ɫ*/
	outtextxy(x + 3 * width, y + height / 2, "0."); /*����ַ���"0."*/
	x = 2 * width - width / 2; /*����x������ֵ*/
	y = 2 * height + height / 2; /*����y������ֵ*/
	for (j = 0; j<4; ++j) /*����ť*/
	{
		for (i = 0; i<5; ++i)
		{
			setfillstyle(SOLID_FILL, color);
			setcolor(RED);
			bar(x, y, x + width, y + height); /*��һ��������*/
			rectangle(x, y, x + width, y + height);
			sprintf(str2, "%c", str1[j * 5 + i]);
			/*���ַ����浽str2��*/
			outtextxy(x + (width / 2), y + height / 2, str2);
			x = x + width + (width / 2); /*�ƶ�������*/
		}
		y += (height / 2) * 3; /* �ƶ�������*/
		x = 2 * width - width / 2; /*��λ������*/
	}
	x0 = 2 * width;
	y0 = 3 * height;
	x = x0;
	y = y0;
	gotoxy(x, y); /*�ƶ���굽x,yλ��*/
	arrow(); /*��ʾ���*/
	putimage(x, y, rar, XOR_PUT);
	m = 0;
	n = 0;
	strcpy(str2, ""); /*����str2Ϊ�մ�*/
	while ((v = specialkey()) != 45) /*��ѹ��Alt+x���������򣬷���ִ�������ѭ��*/
	{
		while ((v = specialkey()) != ENTER) /*��ѹ�¼����ǻس�ʱ*/
		{
			putimage(x, y, rar, XOR_PUT); /*��ʾ���ͼ��*/
			if (v == RIGHT) /*���Ƽ�ͷʱ��λ�ü���*/
			if (x >= x0 + 6 * width)
				/*������ƣ��Ƶ�β�����ƶ���������ַ�λ��*/
			{
				x = x0;
				m = 0;
			}
			else
			{
				x = x + width + width / 2;
				m++;
			} /*�������Ƶ���һ���ַ�λ��*/
			if (v == LEFT) /*���Ƽ�ͷʱ��λ�ü���*/
			if (x <= x0)
			{
				x = x0 + 6 * width;
				m = 4;
			} /*����Ƶ�ͷ�������ƣ����ƶ������ұ��ַ�λ��*/
			else
			{
				x = x - width - width / 2;
				m--;
			} /*�������Ƶ�ǰһ���ַ�λ��*/
			if (v == UP) /*���Ƽ�ͷʱ��λ�ü���*/
			if (y <= y0)
			{
				y = y0 + 4 * height + height / 2;
				n = 3;
			} /*����Ƶ�ͷ�������ƣ����ƶ������±��ַ�λ��*/
			else
			{
				y = y - height - height / 2;
				n--;
			} /*�����Ƶ��ϱ�һ���ַ�λ��*/
			if (v == DOWN) /*���Ƽ�ͷʱ��λ�ü���*/
			if (y >= 7 * height)
			{
				y = y0;
				n = 0;
			} /*����Ƶ�β�������ƣ����ƶ������ϱ��ַ�λ��*/
			else
			{
				y = y + height + height / 2;
				n++;
			} /*�����Ƶ��±�һ���ַ�λ��*/
			putimage(x, y, rar, XOR_PUT); /*���µ�λ����ʾ����ͷ*/
		}
		c = str1[n * 5 + m]; /*���ַ����浽����c��*/
		if (isdigit(c) || c == '.') /*�ж��Ƿ������ֻ�С����*/
		{
			if (flag == -1) /*�����־Ϊ-1������Ϊ����*/
			{
				strcpy(str2, "-"); /*���������ӵ��ַ�����*/
				flag = 1;
			} /*����־ֵ�ָ�Ϊ1*/
			sprintf(temp, "%c", c); /*���ַ����浽�ַ�������temp��*/
			strcat(str2, temp); /*��temp�е��ַ������ӵ�str2��*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, str2); /*��ʾ�ַ���*/
		}
		if (c == '+')
		{
			num1 = atof(str2); /*����һ��������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 1; /*������ӷ���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '-')
		{
			if (strcmp(str2, "") == 0) /*���str2Ϊ�գ�˵���Ǹ��ţ������Ǽ���*/
				flag = -1; /*���ø�����־*/
			else
			{
				num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
				strcpy(str2, ""); /*��str2���*/
				act = 2; /*�����������־ֵ*/
				setfillstyle(SOLID_FILL, color + 3);
				bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
				outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
			}
		}
		if (c == '*')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 3; /*������˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '/')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 4; /*�����������־ֵ*/
			setfillstyle(SOLID_FILL, color + 3);
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2);
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '^')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 5; /*������˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '%')
		{
			num1 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			strcpy(str2, ""); /*��str2���*/
			act = 6; /*������ģ����˷���־ֵ*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*������*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == '=')
		{
			num2 = atof(str2); /*���ڶ���������ת��Ϊ������*/
			switch (act) /*����������ż���*/
			{
			case 1:result = num1 + num2; break; /*���ӷ�*/
			case 2:result = num1 - num2; break; /*������*/
			case 3:result = num1*num2; break; /*���˷�*/
			case 4:result = num1 / num2; break; /*������*/
			case 5:result = pow(num1, num2); break; /*��x��y�η�*/
			case 6:result = fmod(num1, num2); break; /*��ģ����*/
			}
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*���ǽ����*/
			sprintf(temp, "%f", result); /*��������浽temp��*/
			outtextxy(5 * width, height, temp); /*��ʾ���*/
		}
		if (c == 'c')
		{
			num1 = 0; /*��������������λ0�����ű�־Ϊ1*/
			num2 = 0;
			flag = 1;
			strcpy(str2, ""); /*��str2���*/
			setfillstyle(SOLID_FILL, color + 3); /*�����õ���ɫʵ�����*/
			bar(2 * width + width / 2, height / 2, 15 * width / 2, 3 * height / 2); /*���ǽ����*/
			outtextxy(5 * width, height, "0."); /*��ʾ�ַ���*/
		}
		if (c == 'Q')exit(0); /*���ѡ����q�س��������������*/
	}
	putimage(x, y, rar, XOR_PUT); /*���˳�֮ǰ��ȥ����ͷ*/
	return; /*����*/
}
/*���ں���*/
void mwindow(char *header)
{
	int height;
	cleardevice(); /* ���ͼ����Ļ */
	setcolor(MaxColors - 1); /* ���õ�ǰ��ɫΪ��ɫ*/
	setviewport(20, 20, MaxX / 2, MaxY / 2, 1); /* �����ӿڴ�С */
	height = textheight("H"); /* ��ȡ�����ı���С */
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);/*�����ı���ʽ*/
	settextjustify(CENTER_TEXT, TOP_TEXT);/*�����ַ����з�ʽ*/
	outtextxy(MaxX / 4, 2, header); /*�������*/
	setviewport(20, 20 + height + 4, MaxX / 2 + 4, MaxY / 2 + 20, 1); /*�����ӿڴ�С*/
	drawboder(); /*���߿�*/
}
void drawboder(void) /*���߿�*/
{
	struct viewporttype vp; /*�����ӿ����ͱ���*/
	setcolor(MaxColors - 1); /*���õ�ǰ��ɫΪ��ɫ */
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);/*���û��߷�ʽ*/
	getviewsettings(&vp);/*����ǰ�ӿ���Ϣװ��vp��ָ�Ľṹ��*/
	rectangle(0, 0, vp.right - vp.left, vp.bottom - vp.top); /*�����α߿�*/
}
/*������ͼ�κ���*/
int arrow()
{
	int size;
	int raw[] = { 4, 4, 4, 8, 6, 8, 14, 16, 16, 16, 8, 6, 8, 4, 4, 4 }; /*������������*/
	setfillstyle(SOLID_FILL, 2); /*�������ģʽ*/
	fillpoly(8, raw); /*����һ����ͷ*/
	size = imagesize(4, 4, 16, 16); /*����ͼ���С*/
	rar = malloc(size); /*�����ڴ�����*/
	getimage(4, 4, 16, 16, rar); /*��Ź���ͷͼ��*/
	putimage(4, 4, rar, XOR_PUT); /*��ȥ����ͷͼ��*/
	return 0;
}
/*��������*/
int specialkey(void)
{
	int key;
	while (bioskey(1) == 0); /*�ȴ���������*/
	key = bioskey(0); /*��������*/
	key = key & 0xff ? key & 0xff : key >> 8; /*ֻȡ�������ɨ��ֵ������Ϊ0*/
	return(key); /*���ؼ�ֵ*/
}

