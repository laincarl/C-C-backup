#include <windows.h>
#include <stdio.h>
#include <conio.h>
HANDLE hOut;
void DeleteLine(int row); // ɾ��һ��
void MoveText(int x, int y, SMALL_RECT rc); // �ƶ��ı�������
void ClearScreen(void); // ����
int main(void)
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); // ��ȡ��׼����豸���
	WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE;// ��������ɫ���ı���ɫ�ǻ�ɫ
	SetConsoleTextAttribute(hOut, att);
	ClearScreen();
	printf("\n\nThe soul selects her own society\n");
	printf("Then shuts the door;\n");
	printf("On her devine majority;\n");
	printf("Obtrude no more.\n\n");
	COORD endPos = { 0, 15 };
	SetConsoleCursorPosition(hOut, endPos); // ���ù��λ��
	SMALL_RECT rc = { 0, 2, 40, 5 };
	_getch();
	MoveText(10, 5, rc);
	_getch();
	DeleteLine(5);
	CloseHandle(hOut); // �رձ�׼����豸���
	return 0;
}
void DeleteLine(int row)
{
	SMALL_RECT rcScroll, rcClip;
	COORD crDest = { 0, row - 1 };
	CHAR_INFO chFill;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	rcScroll.Left = 0;
	rcScroll.Top = row;
	rcScroll.Right = bInfo.dwSize.X - 1;
	rcScroll.Bottom = bInfo.dwSize.Y - 1;
	rcClip = rcScroll;
	chFill.Attributes = bInfo.wAttributes;
	chFill.Char.AsciiChar = ' ';
	ScrollConsoleScreenBuffer(hOut, &rcScroll, &rcClip, crDest, &chFill);
}
void MoveText(int x, int y, SMALL_RECT rc)
{
	COORD crDest = { x, y };
	CHAR_INFO chFill;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	chFill.Attributes = bInfo.wAttributes;
	chFill.Char.AsciiChar = ' ';
	ScrollConsoleScreenBuffer(hOut, &rc, NULL, crDest, &chFill);
}
void ClearScreen(void)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	COORD home = { 0, 0 };
	WORD att = bInfo.wAttributes;
	unsigned long size = bInfo.dwSize.X * bInfo.dwSize.Y;
	FillConsoleOutputAttribute(hOut, att, size, home, NULL);
	FillConsoleOutputCharacter(hOut, ' ', size, home, NULL);
}
