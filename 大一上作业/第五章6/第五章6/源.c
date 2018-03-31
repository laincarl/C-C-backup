#include<stdio.h>
int main()
{
float i,j,sum,p;
	sum = 0;
	
	for (i = 1; i <= 20; i++)
	{
		p = 1;
		for (j =i; j >= 1; j--)
			p = p*j;
		sum = sum + p;
	}
	printf("%.0f", sum);
	return 0;
}