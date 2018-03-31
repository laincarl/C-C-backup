//Time.h TimeÀàµÄÉùÃ÷
#ifndef _TIME_INC_
#define _TIME_INC_
#include <string>
using namespace std;
class Time
{
public:
	Time() :hour(0), minute(0), sec(0){}
	void Reset();

	Time operator++();
	Time operator--();

	string GetTime()const;

private:
	int hour;
	int minute;
	int sec;
};
class date
{
public:
	date() :year(2015), month(05), day(03){}
	void Reset();

	Time operator++();
	Time operator--();

	string Getdate()const;

private:
	int year;
	int month;
	int day;
};

#endif
