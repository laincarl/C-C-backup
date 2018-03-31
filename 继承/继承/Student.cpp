#include "Student.h"

Student::Student(){}
Student::Student(const string& name, const char& sex, const Date& birthday,
	const string& birthPlace, const string& id,
	const string& schoolName, int number, float gpa, const string major) :Pupil(name, sex, birthday,
	birthPlace, id, schoolName,number, gpa), m_strMajor(major)
{}
	
/*Student::~Student()
{
}*/
COURSE::COURSE(const string&name, float credit, int score) :
strName(name), fCredit(credit), nScore(score){}
COURSE Student::GetCourse(const string&courseName)const
{
	for each(auto& c in m_vCourses)
	{

		if (c.strName == courseName)
			return c;
	}
	//return COURSE();
}
ostream&operator<<(ostream&sout, const COURSE&r)
{
	sout << "Course Name:" << r.strName << endl;
	sout << "     Credit:" << r.fCredit << endl;
	sout << "      Score:" << r.nScore << endl;

	return sout;
}
istream&operator>>(istream&sin, COURSE&r)
{
	sin >> (Pupil&)r;
	char buf[256];
	sin.getline(buf, 256, '\n');
	r.strName= buf;
	//sin >> r.strName;
	//sin >> r.fCredit;
	//sin >> r.nScore;
	return sin;
}
ostream&operator<<(ostream&sout, const Student&r)
{
	sout << (const Pupil&)r;

	sout << "     Major:" << r.m_strMajor<<endl;
	for each(auto&c in r.m_vCourses)
	{
		sout << endl << c;
	}

	return sout;
}
istream&operator>>(istream&sin, Student&r)
{
	sin >> (Pupil&)r;
	char buf[256];
	sin.getline(buf,256, '\n');
	r.m_strMajor = buf;
	//sin >> r.m_strMajor;

	COURSE c;
	while (sin >> c&&c.strName!="")
	{
		r.AddCourse(c);
	}

	return sin;
}
void Student::Display()const{
	cout << *this;
}
/*void Student::Load(istream& sin){
	string temp;
	getline(sin, temp);
	sin >> *this;
}
void Student::Save(ostream& sout){
	sout << *this;
}*/

