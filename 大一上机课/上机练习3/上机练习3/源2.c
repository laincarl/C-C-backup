extern float a, b, c, d;//��չ����������
float Score(int array[5][4], float m[])//���庯��
{
	int i, j;
	for (i = 0; i < 5; i++)
		m[i] = array[i][0] * a + array[i][1] * b + array[i][2] * c + array[i][3] * d;
	return;
}
float Sort(float s[])//���庯��
{
	int i, j;
	float m;
	for (j = 1; j <= 4; j++)
	for (i = 4; i >= j; i--)
	if (s[i]>s[i - 1])
	{
		m = s[i - 1];
		s[i - 1] = s[i];
		s[i] = m;
	}//��ֵ�������򣬴Ӵ�С
	return;
}
