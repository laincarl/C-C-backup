#include<stdio.h>
int main()
{
	int year;
	printf("������һ����ݣ�");
	scanf_s("%d", &year);
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))//����һ�򣬰��겻���İ���һ��
		printf("%d�������ꡣ\n", year);
	else
		printf("%d�겻�����ꡣ\n", year);
	return 0;
}