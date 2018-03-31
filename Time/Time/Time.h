#include <iostream>
using namespace std;

class Time
{
public:
	Time(){ minute = 0; sec = 0; }               //默认构造函数
	Time(int m, int s) :minute(m), sec(s){ }  //构造函数重载
	Time operator++();                    //前置自增运算符++
	Time operator++(int);                  //后置自增运算符++

	void display(){                       //定义输出时间函数
		cout << minute << ":" << sec << endl;
	}
private:
	int minute;
	int sec;
};
//定义前置自增运算符函数
Time Time::operator++()
{
	//满60秒进1分钟
	if (++sec >= 60){
		sec = 0;
		++minute;
	}
	return *this; //返回当前对象值
}

//定义后置自增运算符函数
Time Time::operator++(int)
{
	Time temp(*this);
	if (++sec >= 60){
		sec = 0;
		++minute;
	}
	return temp;  //返回的是自加前的对象
}