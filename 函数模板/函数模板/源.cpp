#include<iostream>
using namespace std;
template<typename T>//也可以不用T
T max(T a, T b)
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