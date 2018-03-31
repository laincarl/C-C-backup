#include<stdio.h>
int main()
{
	int i,a,b,c;
	printf("Ë®ÏÉ»¨Êý:\n");
	for (i = 100; i <= 999; i++)
	{
		a = i / 100;
		b = (i % 100) / 10;
		c = i % 10;
		if (i == a*a*a + b*b*b + c*c*c)
			printf("%d\t", i);
	}
		return 0;
	
}