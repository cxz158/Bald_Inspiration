#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <stack>
#include <math.h>

using namespace std;
int titlenmum = 0;//用于记录题目的编号
#define MAX_TREE_SIZE 8    //用于限定算式的长度
#define INFINITY 45421341233213			//定义无穷大
float ArithmeticList[MAX_TREE_SIZE];  //用于存储算式的完全二叉树的顺序结构


int GetOperator(int type)//获得随机符号函数  "请选择你想要定制运算题目类型：0.加法运算 1.减法运算 2.乘法运算 3.除法运算 4.四则混合运算 \n";
{
	switch (type)
	{
		case 0:return '+';
		case 1:return '-';
		case 2:return '*';
		case 3:return '/';
		case 4:switch (rand() % 4)
			{
				case 0: return '+';
				case 1: return '-';
				case 2: return '*';
				case 3: return '/';
			}
	}
}

void Arithmetic_Creat(int range, int type)  //随机算式生成
{
	int flag = 1, OperandNum;
	for (int i = 1; i < MAX_TREE_SIZE; i++) //初始化
		ArithmeticList[i] = INFINITY;
	ArithmeticList[1] = GetOperator(type);
	if (type < 4)					//非四则混合运算
	{
		ArithmeticList[2] = rand() % range;
		ArithmeticList[3] = rand() % range;
	}
	else {							//四则混合运算
		OperandNum = rand() % 2 + 3;
		if (OperandNum == 3)					//参与运算数为三个
		{
			flag = rand() % 2;			//随机符号位置
			if (flag == 0)
			{
				ArithmeticList[2] = GetOperator(type);
				ArithmeticList[3] = rand() % range;
			}
			else {
				ArithmeticList[3] = GetOperator(type);
				ArithmeticList[2] = rand() % range;
			}
			ArithmeticList[(flag + 2) * 2] = rand() % range;
			ArithmeticList[(flag + 2) * 2 + 1] = rand() % range;
		}
		else {								//参与运算数为四个
			ArithmeticList[2] = GetOperator(type);
			ArithmeticList[3] = GetOperator(type);
			for (int i = 4; i < 8; i++)
				ArithmeticList[i] = rand() % range;
		}
	}
}

float Calculate(float a, float b, char op)//重定向四则运算函数
{
	switch (op)
	{
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':return a / b;
	}
}

int Resultjungle(int rtyped)//算式结果计算函数并判断，根据返回值判断算式是否符合要求
{
	float result;
	float Y[MAX_TREE_SIZE];
	for (int i = 1; i < MAX_TREE_SIZE; i++)
		Y[i] = ArithmeticList[i];
	for (int i = MAX_TREE_SIZE - 1; i > 2; i = i - 2)
	{
		if (Y[i] != INFINITY)
		{
			if ((Y[i] == 0 && Y[(i - 1) / 2] == '/') || Y[i] < 0)   //除数不能为0且运算过程中不能出现负数
				return 0;
			else Y[(i - 1) / 2] = Calculate(Y[i - 1], Y[i], char(Y[(i - 1) / 2]));
		}
	}
	if (Y[1] < 0 || Y[2] < 0)   //结果不能为负
		return 0;
	ArithmeticList[0] = Y[1];     //将运算结果存入ArithmeticList[0]中
	switch (rtyped)//0.无 1.只允许为整数 2.两位小数内必须除尽\n";
	{
	case 0:return 1;
	case 1:if (Y[1] - (int)Y[1] == 0)
				return 1;
		   else return 0;
	case 2:result = 100 * Y[1];
		   if (result - (int)result == 0)
				return 1;
		else return 0;
	}
}

