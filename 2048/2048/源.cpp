#include <stdlib.h>
#include<stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
int map[4][4] = { 0 }; //2048��ͼ
int g_Score = 0; //�����Ϸ�ķ���
typedef struct _MYRECT
{
	short x;
	short y;
	short width;
	short height;
}MYRECT, *PMYRECT; //һ����ʾ����Ľṹ�壬��Ա�����Ͻ�����ͷ���ĳ�������

//�����������ڿ���̨�Ľ�����ʹ�ã�
//���Կ����������̨�����һ���������壬������Ҫ������Ϸ������һ���ֱ��ɣ�
//����̨��һЩ��Ϊ���Ϳ��Կ�������ʵ�֣��������ù��λ�ã����������ɫ�ȵȡ�
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);


/************************************
������ : PrintInstruction
��������: ��ӡ��Ϸ˵��
����ֵ : void
˵�� ��
************************************/
void PrintInstruction()
{
	COORD pos = { 36, 3 };
	DWORD dwSize = 0;
	//�������ã����ù��λ��
	SetConsoleCursorPosition(hOut, pos);
	printf("���ֹ��򣺻�������Ϊ�����ɵ�����");
	FillConsoleOutputAttribute(hOut, FOREGROUND_RED, 10, pos, &dwSize);
	pos.Y++;
	SetConsoleCursorPosition(hOut, pos);
	printf("��Ϸ������w:�� s:�� a:�� d:��");
	//�������ã�����һ�¿���̨����ĳ������Ϊ��ʼ���ı�����ɫ
	FillConsoleOutputAttribute(hOut, FOREGROUND_RED, 10, pos, &dwSize);
}

/************************************
������ : PrintScore
��������: ��ӡһ��Ŀǰ�ķ���
����ֵ : void
˵�� ��
************************************/
void PrintScore()
{
	COORD pos = { 12, 2 };
	DWORD dwSize = 0;
	//�������ã����ù��λ��
	SetConsoleCursorPosition(hOut, pos);
	printf("����:%d", g_Score);
	//�������ã�����һ�¿���̨����ĳ������Ϊ��ʼ���ı�����ɫ
	FillConsoleOutputAttribute(hOut, FOREGROUND_RED, 10, pos, &dwSize);
}



/************************************
������ : DrawRecet
��������: ��һ�����飬���������÷������ɫ�����������÷�������ʾ����ɫ
����ֵ : void
���� : char * szBuf Ҫ�ڷ�������ʾ������
���� : PMYRECT rect ��������Ͻ������볤�ȺͿ��
���� : short foreColour �����ǰ��ɫ��Ҳ����������ɫ
���� : short bacColour ����ı���ɫ��Ҳ���ǡ�����������ɫ
˵�� ��
************************************/
void DrawRecet(char* szBuf, PMYRECT rect, short foreColour, short bacColour)
{
	COORD pos = { 0, 0 };
	DWORD dwCount = strlen(szBuf); //�ַ�����
	DWORD dwSize = 0;
	//��ȡ���ַ��ڷ��������λ�ã�����ӡ�ַ�
	pos.X = rect->x + rect->width / 2 - dwCount / 2;
	pos.Y = rect->y + rect->height / 2;
	SetConsoleCursorPosition(hOut, pos);
	printf(szBuf);
	//��ʼΪ���������ɫ��һ��һ�е����
	pos.X = rect->x;
	pos.Y = rect->y;
	for (int i = rect->y; i<rect->y + rect->height; i++)
	{
		pos.Y = i;
		FillConsoleOutputAttribute(hOut, foreColour | bacColour, rect->width, pos, &dwSize);
	}
}

/************************************
������ : CreateNumber
��������: �ڵ�ͼ���������һ��2����4
����ֵ : void
˵�� ��
************************************/
void CreateNumber()
{
	//��ʼ��һ�����������
	srand(time(NULL));
	//�������һ������
	int x = rand() % 4;
	int y = rand() % 4;
	//�������һ��2����4
	int nNumber = rand() % 2 ? 2 : 4;
	do
	{
		//������ͼ�����λ���ǲ���û�����֣����û�����֣������ɳɹ���
		//������Ҫ������
		if (map[x][y] == 0)
		{
			map[x][y] = nNumber;
			break;
		}
		x = rand() % 4;
		y = rand() % 4;
	} while (true);
}

