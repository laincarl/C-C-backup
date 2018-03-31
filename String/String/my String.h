#include <iostream>
#include <string>
using namespace std;
class String
{
public:
	/*String(){ p = NULL; }
	String(char *str)
	{
		p =new char [strlen(str)+1]; 
		strcpy_s(p, strlen(str) + 1, str);
	}
	
	//�������������Ϊ��Ԫ����
	friend bool operator> (String &str1, String &str2);
	friend bool operator< (String &str1, String &str2);
	friend bool operator==(String &str1, String &str2);

	void display(){ cout << p; }
	
private:
	char *p; //�ַ���ָ�룬����ָ���ַ���
	};*/
String(){ p = NULL; }     //Ĭ�Ϲ��캯��
String(char *str);       //�������캯��
String(const String& s); //���ƹ��캯��
~String();               //��������

int  Size()const{ return p ? strlen(p) : 0; }
bool Empty()const{ return (p == 0 || strlen(p) == 0); }

operator char*()const{ return p; } //����ת������  
const String& operator=(const String& s); //��ֵ������

//���������
friend String operator+(const String& l, const String& r);
friend bool operator> (const String& l, const String& r);
friend bool operator==(const String& l, const String& r);
friend istream& operator>>(istream& sin, String& r);
friend ostream& operator<<(ostream& sout, const String& r);
friend bool operator> (String &str1, String &str2);
friend bool operator< (String &str1, String &str2);
friend bool operator==(String &str1, String &str2);

void display(){ cout << p; }
private:
	char *p; //�ַ���ָ�룬����ָ��String�洢���ַ���
};

bool operator> (String &str1, String &str2);
bool operator< (String &str1, String &str2);
bool operator==(String &str1, String &str2);
