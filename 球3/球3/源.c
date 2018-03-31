#include<stdio.h>
int main()
{
	int a[20], i,s1=0, s2=0, s3=0, s4=0;
	
	for (i = 0; i <= 19; i++)
	{
		scanf_s("%d", &a[i]);
		if (a[i] == 1)
			s1 = s1 + 1;
		else if (a[i] == 2)
			s2 = s2 + 1;
		else if (a[i] == 3)
			s3 = s3 + 1;
		else if (a[i] == 4)
			s4 = s4 + 1;
	}
	printf("红球的个数为;%d\n",s1);
    printf("黄球的个数为:%d\n",s2);
	printf("蓝球的个数为;%d\n",s3);
	printf("白球的个数为;%d\n",s4);
	return 0;

}