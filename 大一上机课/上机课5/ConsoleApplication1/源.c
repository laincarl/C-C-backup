#include<stdio.h>
int main()
{
	int i, a[5], b[5];
	void s(int b[5]);
	for (i = 0; i < 5; i++)
		scanf_s("%d", &a[i]);
	s(a);
	for (i = 0; i < 5; i++)
		printf("%d ", a[i]);
	return 0;
}
void s(int b[5])
{
	int i, j, k, t;
	for (i = 0; i < 4; i++)
	{
		k = i;
		for (j = i + 1; j < 5; j++)
		if (b[j] < b[k])
			k = j;
		t = b[k]; b[k] = b[i]; b[i] = t;
	}
}
