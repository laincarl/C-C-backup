#include<iostream>
using namespace std;
/*int max(int a, int b)//��һ�֣��������������Ͳ�ͬ��������ͬ
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
	cout << "��������������С����������" << endl;
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
//�ڶ��֣���������������ͬ��������ͬ
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
//�����֣����͸�������ͬ
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