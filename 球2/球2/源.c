#include<stdio.h>
int main()
{
	int i=1, s1=0,s2=0,s3=0,s4=0,a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20;
	
	printf("请输入二十个数：\n");

	scanf_s("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &a1, &a2, &a3, &a4, \
		&a5, &a6, &a7, &a8, &a9, &a10, &a11, &a12, &a13, &a14, &a15, &a16, &a17, &a18, &a19, &a20);
	int ai = a1;
	for (i = 1; i <= 20; i++)
	{
		if (ai == 1)
			s1 = s1 + 1;
		else if (ai == 2)
			s2 = s2 + 1;
		else if (ai == 3)
			s3 = s3 + 1;
		else if (ai == 4)
			s4 = s4 + 1;
	}

	
	printf("红球的个数为：%d\n",s1);
	printf("黄球的个数为：%d\n",s2);
	printf("篮球的个数为：%d\n",s3);
	printf("白球的个数为：%d\n",s4);

		return 0;

}