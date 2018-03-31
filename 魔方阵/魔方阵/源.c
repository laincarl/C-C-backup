#include<stdio.h>
int main()
{
	int a[15][15] = { 0 };
	int i, j, k, n;
	scanf_s("%d", &n);
	a[0][(n - 1) / 2] = 1;
	i = 1; j = (n + 1) / 2;
	for (k = 2; k <= n*n; k++)
	{
			i = i - 1;
			j = j + 1;
		 if (i==-1)
			i = n - 1;
        if (j==n)
			j = 0;
		a[i][j] = k;
		if (a[i][j] == 0)
		{
			a[i][j] = k;
		}

	}
	for (i = 0; i <= n - 1; i++)
	{
		for (j = 0; j <= n - 1; j++)
			printf("%d\t", a[i][j]);
		printf("\n");
	}
	return 0;
}