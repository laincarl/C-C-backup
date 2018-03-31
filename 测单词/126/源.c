#include<stdio.h>
int main()
{
	int i,m=0,n;
	char a[100];
	gets_s(a, 100);
	for (i = 0; a[i-1] != '.'; i++)

	{
		if ((a[i] != ' ')&&(a[i]!='.'))
			m = m + 1;
		else if (m != 0)
		{
			printf("%d", m);
			if (a[i] != '.')
				printf(" ");
			m = 0;
		}
	}
	return 0;
}