#include <stdio.h>
int main()
{
	int i, score[8], s=0, below[8];
	int fun(int a[8],int below[8], int m);
	printf("������8������\n");
	for (i = 0; i <= 7; i++)
	
	scanf_s("%d", &score[i]);
	s = fun(score, below, s);
	printf("����ƽ���ֵ�����%d��\n", s);
	printf("���ǵķ���Ϊ:");
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