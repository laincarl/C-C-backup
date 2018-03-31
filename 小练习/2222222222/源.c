#include<stdio.h>
void main()
{
	int n,i, s=1;
	scanf_s("%d",&n);
	for (i = 1; i <= n; i++)
		s = s*i;
	printf("%d", s);
}