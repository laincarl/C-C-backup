#include<stdio.h>
int main()
{
/*int a;
a = 99;
printf("%d %d\n", a++, ++a);
*/
	int a;
	a = 99;
	printf("%d\n",++a);
	printf("%d\n", a++);
	printf("%d\n", a);
}/*a++是先执行表达式后再自增，执行表达式时使用的是a的原值。
++a是先自增再执行表达示，执行表达式时使用的是自增后的a。
例：
int a=0
printf("%d",a++); //输出0,执行完后a=1

int a=0
printf("%d",++a);//输出1，执行完后a=1
程序是按照步骤来的，如果是a++的话，在那一行代码中，
a的值是不变的，下一行才发生变化，++a则是在那一行已经发生了变化。*/




