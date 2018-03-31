#include<stdio.h>
int main()
{
	float add(float x, float y);
	float a, b, c;
	printf("Please enter a and b:");
	scanf_s("%f%f", &a, &b);
	c = add(a, b);
	printf("sum is %f:", c);
	return 0;
}
float add(float x, float y)
{
	float z;
	z = x + y;
	return z;
}
