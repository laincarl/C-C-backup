#include "rational.h"

// Subtract(): subtract r from current Rational and return result

Rational Rational::Subtract(const Rational &r) const {
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	// complete function body
	int e = a*d - b*c;
	int f = b*d;
	int g = e%f;
	if (g == 0)
	{
		e = (a*d - b*c) / f;
		f = b*d / f;
		return Rational(e, f);
	}
	else {
		while (g != 0)
		{
			e = f;
			f = g;
			g = e%f;
		}
		e = (a*d - b*c) / f;
		f = b*d / f;
		return Rational(e, f);
	}
}
Rational Rational::Divide(const Rational &r) const{
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	int e = a*d;
	int f = b*c;
	int g = e%f;
	if (g == 0)
	{
		e = a*d / f;
		f = b*c / f;
		return Rational(e, f);
	}
	else {
		while (g != 0)
		{
			e = f;
			f = g;
			g = e%f;
		}
		e = a*d / f;
		f = b*c / f;
		return Rational(e, f);
	}
	//���Լ�����㷨��
	//1��	g�����洢e��f��������
		//2��	���r����0���㷨��ֹ������fΪ���Լ�������r��Ϊ0������������
		//e = f, f = g, �ٷ��ص�һ��ѭ����

	
};
// operator -: overload subtraction for rationals

Rational operator-(const Rational &r, const Rational &s) {
	return r.Subtract(s);
}

// operator /: overload division for rationals

Rational operator/(const Rational &r, const Rational &s) {
	return r.Divide(s);
}
