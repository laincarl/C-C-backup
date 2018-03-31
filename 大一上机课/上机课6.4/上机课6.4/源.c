#include<stdio.h>
int main()
{
	void inv(int b[],int n);
	int i, a[10] = { 3, 7, 9, 11, 0, 6, 7, 5, 4, 2 };
	printf("the original array:\n");
	for (i=0;i<10;i++)
	printf("%d ", a[i]);
	printf("\n");
	inv(a,10);
	printf("the interted array:\n");
	for (i = 0; i<10; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
void inv(int b[],int n)
{
	int term,i; 
	for (i = 0; i <=4; i++)
	{
		term = b[i];
		b[i] = b[9-i];
		b[9-i] = term;
	}
}