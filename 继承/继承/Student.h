#ifndef _STUDENT_H
#define _STUDENT_H
#pragma once
#include<vector>
#include "Pupil.h"
struct COURSE
{
	//COURSE();
	COURSE(const string& name = " ", float credit = 0.0f, int score = 0);
	string strName = "";
	float fCredit = 0.0f;
	int nScore = 0;
};
ostream&operator<<(ostream&, const COURSE&r);
istream&operator>>(istream&, COURSE&r);

class Student : public Pupil
{
	friend ostream&operator<<(ostream&sout, const Student&r);
	friend istream&operator>>(istream&sin, Student&r);
public:
	Student();
	Student(const string& name, const char& sex, const Date& birthday,
		const string& birthPlace, const string& id,
		const string& schoolName, int number, float gpa, string major);
	~Student();
	void AddCourse(const COURSE&course){
		m_vCourses.push_back(course);
	}
	COURSE GetCourse(const string&courseName)const;

	virtual void Display()const;
	//virtual void Load(istream& sin);
	//virtual void Save(ostream& sout);

private:
	string m_strMajor;
	vector<COURSE> m_vCourses;
};
#endif
