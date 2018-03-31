#include<stdio.h>
#include<math.h>
int main()
{
	int i, a, j;

	
	for (j = 1; j <= 7; j++)
	{a = fabs(j - 4);
	for (i = 1; i <= a; i++)
		printf(" ");
	for (i = 1; i <=7-2*a; i++)
		printf("*");
	for (i = 1; i <= a; i++)
		printf(" ");
	printf("\n");
	}
	return 0;
}