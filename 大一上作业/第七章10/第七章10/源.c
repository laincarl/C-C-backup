#include<stdio.h>
int main()
{
	int i, begin1 =-1, begin2 = 0, end1 = 0, end2 = 0, long1 = 0, long2 = 0;
	char a[40];
	printf("请输入一个句子：");
	gets_s(a, 40);
	printf("\n");
	for (i = 0; i<=19; i++)
	{
		if (a[i] == ' '||a[i]=='\0')
		{
			end1 = i;
			long1 = end1 - begin1-1;
			begin1 = i;
		}
		if (long1 > long2)
		{
			long2 = long1;
			begin2 = begin1;
			end2 = end1;
		}
	}
	printf("最长的单词为：");
	for (i = end2 - long2; i <= end2; i++)
		printf("%c", a[i]);

	return 0;
}