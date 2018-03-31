#include<iostream>
#include"astack.h"
using namespace std;
int main()
{
	double n;
	AStack<int> S;
	int sum, arr[100], i = 2; 
	arr[0] = 0;
	arr[1] = 1;
	cout << "ÇëÊäÈënµÄÖµ:";
	cin >> n;
	if (n == 1)
	{
		cout << "1" << endl;
		return 0;
	}
	double m = 2;
	for (; n >= m; m++)
	{
		arr[(int)m] = arr[(int)ceil(m / 2)] + arr[(int)floor(m / 2)] + (int)m;
		S.push(arr[(int)m]);
	}
	cout << S.pop() << endl;
	return 0;

}