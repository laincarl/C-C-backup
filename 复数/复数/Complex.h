#include <iostream>
using namespace std;

class Complex  //Complex�ඨ��
{
	friend Complex operator+(const Complex &l, const Complex &r);
public:
	Complex(){ real = 0; imag = 0; }   //Ĭ�Ϲ��캯��
	Complex(double r, double i)   //���캯������
	{
		real = r; imag = i;
	}
	//����������Ӻ���
	//Complex add(const Complex &c2)const;
	//Complex operator+(const Complex &c2)const;
	void display();             //�����������
private:
	double real;                 //ʵ��
	double imag;                 //�鲿
};
Complex operator+(const Complex &l, const Complex &r);

/*Complex Complex::add(const Complex &c2)
const{
	Complex c;
	c.real = real + c2.real;
	c.imag = imag + c2.imag;
	return c;
}*/
void Complex::display(){         //�����������
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