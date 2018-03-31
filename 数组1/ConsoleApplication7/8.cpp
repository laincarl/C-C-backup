#include<stdio.h>
int main()
{
	int i, a[5];
	
	for (i = 4; i >= 0; i--)
		a[i] = i + 1;
	
		for (i = 0; i <= 4; i++)
	
		printf("a[%d]µÄÖµÎª£º%d\n",i, a[i]);
	
	return 0;
}