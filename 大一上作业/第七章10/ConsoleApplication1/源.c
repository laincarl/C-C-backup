#include<stdio.h>
int main()
{
	int i, g1 = 0, g2 = 0, j = 0, g = 0;
	char a[40];
	gets_s(a, 40);
	for (i = 0; (a[i] >= 'A'&&a[i] <= 'Z') || (a[i] >= 'a'&&a[i] <= 'z'); i++)
		g1 = i + j + 1;
	j++;
	if (g1 > g)
		g = g1;
	for (i = 0; i <= 39; i++)
	{
		for (i = g + 1; (a[i] >= 'A'&&a[i] <= 'Z') || (a[i] >= 'a'&&a[i] <= 'z'); i++)
			g2 = i - g1 + j;
		j++;
		if (g2 > g)
			g = g2;
	}
	printf("%d", g);
	return 0;
}