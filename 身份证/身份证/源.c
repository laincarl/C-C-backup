#include<stdio.h>
#include <stdlib.h> 
int main()
{

	char a[20], b[3];
	int m, i;
	printf("����18λ���֤��");
	scanf_s("%s", a, 20);//scanf("%s", a);
	for (i = 0; i < 3; i++)
		b[i] = a[i];
	m = atoi(b);
	printf("����ʡ�ݣ�");
	switch (m)
	{
	case 110:printf("����"); break;
	case 130:printf("�ӱ�ʡ"); break;
	case 140:printf("ɽ��ʡ"); break;
	case 150:printf("���ɹ�������"); break;
	case 210:printf("����ʡ"); break;
	case 220:printf("����ʡ"); break;
	case 230:printf("������ʡ"); break;
	case 310:printf("�Ϻ���"); break;
	case 320:printf("����ʡ"); break;
	case 330:printf("�㽭ʡ"); break;
	case 340:printf("����ʡ"); break;
	case 350:printf("����ʡ"); break;
	case 360:printf("����ʡ"); break;
	case 370:printf("ɽ��ʡ"); break;
	case 410:printf("����ʡ"); break;
	case 420:printf("����ʡ"); break;
	case 430:printf("����ʡ"); break;
	case 440:printf("�㶫ʡ"); break;
	case 450:printf("����ʡ"); break;
	case 460:printf("����"); break;
	case 500:printf("������"); break;
	case 510:printf("�Ĵ�ʡ"); break;
	case 520:printf("����ʡ"); break;
	case 530:printf("����ʡ"); break;
	case 540:printf("����"); break;
	case 610:printf("����ʡ"); break;
	case 620:printf("����ʡ"); break;
	case 630:printf("�ຣʡ"); break;
	case 640:printf("����"); break;
	case 650:printf("�½�"); break;
	}
	printf("\n");
	return 0;
}
