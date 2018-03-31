#include <iostream>
#include <Windows.h>
using namespace std;
void gotoxy(int x, int y)
{
	COORD loc = { x, y };
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, loc);
}
int main()
{
	gotoxy(5, 5);
	cout << "Hello World!" << endl;
	system("pause");
	return 0;
}