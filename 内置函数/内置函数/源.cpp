#include<iostream>
using namespace std;
inline int max(int a, int b, int c)//和宏定义函数的区别，比如1+1*1+1和（1+1）*（1+1）
{
	if (b > a)a = b;
	if (c > a)a = c;
	return c;
}
int main()
{
	int i = 7, j = 10, k = 25, m;
	m = max(i, j, k);
	cout << "max=" << m << endl;
	return 0;
}