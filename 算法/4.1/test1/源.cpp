#include <iostream>
#include "alist.h"
using namespace std;
int main()
{
	AList<int>l1;
	l1.append(2);
	l1.append(23);
	l1.append(15);
	l1.append(5);
	l1.append(9);
	cout << "移除之前"<<"\n";
	while (l1.currPos()<l1.length())
	{
		cout << l1.getValue() <<" ";
		l1.next();
	}
	cout<< "\n";
	l1.moveToPos(2);
	
	int del = l1.remove();
	cout << "移除之后" << "\n";
	l1.moveToStart();
	while (l1.currPos()<l1.length())
	{
		cout << l1.getValue() <<" ";
		l1.next();
	}
	return 0;
}