#include<stdio.h>
void main()
{
	int i, j, n, k, g, s;
	int a[15][15] = { 0 };
	printf("�ú���ֻ֧��������ħ��������\n");
	do{
		printf("������һ������\n");
		scanf_s("%d", &n);
	} while (n % 2 == 0);
	i = 1;
	j = (n + 1) / 2;
	a[0][j - 1] = 1;
	for (k = 2; k <= n*n; k++)
	{
		i = i - 1;
		j = j + 1;
		s = 0;
		g = 0;
		if (i == 0)
		{
			i = n;
			g = 1;
		}
		if (j == n + 1)
		{
			j = 1;
			s = 1;
		}
		if (a[i - 1][j - 1] == 0)
		{
			a[i - 1][j - 1] = k;
		}
		else
		{
			if (g == 1)
				i = 0;
			if (s == 1)
				j = n + 1;
			i = i + 2;
			j = j - 1;
			a[i - 1][j - 1] = k;
		}
	}
	printf("���õ���ħ����Ϊ\n");
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
			printf("%4d", a[i][j]);
		printf("\n");
	}
}