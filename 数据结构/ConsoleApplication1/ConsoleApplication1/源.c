/*#include<stdio.h>
int main()
{
	int i = 1;
	printf("it is%d", i);
	//return 0;
}*/
#include<stdio.h>
int main()
{
	int income, tax=1;
	//scanf("%d", &income);
	scanf("income:%d", &income);
	if (income>2000 && income <= 2500)
		tax = (income - 2000)*0.05;
	else if (income>2500 && income <= 4000)
		tax = (income - 2000)*0.1;
	else if (income>4000 && income <= 7000)
		tax = (income - 2000)*0.15;
	printf("tax=%d\n", tax);
	return 0;
}
