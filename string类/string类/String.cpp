#include "String.h"

//�������캯��
String::String(char* c)
{
	if (c)
	{
		p = new char[strlen(c) + 1];
		strcpy(p, c);
	}
	else
		p = NULL;
}

//���ƹ��캯��
String::String(const String& s)
{
	if (!s.Empty())
	{
		p = new char[s.Size() + 1];
		strcpy(p, s);
	}
	else
		p = NULL;
}

//��������
String::~String()
{
	if (p)
		delete[] p;
}


///////////////////////////////////////////////////////////
//��ֵ������
const String& String::operator=(const String& s)
{
	if (this != &s)
	{
		if (p)
			delete[] p;
		p = new char[s.Size() + 1];
		strcpy(p, s);
	}

	return *this;
}

//����+�����
String operator+(const String& l, const String& r)
{
	char* c = new char[l.Size() + r.Size() + 1];
	int i;
	for (i = 0; i <= l.Size(); i++)
		c[i] = l[i];
	//strcpy(c, l);
	for (i = 0; i <= r.Size() + 1; i++)
		c[l.Size()+i] = r[i];
	//strcat(c, r);
	String s(c);
	delete[] c;

	return s;
}

//��ȡ����
istream& operator>>(istream& sin, String& r)
{
	char c[256];
	sin >> c;
	r = String(c);
	return sin;
}

//�������
ostream& operator<<(ostream& sout, const String& r)
{
	sout << (char*)r;
	return sout;
}

//���ع�ϵ�����
bool operator>(const String& l, const String& r)
{
	return (strcmp(l.p, r.p) > 0);
}

bool operator==(const String& l, const String& r)
{
	return (strcmp(l.p, r.p) == 0);
}

//����4����ϵ�����������> ��==����
bool operator!=(const String& l, const String& r)
{
	return !(l == r);
}

bool operator<(const String& l, const String& r)
{
	return !(l>r) && (l != r);
}

bool operator>=(const String& l, const String& r)
{
	return !(l<r);
}

bool operator<=(const String& l, const String& r)
{
	return !(l>r);
}

