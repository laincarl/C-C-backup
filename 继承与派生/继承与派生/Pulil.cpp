#include "Pulil.h"

Pulil::Pulil() :m_nNumber(0), m_fGPA(0.0f)
{
}
Pulil::Pulil(const string& name, const char& sex, const Date& birthday,
	const string& birthPlace, const string& id,
	const string& schoolName, int number, float gpa) :
	Person(name, sex, birthday, birthPlace, id), m_strSchoolName(schoolName), m_nNumber(number),
	m_fGPA(gpa)

{
}

ostream&operator<<(ostream&sout, const Pulil&r)
{
	sout << (const Person&)r;
	sout << r.m_strSchoolName << endl;
	sout << r.m_nNumber << endl;
	sout << r.m_fGPA;
	return sout;
}
istream&operator>>(istream&sin, Pulil&r)
{
	sin>> (Person&)r;
	sin>> r.m_strSchoolName;
	sin>>r.m_nNumber;
	sin>>r.m_fGPA;
	return sin;
}

/*Pulil::~Pulil()
{
}*/
