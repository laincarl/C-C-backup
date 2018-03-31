// saolei.cpp : 定义控制台应用程序的入口
#include <windows.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#define Boom 10
int a[10][10] = { 0 };
COORD TempPos[100] = { 0 };
int nSign = 0;


/************************************
函数名 : WriteWchar
函数作用: 在控制台相应的坐标上显示一串字符
返回值 : void
参数 : int x 横坐标
参数 : int y 纵坐标
参数 : char szString[] 要显示的字符串
说明 ：
************************************/
void WriteWchar(int x, int y, char szString[])
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(hOut, pos);
	printf("%s", szString);
}


/************************************
函数名 : DrawNumber
函数作用: 在相应的坐标上，根据传入的数字，打印相应的数字字符
返回值 : void
参数 : COORD pos 要打印的位置
参数 : int nNumber 要打印的数字
说明 ：
************************************/
void DrawNumber(COORD pos, int nNumber)
{
	switch (nNumber)
	{
	case 1:
		WriteWchar(pos.X, pos.Y, "①");
		break;
	case 2:
		WriteWchar(pos.X, pos.Y, "②");
		break;
	case 3:
		WriteWchar(pos.X, pos.Y, "③");
		break;
	case 4:
		WriteWchar(pos.X, pos.Y, "④");
		break;
	case 5:
		WriteWchar(pos.X, pos.Y, "⑤");
		break;
	case 6:
		WriteWchar(pos.X, pos.Y, "⑥");
		break;
	case 7:
		WriteWchar(pos.X, pos.Y, "⑦");
		break;
	case 8:
		WriteWchar(pos.X, pos.Y, "⑧");
		break;
	default:
		break;
	}
}

/************************************
函数名 : GetNumber
函数作用: 获取一个点的四周有几颗雷
返回值 : int
参数 : COORD pos 要探测的点的坐标
说明 ：
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
函数名 : Drawmap
函数作用: 打印一下地图
返回值 : void
说明 ：
************************************/
void Drawmap()
{
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			WriteWchar(j, i, "■");
		}
	}
}


/************************************
函数名 : Init
函数作用: 随机生成10个地雷，然后存到数组中
返回值 : void
说明 ：
************************************/
void Init()
{
	srand(time(NULL));
	for (int i = 0; i<10; i++)
	{
		int Temp_x = rand() % 10;
		int Temp_y = rand() % 10;
		//判断这个地方是不是已经生成一个雷了，如果没有，赋值为雷
		if (a[Temp_x][Temp_y] != Boom)
		{
			a[Temp_x][Temp_y] = Boom;
		}
		//如果是雷，就相当于本次生成没有发生过。。。。。
		else
		{
			i--;
		}
	}
	Drawmap();
}

/************************************
函数名 : IsClose
函数作用: 判断是不是已经探测过的点，由于使用的8方向递归的探测，这样避免重复
返回值 : bool
参数 : COORD posTemp
说明 ：
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
函数名 : IsKongdi
函数作用: 判断一个点是空地，还是雷，如果是空地，需要做其他处理
返回值 : void
参数 : COORD pos
说明 ：
************************************/
bool IsKongdi(COORD pos)
{
	int nNumber = 0;
	//1 如果是雷，就直接返回一个false说明要挂了
	if (a[pos.Y][pos.X] == Boom)
	{
		return false;
	}
	//2 如果不是雷，那么就做后续处理
	else
	{
		//2.1先判断一下周围有几颗雷
		nNumber = GetNumber(pos);
		if (nNumber != 0){
			//有几颗雷，就打印这个数字
			DrawNumber(pos, nNumber);
			return true;
		}
		else
		{
			//如果没有雷，那就先画空地出来，然后向周围扩散去探测其他点
			WriteWchar(pos.X, pos.Y, " ");
		}
	}
	//2.2点到了空地，但是周围没有雷的情况的处理，继续去探测周围8个点
	for (int i = -1; i <= 1; i++)
	for (int j = -1; j <= 1; j++)
	{
		COORD posTemp = { pos.X + i, pos.Y + j };
		//是不是越界了
		if (i == 0 && j == 0 || posTemp.X == -1 || posTemp.Y == -1 || posTemp.X == 10 || posTemp.Y == 10)
			continue;
		//这个点是不是已经探测过了
		if (IsClose(posTemp))
			continue;
		//这个点没有探测过，就将其加入到数组中，然后使其在以后的探测中，存入
		TempPos[nSign++] = posTemp;
		IsKongdi(posTemp);
	}
	return true;
}

/************************************
函数名 : GetMousePosition
函数作用: 获取鼠标点击的位置，假如没有获取到，就返回(-1,-1)
返回值 : COORD 鼠标点击的坐标
说明 ：
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
	//开始游戏
	while (1)
	{
		//获取鼠标点击位置
		pos = GetMousePosition();
		if (pos.X != -1)
		{
			//如果鼠标点击的位置被探测过了，就开始下一次循环
			if (IsClose(pos))
			{
				continue;
			}
			TempPos[nSign++] = pos;
			bool bIskongdi = IsKongdi(pos);
			//点到雷了，就直接退出游戏了。
			if (false == bIskongdi)
			{

				system("cls");
				WriteWchar(15, 10, "你。踩。到。雷。了");
				getchar();
				break;
			}
			//检测是不是赢了，赢的条件就是没有被探测的点的个数和雷的个数相等
			if (nSign == 90)
			{
				system("cls");
				WriteWchar(20, 10, "you win");
			}
		}
	}
	return 0;
}