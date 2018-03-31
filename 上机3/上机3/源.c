#include<stdio.h>
int main()
{
	double f1 = 1, f2 = 1, f3;
	int i;
	printf("%30.0f\n%30.0f\n", f1, f2);
	for (i = 1; i <= 98; i++)
	{
		f3 = f1 + f2;
		printf("%30.0f\n",f3);
		f1 = f2;
		f2 = f3;
		
	}
	return 0;
}