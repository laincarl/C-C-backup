#include"rect.h"
#include"uniform.h"
using namespace std;

const float WIN_SIZE = 12.0;
const int MAX_SIZE = 3;

SimpleWindow W("KaleidoWindow", WIN_SIZE, WIN_SIZE);//创建一个新窗口
//产生随机颜色，color是ezwin图形库中定义的表示颜色的枚举类型

color RandomColor()
{
	return (color)Uniform(0, MaxColors - 1);
}

//随机产生正方形与中心的距离
float RandomOffSet(int Range, float TrinketSize)
{
	float OffSet = Uniform(0, Range * 10) / 10.0f;
	//正方形与中心的距离必须大于其边长的一半
	if (OffSet < TrinketSize / 2.0f)
	{
		OffSet = TrinketSize / 2.0f;
	}
	return OffSet;
}
int Randomx()
{
	int x = Uniform(0, 1);


	return x;
}
//正方形与中心的距离必须大于其边长的一半
//随机设置正方形的边长
float RandomTrinketetSize(int MaxSize)
{
	return Uniform(10, MaxSize * 10) / 10.0f;
}
int Kaleidoscope()
{
	const float Center = WIN_SIZE / 2;                   //窗口中心
	const float Size = RandomTrinketetSize(MAX_SIZE);  //设置正方形边长
	const color Color1 = RandomColor();	                 //产生随机颜色
	const color Color2 = RandomColor();
	float OffSet = RandomOffSet(MAX_SIZE, Size);
	int x = Randomx();
	//设置正方形与中心的距离
	//创建四个矩形
	RectangleShape Trinket1(W, Center + x*OffSet, Center + OffSet, Color1, Size, Size);
	RectangleShape Trinket2(W, Center - OffSet, Center + x*OffSet, Color2, Size, Size);
	RectangleShape Trinket3(W, Center - x*OffSet, Center - OffSet, Color1, Size, Size);
	RectangleShape Trinket4(W, Center + OffSet, Center - x*OffSet, Color2, Size, Size);

	//绘制四个矩形
	Trinket1.Draw();
	Trinket2.Draw();
	Trinket3.Draw();
	Trinket4.Draw();

	return 0;
}

int ApiMain()
{
	W.Open();
	W.SetTimerCallback(Kaleidoscope);
	W.StartTimer(500);
	return 0;
}






