#include<stdio.h>
int main()
{
	int i, a, b, c, d,e;
	a = 1, b = 2, c = 3, d = 4,e=5;
	for (i = 1; i <= 5; i++)
	{
		if (i == 3)
			printf("*\t*\t*\t*\t*\t*\t*\n");
		
		else if (i!=3)
			printf("*\t%d\t%d\t*\t%d\t%d\t*\n", a, b, d, e);
			a = a + 1, b = b + a, c = c + b, d = d + c, e = e + d;
		
	}
		

	
	return 0;
}