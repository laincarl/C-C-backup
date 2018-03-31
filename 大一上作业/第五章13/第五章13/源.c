#include<stdio.h>
#include<math.h>
int main()
{
	float a, x0, x1=0;
	printf("请输入一个正数：\n");
	scanf_s("%f", &a);
	x0 = a/2;
	x1 = (x0 + a / x0) / 2;
	do
	{
	x0 = x1;
	x1 = 0.5*(x0 + a / x0);
	
	} while (fabs(x1 - x0)>=1e-5);
	printf("%f的平方根是%f",a,x1);	return 0;
}