#include<iostream>
using namespace std;
int T(double n)
{
	int c;
	double b = n / 2;
	if (n == 1)
		c = 1;
	else		
	c=T(ceil(n / 2)) + T(floor(n / 2)) + n;
	return c;
}

int main()
{
	double m;
	cout << "ÇëÊäÈënµÄÖµ:";
	while (cin >> m)
		cout << T(m) << endl;
	return 0;
}