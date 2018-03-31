#include<stdio.h>
int main()
{
	int year;
	printf("请输入一个年份：");
	scanf_s("%d", &year);
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))//四年一闰，百年不闰，四百年一闰
		printf("%d年是闰年。\n", year);
	else
		printf("%d年不是闰年。\n", year);
	return 0;
}