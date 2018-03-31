#include<stdio.h>
int main()
{
	int I, t,m;
	t = 0;
	printf("请输入利润：\n");
	scanf_s("%d", &I);
	m = I/100000;
	if (I>= 1000000)
		m = 10;

	else if (m == 5 || m == 3)
		m = m - 1;
	else if (m ==7 || m == 8 || m == 9)
		m = 6;
	switch (m)
	{
	case 0:	
		    t = 0.1*I;
	case 1:
		t = 10000 + 0.075*(I - 100000); break;
	case 2:
		t = 17500 + 0.05*(I - 200000); break;
	case 4:
		t = 27500 + 0.03*(I - 400000); break;
	case 6:
		t = 33500 + 0.015*(I - 600000); break;
	case 10:
		t = 39500 + 0.001*(I - 1000000); break;
	}
	printf("应发奖金数为：%d", t);
	return 0;

}