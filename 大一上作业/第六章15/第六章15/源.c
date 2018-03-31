#include<stdio.h>
#include<string.h>
int main()
{
	char s1[5], s2[5];
	int i;
	printf("input s2:\n");
scanf_s("%s",s2,80);//“≤ø…“‘gets_s(s2,80)
	for (i = 0; i <= strlen(s2); i++)
		s1[i] = s2[i];
	printf("%s", s1);//puts(s2);
	return 0;
}
