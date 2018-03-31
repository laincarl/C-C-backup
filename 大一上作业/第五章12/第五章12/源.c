#include<stdio.h>
int main()
{
	int s, i;
	s = 1;
	for (i = 1; i <= 9; i++)
		s = (s + 1)*2;
	printf("桃子的总数为：%d", s);
	return 0;
}