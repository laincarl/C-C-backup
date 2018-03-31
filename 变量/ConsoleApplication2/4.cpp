#include<stdio.h>
int main()
{
	short s;
	int i;
	long l;
	char c = 'a';
	float f;
	double d;
	bool boolean = true;
	s = 22015;
	i = 1000000;
	l = 65535;

	f = 0.23;
	d = 1.0E-4;

	printf("短整型变量：s=%d；\n", s);
	printf("整形变量：i=%d；\n", i);
	printf("长整型变量：l=%d；\n", l);
	printf("字符型变量：c=%c；\n", c);
	printf("浮点型变量: f=%f；\n", f);
	printf("双精度变量：d=%E；\n", d);
	printf("布尔型变量：boolean = %d；\n",boolean);
	return 0;
}