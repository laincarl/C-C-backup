#include<stdio.h> 
int main()
{
	int n, i = 1, sum = 1;
	printf("请输入一个正整数n：\n");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		sum = sum*i;
	printf("他的阶乘是:%d", sum);	return 0;
}