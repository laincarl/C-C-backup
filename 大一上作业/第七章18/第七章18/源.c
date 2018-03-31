#include<stdio.h>
int main()
{
	int year, month, day, sday=0,i,j;
	int dayday(int x, int y, int z);
	
	printf("请输入年月日：");
	scanf_s("%d%d%d", &year, &month, &day);
	sday=dayday(year,month,day);
	
	printf("%d年%d月%d日是%d年的第%d天\n",year,month,day,year, sday);
	return 0;
}
int dayday(int x, int y, int z)
{
	int i, j;
	int s=0;
	int a[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int b[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
if ((x % 4 == 0 && x % 100 != 0) || (x % 400 == 0))//四年一闰，百年不闰，四百年一闰if (year)
{
	i = 0;
	while (y - i - 1 > 0)
	{
		s = s + a[i];
		s = s + z;
		i++;
	}
}
else
{
	i = 0;
	while (y - i - 1 > 0)
	{
		s = s + a[i];
		s = s + z;
		i++;
	}
}
return s;
}