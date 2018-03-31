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
	
	//声明运算符函数为友元函数
	friend bool operator> (String &str1, String &str2);
	friend bool operator< (String &str1, String &str2);
	friend bool operator==(String &str1, String &str2);

	void display(){ cout << p; }
	
private:
	char *p; //字符型指针，用于指向字符串
	};*/
String(){ p = NULL; }     //默认构造函数
String(char *str);       //参数构造函数
String(const String& s); //复制构造函数
~String();               //析构函数

int  Size()const{ return p ? strlen(p) : 0; }
bool Empty()const{ return (p == 0 || strlen(p) == 0); }

operator char*()const{ return p; } //类型转换函数  
const String& operator=(const String& s); //赋值操作符

//其它运算符
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
	char *p; //字符型指针，用于指向String存储的字符串
};

bool operator> (String &str1, String &str2);
bool operator< (String &str1, String &str2);
bool operator==(String &str1, String &str2);
