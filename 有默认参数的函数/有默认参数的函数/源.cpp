#include<iostream>
using namespace std;
int max(int a, int b = 1)//�������ܼ������غ���������Ĭ�ϲ����ĺ���
{
	if (a < b)a = b;
	return a;
}
int main()
{
	cout << max(5) << endl<<max(2, 4) << endl;
	return 0;
}