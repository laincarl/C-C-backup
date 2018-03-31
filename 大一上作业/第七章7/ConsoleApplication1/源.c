#include<stdio.h>
int main()
{
	char a[10], b[10];
	int i, j = 0;
	scanf_s("%s", a, 10);
	for (i = 0; a[i] != '\0'; i++)
	if (a[i] == 'a' || a[i] == 'e' || a[i] == 'i' || a[i] == 'o' || a[i] == 'u' || \
		a[i] == 'A' || a[i] == 'E' || a[i] == 'I' || a[i] == 'O' || a[i] == 'U')
	{
		b[j] = a[i];
		j++;
	}
	b[j] = '\0';
	printf("%s", b);
	return 0;
}