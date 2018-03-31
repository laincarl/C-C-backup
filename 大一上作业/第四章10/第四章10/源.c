#include<stdio.h>
int main()
{
	int I,t;
	t = 0;
	printf("请输入利润：\n");
	scanf_s("%d", &I);
	if (I <= 100000)
		t = 0.1*I;
	else if (I <= 200000)
		t = 10000 + 0.075*(I - 100000);
	else if (I <= 400000)
		t = 17500 + 0.05*(I - 200000);
	else if (I <= 600000)
		t = 27500 + 0.03*(I - 400000);
	else if (I <= 1000000)
		t = 33500 + 0.015*(I - 600000);
	else if (I > 1000000)
		t = 39500 + 0.001*(I - 1000000);
	printf("应发奖金数为：%d", t);
	return 0;

}