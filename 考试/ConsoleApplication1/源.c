#include <stdio.h>
int main()
{
	int i, score[8], s=0, below[8];
	int fun(int a[8],int below[8], int m);
	printf("请输入8个分数\n");
	for (i = 0; i <= 7; i++)
	
	scanf_s("%d", &score[i]);
	s = fun(score, below, s);
	printf("低于平均分的人有%d个\n", s);
	printf("他们的分数为:");
	for (i = 0; i <= s - 1; i++)
		printf("%4d", below[i]);
	return 0;

}
int fun(int a[8],int b[8], int m)
{
	int below[8];
	int sum = 0, i, average;
	m = 0;
	for (i = 0; i <= 7; i++)
		sum = sum + a[i];
	average = sum / 8;
	for (i = 0; i <= 7; i++)
	{
		if (a[i] < average)
		{
			b[m] = a[i];
			m = m + 1;
			
		}
	}
	return m;
}