#include"Person.h"
#include<time.h>
#include<stdio.h>
//Date::Date(){}
Date::Date(short year, short month, short day) :
m_nYear(year), m_nMonth(month), m_nDay(day)
{}
string Date::GetDate()const
{
	char buf[12];
	sprintf_s(buf, 12, "%04d-%02d-%02d", m_nYear, m_nMonth, m_nDay);

	return string(buf);//return buf;
}
short Date::GetYear()const{ return m_nYear; }
short Date::GetMonth()const{ return m_nMonth; }
short Date::GetDay()const{ return m_nDay; }

void SetYear();
void SetMonth();
void SetDay();
const int MONTH_DAYS[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
bool IsLeapYear(int m_nYear)
{
	if ((m_nYear % 4 == 0 && m_nYear % 100 != 0) || (m_nYear % 400 == 0))
		return 1;
	else
		return 0;
}
void Date::operator++()
{
	++m_nDay;
	if (m_nMonth == 2 && IsLeapYear(m_nYear) && m_nDay > 29)
	{
		m_nDay = 1;
		++m_nMonth;
	}
	else if (m_nDay > MONTH_DAYS[m_nMonth])
	{
		m_nDay = 1;
		++m_nMonth;
	}
	if (m_nMonth > 12)
	{
		m_nMonth = 1;
		++m_nYear;
	}
}
void Date::operator--()
{
};
void Date::Display()const
{
	cout << GetDate();
};
ostream& operator<<(ostream& sout, const Date& r)
{
	sout << r.GetDate();
	return sout;
}
istream& operator>>(istream&sin, Date& r)
{
	sin >> r.m_nYear >> r.m_nMonth >> r.m_nDay;
	return sin;
}
////////////////////////////////////////////////
//Person::Person() :m_cSex(FEMALE){};
Person::Person(){}
Person::Person(const string& name, const char& sex, const Date& birthday,
	const string& birthPlace, const string& id) :m_strName(name), m_cSex(sex), m_Birthday(birthday),
	m_strBirthPlace(birthPlace), m_strID(id){}
string Person::GetName()const{ return m_strName; }
char Person::GetSex()const{ return m_cSex; }
Date Person::GetBirthday()const{ return m_Birthday; }
string Person::GetBirthPlace()const{ return m_strBirthPlace; }
string Person::GetID()const{ return m_strID; }
string Person::GetAddress()const{ return m_strAddress; }
/*int  Person::GetAge()const
{
	time_t tt = time(NULL);//这句返回的只是一个时间cuo
	tm* t = localtime(&tt);
	t->tm_year;
	time_t tt = time(NULL);//这句返回的只是一个时间cuo
	tm* t = localtime(&tt);
	Date():year(t->tmyear), month(t->tmmonth), day(t->tmday){}
}
*/

void SetName(const string &name){}
void SetAddress(const string &name);

void Person::Display()const
{
	cout << *this<<endl;
}
void Person::Load(istream& sin){
	string temp;
	getline(sin, temp);
	sin >> *this;
}
void Person::Save(ostream& sout){
	sout << *this;
}


ostream& operator<<(ostream&sout, const Person& r)
{
	sout <<"      Name:"<< r.m_strName << endl;
	sout <<"       Sex:"<< r.m_cSex << endl;
	sout <<"  Birthday:"<< r.m_Birthday << endl;
	sout <<"BirthPlace:"<< r.m_strBirthPlace << endl;
	sout <<"        ID:"<< r.m_strID;
	return sout;
}
istream& operator>>(istream&sin, Person& r)
{
	/*sin >> r.m_strName;
	sin >> r.m_cSex;
	sin >> r.m_Birthday;
	sin >> r.m_strBirthPlace;
	sin >> r.m_strID;
	*/
	char buf[256];
 sin.getline(buf,256,'\n');
 r.m_strName = buf;
sin>>r.m_cSex;
sin>>r.m_Birthday;
sin.getline(buf,256, '\n');

sin.getline(buf,256, '\n');
r.m_strBirthPlace = buf;

sin.getline(buf, 256,'\n');
r.m_strID=buf;
return sin;
}