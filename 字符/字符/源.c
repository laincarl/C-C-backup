#include<stdio.h>
int main()
{
	int i,a[20];
	printf("������20���ַ�");
	for (i = 1; i <= 20; i++)
		scanf_s("%c", &a[i]);
	for (i = 20; i >= 0; i--)
		printf("%c", a[i]);
	printf("\n");

	return 0;

}
