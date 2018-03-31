#ifndef _WKQ_PERSON_H
#define _WKQ_PERSON_H
#include<iostream>
#include<string>
using namespace std;
enum SEX
{
	MALE = 'M',
	FEMALE = 'F',
};
class Date
{
	friend ostream& operator<<(ostream&sout, const Date& r);
	friend istream& operator>>(istream&sin, Date& r);

	//Date(short year=0,short month=0,short day=0);

public:
	//Date();
	//Date(const short& year, const short& month, const short& day);
	Date(short year = 0, short month = 0, short day = 0);
	string GetDate()const;
	short GetYear()const;
	short GetMonth()const;
	short GetDay()const;

	void SetYear();
	void SetMonth();
	void SetDay();

	void Display()const;
protected:

private:
	short m_nYear;
	short m_nMonth;
	short m_nDay;

	void operator++();
	void operator--();

};
class Person
{
	friend ostream& operator<<(ostream&sout, const Person& r);

	friend istream& operator>>(istream&sin, Person& r);
public:
	Person();
	Person(const string& name, const char& sex, const Date& birthday,
		const string& birthPlace, const string& id);
	string GetName()const;
	char   GetSex()const;
	Date   GetBirthday()const;
	string GetBirthPlace()const;
	string GetID()const;
	string GetAddress()const;
	int    GetAge()const;


	void SetName(const string &name);
	void SetAddress(const string &name);

	virtual void Display()const;
	virtual void Load(istream& sin);
	virtual void Save(ostream& sout);
protected:
	string m_strName;
	char   m_cSex;//MALE='M' or FEMALE='F'
	Date   m_Birthday;

private:
	string m_strBirthPlace;
	string m_strAddress;
	string m_strID;

};
ostream& operator<<(ostream&sout, const Person& r);
istream& operator>>(istream&sin, const Person& r);
ostream& operator<<(ostream&sout, const Date& r);

#endif //_WKQ_PERSON_H