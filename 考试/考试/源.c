#include <stdio.h>
#define N 80
int main()
{
	int i = 0,m;
	char str[N];
	char ch;
	printf("\n Input a string:\n");
	gets_s(str,80);
	printf("\n Input a charator;\n");
	scanf_s("%c", &ch,1);
	//ch = getchar();
	for (i = 0; i <= 80 - 1;i++)
		if (str[i] == ch)
			m = i;
	for (i=m; i <= 80 - 1;i++)
	str[i] ='\0';
	printf("\n*** display string ***\n");
	puts(str);
	return 0;
}
