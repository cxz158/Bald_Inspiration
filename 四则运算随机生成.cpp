#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

typedef struct quation//��¼һ����ʽ�Ľṹ��
{
	int num1, num2;//����
	float result;//���
	char sign;//������
}quation;

ofstream question;
ofstream answer;//����txt�ļ������ڴ洢question���ڴ�����Ŀ��answer���ڴ洢��Ӧ�Ĵ�
int Titlenum = 0;//ȫ�ֱ��������ڼ�¼��Ŀ�ı��

void Addfun(int range, quation A[])//�ӷ��������ɺ���
{

	A[Titlenum].num1 = rand() % range;
	A[Titlenum].num2 = rand() % range;
	A[Titlenum].sign = '+';
	A[Titlenum].result = (float)A[Titlenum].num1 + A[Titlenum].num2;
}

void Subfun(int range, quation A[])//�����������ɺ���
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

void Mulfun(int range, quation A[])//�˷����ɺ���
{
	A[Titlenum].num1 = rand() % range;
	A[Titlenum].num2 = rand() % range;
	A[Titlenum].sign = '*';
	A[Titlenum].result = (float)A[Titlenum].num1 * A[Titlenum].num2;
}

void Divfun(int range, quation A[], int rtyped)//�����������ɺ���
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
		if (rtyped == 1)//���Ϊ�������
			if (A[Titlenum].result - (int)A[Titlenum].result == 0)
				sign = 0;
		if (rtyped == 2)//�����λС���ڱ���������
		{
			i = 100 * A[Titlenum].result;//���������100�����ж�i�루int��i�Ƿ����
			if ((int)i - i == 0)
				sign = 0;
		}
		if (A[Titlenum].num2 == 0)//��������Ϊ0
			sign = 1;
	}
}
void Show(quation A[], int format1, int format2)//��ʽ�������
{
	int i = 1, j = 1, k = 0;
	setiosflags(ios::left);
	for (i = 1, k = 0; i <= Titlenum; i++, j++)
	{
		cout << left << "(" << i << "��" << A[i].num1 << A[i].sign << A[i].num2 << "=";
		question << left << "(" << i << ") " << A[i].num1 << A[i].sign << A[i].num2 << "=";
		answer << "(" << i << ") " << A[i].result << endl;
		for (k = 0; k < format2; k++)//ÿ��֮��ո����
		{
			cout << " ";
			question << " ";
		}//for
		if (j == format1)//ÿ����Ŀ�����������
		{
			j = 0;
			cout << endl;
			question << endl;
		}//if
	}//for
}//Show
void Creat(int range, int rtyped, quation A[], int sum, int type)//��ʽ��Ŀ���ɺ���
{
	int i, j;
	for (i = 0; i < sum; i++)//������Ŀ
	{
		Titlenum++;
		if (type == 4)
			j = rand() % type;//���������ʽ��־
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
	int type, rtyped;//��¼��Ҫ��Ŀ����������,����������
	int range, sum;//�������ķ�Χ,��Ŀ�ĸ���
	int format1, format2;//���ڼ�¼��ʽ����ĸ���ָ��
	cout << "����������Ҫ�ƶ����������ķ�Χ��";
	cin >> range;
	while (range <= 0)
	{
		cout << "����������������룺";
		cin >> range;
	}
	cout << "����������Ҫ����Ŀ����(��������100����Ŀ)�� ";
	cin >> sum;
	while (sum <= 0)
	{
		cout << "����������������룺";
		cin >> sum;
	}
	cout << "��ѡ������Ҫ����������Ŀ���ͣ�0.�ӷ����� 1.�������� 2.�˷����� 3.�������� 4.��������������\n";
	cin >> type;
	while (type != 0 && type != 1 && type != 2 && type != 3 && type != 4)
	{
		cout << "����������������룺";
		cin >> type;
	}
	cout << "����������Ҫ�����������ͣ�0.�� 1.ֻ����Ϊ���� 2.��λС���ڱ������\n";
	cin >> rtyped;
	while (rtyped != 0 && rtyped != 1 && rtyped != 2)
	{
		cout << "����������������룺";
		cin >> rtyped;
	}
	cout << "��ѡ�������ʽ\n" << "��������ÿ����Ҫ����Ŀ������";
	cin >> format1;
	while (format1 <= 0)
	{

		cout << "����������������룺";
		cin >> format1;
	}
	cout << "������ÿ��֮����Ҫ�Ŀո�����";
	cin >> format2;
	while (format2 < 0)
	{
		cout << "�����������������:";
		cin >> format2;
	}
	srand((unsigned)time(0));//���������
	cout << "�����Ŀ����:\n";
	Creat(range, rtyped, A, sum, type);
	Show(A, format1, format2);
	question.close();
	answer.close();
	cout << endl << "������,�������������Ŀ���ı�question�����ı�answer.";
	return 0;
}