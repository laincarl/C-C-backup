#include<stdio.h>
int main()
{
	int a[4], i,j,t;
	printf("�����ĸ�����\n");
	for (i = 0; i <= 3; i++)

		scanf_s("%d", &a[i]);
	printf("\n");
	for (j = 0; j <=3;j++)
	for (i = 0; i <=3 - j;i++)
	if (a[i] < a[i + 1])
	{
		t = a[i]; a[i] = a[i + 1]; a[i + 1] = t;
	}
	printf("��С��������Ϊ��\n");
	for (i = 3; i>=0; i--)
		printf("%d", a[i]);
	printf("\n");
	return 0;
}