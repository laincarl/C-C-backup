#include <iostream>
using namespace std;

class Time
{
public:
	Time(){ minute = 0; sec = 0; }               //Ĭ�Ϲ��캯��
	Time(int m, int s) :minute(m), sec(s){ }  //���캯������
	Time operator++();                    //ǰ�����������++
	Time operator++(int);                  //�������������++

	void display(){                       //�������ʱ�亯��
		cout << minute << ":" << sec << endl;
	}
private:
	int minute;
	int sec;
};
//����ǰ���������������
Time Time::operator++()
{
	//��60���1����
	if (++sec >= 60){
		sec = 0;
		++minute;
	}
	return *this; //���ص�ǰ����ֵ
}

//��������������������
Time Time::operator++(int)
{
	Time temp(*this);
	if (++sec >= 60){
		sec = 0;
		++minute;
	}
	return temp;  //���ص����Լ�ǰ�Ķ���
}