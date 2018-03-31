#include<iostream>
#include"student.h"
using namespace std;
void Student::Input()
{
	cin >> num
		>> name
		>> sex;
}
void Student::Display()
{
	cout << num << name << sex << endl;
}