#include<stdio.h>
#include<math.h>
int main()
{
	int h;
	float x, y;
	printf("���������꣨x,y):\n");
	scanf_s("%f,%f", &x,&y);
	x = fabs(x);
	y = fabs(y);
	if ((x - 2)*(x - 2) + (y - 2)*(y - 2) <= 1)
		h = 10;
	else
		h = 0;
	printf("�õ�Ľ����߶�Ϊ:%d", h);
	return 0;


}