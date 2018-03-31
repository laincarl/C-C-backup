#pragma once
#include "Person.h"
class Pupil :
	public Person
{
	friend ostream&operator<<(ostream&sout, const Pupil&r);
	friend istream&operator>>(istream&sin, Pupil&r);

public:
	Pupil();
	Pupil(const string& name, const char& sex, const Date& birthday,
		const string& birthPlace, const string& id,
		const string& schoolName = "", int number = 0, float gpa = 0.0f);
	//~Pupil();
	void SetSchoolName(const string&name){ m_strSchoolName = name; }
	void SetNumber(const int&number){ m_nNumber = number; }
	void SetGPA(float gpa){ m_fGPA = gpa; }

	string GetSchoolName()const{ return m_strSchoolName; }
	int GetNumber()const{ return m_nNumber; }
	float GetGPA()const{ return m_fGPA; }
	
	virtual void Display()const;
	virtual void Load(istream& sin);
	virtual void Save(ostream& sout);

protected:
	string m_strSchoolName;
	int m_nNumber;
	float m_fGPA;
};

