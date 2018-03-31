#include<stdio.h>
int main()
{
	int year;
	for (year = 2000; year <= 2020; ++year)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))//四年一闰，百年不闰，四百年一闰
			printf("%d是闰年。\n", year);
		else
			printf("%d不是闰年。\n", year);
	}
	return 0;
}