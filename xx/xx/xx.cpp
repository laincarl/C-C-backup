#include<iostream>
#include<string>
using namespace std;
class Date{
	private:
	  int year,month,day;
	public:
	  Date(int year,int month,int day):year(year),month(month),day(day) {cout<<"���������๹�캯��"<<endl;}
	  ~Date(){cout<<"������������������"<<endl;}	
	  Date(Date&D)  {year=D.year;month=D.month;day=D.day;cout<<"���������࿽������"<<endl;}
};
class ID_number{
    public:
	  ID_number(int i):i(i) {cout<<"����ѧ��"<<i<<endl;}
	  ~ID_number(){cout<<"����ѧ��"<<i<<endl;}
	private:
	  int i;
};
class Student{
    private:
	  string name;
	  char sex;
	  ID_number id;
	  Date birthday;
	public:
	  Student(string name,char sex,ID_number id,Date&birthday):name(name),sex(sex),id(id),birthday(birthday){cout<<"����ѧ��"<<name<<"�๹�캯��"<<endl;}
	  ~Student(){cout<<"����ѧ��"<<name<<"����������"<<endl;}	
};
int main()
{
	Date D1(1996,8,24);
	Student S1("Wang Yu",'F',20154558,D1);
	return 0;
}
