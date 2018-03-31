#include<stdio.h>
int main()
{
	int i,s;
	int term(int x);
	scanf_s("%d", &i);
	s = term(i);
	printf("%d", s);
	return 0;
}
int term(int x)
{
	int y;
	if (x == 1)
		y = 1;
	else
		y = x*term(x - 1);
	
	return y;
}