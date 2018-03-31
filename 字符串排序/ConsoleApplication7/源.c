#include<stdio.h>
#include<string.h>
int main()
{
	int i;
	char str1[10], str2[10], str3[10], temp[10];
	printf("please input three strings:\n");
	scanf_s("%s", str1,10);
	scanf_s("%s", str2,10);
	scanf_s("%s", str3,10);
	if (str2[0]>str3[0])
	for (i = 0; i < 10; i++)
	{
		temp[i] = str3[i];
		str3[i] = str2[i];
		str2[i] = temp[i];
	}
	if (str1[0] <= str2[0])

	{
		puts(str1);
		puts(str2);
		puts(str3);
	}
	else if (str1[0] <= str3[0])
	{
		puts(str2);
		puts(str1);
		puts(str3);
	}
	else

	{
	puts(str2);
	puts(str3);
	puts(str1);
	}
	
	
	return 0;
}