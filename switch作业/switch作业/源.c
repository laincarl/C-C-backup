#include<stdio.h>
int main()
{
	void y(int n);
	int num;
	scanf_s("%d", &num);
	if (num < 0)
	{
		printf("- ");
		num = -num;
	}
	y(num);
	return 0;
}
void y(int n)
{
	int i;
	if ((i = n / 10) != 0)
		y(i);
	{
		putchar(n + 48);
		putchar(32);
	}
}