#include<stdio.h>
int main()
{
	int year;
	for (year = 2000; year <= 2020; ++year)
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))//����һ�򣬰��겻���İ���һ��
			printf("%d�����ꡣ\n", year);
		else
			printf("%d�������ꡣ\n", year);
	}
	return 0;
}