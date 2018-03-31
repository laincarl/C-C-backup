#include<stdio.h>
int main()
{
	int b[2][3] = { { 0, 1, 2 }, { 3, 4, 5 } };
	int j, k;
	for (j = 0; j <= 1; j++)
	{
		for (k = 0; k <= 2; k++)
		{
			printf("b[%d][%d]µÄÖµÎª:%5d\n", b[j][k]);
		}

	}
	return 0;
}