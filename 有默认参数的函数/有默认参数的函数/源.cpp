#include<iostream>
using namespace std;
int max(int a, int b = 1)//函数不能既做重载函数又做有默认参数的函数
{
	if (a < b)a = b;
	return a;
}
int main()
{
	cout << max(5) << endl<<max(2, 4) << endl;
	return 0;
}