#include<stdio.h>
int main()
{
	int i, j, k = 5, s = 1, m = 0, n = 0;
	float a[1][5], a1, a2, s1 = 0, s2 = 0,max=0,sa=0,sa2=0,f=0;
	for (i = 0; i <= (s - 1); i++)
	for (j = 0; j <= (k - 1); j++)
		scanf_s("%f", &a[i][j]);
	for (i = 0; i <= s - 1; i++)
	{
		for (j = 0; j <= k - 1; j++)
			s1 = s1 + a[i][j];
			a1 = s1 / k;
			sa = sa + a1;
			sa2 = sa2 + a1*a1;
			s1 = 0;
		printf("学生%d的平均分为：%.2f\n", i+1, a1);
	}
	for (j = 0; j <= k - 1; j++)
	{
		for (i = 0; i <= s - 1; i++)
			s2 = s2 + a[i][j];
		a2 = s2 / s;
		s2 = 0;
		printf("学科%d的平均分为：%.2f\n", j+1, a2);
	}
	for (i = 0; i <= (s - 1); i++)
	for (j = 0; j <= (k - 1); j++)
	{
		if (a[i][j] > max)
		{
			max = a[i][j];
			m = i + 1;
			n = j + 1;
		}
	}
	printf("最高分为学生%d的学科%d:%.2f分\n",m, n, max);
	f = sa2 / s - sa*sa / s / s;
	printf("方差为：%f\n", f);
	return 0;
}