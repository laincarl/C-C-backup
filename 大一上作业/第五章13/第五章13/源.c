#include<stdio.h>
#include<math.h>
int main()
{
	float a, x0, x1=0;
	printf("������һ��������\n");
	scanf_s("%f", &a);
	x0 = a/2;
	x1 = (x0 + a / x0) / 2;
	do
	{
	x0 = x1;
	x1 = 0.5*(x0 + a / x0);
	
	} while (fabs(x1 - x0)>=1e-5);
	printf("%f��ƽ������%f",a,x1);	return 0;
}