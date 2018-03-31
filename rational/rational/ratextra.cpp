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
	//最大公约数的算法：
	//1、	g用来存储e除f的余数。
		//2、	如果r等于0，算法终止，并且f为最大公约数。如果r不为0，则重新设置
		//e = f, f = g, 再返回第一步循环。

	
};
// operator -: overload subtraction for rationals

Rational operator-(const Rational &r, const Rational &s) {
	return r.Subtract(s);
}

// operator /: overload division for rationals

Rational operator/(const Rational &r, const Rational &s) {
	return r.Divide(s);
}
