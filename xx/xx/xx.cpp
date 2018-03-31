#include<iostream>
#include<string>
using namespace std;
class Date{
	private:
	  int year,month,day;
	public:
	  Date(int year,int month,int day):year(year),month(month),day(day) {cout<<"调用日期类构造函数"<<endl;}
	  ~Date(){cout<<"调用日期类析构函数"<<endl;}	
	  Date(Date&D)  {year=D.year;month=D.month;day=D.day;cout<<"调用日期类拷贝函数"<<endl;}
};
class ID_number{
    public:
	  ID_number(int i):i(i) {cout<<"构造学号"<<i<<endl;}
	  ~ID_number(){cout<<"析构学号"<<i<<endl;}
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
	  Student(string name,char sex,ID_number id,Date&birthday):name(name),sex(sex),id(id),birthday(birthday){cout<<"调用学生"<<name<<"类构造函数"<<endl;}
	  ~Student(){cout<<"调用学生"<<name<<"类析构函数"<<endl;}	
};
int main()
{
	Date D1(1996,8,24);
	Student S1("Wang Yu",'F',20154558,D1);
	return 0;
}
