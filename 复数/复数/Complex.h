#include <iostream>
using namespace std;

class Complex  //Complex类定义
{
	friend Complex operator+(const Complex &l, const Complex &r);
public:
	Complex(){ real = 0; imag = 0; }   //默认构造函数
	Complex(double r, double i)   //构造函数重载
	{
		real = r; imag = i;
	}
	//声明复数相加函数
	//Complex add(const Complex &c2)const;
	//Complex operator+(const Complex &c2)const;
	void display();             //声明输出函数
private:
	double real;                 //实部
	double imag;                 //虚部
};
Complex operator+(const Complex &l, const Complex &r);

/*Complex Complex::add(const Complex &c2)
const{
	Complex c;
	c.real = real + c2.real;
	c.imag = imag + c2.imag;
	return c;
}*/
void Complex::display(){         //定义输出函数
	cout << "(" << real << ", " << imag << "i)" << endl;
}
/*Complex Complex::operator+(const Complex &c2)
const{
	Complex c;
	c.real = real + c2.real;
	c.imag = imag + c2.imag;
	return c;
}
*/