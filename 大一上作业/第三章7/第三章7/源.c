#include<stdio.h>
int main()
{
	float r, l, s1, s2, v1, v2, t;
	int h;
	t = 3.1415926535;
	h = 3;
	scanf_s("%f,%d", &r, &h);
	l = 2 * t*r;
	s1 = t*r*r;
	s2 = 4 * t*r*r;
	v1 = 4 * t*r*r / 3;
	v2 = t*r*r*h;
	printf("Բ�ܳ�Ϊ��%.1f\n", l);
	printf("Բ���Ϊ��%.1f\n", s1);
	printf("Բ������Ϊ��%.1f\n", s2);
	printf("Բ�����Ϊ��%.1f\n", v1);
	printf("Բ�����Ϊ��%.1f\n", v2);
	return 0;
}
