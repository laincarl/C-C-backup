#include"my String.h"
void compare(String &str1, String &str2)
{
	if (str1 > str2)
	{
		    str1.display();
			cout << ">";
			str2.display();
			cout << endl;
	}
	else if (str1<str2)
	{
		str1.display();
		cout << "<";
		str2.display();
		cout << endl;
	}
	else if (str1==str2)
	{
		str1.display();
		cout << "==";
		str2.display();
		cout << endl;
	}
}
void GetLine(String& s)
{
	char c[256];
	gets_s(c, 256);
	s = String(c);
}
//ÖØÔØÔËËã·û>
bool operator>(String &str1, String &str2) {
	if (strcmp(str1.p, str2.p)>0)
		return true;
	else
		return false;
}
//ÖØÔØÔËËã·û<
bool operator<(String &str1, String &str2) {
	if (strcmp(str1.p, str2.p)<0)
		return true;
	else
		return false;
}
//ÖØÔØÔËËã·û==
bool operator==(String &str1, String &str2){
	if (strcmp(str1.p, str2.p) == 0)
		return true;
	else
		return false;
}



/*void compare(String &str1, String &str2)
{
if (operator>(str1, str2) == 1)
{
str1.display();
cout << ">";
str2.display();
}
else if (operator<(str1, str2) == 1)
{
str1.display();
cout << "<";
str2.display();
}
else if (operator==(str1, str2) == 1)
{
str1.display();
cout << " = ";
str2.display();
}

cout << endl;
}*/


int main()
{
	/*String str1("Hello"), str2("Book");
	String str3("Computer"), str4("Hello");

	compare(str1, str2);
	compare(str2, str3);
	compare(str1, str4);

	return 0;*/
	String str;
	GetLine(str);
	cout << str.p << endl;
	return 0;
}
