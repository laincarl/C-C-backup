#include<stdio.h>
int main()
{
	void term(int *p1, int *p2);
	int *point_1, *point_2, a, b;
	printf("please enter a and b:");
	scanf_s("%d,%d", &a, &b);
	point_1 = &a;
	point_2 = &b;
	if (a < b)
		term(point_1, point_2);
	printf("max=%d,min=%d", *point_1, *point_2);
	return 0;
}
void term(int *p1, int *p2)
{
	int p;
	p = *p1;
	*p1 = *p2;
	*p2 = p;
}