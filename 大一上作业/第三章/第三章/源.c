#include<stdio.h>
#include<math.h>
int main()
{
	int d, p;
	float r, m;
	d = 300000;
	p = 6000;
	r = 0.01;
	m = log(p / (p - d*r)*(1 + r));
	printf("m=%.1f\n", m);
	return 0;
}
