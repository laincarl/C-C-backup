#include<stdio.h>
int main()
{
	int i, j, k, l, d1, d2, d3, d4, d5;
	i = 0;
	j = 0;
	k = 0;
	l = 0;
	printf("�������������\n");
	scanf_s("%d,%d,%d,%d,%d,%d", &d1, &d2, &d3, &d4, &d5);
	if (d1 == 1)
		i = i + 1;
	else if (d1 == 2)
		j = j + 1;
	else if (d1 == 3)
		k = k + 1;
	else if (d1 == 4)
	l = l + 1;

	if (d2 == 1)
		i = i + 1;
	else if (d2 == 2)
		j = j + 1;
	else if (d2 == 3)
		k = k + 1;
	else if (d2 == 4)
	l = l + 1;

	if (d3 == 1)
		i = i + 1;
	else if (d3 == 2)
		j = j + 1;
	else if (d3 == 3)
		k = k + 1;
	else if (d3 == 4)
	l = l + 1;

	if (d4 == 1)
		i = i + 1;
	else if (d4 == 2)
		j = j + 1;
	else if (d4 == 3)
		k = k + 1;
	else if  (d4 == 4)
		l = l + 1;

	if (d5 == 1)
		i = i + 1;
	else if (d5 == 2)
		j = j + 1;
	else if (d5 == 3)
		k = k + 1;
	else if (d5 == 4)
	    l = l + 1;
	printf("����ĸ���Ϊ��%d\n", i);
	printf("����ĸ���Ϊ��%d\n", j);
	printf("����ĸ���Ϊ��%d\n", k);
	printf("����ĸ���Ϊ��%d\n", l);
	return 0;

}
