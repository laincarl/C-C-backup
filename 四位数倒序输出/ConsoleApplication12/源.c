#include <stdio.h>
void main()
{
	printf("������һ����λ��");
	int num=0;
	scanf_s("%d", &num);
	if (num > 999 && num < 10000)
	while (num>0)
	{
		printf("%d", num % 10);
		num /= 10;
	}
	else
		printf("������������Ϲ���\n");
}
