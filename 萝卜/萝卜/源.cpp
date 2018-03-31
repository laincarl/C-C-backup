#include <iostream>
using namespace std;

int carrots;


int carrot()
{
	carrots = carrots + 2;
	cout << "你有" << carrots << "个萝卜了！ ";
	return carrots;
}



int main()
{

	cout << "有几个萝卜？\n";
	cin >> carrots;
	cout << "你敢不敢按下回车？";
	cin.get();
	cin.get();
	cout << "你还真敢按啊？有种再按一次？";
	cin.get();

	cout << "再多给你两个吧～";
	carrot();

}