/************************************
������ : DrawNumber
��������: ��ָ���ķ����ڻ�����Ϸ�е�����
����ֵ : void
���� : int nNumber 2��4��8��16...�ȵȵ�����
���� : PMYRECT rect ���������Ϳ��
˵�� �� 1 ���������DrawRecet����
2 ���ڿ���̨�����ƣ��߶�ʼ����3���ַ������ʼ����6���ַ�������ʹ����ÿ�һЩ��
************************************/
void DrawNumber(int nNumber, PMYRECT rect)
{
	switch (nNumber)
	{
	case 0:
		DrawRecet(" ", rect, FOREGROUND_BLUE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	case 2:
		DrawRecet(" 02 ", rect, FOREGROUND_BLUE, BACKGROUND_RED);
		break;
	case 4:
		DrawRecet(" 04 ", rect, FOREGROUND_BLUE, BACKGROUND_GREEN);
		break;
	case 8:
		DrawRecet(" 08 ", rect, FOREGROUND_RED, BACKGROUND_BLUE);
		break;
	case 16:
		DrawRecet(" 16 ", rect, FOREGROUND_RED, BACKGROUND_BLUE | BACKGROUND_GREEN);
		break;
	case 32:
		DrawRecet(" 32 ", rect, FOREGROUND_GREEN, BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	case 64:
		DrawRecet(" 64 ", rect, FOREGROUND_BLUE | FOREGROUND_GREEN, BACKGROUND_BLUE | BACKGROUND_RED);
		break;
	case 128:
		DrawRecet("0128", rect, FOREGROUND_BLUE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
		break;
	case 256:
		DrawRecet("0256", rect, FOREGROUND_BLUE, BACKGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_RED);
		break;
	case 512:
		DrawRecet("0512", rect, FOREGROUND_BLUE, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	case 1024:
		DrawRecet("1024", rect, FOREGROUND_BLUE, BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	case 2048:
		DrawRecet("2048", rect, FOREGROUND_BLUE, BACKGROUND_BLUE | BACKGROUND_RED);
		break;
	case 4096:
		DrawRecet("4096", rect, FOREGROUND_BLUE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	case 8192:
		DrawRecet("8912", rect, FOREGROUND_BLUE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	default:
		DrawRecet("NANA", rect, FOREGROUND_BLUE, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		break;
	}
}

/************************************
������ : InitGame
��������: ��ʼ����Ϸ��������һ�����ֺ󣬽���ͼ������
����ֵ : void
˵�� ��
************************************/
void InitGame()
{
	MYRECT rect = { 0, 0, 6, 3 };
	PrintInstruction();
	CreateNumber();
	//rect���ʼ����6���߶�ʼ����3������һ�����ӵ�ʱ�򣬺����һ��Խ��6���ַ�
	//�����һ��Խ��3���ַ�
	for (int i = 0; i<4; i++)
	for (int j = 0; j<4; j++)
	{
		rect.x = (i + 2) * 6;
		rect.y = (j + 1) * 3;
		DrawNumber(map[j][i], &rect);
	}
}

/************************************
������ : DrawMap
��������: ����ͼ�е��������ֻ�һ��
����ֵ : void
˵�� ��
************************************/
void DrawMap()
{
	MYRECT rect = { 0, 0, 6, 3 };
	for (int i = 0; i<4; i++)
	for (int j = 0; j<4; j++)
	{
		rect.x = (i + 2) * 6;
		rect.y = (j + 1) * 3;
		DrawNumber(map[j][i], &rect);
	}
}


/************************************
������ : Up
��������: �������ϼ������Ĳ����������ƶ���ͼ�ڵ�Ԫ�أ��ϲ���ͬ������
����ֵ : bool ��ͼ�Ƿ�����һ��
˵�� �� �����°�����ʱ�򣬵�ͼҲ���ܲ�δ�����仯��������Ҫע��
************************************/
bool Up()
{
	bool bIsMove = false;
	//1 �ڵ�ͼ��һ��һ�еĴ��ϵ�����Ѱ����ȷ����ǰԪ����ʲô
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			//2 �ҵ���Ϊ0��Ԫ���ˣ���ô�������ҿ��ܲ����ҵ�һ����Ԫ��
			if (map[j][i] != 0)
			{
				//ע��m����ʼֵ��j+1��Ҳ���Ǽ���������
				for (int m = j + 1; m<4; m++)
				{
					//���˵�һ����Ԫ�أ���ô�͸úϲ���
					if (map[j][i] == map[m][i])
					{
						//�Լ�����һ��
						map[j][i] *= 2;
						//�ҵ����Ǹ�Ԫ�ر��ϲ��ˣ����Ǹ�ֵΪ0
						map[m][i] = 0;
						//�ӷ�
						g_Score += map[j][i];
						//��Ϸ������һ��
						bIsMove = true;
						break;
					}
					//���������ҵ��˲�һ����Ԫ�أ���ô�����Լ���˵��
					//�Լ��ǲ������κα仯��
					else if (map[m][i] != 0)
					{
						break;
					}
				}
			}
			//3 �ҵ���Ϊ0��Ԫ�أ���ô��������Ѱ�������Ƿ���Ԫ���ܹ��ƶ�����
			else
			{
				for (int m = j; m<4; m++)
				{
					//�ҵ���һ����Ϊ0��Ԫ�أ����ǰ����ƶ�������
					if (map[m][i] != 0)
					{
						//�ƶ�
						map[j][i] = map[m][i];
						//���ҵ���λ�ø�ֵΪ0
						map[m][i] = 0;
						//j��Ҫ�Լ�һ�£�Ϊ���ܹ�����Ƿ����滹��һ����Ԫ�ء�
						j--;
						//��ͼ�Ϸ������ƶ�
						bIsMove = true;
						break;
					}
				}
			}
		}
	}
	return bIsMove;
}
/************************************
������ : Down
��������: �������¼������Ĳ����������ƶ���ͼ�ڵ�Ԫ�أ��ϲ���ͬ������
����ֵ : bool
˵�� �� �߼�ͬ��
************************************/
bool Down()
{
	bool bIsMove = false;
	for (int i = 0; i<4; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (map[j][i] != 0)
			{
				for (int m = j - 1; m >= 0; m--)
				{
					if (map[j][i] == map[m][i])
					{
						map[j][i] *= 2;
						map[m][i] = 0;
						g_Score += map[j][i];
						bIsMove = true;
						break;
					}
					else if (map[m][i] != 0)
					{
						break;
					}
				}
			}
			else
			{
				for (int m = j - 1; m >= 0; m--)
				{
					if (map[m][i] != 0)
					{
						map[j][i] = map[m][i];
						map[m][i] = 0;
						j++;
						bIsMove = true;
						break;
					}
				}
			}
		}
	}
	return bIsMove;
}

/************************************
������ : Down
��������: �������¼������Ĳ����������ƶ���ͼ�ڵ�Ԫ�أ��ϲ���ͬ������
����ֵ : bool
˵�� �� �߼�ͬ��
************************************/
bool Right()
{
	bool bIsMove = false;
	for (int i = 0; i<4; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (map[i][j] != 0)
			{
				for (int m = j - 1; m >= 0; m--)
				{
					if (map[i][j] == map[i][m])
					{
						map[i][j] *= 2;
						map[i][m] = 0;
						g_Score += map[i][j];
						bIsMove = true;
						break;
					}
					else if (map[i][m] != 0)
					{
						break;
					}
				}
			}
			else
			{
				for (int m = j - 1; m >= 0; m--)
				{
					if (map[i][m] != 0)
					{
						map[i][j] = map[i][m];
						map[i][m] = 0;
						j++;
						bIsMove = true;
						break;
					}
				}
			}
		}
	}
	return bIsMove;
}

/************************************
������ : Down
��������: �������¼������Ĳ����������ƶ���ͼ�ڵ�Ԫ�أ��ϲ���ͬ������
����ֵ : bool
˵�� �� �߼�ͬ��
************************************/
bool Left()
{
	bool bIsMove = false;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			if (map[i][j] != 0)
			{
				for (int m = j + 1; m<4; m++)
				{
					if (map[i][j] == map[i][m])
					{
						map[i][j] *= 2;
						map[i][m] = 0;
						g_Score += map[i][j];
						bIsMove = true;
						break;
					}
					else if (map[i][m] != 0)
					{
						break;
					}
				}
			}
			else
			{
				for (int m = j + 1; m<4; m++)
				{
					if (map[i][m] != 0)
					{
						map[i][j] = map[i][m];
						map[i][m] = 0;
						bIsMove = true;
						j--;
						break;
					}
				}
			}
		}
	}
	return bIsMove;
}

/************************************
������ : StartGame
��������: ��ʼ��Ϸ����ȡ��ҵİ�����a��s��d��w
����ֵ : void
˵�� ��
************************************/
void StartGame()
{
	InitGame();
	PrintScore();
	char cOper = 0;
	bool bIsMove = false;
	while (true)
	{
		cOper = _getch();
		switch (cOper)
		{
		case 'w':
			bIsMove = Up();
			break;
		case 's':
			bIsMove = Down();
			break;
		case 'a':
			bIsMove = Left();
			break;
		case 'd':
			bIsMove = Right();
		default:
			break;
		}
		//�����ͼ�������ƶ������ʱ���Ӧ�ã�
		//����һ���µ����ֳ������ػ��ͼ�����·���
		if (bIsMove)
		{
			CreateNumber();
			DrawMap();
			PrintScore();
		}

	}
}
int main(int argc, CHAR* argv[])
{
	StartGame();
	return 0;
}