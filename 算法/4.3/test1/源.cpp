#include <iostream>
#include "alist.h"
using namespace std;
int main()
{
	AList<int>l1(20);
	l1.append(2);
	l1.append(23);
	l1.append(15);
	l1.append(5);
	l1.append(9);
	l1.moveToPos(2);
	return 0;
}