#include"rect.h"
#include"uniform.h"
using namespace std;

const float WIN_SIZE = 12.0;
const int MAX_SIZE = 3;

SimpleWindow W("KaleidoWindow", WIN_SIZE, WIN_SIZE);//����һ���´���
//���������ɫ��color��ezwinͼ�ο��ж���ı�ʾ��ɫ��ö������

color RandomColor()
{
	return (color)Uniform(0, MaxColors - 1);
}

//������������������ĵľ���
float RandomOffSet(int Range, float TrinketSize)
{
	float OffSet = Uniform(0, Range * 10) / 10.0f;
	//�����������ĵľ�����������߳���һ��
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
//�����������ĵľ�����������߳���һ��
//������������εı߳�
float RandomTrinketetSize(int MaxSize)
{
	return Uniform(10, MaxSize * 10) / 10.0f;
}
int Kaleidoscope()
{
	const float Center = WIN_SIZE / 2;                   //��������
	const float Size = RandomTrinketetSize(MAX_SIZE);  //���������α߳�
	const color Color1 = RandomColor();	                 //���������ɫ
	const color Color2 = RandomColor();
	float OffSet = RandomOffSet(MAX_SIZE, Size);
	int x = Randomx();
	//���������������ĵľ���
	//�����ĸ�����
	RectangleShape Trinket1(W, Center + x*OffSet, Center + OffSet, Color1, Size, Size);
	RectangleShape Trinket2(W, Center - OffSet, Center + x*OffSet, Color2, Size, Size);
	RectangleShape Trinket3(W, Center - x*OffSet, Center - OffSet, Color1, Size, Size);
	RectangleShape Trinket4(W, Center + OffSet, Center - x*OffSet, Color2, Size, Size);

	//�����ĸ�����
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






