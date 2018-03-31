#include "circle.h"  //ezWinLibrary�е�Բ����
#include "label.h"   //ezWinLibrary�еı�ǩ��
#include "Time.h"    //�Զ����ʱ����

const float WIN_SIZE = 8.0f;
SimpleWindow W("Clock", WIN_SIZE, WIN_SIZE);

int Clock(){
	static Time tm;
	--tm;

	CircleShape clock(W, Position(WIN_SIZE / 2, WIN_SIZE / 2),
		Yellow, WIN_SIZE - 0.3f);
	Label time(W, Position(WIN_SIZE / 2, WIN_SIZE / 2),
		tm.GetTime(), Black, Green);

	time.SetFont("Arial", 120);
	clock.Draw();
	time.Draw();
	return 0;
}

int ApiMain()
{
	W.Open();
	W.SetTimerCallback(Clock);
	W.StartTimer(1000);
	return 0;
}

