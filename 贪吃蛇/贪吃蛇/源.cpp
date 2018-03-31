#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3


#define NOTHING0
#define WALL 1
#define FOOD 2
#define SNAKE 3

#define MAP_X 20
#define MAP_Y 20
typedefstruct _BODY
{
	int x;
	int y;
}BODY, *PBODY;

int g_Map[MAP_X][MAP_Y] = { 0 };
BODY g_Snake[100] = { 0 };
int g_Lenth = 0;
int g_Direction = DOWN;
BOOL g_IsHaveFood = FALSE;
/************************************
������ : WriteWchar
��������: �ڿ���̨��Ӧ����������ʾһ���ַ�
����ֵ : void
���� : int x ������
���� : int y ������
���� : char szString[] Ҫ��ʾ���ַ���
˵�� ��
************************************/
void WriteChar(intx, int y, charszString[])
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(hOut, pos);
	printf("%s", szString);

}

/************************************
������ : InitGame
��������: public
����ֵ : void
˵�� �� ��ʼ����ͼ������ͼ���ܸ�ֵΪǽ������ʼ��������
************************************/
voidInitGame()
{
	//1 ��ͼ���ܸ�ֵΪǽ����ǽ������
	for (inti = 0; i<20; i++)
	for (intj = 0; j<20; j++)
	{
		if (i == 0 || i == 19 || j == 0 || j == 19)
		{
			g_Map[i][j] = WALL;
			WriteChar(j, i, "��");
		}
	}

	//2 ����һ������Ϊ3����
	g_Snake[0].x = 10;
	g_Snake[0].y = 10;
	g_Snake[1].x = 10;
	g_Snake[1].y = 11;
	g_Snake[2].x = 10;
	g_Snake[2].y = 12;
	g_Lenth = 3;
}

/************************************
������ : GetOper
��������: public
����ֵ : char
˵�� �� ��ȡ�����������а����Ļ����ذ���ֵ������û�а����Ļ�������0
************************************/
char GetOper()
{
	if (_kbhit())
	{
		return _getch();
	}
	return 0;
}

/************************************
������ : CleanSnakeOnMap
��������: public
����ֵ : void
˵�� �� �������ͼ�е��ߣ������������Ļ�ϵ��ߵ�ͼ��
************************************/
voidCleanSnakeOnMap()
{
	for (inti = 0; i < g_Lenth; i++)
	{
		g_Map[g_Snake[i].y][g_Snake[i].x] = NOTHING;
	}
	//������Ļ�ϵ���β
	WriteChar(g_Snake[g_Lenth - 1].x, g_Snake[g_Lenth - 1].y, " ");
}
voidDrawSnake()
{

	//������ͷ����
	for (inti = 0; i < g_Lenth; i++)
	{
		g_Map[g_Snake[i].y][g_Snake[i].x] = SNAKE;

	}
	WriteChar(g_Snake[0].x, g_Snake[0].y, "��");
}
/************************************
������ : MoveSnake
��������: public
����ֵ : void
˵�� �� �����ƶ�һ�Ρ�
************************************/
boolMoveSnake()
{

	int NewX = 0;
	int NewY = 0;
	switch (g_Direction)
	{
	case UP:
	{
			   NewX = g_Snake[0].x;
			   NewY = g_Snake[0].y - 1;
	}
		break;
	case DOWN:
	{
				 NewX = g_Snake[0].x;
				 NewY = g_Snake[0].y + 1;
	}
		break;
	case LEFT:
	{
				 NewX = g_Snake[0].x - 1;
				 NewY = g_Snake[0].y;
	}
		break;
	case RIGHT:
	{
				  NewX = g_Snake[0].x + 1;
				  NewY = g_Snake[0].y;
	}
		break;
	default:
		break;
	}
	//���ж�һ�£��µ���������û��������Ʒ
	if (g_Map[NewY][NewX] == NOTHING)
	{
		//�����ƶ�������������������һ��
		CleanSnakeOnMap();
		for (inti = g_Lenth - 2; i >= 0; i--)
		{
			memcpy(&g_Snake[i + 1], &g_Snake[i], sizeof(g_Snake[0]));
		}
		g_Snake[0].x = NewX;
		g_Snake[0].y = NewY;
	}
	else
	{
		//�ж�������ʳ���Ǿͳ�����
		if (g_Map[NewY][NewX] == FOOD)
		{
			g_Lenth++;//����䳤��
			for (inti = g_Lenth - 2; i >= 0; i--)
			{
				memcpy(&g_Snake[i + 1], &g_Snake[i], sizeof(g_Snake[0]));
			}
			g_Snake[0].x = NewX;
			g_Snake[0].y = NewY;
			g_IsHaveFood = false;
		}
		//�ж�������ǽ���Ǿ���������
		else if (g_Map[NewY][NewX] == WALL)
		{
			return false;
		}
		//�ж����������Լ�����Ҳ��������
		else if (g_Map[NewY][NewX] == SNAKE)
		{
			return false;
		}
	}
	DrawSnake();
	return true;
}

/************************************
������ : CreateFood
��������: public
����ֵ : void
˵�� �� ����һ���Եĳ���
************************************/
voidCreateFood()
{
	static int nFoodPos_x = 0;
	static int nFoodPos_y = 0;
	//�����ͼ���гԵģ��ǾͲ��ô�����
	if (g_IsHaveFood)
	{
		return;
	}
	//��ͼ��û�гԵģ��Ǿʹ���һ�������Ҳ��ܴ�����������
	else
	{
		while (true)
		{
			nFoodPos_x = rand() % MAP_X;
			nFoodPos_y = rand() % MAP_Y;
			if (g_Map[nFoodPos_y][nFoodPos_x] == 0)
			{
				break;
			}
		}
		g_Map[nFoodPos_y][nFoodPos_x] = FOOD;
		g_IsHaveFood = TRUE;
		WriteChar(nFoodPos_x, nFoodPos_y, "��");
	}

}
/************************************
������ : StartGame
��������: public
����ֵ : void
˵�� �� ��ʼ��Ϸ
************************************/
voidStartGame()
{
	char cOper = 0;
	int nTime = 0;
	bool bResult = false;
	while (true)
	{
		Sleep(1);
		cOper = GetOper();
		switch (cOper)
		{
		case 'w':
			g_Direction = UP;
			break;
		case 's':
			g_Direction = DOWN;
			break;
		case 'a':
			g_Direction = LEFT;
			break;
		case 'd':
			g_Direction = RIGHT;
		default:
			break;
		}
		nTime++;
		if (nTime % 100 == 0)
		{
			//�����ǲ��Ǹ���ʳ����������
			CreateFood();
			//�����ƶ�һ��
			bResult = MoveSnake();
			//�����ˡ������Ǿ�Gameover��
			if (!bResult)
			{
				//����
				system("cls");
				printf("������,����������������\n");
				break;
			}
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	InitGame();
	StartGame();
	system("pause");
	return 0;
}