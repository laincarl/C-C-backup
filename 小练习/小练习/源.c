#include<stdio.h> 
int main()
{
	int n, i = 1, sum = 1;
	printf("������һ��������n��\n");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		sum = sum*i;
	printf("���Ľ׳���:%d", sum);	return 0;
}