#include<stdio.h>
int main()
{
	int year, month, day, sday=0,i,j;
	int dayday(int x, int y, int z);
	
	printf("�����������գ�");
	scanf_s("%d%d%d", &year, &month, &day);
	sday=dayday(year,month,day);
	
	printf("%d��%d��%d����%d��ĵ�%d��\n",year,month,day,year, sday);
	return 0;
}
int dayday(int x, int y, int z)
{
	int i, j;
	int s=0;
	int a[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int b[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
if ((x % 4 == 0 && x % 100 != 0) || (x % 400 == 0))//����һ�򣬰��겻���İ���һ��if (year)
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