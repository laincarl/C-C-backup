#ifndef _STRING_CLASS_H
#define _STRING_CLASS_H

#include <iostream>
#include <cstring>
using namespace std;

class String
{
	//��Ԫ���������
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

	String() :p(0){}         //Ĭ�Ϲ��캯��
	String(char *str);       //�������캯��
	String(const String& s); //���ƹ��캯��
	~String();               //��������

	//�ַ�������
	int Size()const
	{
		return p ? strlen(p) : 0;
	}
	//�ַ����Ƿ�Ϊ��
	bool Empty()const
	{
		return (p == 0 || strlen(p) == 0);
	}

	operator char*()const{ return p; }        //����ת������  
	const String& operator=(const String& s); //��ֵ������

private:
	char *p; //�ַ���ָ�룬����ָ��String�洢���ַ���
};

//ȫ�����������
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