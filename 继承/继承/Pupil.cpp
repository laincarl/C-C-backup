#include "Pupil.h"

//Pupil::Pupil() :m_nNumber(0), m_fGPA(0.0f)
//{}
Pupil::Pupil(){}
Pupil::Pupil(const string& name, const char& sex, const Date& birthday,
	const string& birthPlace, const string& id,
	const string& schoolName, int number, float gpa) :
	Person(name, sex, birthday, birthPlace, id), m_strSchoolName(schoolName), m_nNumber(number),
	m_fGPA(gpa){}

ostream&operator<<(ostream&sout, const Pupil&r)
{
	sout << (const Person&)r<<endl;
	sout <<"SchoolName:"<<r.m_strSchoolName << endl;
	sout <<"    Number:"<< r.m_nNumber << endl;
	sout <<"       GPA:"<< r.m_fGPA<<endl;
	return sout;
}
istream&operator>>(istream&sin, Pupil&r)
{

	sin >> (Person&)r;
	char buf[256];
	sin.getline(buf,256, '\n');
	r.m_strSchoolName = buf;
	//sin >> r.m_strSchoolName;
	sin >> r.m_nNumber;
	sin >> r.m_fGPA;
	return sin;
}
void Pupil::Display()const{ 
	cout << *this;
}
void Pupil::Load(istream& sin){
	string temp;
	getline(sin, temp);
	sin >> *this;
}
void Pupil::Save(ostream& sout){
	sout << *this;
}
/*Pulil::~Pulil()
{
}*/

