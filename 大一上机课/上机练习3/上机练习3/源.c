#include<stdio.h>
float a = 0.1, b = 0.2, c = 0.2, d = 0.5;
int main()
{
	float Score(int array[5][4],float m[]);//��������
	float Sort(float s[]);//��������
	int a[5][4] = { { 80, 90, 75, 80 }, { 90, 60, 80, 78 }, { 30, 75, 60, 50 }, { 100, 90, 90, 85 }, { 50, 80, 80, 95 } };
	float b[5] = { 0 };
	int i;
	Score(a,b);
	Sort(b);
	for (i = 0; i < 5;i++)
	printf("%.2f ", b[i]);//���
	return 0;
}
