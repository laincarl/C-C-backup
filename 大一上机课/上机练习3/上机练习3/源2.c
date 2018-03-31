extern float a, b, c, d;//扩展变量作用域
float Score(int array[5][4], float m[])//定义函数
{
	int i, j;
	for (i = 0; i < 5; i++)
		m[i] = array[i][0] * a + array[i][1] * b + array[i][2] * c + array[i][3] * d;
	return;
}
float Sort(float s[])//定义函数
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
	}//对值重新排序，从大到小
	return;
}
