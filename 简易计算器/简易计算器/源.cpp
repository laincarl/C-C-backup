#include<iostream>
using namespace std;
int main()
{
	double a, b;
	char c;
	a = 0;
	b = 0;
	cin >> a >> c >> b;
	if (c == '+')
		cout << a << "+" << b << "=" << a + b << endl;
	else if (c == '-')
		cout << a << "-" << b << "=" << a - b << endl;
	else if (c == '*')
		cout << a << "*" << b << "=" << a * b << endl;
	else if (c == '/')
		cout << a << "/" << b << "=" << a / b << endl;
	return 0;
}