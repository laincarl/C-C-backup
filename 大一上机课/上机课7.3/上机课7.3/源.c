#include<stdio.h>
int main()
{
	int year[4] = { 2015, 2016, 2017, 2018 }, s, i,*p;
	s = 2015;
	p = year;
	void money(int *x);
	money(year);
	for (i = 0; i <= 3; i++, s++,p++)
		printf("%d年3月1号的机票为%d元\n", s,*p);
		return 0;
}
void money(int *x)
{
	int j, *k, day[4], y1 = 28, y2 = 29, y3 = 31;
	k = x;
	day[0] = y1 - 19 + 1;
	day[1] = y2 - 8 + 1;
	day[2] = y3 - 28 + y2 + 1;
	day[3] = y1 - 16 + 1;
	for (j = 0; j <= 3; j++, x++)
	{
		if (day[j] <= 12)
			*x = 300 + 100 * day[j];
		else if (day[j] <= 17)
			*x = 1500;
		else if (day[j] <= 29)
			*x = 1500 - (day[j] - 16) * 100;
		else
			*x = 300;
	}
}