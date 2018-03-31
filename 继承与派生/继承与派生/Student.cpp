#include "Student.h"


Student::Student(const string& name, const char& sex, const Date& birthday,
	const string& birthPlace, const string& id,
	const string& schoolName, int number, float gpa, const string major) :
	m_strName(name), m_cSex(sex), m_Birthday(birthday),
	m_strBirthPlace(birthPlace), m_strID(id), m_strSchoolName(schoolName), m_nNumber(number),
	m_fGPA(gpa)£¬m_strMajor{}
}


Student::~Student()
{
}
COURSE Student::GetCourse(const string&courseName)const
{
	for each(auto& c in m_vCourses)
	{
		if (c.strName == courseName)
			return c;
	}
	return COURSE();
}
ostream&operator<<(ostream&sout, const COURSE&r)
{
	sout << "Course Name:" << r.strName << endl;
	sout << "Credit:" << r.fCredit << endl;
	sout << "Score:" << r.nScore << endl;

	return sout;
}
istream&operator>>(istream&sin, COURSE&r)
{
	sin >>r.strName;
	sin >>r.fCredit;
	sin>> r.nScore;
	return sin;
}
ostream&operator<<(ostream&sout, const Student&r)
{
	sout << (const Pulil&)r;

	sout << "Major:" << r.m_strMajor << endl;
	for each(auto&c in r.m_vCourses)
	{
		sout <<endl<< c;
	}

	return sout;
}
istream&operator>>(istream&sin, Student&r)
{
	sin >> (Pulil&)r;
	sin >> r.m_strMajor;
	
	COURSE c;
	while (sin >> c)
	{
		r.AddCourse(c);
	}

	return sin;
}



