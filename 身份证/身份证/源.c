#include<stdio.h>
#include <stdlib.h> 
int main()
{

	char a[20], b[3];
	int m, i;
	printf("输入18位身份证号");
	scanf_s("%s", a, 20);//scanf("%s", a);
	for (i = 0; i < 3; i++)
		b[i] = a[i];
	m = atoi(b);
	printf("所在省份：");
	switch (m)
	{
	case 110:printf("北京"); break;
	case 130:printf("河北省"); break;
	case 140:printf("山西省"); break;
	case 150:printf("内蒙古自治区"); break;
	case 210:printf("辽宁省"); break;
	case 220:printf("吉林省"); break;
	case 230:printf("黑龙江省"); break;
	case 310:printf("上海市"); break;
	case 320:printf("江苏省"); break;
	case 330:printf("浙江省"); break;
	case 340:printf("安徽省"); break;
	case 350:printf("福建省"); break;
	case 360:printf("江西省"); break;
	case 370:printf("山东省"); break;
	case 410:printf("河南省"); break;
	case 420:printf("湖北省"); break;
	case 430:printf("湖南省"); break;
	case 440:printf("广东省"); break;
	case 450:printf("广西省"); break;
	case 460:printf("海南"); break;
	case 500:printf("重庆市"); break;
	case 510:printf("四川省"); break;
	case 520:printf("贵州省"); break;
	case 530:printf("云南省"); break;
	case 540:printf("西藏"); break;
	case 610:printf("陕西省"); break;
	case 620:printf("甘肃省"); break;
	case 630:printf("青海省"); break;
	case 640:printf("宁夏"); break;
	case 650:printf("新疆"); break;
	}
	printf("\n");
	return 0;
}
