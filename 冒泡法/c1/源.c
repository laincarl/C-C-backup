#include<stdio.h>
int main()
{
	int i, j, t, a[8];
	printf("Please input eight number:");
	for (i = 0; i < 8; i++)
		scanf("%d", &a[i]);
	for(i=0;i<8;i++)
	{
		for(j=0;j<8-i;j++)
		if (a[j]<a[j + 1])
		{
			t = a[j];
			a[j] = a[j + 1];
		    a[j+1]=t;
		}

	}
	for (i = 0; i < 8; i++)
		printf("%d ", a[i]);
	return 0;
}