#include <iostream>
using namespace std;

int carrots;


int carrot()
{
	carrots = carrots + 2;
	cout << "����" << carrots << "���ܲ��ˣ� ";
	return carrots;
}



int main()
{

	cout << "�м����ܲ���\n";
	cin >> carrots;
	cout << "��Ҳ��Ұ��»س���";
	cin.get();
	cin.get();
	cout << "�㻹��Ұ����������ٰ�һ�Σ�";
	cin.get();

	cout << "�ٶ���������ɡ�";
	carrot();

}