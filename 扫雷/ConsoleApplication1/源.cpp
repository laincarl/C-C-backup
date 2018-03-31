// saolei.cpp : �������̨Ӧ�ó�������
#include <windows.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define Boom 10
int a[10][10] = { 0 };
COORD TempPos[100] = { 0 };
int nSign = 0;


/************************************
������ : WriteWchar
��������: �ڿ���̨��Ӧ����������ʾһ���ַ�
����ֵ : void
���� : int x ������
���� : int y ������
���� : char szString[] Ҫ��ʾ���ַ���
˵�� ��
************************************/
void WriteWchar(int x, int y, char szString[])
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(hOut, pos);
	printf("%s", szString);
}


/************************************
������ : DrawNumber
��������: ����Ӧ�������ϣ����ݴ�������֣���ӡ��Ӧ�������ַ�
����ֵ : void
���� : COORD pos Ҫ��ӡ��λ��
���� : int nNumber Ҫ��ӡ������
˵�� ��
************************************/
void DrawNumber(COORD pos, int nNumber)
{
	switch (nNumber)
	{
	case 1:
		WriteWchar(pos.X, pos.Y, "��");
		break;
	case 2:
		WriteWchar(pos.X, pos.Y, "��");
		break;
	case 3:
		WriteWchar(pos.X, pos.Y, "��");
		break;
	case 4:
		WriteWchar(pos.X, pos.Y, "��");
		break;
	case 5:
		WriteWchar(pos.X, pos.Y, "��");
		break;
	case 6:
		WriteWchar(pos.X, pos.Y, "��");
		break;
	case 7:
		WriteWchar(pos.X, pos.Y, "��");
		break;
	case 8:
		WriteWchar(pos.X, pos.Y, "��");
		break;
	default:
		break;
	}
}

/************************************
������ : GetNumber
��������: ��ȡһ����������м�����
����ֵ : int
���� : COORD pos Ҫ̽��ĵ������
˵�� ��
************************************/
int GetNumber(COORD pos)
{
	int nCount = 0;
	for (int i = pos.X - 1; i <= pos.X + 1; i++)
	for (int j = pos.Y - 1; j <= pos.Y + 1; j++)
	{
		if (a[j][i] == Boom)
		{
			nCount++;
		}
	}
	return nCount;
}

/************************************
������ : Drawmap
��������: ��ӡһ�µ�ͼ
����ֵ : void
˵�� ��
************************************/
void Drawmap()
{
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			WriteWchar(j, i, "��");
		}
	}
}


/************************************
������ : Init
��������: �������10�����ף�Ȼ��浽������
����ֵ : void
˵�� ��
************************************/
void Init()
{
	srand(time(NULL));
	for (int i = 0; i<10; i++)
	{
		int Temp_x = rand() % 10;
		int Temp_y = rand() % 10;
		//�ж�����ط��ǲ����Ѿ�����һ�����ˣ����û�У���ֵΪ��
		if (a[Temp_x][Temp_y] != Boom)
		{
			a[Temp_x][Temp_y] = Boom;
		}
		//������ף����൱�ڱ�������û�з���������������
		else
		{
			i--;
		}
	}
	Drawmap();
}

/************************************
������ : IsClose
��������: �ж��ǲ����Ѿ�̽����ĵ㣬����ʹ�õ�8����ݹ��̽�⣬���������ظ�
����ֵ : bool
���� : COORD posTemp
˵�� ��
************************************/
bool IsClose(COORD posTemp)
{
	for (int i = 0; i<nSign; i++)
	{
		if (TempPos[i].X == posTemp.X&&TempPos[i].Y == posTemp.Y)
			return true;
	}
	return false;
}

/************************************
������ : IsKongdi
��������: �ж�һ�����ǿյأ������ף�����ǿյأ���Ҫ����������
����ֵ : void
���� : COORD pos
˵�� ��
************************************/
bool IsKongdi(COORD pos)
{
	int nNumber = 0;
	//1 ������ף���ֱ�ӷ���һ��false˵��Ҫ����
	if (a[pos.Y][pos.X] == Boom)
	{
		return false;
	}
	//2 ��������ף���ô������������
	else
	{
		//2.1���ж�һ����Χ�м�����
		nNumber = GetNumber(pos);
		if (nNumber != 0){
			//�м����ף��ʹ�ӡ�������
			DrawNumber(pos, nNumber);
			return true;
		}
		else
		{
			//���û���ף��Ǿ��Ȼ��յس�����Ȼ������Χ��ɢȥ̽��������
			WriteWchar(pos.X, pos.Y, " ");
		}
	}
	//2.2�㵽�˿յأ�������Χû���׵�����Ĵ�������ȥ̽����Χ8����
	for (int i = -1; i <= 1; i++)
	for (int j = -1; j <= 1; j++)
	{
		COORD posTemp = { pos.X + i, pos.Y + j };
		//�ǲ���Խ����
		if (i == 0 && j == 0 || posTemp.X == -1 || posTemp.Y == -1 || posTemp.X == 10 || posTemp.Y == 10)
			continue;
		//������ǲ����Ѿ�̽�����
		if (IsClose(posTemp))
			continue;
		//�����û��̽������ͽ�����뵽�����У�Ȼ��ʹ�����Ժ��̽���У�����
		TempPos[nSign++] = posTemp;
		IsKongdi(posTemp);
	}
	return true;
}

/************************************
������ : GetMousePosition
��������: ��ȡ�������λ�ã�����û�л�ȡ�����ͷ���(-1,-1)
����ֵ : COORD �����������
˵�� ��
************************************/
COORD GetMousePosition()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD stcInput = { 0 };
	DWORD buffer;
	COORD pos = { -1, -1 };
	ReadConsoleInput(hIn, &stcInput, 1, &buffer);
	if (stcInput.EventType == MOUSE_EVENT)
	{
		MOUSE_EVENT_RECORD stcMouseEnent = stcInput.Event.MouseEvent;

		if (stcMouseEnent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			pos = stcMouseEnent.dwMousePosition;
			pos.X /= 2;
		}
	}
	return pos;
}
int main(int argc, CHAR* argv[])
{
	Init();
	COORD pos;
	//��ʼ��Ϸ
	while (1)
	{
		//��ȡ�����λ��
		pos = GetMousePosition();
		if (pos.X != -1)
		{
			//����������λ�ñ�̽����ˣ��Ϳ�ʼ��һ��ѭ��
			if (IsClose(pos))
			{
				continue;
			}
			TempPos[nSign++] = pos;
			bool bIskongdi = IsKongdi(pos);
			//�㵽���ˣ���ֱ���˳���Ϸ�ˡ�
			if (false == bIskongdi)
			{

				system("cls");
				WriteWchar(15, 10, "�㡣�ȡ������ס���");
				getchar();
				break;
			}
			//����ǲ���Ӯ�ˣ�Ӯ����������û�б�̽��ĵ�ĸ������׵ĸ������
			if (nSign == 90)
			{
				system("cls");
				WriteWchar(20, 10, "you win");
			}
		}
	}
	return 0;
}