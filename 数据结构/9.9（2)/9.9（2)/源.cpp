#include<iostream>
#include"string"
using namespace std;
int main()
{
	void MoveToFront(char A[], char c);

	char s[] = "abcdef";
	char m;
	int leng,x=0;
	while (x <= 5)
	{
		leng = strlen(s);
		cout << "原始字符串为:" << endl;
		for (int i = 0; i < leng; i++)
			cout << s[i] << " ";
		cout << endl;
		cout << "请输入要查询的字符:" << endl;
		cin >> m;
		MoveToFront(s, m);
		cout << "查询后字符串为:" << endl;
		for (int i = 0; i < leng + 1; i++)
			cout << s[i] << " ";
		cout <<endl;
		x++;
	}
	return 0;
}
void MoveToFront(char A[], char c)
{
	bool check(char A[], char c);
	void move2(char A[], char c);
	if (check(A,c)!=true)
	move2(A,c);
	

}
bool check(char A[], char c)
{
	for (int i = 0; i < strlen(A); i++)
	{
		if (c == A[i])
		{
			cout << "存在此值" << endl;
			return true;
		}
	}
}
void move2(char A[], char c)
{
	int i = strlen(A);
	A[i + 1] = '\0';
	for (; i > 0; i--)
		A[i] = A[i-1];
	    A[0] = c;
	cout << "不存在此值，已经加到数组第一个" << endl;
}