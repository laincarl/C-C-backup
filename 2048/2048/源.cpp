#include <stdlib.h>
#include<stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
int map[4][4] = { 0 }; //2048地图
int g_Score = 0; //这局游戏的分数
typedef struct _MYRECT
{
	short x;
	short y;
	short width;
	short height;
}MYRECT, *PMYRECT; //一个表示方块的结构体，成员是左上角坐标和方块的长度与宽度

//输出句柄，用于控制台的界面编程使用，
//可以看成是与控制台输出的一个抽象物体，就像你要控制游戏，得有一个手柄吧，
//控制台的一些行为，就可以控制它来实现，比如设置光标位置，设置输出颜色等等。
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);


/************************************
函数名 : PrintInstruction
函数作用: 打印游戏说明
返回值 : void
说明 ：
************************************/
void PrintInstruction()
{
	COORD pos = { 36, 3 };
	DWORD dwSize = 0;
	//函数作用：设置光标位置
	SetConsoleCursorPosition(hOut, pos);
	printf("积分规则：积分增长为新生成的数字");
	FillConsoleOutputAttribute(hOut, FOREGROUND_RED, 10, pos, &dwSize);
	pos.Y++;
	SetConsoleCursorPosition(hOut, pos);
	printf("游戏按键：w:上 s:下 a:左 d:右");
	//函数作用：设置一下控制台上以某个坐标为起始的文本的颜色
	FillConsoleOutputAttribute(hOut, FOREGROUND_RED, 10, pos, &dwSize);
}

/************************************
函数名 : PrintScore
函数作用: 打印一下目前的分数
返回值 : void
说明 ：
************************************/
void PrintScore()
{
	COORD pos = { 12, 2 };
	DWORD dwSize = 0;
	//函数作用：设置光标位置
	SetConsoleCursorPosition(hOut, pos);
	printf("分数:%d", g_Score);
	//函数作用：设置一下控制台上以某个坐标为起始的文本的颜色
	FillConsoleOutputAttribute(hOut, FOREGROUND_RED, 10, pos, &dwSize);
}



/************************************
函数名 : DrawRecet
函数作用: 画一个方块，并且能设置方块的颜色，并且能设置方块内显示的颜色
返回值 : void
参数 : char * szBuf 要在方块内显示的内容
参数 : PMYRECT rect 方块的左上角坐标与长度和宽度
参数 : short foreColour 方块的前景色，也就是文字颜色
参数 : short bacColour 方块的背景色，也就是。。。背景颜色
说明 ：
************************************/
void DrawRecet(char* szBuf, PMYRECT rect, short foreColour, short bacColour)
{
	COORD pos = { 0, 0 };
	DWORD dwCount = strlen(szBuf); //字符个数
	DWORD dwSize = 0;
	//获取到字符在方块的中心位置，并打印字符
	pos.X = rect->x + rect->width / 2 - dwCount / 2;
	pos.Y = rect->y + rect->height / 2;
	SetConsoleCursorPosition(hOut, pos);
	printf(szBuf);
	//开始为方块填充颜色，一行一行的添加
	pos.X = rect->x;
	pos.Y = rect->y;
	for (int i = rect->y; i<rect->y + rect->height; i++)
	{
		pos.Y = i;
		FillConsoleOutputAttribute(hOut, foreColour | bacColour, rect->width, pos, &dwSize);
	}
}

/************************************
函数名 : CreateNumber
函数作用: 在地图中随机生成一个2或者4
返回值 : void
说明 ：
************************************/
void CreateNumber()
{
	//初始化一个随机数种子
	srand(time(NULL));
	//随机出来一个坐标
	int x = rand() % 4;
	int y = rand() % 4;
	//随机出来一个2或者4
	int nNumber = rand() % 2 ? 2 : 4;
	do
	{
		//看看地图的这个位置是不是没有数字，如果没有数字，就生成成功，
		//否则还需要再生成
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
函数名 : DrawNumber
函数作用: 在指定的方格内画出游戏中的数字
返回值 : void
参数 : int nNumber 2，4，8，16...等等的数字
参数 : PMYRECT rect 方块的坐标和宽度
说明 ： 1 这里调用了DrawRecet函数
2 由于控制台的限制，高度始终是3个字符，宽度始终是6个字符，才能使界面好看一些。
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
函数名 : InitGame
函数作用: 初始化游戏，创建出一个数字后，将地图画出来
返回值 : void
说明 ：
************************************/
void InitGame()
{
	MYRECT rect = { 0, 0, 6, 3 };
	PrintInstruction();
	CreateNumber();
	//rect宽度始终是6，高度始终是3，画下一个格子的时候，横向就一次越过6个字符
	//纵向就一次越过3个字符
	for (int i = 0; i<4; i++)
	for (int j = 0; j<4; j++)
	{
		rect.x = (i + 2) * 6;
		rect.y = (j + 1) * 3;
		DrawNumber(map[j][i], &rect);
	}
}

/************************************
函数名 : DrawMap
函数作用: 将地图中的所有数字画一遍
返回值 : void
说明 ：
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
函数名 : Up
函数作用: 按了向上键后，做的操作，包括移动地图内的元素，合并相同的数字
返回值 : bool 地图是否发生了一栋
说明 ： 当按下按键的时候，地图也可能并未发生变化，这里需要注意
************************************/
bool Up()
{
	bool bIsMove = false;
	//1 在地图中一列一列的从上到下搜寻，来确定当前元素是什么
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			//2 找到不为0的元素了，那么就往下找看能不能找到一样的元素
			if (map[j][i] != 0)
			{
				//注意m的起始值是j+1，也就是继续往下找
				for (int m = j + 1; m<4; m++)
				{
					//找了到一样的元素，那么就该合并。
					if (map[j][i] == map[m][i])
					{
						//自己自增一倍
						map[j][i] *= 2;
						//找到的那个元素被合并了，于是赋值为0
						map[m][i] = 0;
						//加分
						g_Score += map[j][i];
						//游戏发生了一栋
						bIsMove = true;
						break;
					}
					//假如往下找到了不一样的元素，那么对于自己来说，
					//自己是不发生任何变化的
					else if (map[m][i] != 0)
					{
						break;
					}
				}
			}
			//3 找到了为0的元素，那么就往下搜寻，看看是否有元素能够移动上来
			else
			{
				for (int m = j; m<4; m++)
				{
					//找到了一个不为0的元素，于是把它移动上来。
					if (map[m][i] != 0)
					{
						//移动
						map[j][i] = map[m][i];
						//将找到的位置赋值为0
						map[m][i] = 0;
						//j还要自减一下，为了能够检测是否下面还有一样的元素。
						j--;
						//地图上发生了移动
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
函数名 : Down
函数作用: 按了向下键后，做的操作，包括移动地图内的元素，合并相同的数字
返回值 : bool
说明 ： 逻辑同上
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
函数名 : Down
函数作用: 按了向下键后，做的操作，包括移动地图内的元素，合并相同的数字
返回值 : bool
说明 ： 逻辑同上
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
函数名 : Down
函数作用: 按了向下键后，做的操作，包括移动地图内的元素，合并相同的数字
返回值 : bool
说明 ： 逻辑同上
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
函数名 : StartGame
函数作用: 开始游戏，获取玩家的按键，a，s，d，w
返回值 : void
说明 ：
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
		//如果地图发生了移动，这个时候就应该：
		//创建一个新的数字出来，重绘地图，更新分数
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