void ShowArithmetic(int type, int PrintType, int format1, int format2)//输出算式函数，并且将数据输入至文本
{		
	ofstream question;
	ofstream answer;//声明txt文件，用于存储题目的的question和用于存储答案的answer

	if (PrintType)
	{
		question.open("question.txt");
		answer.open("answer.txt");
	}

	int i = 0,j = 0; 
	if (PrintType)
	{
		answer << "(" << titlenmum << ")" << ArithmeticList[0] << endl;
	}
	if (type < 4)					//普通运算输出
	{
		cout << "(" << titlenmum << ")" << ArithmeticList[2] << (char)ArithmeticList[1] << ArithmeticList[3] << "=";
		if (PrintType)
		{
			question << "(" << titlenmum << ")" << ArithmeticList[2] << (char)ArithmeticList[1] << ArithmeticList[3] << "=";
		}
	}
	else
	{
		cout << "(" << titlenmum << ")";	//题目编号输出
		question << "(" << titlenmum << ")";
		if (ArithmeticList[4] != INFINITY)
		{
			if (ArithmeticList[1] == '*' || ArithmeticList[1] == '/')
				if (ArithmeticList[2] == '+' || ArithmeticList[2] == '-')
				{
					j = 1;  //带括号输出标志
				}

			if (j == 1)//带括号输出左子树
			{
				cout << "(" << ArithmeticList[4] << (char)ArithmeticList[2] << ArithmeticList[5] << ")";
				if (PrintType)
				{
					question << "(" << ArithmeticList[4] << (char)ArithmeticList[2] << ArithmeticList[5] << ")";
				}
			}
			else {   // 不带括号输出左子树
				cout << ArithmeticList[4] << (char)ArithmeticList[2] << ArithmeticList[5];
				if (PrintType)
				{
					question << ArithmeticList[4] << (char)ArithmeticList[2] << ArithmeticList[5];
				}
			}
		}//if
		else {
			cout << ArithmeticList[2];
			if (PrintType)
			{
				question << ArithmeticList[2];
			}
		}
		//2号位为数字
		cout << (char)ArithmeticList[1];
		if (PrintType)
		{
			question << (char)ArithmeticList[1];
		}
		if (ArithmeticList[6] != INFINITY)
		{
			if (ArithmeticList[1] == '/')
				i = 1;					//i为括号标记，当i=1时表示该子树的括号不可去
			if (ArithmeticList[1] == '*' || ArithmeticList[1] == '-')
				if (ArithmeticList[3] == '+' || ArithmeticList[3] == '-')
					i = 1;
			if (i == 1)                 //带括号输出右子树
			{
				cout << "(" << ArithmeticList[6] << (char)ArithmeticList[3] << ArithmeticList[7] << ")" << "=";
				if (PrintType)
				{
					question << "(" << ArithmeticList[6] << (char)ArithmeticList[3] << ArithmeticList[7] << ")" << "=";
				}
			}
			else {                      // 不带括号输出右子树
				cout << ArithmeticList[6] << (char)ArithmeticList[3] << ArithmeticList[7] << "=";
				if (PrintType)
				{
					question << ArithmeticList[6] << (char)ArithmeticList[3] << ArithmeticList[7] << "=";
				}
			}
		}//if
		else {
			cout << ArithmeticList[3] << "=";//三号位为数字
			if (PrintType)
			{
				question << ArithmeticList[3] << "=";
			}
		}
	}

	if (titlenmum % format1 == 0)
	{
		cout << endl;
		if (PrintType)
		{
			question << endl;
		}
	}
	else {
		for (int x = 0; x < format2; x++)
		{
			cout << " ";
			if (PrintType)
			{
				question << " ";
			}
		}
	}

	if (PrintType)
	{
		answer.close();
		question.close();
	}
}

int main()
{
	srand((unsigned)time(0));//布置随机数种子；

	int Range, ResultType, OperatorType, Num, PrintType;//记录运算数范围，结果类型，题目个数,type用于记录运算类型,
	int format1, format2;//用于记录输出格式的参数format1用于记录每行题数，format2用于记录每题空白数

	cout << "请输入你想到制定的运算数的范围:";
	cin >> Range;
	while (Range <= 0)
	{
		cout << "输入错误，请重新输入:";
		cin >> Range;
	}

	cout << "请输入你想要的题目个数: ";
	cin >> Num;
	while (Num <= 0)
	{
		cout << "输入错误，请重新输入:";
		cin >> Num;
	}

	cout << "请选择你想要定制运算题目类型：0.加法运算 1.减法运算 2.乘法运算 3.除法运算 4.四则混合运算 \n";
	cin >> OperatorType;
	while (OperatorType != 0 && OperatorType != 1 && OperatorType != 2 && OperatorType != 3 && OperatorType != 4)
	{
		cout << "输入错误，请重新输入:";
		cin >> OperatorType;
	}

	cout << "请输入你想要的运算结果类型：0.无 1.只允许为整数 2.两位小数内必须除尽\n";
	cin >> ResultType;
	while (ResultType != 0 && ResultType != 1 && ResultType != 2)
	{
		cout << "输入错误，请重新输入：";
		cin >> ResultType;
	}

	cout << "请选择输出格式\n" << "请问你需要每行打印多少个题目：";
	cin >> format1;
	while (format1 <= 0)
	{
		cout << "输入错误，请重新输入：";
	}

	cout << "请问每个题目之间需要留多空格：";
	cin >> format2;
	while (format2 <= 0)
	{
		cout << "输入错误，请重新输入：";
	}

	cout << "请选择是否输出到文件\n" << "0.不通过文件输出  1.通过文建输出" << endl;
	cin >> PrintType;
	while (PrintType!=0 && PrintType!=1)
	{
		cout << "输入错误，请重新输入;";
	}

	cout << "输出题目如下:\n";
	for (int i = 0; i < Num; i++)
	{
		Arithmetic_Creat(Range, OperatorType);//生成算式
		if (Resultjungle(ResultType) == 0)      //判断算式的正确性
		{
			i--;							//不正确i--,重新生成
			continue;
		}
		titlenmum++;
		ShowArithmetic(OperatorType,PrintType,format1,format2);
	}

	return 0;
}