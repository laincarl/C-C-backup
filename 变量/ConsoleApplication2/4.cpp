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

	printf("�����ͱ�����s=%d��\n", s);
	printf("���α�����i=%d��\n", i);
	printf("�����ͱ�����l=%d��\n", l);
	printf("�ַ��ͱ�����c=%c��\n", c);
	printf("�����ͱ���: f=%f��\n", f);
	printf("˫���ȱ�����d=%E��\n", d);
	printf("�����ͱ�����boolean = %d��\n",boolean);
	return 0;
}