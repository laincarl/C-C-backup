# include <stdio.h>
int main()
{
	int n, a, i;
	printf("ÇëÊäÈëÆæÊı n:\n\n");
	scanf_s("%d", &n);
	for (a = 1; a <=( n+1)/2; a++)
	{
		for (i = 1; i <= n - a; i++)
			printf(" ");
		for (; i<n + a; i++)
			printf("*");
		printf("\n");
	}
	return 0;
}
