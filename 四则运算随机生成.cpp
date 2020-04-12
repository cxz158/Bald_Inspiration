#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

typedef struct quation//记录一个算式的结构体
{
	int num1, num2;//算数
	float result;//结果
	char sign;//算数符
}quation;

ofstream question;
ofstream answer;//声明txt文件，用于存储question用于储存题目，answer用于存储对应的答案
int Titlenum = 0;//全局变量，用于记录题目的编号

void Addfun(int range, quation A[])//加法运算生成函数
{

	A[Titlenum].num1 = rand() % range;
	A[Titlenum].num2 = rand() % range;
	A[Titlenum].sign = '+';
	A[Titlenum].result = (float)A[Titlenum].num1 + A[Titlenum].num2;
}

void Subfun(int range, quation A[])//减法运算生成函数
{
	int temp;
	A[Titlenum].num1 = rand() % range;
	A[Titlenum].num2 = rand() % range;
	A[Titlenum].sign = '-';
	A[Titlenum].result = (float)A[Titlenum].num1 - A[Titlenum].num2;
	if (A[Titlenum].result > 0)
	{
		return;
	}
	else
	{
		temp = A[Titlenum].num1;
		A[Titlenum].num1 = A[Titlenum].num2;
		A[Titlenum].num2 = temp;
	}
}

void Mulfun(int range, quation A[])//乘法生成函数
{
	A[Titlenum].num1 = rand() % range;
	A[Titlenum].num2 = rand() % range;
	A[Titlenum].sign = '*';
	A[Titlenum].result = (float)A[Titlenum].num1 * A[Titlenum].num2;
}

void Divfun(int range, quation A[], int rtyped)//除法运算生成函数
{
	int sign = 1;
	float i;
	A[Titlenum].sign = '/';
	while (sign)
	{
		A[Titlenum].num1 = rand() % range;
		A[Titlenum].num2 = rand() % range;
		A[Titlenum].result = (float)A[Titlenum].num1 / A[Titlenum].num2;
		if (rtyped == 0)
			sign = 0;
		if (rtyped == 1)//结果为整数情况
			if (A[Titlenum].result - (int)A[Titlenum].result == 0)
				sign = 0;
		if (rtyped == 2)//结果两位小数内必须除尽情况
		{
			i = 100 * A[Titlenum].result;//将结果扩大100倍，判断i与（int）i是否相等
			if ((int)i - i == 0)
				sign = 0;
		}
		if (A[Titlenum].num2 == 0)//除数不能为0
			sign = 1;
	}
}
void Show(quation A[], int format1, int format2)//算式输出函数
{
	int i = 1, j = 1, k = 0;
	setiosflags(ios::left);
	for (i = 1, k = 0; i <= Titlenum; i++, j++)
	{
		cout << left << "(" << i << "）" << A[i].num1 << A[i].sign << A[i].num2 << "=";
		question << left << "(" << i << ") " << A[i].num1 << A[i].sign << A[i].num2 << "=";
		answer << "(" << i << ") " << A[i].result << endl;
		for (k = 0; k < format2; k++)//每题之间空格控制
		{
			cout << " ";
			question << " ";
		}//for
		if (j == format1)//每行题目输入个数控制
		{
			j = 0;
			cout << endl;
			question << endl;
		}//if
	}//for
}//Show
void Creat(int range, int rtyped, quation A[], int sum, int type)//算式题目生成函数
{
	int i, j;
	for (i = 0; i < sum; i++)//生成题目
	{
		Titlenum++;
		if (type == 4)
			j = rand() % type;//随机生成算式标志
		else j = type;
		switch (j)
		{
		case 0:
			Addfun(range, A); break;
		case 1:
			Subfun(range, A); break;
		case 2:
			Mulfun(range, A); break;
		case 3:
			Divfun(range, A, rtyped); break;
		}
	}
}
int main()
{
	question.open("question.txt");
	answer.open("answer.txt");
	quation A[101];
	int type, rtyped;//记录需要题目的运算类型,运算结果类型
	int range, sum;//运算数的范围,题目的个数
	int format1, format2;//用于记录格式输出的各项指标
	cout << "请输入你想要制定的运算数的范围：";
	cin >> range;
	while (range <= 0)
	{
		cout << "输入错误，请重新输入：";
		cin >> range;
	}
	cout << "请输入你想要的题目个数(最多可生成100个题目)： ";
	cin >> sum;
	while (sum <= 0)
	{
		cout << "输入错误，请重新输入：";
		cin >> sum;
	}
	cout << "请选择你想要定制运算题目类型：0.加法运算 1.减法运算 2.乘法运算 3.除法运算 4.四种运算混合类型\n";
	cin >> type;
	while (type != 0 && type != 1 && type != 2 && type != 3 && type != 4)
	{
		cout << "输入错误，请重新输入：";
		cin >> type;
	}
	cout << "请输入你想要的运算结果类型：0.无 1.只允许为整数 2.两位小数内必须除尽\n";
	cin >> rtyped;
	while (rtyped != 0 && rtyped != 1 && rtyped != 2)
	{
		cout << "输入错误，请重新输入：";
		cin >> rtyped;
	}
	cout << "请选择输出格式\n" << "请输入你每行想要的题目数量：";
	cin >> format1;
	while (format1 <= 0)
	{

		cout << "输入错误，请重新输入：";
		cin >> format1;
	}
	cout << "请输入每题之间想要的空格数：";
	cin >> format2;
	while (format2 < 0)
	{
		cout << "输入错误，请重新输入:";
		cin >> format2;
	}
	srand((unsigned)time(0));//随机数种子
	cout << "输出题目如下:\n";
	Creat(range, rtyped, A, sum, type);
	Show(A, format1, format2);
	question.close();
	answer.close();
	cout << endl << "输出完毕,且已生成相关题目的文本question及答案文本answer.";
	return 0;
}