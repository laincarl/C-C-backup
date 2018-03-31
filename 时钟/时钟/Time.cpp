#include "Time.h"

void Time::Reset()
{
	hour = 0;
	minute = 0;
	sec = 0;
}
void date::Reset()
{
	year = 0;
	month = 0;
	day= 0;
}
Time Time::operator++()
{
	if (++sec >= 60){
		sec = 0;
		++minute;
	}

	if (minute >= 60){
		minute = 0;
		++hour;
	}

	if (hour >= 24)
		hour = 0;

	return *this;
}
Time Time::operator--()
{
	if (--sec < 0){
		sec = 59;
		--minute;
	}

	if (minute < 0){
		minute = 59;
		--hour;
	}

	if (hour < 0)
		hour = 23;

	return *this;
}

string Time::GetTime()const
{
	char c[32];
	sprintf_s(c, 32,
		"%02d:%02d:%02d",
		hour, minute, sec);
	return string(c);
}
string date::Getdate()const
{
	char d[32];
	sprintf_s(d, 32,
		"%02d/%02d/%02d",
		year, month, day);
	return string(d);
}
