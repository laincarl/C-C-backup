#include<stdio.h>
int main()
{
	int i;
	void move(int[20], int, int);
	int number[20], n, m, i;
	printf("输入数字个数：");
	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
		scanf_s("%d", &number[i]);
	printf("输入移动间隔：");
	scanf_s("%d,&m");
	move(number, n, m);
	printf("Now,they are:\n");
	for (i = 0; i < n; i++)
		printf("%d  ", number[i]);
	printf("\n");
	return 0;
}
void move(int array[20], int n, int m)
{
	int *p, array_end;
	array_end = *(array + n - 1);
	for (p = array + n - 1; p>array; p--)
		*p = *(p - 1);
	*array = array_end;
	m--;
	if (m > 0) move(array, n, m);
}