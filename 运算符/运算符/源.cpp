//��10.1 ͨ��������ʵ�ָ������
#include <iostream>
using namespace std;
class Complex  //Complex�ඨ��
{
public:
	Complex(){ real = 0; imag = 0; }   //Ĭ�Ϲ��캯��
	Complex(double r, double i)   //���캯������
	{
		real = r; imag = i;
	}
	//����������Ӻ���
	Complex add(const Complex &c2)const;
	void display();             //�����������

private:
	double real;                 //ʵ��
	double imag;                 //�鲿
};


Complex Complex::add(const Complex &c2)const{
	Complex c;
	c.real = real + c2.real;
	c.imag = imag + c2.imag;
	return c;
}
void Complex::display(){         //�����������
	cout << "(" << real << ", " << imag << "i)" << endl;
}

int main() {
	Complex c1(3, 4), c2(5, -10), c3;  //����3����������
	c3 = c1.add(c2);               //���ø�����Ӻ���
	cout << "c1 = "; c1.display();    //���c1��ֵ
	cout << "c2 = "; c2.display();    //���c2��ֵ
	cout << "c1 + c2 = "; c3.display(); //���c3��ֵ
	return 0;
}

