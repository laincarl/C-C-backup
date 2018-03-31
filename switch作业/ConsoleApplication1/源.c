#include <stdio.h>
int main(){
	int n, sum;
	int i = 1;
	printf("%d\n", i);
	while (scanf_s("%d", &n) == 1){
		sum = 0;
		for (i = 1; i <= n; i++)
			sum += i;
		printf("%d\n\n", sum);
	}
	return 0;
}
/*#include <stdio.h>
int main()
{
	int n, sum;
	while (scanf("%d", &n) == 1)
	{
		sum = 0;
		while (n != 0)
		{
			sum += n--;
		}
		printf("%d\n\n", sum);
	}
	return 0;
}*/