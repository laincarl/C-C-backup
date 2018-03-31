#include<iostream>
using namespace std;
/*int max(int a, int b)//第一种：函数参数的类型不同，个数相同
{
	if (a < b)a = b;
	return a;
}
float max(float a, float b)
{
	if (a < b)a = b;
	return a;
}
long max(long a, long b)
{
	if (a < b)a = b;
	return a;
}
int main()
{
	int c, d;
	float e, f;
	long g, h;
	cout << "输入两个整数，小数，长整数" << endl;
	cin >> c >> d;
	cin >> e >> f;
	cin >> g >> h;
	int m;
	float n;
	long o;
	m = max(c, d);
	cout << m << endl;
	n = max(e, f);
	cout << n << endl;
	o = max(g, h);
	cout << o << endl;
	return 0;
}      
//第二种：函数参数个数不同，类型相同
int max(int a, int b)
{
	if (a < b)a = b;
	return a;
}
int max(int a, int b, int c)
{
	if (a < b)a = b;
	if (a < c)a = c;
	return a;
}
int main()
{
	int c, d,e;
	cin >> c >> d >> e;
	cout<<max(c,d)<<endl;
	cout<<max(c,d,e)<<endl;
	return 0;
}*/
//第三种：类型个数都不同
int max(int a, int b)
{
	if (a < b)a = b;
	return a;
}
float max(float a, float b, float c)
{
	if (a < b)a = b;
	if (a < c)a = c;
	return a;
}
int main()
{
	int c, d;
	float e, f, g;
	cin >> c >> d >> e >> f >> g;
	cout << max(c, d) <<endl<< max(e, f, g) << endl;
	return 0;
}