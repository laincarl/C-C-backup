#include<iostream>
#include"LList.h"
using namespace std;
int min(int a, int b)
{
	return (a < b) ? a : b;
}

void connect(LList<int>&a, LList<int>&b, LList<int>&c)
{
	a.moveToPos(0);
	b.moveToPos(0);
	c.moveToPos(0);
	while (a.getPValue() != NULL&&b.getPValue() != NULL)
	{
		if (a.getValue() < b.getValue())
		{
			c.insert(a.getValue());
			a.next();
		}
		else
		{
			c.insert(b.getValue());
			b.next();
		}
		c.moveToPos(c.currPos() + 1);
	}
	while (a.getPValue() != NULL)
	{
		c.append(a.getValue());
		a.next();
	}
	while (b.getPValue() != NULL)
	{
		c.append(b.getValue());
		b.next();
	}
}

int main()
{
	LList<int>a, b, c;
	a.append(1);
	a.append(6);
	a.append(7);
	a.append(8);

	b.append(5);
	b.append(9);
	b.append(11);
	b.append(15);
	b.append(20);
	b.append(21);

	connect(a, b, c);
	c.moveToPos(0);
	for (; c.getPValue() != NULL;)
	{
		cout << c.getValue() << "   ";
		c.next();
	}
	return 0;

}