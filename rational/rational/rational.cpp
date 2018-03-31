#include <iostream>
#include <string>
using namespace std;

#include "rational.h"


// (numer, denom) constructor
Rational::Rational(int numer, int denom) {
	SetNumerator(numer);
	SetDenominator(denom);
}

// get the numerator
int Rational::Numerator() const {
	return NumeratorValue;
}

// get the denominator
int Rational::Denominator() const {
	return DenominatorValue;
}

// set the numerator
void Rational::SetNumerator(int numer) {
	NumeratorValue = numer;
}

// set the denominator
void Rational::SetDenominator(int denom) {
	if (denom != 0)
		DenominatorValue = denom;
	else {
		cerr << "Illegal denominator: " << denom
			<< " using 1" << endl;
		DenominatorValue = 1;
	}
}

// adding Rationals
Rational Rational::Add(const Rational &r) const {
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	return Rational(a*d + b*c, b*d);
}

// multiplying Rationals
/*Rational Rational::Subtract(const Rational &r) const{
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	return Rational(a*d + b*c, b*d);
};*/

Rational Rational::Multiply(const Rational &r) const {
	int a = Numerator();
	int b = Denominator();
	int c = r.Numerator();
	int d = r.Denominator();
	return Rational(a*c, b*d);
}


// inserting a Rational
void Rational::Insert(ostream &sout) const {
	sout << Numerator() << '/' << Denominator();
	return;
}

// extracting a Rational
void Rational::Extract(istream &sin) {
	int numer;
	int denom;
	char slash;
	sin >> numer >> slash >> denom;
	SetNumerator(numer);
	SetDenominator(denom);
	return;
}

// adding Rationals
Rational operator+(const Rational &r,
	const Rational &s) {
	return r.Add(s);
}

// multiplying Rationals
Rational operator*(const Rational &r,
	const Rational &s) {
	return r.Multiply(s);
}

// inserting a Rational
ostream& operator<<(ostream &sout, const Rational &r) {
	r.Insert(sout);
	return sout;
}

// extracting a Rational
istream& operator>>(istream &sin, Rational &r) {
	r.Extract(sin);
	return sin;
}


