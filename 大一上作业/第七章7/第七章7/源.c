#include<stdio.h>
int main()
{
	void x(char[], char[]);
	char c[100], d[100];
	printf("请输入字符串：");
	scanf_s("%s", c, 100);
	x(c, d);
	printf("其中的元音字母为:%s", d);
	return 0;
}
void x(char a[], char b[])
{
	int i, j = 0;
	for (i = 0; a[i] != '\0'; i++)
	if (a[i] == 'a' || a[i] == 'e' || a[i] == 'i' || a[i] == 'o' || a[i] == 'u' || \
		a[i] == 'A' || a[i] == 'E' || a[i] == 'I' || a[i] == 'O' || a[i] == 'U')
	{
		b[j] = a[i];
		j++;
	}
	b[j] = '\0';
}