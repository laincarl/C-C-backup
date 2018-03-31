#include<iostream>
#include<string>
using namespace std;

void PrintChar(char c = '*', int n = 80, string s = "");

int main()
{
	PrintChar('@');
	PrintChar();
	PrintChar('#', 100, "\n");
}
void PrintChar(char c, int n, string s)
{
	for (int i = 0; i < n; i++)
		cout << c << s;
	cout << endl;
}