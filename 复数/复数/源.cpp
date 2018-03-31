//例10.1 通过函数来实现复数相加
#include "Complex.h"
Complex operator+(const Complex &l, const Complex &r)
{
	Complex c;
	c.real = l.real + r.real;
	c.imag = l.imag + r.imag;
	return c;
}

int main() {
	Complex c1(3, 4), c2(5, -10), c3(3,6);
	Complex c4(2, 3), c5;//定义3个复数对象
	double d = 10.0;
	c5 = c1 + c2 + c3 + c4;
	c1 = Complex(d,0) + c2;
	//c3 = c1.add(c2);               //调用复数相加函数
	cout << "c1 = "; c1.display();    //输出c1的值
	cout << "c2 = "; c2.display();    //输出c2的值
	cout << "c1 + c2 = "; c3.display(); //输出c3的值
	return 0;
}




