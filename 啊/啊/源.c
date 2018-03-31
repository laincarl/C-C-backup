#include<stdio.h>
int main()
{
	int i;
	char a;
	printf("敢按下回车吗？！");
	for (i = 0; i!=-1; i++)
	{
		a = getchar();
		if (a== '\n')
		printf("敢按下回车吗？！");
	}
	return 0;
}