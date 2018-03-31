#pragma once
#include "Person.h"
class Pulil :
	public Person
{
	friend ostream&operator<<(ostream&sout, const Pulil&r);
	friend istream&operator>>(istream&sin,Pulil&r);

public:
	Pulil();
	Pulil(const string& name, const char& sex, const Date& birthday,
		const string& birthPlace, const string& id,
		const string& schoolName = "", int number = 0, float gpa = 0.0f);
	~Pulil();
	void SetSchoolName(const string&name){ m_strSchoolName = name; }
	void SetNumber(const int&number){ m_nNumber = number; }
	void SetGPA(float gpa){ m_fGPA = gpa; }

	string GetSchoolName()const{ return m_strSchoolName; }
	int GetNumber()const{ return m_nNumber; }
	float GetGPA()const{ return m_fGPA; }
	void Display()const{ cout << *this; }

protected:
	string m_strSchoolName;
	int m_nNumber;
	float m_fGPA;
};

