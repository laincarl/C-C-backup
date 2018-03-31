#ifndef _STRING_CLASS_H
#define _STRING_CLASS_H

#include <iostream>
#include <cstring>
using namespace std;

class String
{
	//友元运算符函数
	friend String operator+ (const String& l, const String& r);
	friend bool   operator> (const String& l, const String& r);
	friend bool   operator< (const String& l, const String& r);
	friend bool   operator>= (const String& l, const String& r);
	friend bool   operator<= (const String& l, const String& r);
	friend bool   operator==(const String& l, const String& r);
	friend bool   operator!=(const String& l, const String& r);
public:
	friend istream& operator>>(istream& sin, String& r);
	friend ostream& operator<<(ostream& sout, const String& r);

	String() :p(0){}         //默认构造函数
	String(char *str);       //参数构造函数
	String(const String& s); //复制构造函数
	~String();               //析构函数

	//字符串长度
	int Size()const
	{
		return p ? strlen(p) : 0;
	}
	//字符串是否为空
	bool Empty()const
	{
		return (p == 0 || strlen(p) == 0);
	}

	operator char*()const{ return p; }        //类型转换函数  
	const String& operator=(const String& s); //赋值操作符

private:
	char *p; //字符型指针，用于指向String存储的字符串
};

//全局运算符函数
istream& operator>>(istream& sin, String& r);
ostream& operator<<(ostream& sout, const String& r);
/*
bool   operator==(const String& l, const String& r);
bool operator!=(const String& l, const String& r);
bool   operator> (const String& l, const String& r);
bool operator<(const String& l, const String& r);
bool operator>=(const String& l, const String& r);
bool operator<=(const String& l, const String& r);
*/
#endif  //_STRING_CLASS_H