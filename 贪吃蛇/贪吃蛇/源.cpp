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
函数名 : WriteWchar
函数作用: 在控制台相应的坐标上显示一串字符
返回值 : void
参数 : int x 横坐标
参数 : int y 纵坐标
参数 : char szString[] 要显示的字符串
说明 ：
************************************/
void WriteChar(intx, int y, charszString[])
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(hOut, pos);
	printf("%s", szString);

}

/************************************
函数名 : InitGame
函数作用: public
返回值 : void
说明 ： 初始化地图，将地图四周赋值为墙，并初始化出来蛇
************************************/
voidInitGame()
{
	//1 地图四周赋值为墙并把墙画出来
	for (inti = 0; i<20; i++)
	for (intj = 0; j<20; j++)
	{
		if (i == 0 || i == 19 || j == 0 || j == 19)
		{
			g_Map[i][j] = WALL;
			WriteChar(j, i, "※");
		}
	}

	//2 生出一个长度为3的蛇
	g_Snake[0].x = 10;
	g_Snake[0].y = 10;
	g_Snake[1].x = 10;
	g_Snake[1].y = 11;
	g_Snake[2].x = 10;
	g_Snake[2].y = 12;
	g_Lenth = 3;
}

/************************************
函数名 : GetOper
函数作用: public
返回值 : char
说明 ： 获取按键，假如有按键的话返回按键值，假如没有按键的话，返回0
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
函数名 : CleanSnakeOnMap
函数作用: public
返回值 : void
说明 ： 清除掉地图中的蛇，并且清除掉屏幕上的蛇的图案
************************************/
voidCleanSnakeOnMap()
{
	for (inti = 0; i < g_Lenth; i++)
	{
		g_Map[g_Snake[i].y][g_Snake[i].x] = NOTHING;
	}
	//擦除屏幕上的蛇尾
	WriteChar(g_Snake[g_Lenth - 1].x, g_Snake[g_Lenth - 1].y, " ");
}
voidDrawSnake()
{

	//画上蛇头即可
	for (inti = 0; i < g_Lenth; i++)
	{
		g_Map[g_Snake[i].y][g_Snake[i].x] = SNAKE;

	}
	WriteChar(g_Snake[0].x, g_Snake[0].y, "■");
}
/************************************
函数名 : MoveSnake
函数作用: public
返回值 : void
说明 ： 把蛇移动一次。
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
	//先判断一下，新的坐标上有没有其他物品
	if (g_Map[NewY][NewX] == NOTHING)
	{
		//可以移动，将蛇身体的坐标更新一下
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
		//有东西，是食物那就长长了
		if (g_Map[NewY][NewX] == FOOD)
		{
			g_Lenth++;//身体变长了
			for (inti = g_Lenth - 2; i >= 0; i--)
			{
				memcpy(&g_Snake[i + 1], &g_Snake[i], sizeof(g_Snake[0]));
			}
			g_Snake[0].x = NewX;
			g_Snake[0].y = NewY;
			g_IsHaveFood = false;
		}
		//有东西，是墙，那就死翘翘了
		else if (g_Map[NewY][NewX] == WALL)
		{
			return false;
		}
		//有东西，是蛇自己，那也死翘翘了
		else if (g_Map[NewY][NewX] == SNAKE)
		{
			return false;
		}
	}
	DrawSnake();
	return true;
}

/************************************
函数名 : CreateFood
函数作用: public
返回值 : void
说明 ： 创建一个吃的出来
************************************/
voidCreateFood()
{
	static int nFoodPos_x = 0;
	static int nFoodPos_y = 0;
	//假如地图上有吃的，那就不用创建了
	if (g_IsHaveFood)
	{
		return;
	}
	//地图上没有吃的，那就创建一个，并且不能创建到蛇身上
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
		WriteChar(nFoodPos_x, nFoodPos_y, "●");
	}

}
/************************************
函数名 : StartGame
函数作用: public
返回值 : void
说明 ： 开始游戏
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
			//看看是不是该有食物生出来了
			CreateFood();
			//将蛇移动一步
			bResult = MoveSnake();
			//蛇死了。。。那就Gameover啦
			if (!bResult)
			{
				//清屏
				system("cls");
				printf("你死了,少侠，从新来过吧\n");
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