#include<stdio.h>
int main()
{
	int i, a[20];
	printf("������20���ַ�:\n");
	for (i = 0; i <= 19; i++)
	{
		a[i]=getchar();
	}
	for (i = 19; i >= 0; i--)
	{
		putchar(a[i]);
	}
	printf("\n");

	return 0;

}
