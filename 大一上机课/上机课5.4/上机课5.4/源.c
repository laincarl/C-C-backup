#include<stdio.h>
float all;
int a, b, c, d;
int main()
{
	int i, e, f;

	for (i = 0; i<4; i++)
		scanf_s("%d%d%d%d", &f, &b, &c, &d);
	int a[4] = { f, b, c, d };
	float Score(int a);
	e = Score(a);
	printf("³É¼¨ÊÇ%f", e);

	return 0;
}
float Score(float a[4])
{
	all = f*0.1 + b*0.2 + c*0.2 + d*0.5;
	return all;
}
