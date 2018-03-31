#include "String.h"

/*void GetLine(String& s)
{
char c[256];
gets_s(c, 256);

s = String(c);
}

int main( )
{
cout << "Please input strings: \n";

String str,str2;
GetLine(str);
GetLine(str2);
cout << str << str2<<endl;
return 0;
}
//*/

//*
int main()
{
	String str1, str2, str3, temp;

	cout << "please input three strings:" << endl;
	cin >> str1 >> str2 >> str3;

	String str4 = str1 + str2;
	cout << "str1 + str2 = " << str4 << endl;

	//使用下标运算符输出字符串
	for (int i = 0; i<str4.Size(); ++i)
		cout << str4[i];
	cout << endl;

	if (str2 > str3){
		temp = str2; str2 = str3; str3 = temp;
	}
	
	if (str1 <= str2)
		cout << str1 << " " << str2 << " " << str3 << endl;
	else if (str1 <= str3)
		cout << str2 << " " << str1 << " " << str3 << endl;
	else
		cout << str2 << " " << str3 << " " << str1 << endl;

	return 0;
}
//*/