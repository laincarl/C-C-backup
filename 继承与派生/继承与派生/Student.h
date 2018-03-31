#ifndef _STUDENT_H
#define _STUDENT_H
#pragma once
#include<vector>
#include "Pulil.h"
struct COURSE
{
	COURSE();
	COURSE (const string&name,float credit,int score):
	strName(name), fCredit(credit), nScore(score){}
	string strName="";
	float fCredit=0.0f;
	int nScore=0;
};
ostream&operator<<(ostream&, const COURSE&r);
istream&operator>>(istream&, COURSE&r);

//#include "Pulil.h"
class Student :	public Pulil
{
	friend ostream&operator<<(ostream&sout, const Student&r);
	friend istream&operator>>(istream&sin, Student&r);
public:
	Student(const string& name, const char& sex, const Date& birthday,
		const string& birthPlace, const string& id,
		const string& schoolName, int number, float gpa, string major);
	~Student();
	void AddCourse(const COURSE&course){
		m_vCourses.push_back(course);
	}
	COURSE GetCourse(const string&courseName)const;

	void Display()const
	{
		cout << *this << endl;
	}
	
private:
	string m_strMajor;
	vector<COURSE> m_vCourses;
};
#endif
