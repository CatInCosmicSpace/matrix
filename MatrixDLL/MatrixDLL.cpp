// CMatrixDLLDLL.cpp: ���������� ���������������� ������� ��� ���������� DLL.
//

#include "stdafx.h"
#include "MatrixDLL.h"
#include <string>
#include <iostream>
#include <fstream>


// ������ ���������������� ����������
MATRIXDLL_API int nCMatrixDLLDLL=0;

// ������ ���������������� �������.
MATRIXDLL_API int fnCMatrixDLLDLL(void)
{
    return 42;
}


using namespace std;

// ���� �� ������� ��� ���������� ��������
int flag = 0;
string s;

// ������ �����������
CMatrixDLL::CMatrixDLL()
{
	string = 0;
	column = 0;
	a = nullptr;
}

// ����������� � �������� ����������� ����� � �������� (������� �������)
CMatrixDLL::CMatrixDLL(int _string, int _column)
{
	this->string = _string;
	this->column = _column;

	a = new double *[string];
	for (int i = 0; i < string; i++)
		a[i] = new double[column];

	for (int i = 0; i < string; i++)
		for (int j = 0; j < column; j++)
			a[i][j] = 0;
}

// ������ ��� ���������� �����-���� �������� � ���������
CMatrixDLL CMatrixDLL::error(CMatrixDLL M)
{
	printf_s("Operation error!\n");
	flag = 1;
	return M;
}

// ����������� �������
CMatrixDLL::CMatrixDLL(CMatrixDLL const & x) : a(new double *[x.column]), column(x.column), string(x.string)
{
	for (int i = 0; i < string; i++)
	{
		a[i] = new double[column];
		for (int j = 0; j < column; j++)
		{
			a[i][j] = x.a[i][j];
		}
	}
}

// ���� �� ������� �������� �����������
CMatrixDLL::CMatrixDLL(int **matr, int _string, int _column)
{
	string = _string;
	column = _column;
	a = new double*[string];
	for (int i = 0; i < string; i++)
		a[i] = new double[column];
	for (int i = 0; i < string; i++)
		for (int j = 0; j < column; j++)
			a[i][j] = matr[i][j];
}

// ����
void CMatrixDLL::read(char *path)
{
	ifstream input;
	input.open(path);
	while (getline(input, s))
	{
		char *str = new char[s.size() + 1];
		strcpy(str, s.c_str());
		char *p = strtok(str, " ");
		while (p != NULL)
		{
			cout << p << endl;
			p = strtok(NULL, " ");
		}

		delete[] str;
	}
	for (int i = 0; i < string; i++)
		for (int j = 0; j < column; j++)
			cin >> a[i][j];
}

// �����
void CMatrixDLL::write()
{
	for (int i = 0; i < string; i++)
	{
		for (int j = 0; j < column; j++)
			printf_s("%3d ", (int)a[i][j]);

		cout << endl;
	}
}

// ��������� ��������� ����� �������
int CMatrixDLL::getStringNumber(CMatrixDLL m)
{
	return m.string;
}
// ��������� ���������� ����� �������
int CMatrixDLL::getColumnNumber(CMatrixDLL m)
{
	return m.column;
}

// ������������
CMatrixDLL& CMatrixDLL::operator =(const CMatrixDLL& m2)
{
	/*if (flag != 1)*/
		if (this != &m2)
			(CMatrixDLL(m2)).swap(*this);
	return *this;
}

// �������� ���� ������
CMatrixDLL CMatrixDLL::operator +(const CMatrixDLL &m2)
{
	/*flag = 0;
	if ((m2.string != this->string) || (m2.column != this->column))
	{
		CMatrixDLL temp = *this;
		return error(temp);
	}
	else
	{*/
		CMatrixDLL temp(this->string, this->column); // ������� ��������� �������, � ������� ����� ��������� ���������������� �������

		for (int i = 0; i < string; i++)
			for (int j = 0; j < column; j++)
				temp.a[i][j] = this->a[i][j] + m2.a[i][j];

		return temp;
	/*}*/
}

// ��������� ���� ������
CMatrixDLL CMatrixDLL::operator -(const CMatrixDLL &m2)
{
	/*flag = 0;
	if ((m2.string != this->string) || (m2.column != this->column))
	{
		CMatrixDLL temp = *this;
		return error(temp);
	}
	else
	{*/
		CMatrixDLL temp(this->string, this->column); // ������� ��������� �������, � ������� ����� ��������� ���������������� �������

		for (int i = 0; i < string; i++)
			for (int j = 0; j < column; j++)
				temp.a[i][j] = this->a[i][j] - m2.a[i][j];

		return temp;
	/*}*/
}

// ��������� ������� �� �����
CMatrixDLL CMatrixDLL::operator *(double num)
{
	CMatrixDLL temp(this->string, this->column); //� ������ ������ ������� - ������������ m1 ��� m2, �. �. ��� ���������� �������������, ������� ������ �����

	for (int i = 0; i < this->string; i++)
		for (int j = 0; j < this->column; j++)
			temp.a[i][j] = this->a[i][j] * num;

	return temp;
}

// ��������� ���� ������
CMatrixDLL CMatrixDLL::operator *(const CMatrixDLL &m2)
{
	flag = 0;
	/*if (this->column != m2.string)
	{
		CMatrixDLL temp = *this;
		return error(temp);
	}
	else
	{*/
		CMatrixDLL temp(this->string, m2.column); // � ������ ������ ������� - ������������ m1 ��� m2, �. �. ��� ���������� �������������, ������� ������ �����

		for (int row = 0; row < this->string; row++)
			for (int col = 0; col < m2.column; col++)
				for (int inner = 0; inner < m2.string; inner++)
					temp.a[row][col] += this->a[row][inner] * m2.a[inner][col];

		return temp;
	/*}*/
}

double* & CMatrixDLL::operator[](int index)
{
	return this->a[index];
}

// ������� ��� operator =
void CMatrixDLL::swap(CMatrixDLL & x)
{
	std::swap(x.a, a);
	std::swap(x.column, column);
	std::swap(x.string, string);
}

//���������� 
CMatrixDLL::~CMatrixDLL()
{
	for (int i = 0; i < string; i++)
		delete[] a[i];
	delete[] a;
}
