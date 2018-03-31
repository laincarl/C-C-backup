#include<stdio.h>
int main()
{
	int i, t = 0;
	float sum = 0, a = 2, b = 1;
	for (i = 1; i <= 20; i++)
	{
		sum = sum + a / b;
		t=a;
		a = a + b;
		b = t;
	}
	printf("%f", sum);
	return 0;
}