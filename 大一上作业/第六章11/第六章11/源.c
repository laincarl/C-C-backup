#include<stdio.h>
int main()
{
	int i, j;
	char a[5][9];
	for (i = 0; i <= 4;i++)
	for (j = 0; j <= 8; j++)
		a[i][j] = '*';
	for (i = 0; i <= 4; i++)
	{
		for (j = 0; j <= i; j++)
			printf("\t");
		for (j = i; j <= i + 4; j++)
		    printf("%c\t", a[i][j]);
		    printf("\n");
	}

	return 0;
}