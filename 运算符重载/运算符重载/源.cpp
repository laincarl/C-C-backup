#include<iostream>
using namespace std;
class Complex
{ public:
Complex(){ real = 0; imag = 0; }
Complex(int r, int i){ real = r; imag = i; }
Complex operator +(Complex &c2);
private:
	int real;
	int imag;
};
	Complex Complex::operator + (Complex &c2)
	{
		Complex c;
		c.real = real + c2.real;
		c.imag = imag + c2.imag;
		return c;
	}
	int main()
	{
		Complex c1(3, 4), c2(5, -10), c3;

	}
	