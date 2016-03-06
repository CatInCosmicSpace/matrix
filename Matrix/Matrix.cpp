#include "stdafx.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// ���� �� ������� ��� ���������� ��������
int flag = 0;
string s;

// ������ �����������
Matrix::Matrix()
{
	string = 0;
	column = 0;
	a = nullptr;
}

// ����������� � �������� ����������� ����� � �������� (������� �������)
Matrix::Matrix(unsigned int _string, unsigned int _column)
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
Matrix Matrix::error(Matrix M) const
{
	printf_s("Operation error!\n");
	flag = 1;
	return M;
}

// ����������� �������
Matrix::Matrix(Matrix const & x) : a(new double *[x.column]), column(x.column), string(x.string)
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
Matrix::Matrix(int **matr, int _string, int _column)
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


// �����
void Matrix::writeToConsole() const
{
	for (int i = 0; i < this->string; i++)
	{
		for (int j = 0; j < this->column; j++)
			printf_s("%3d ", (int)this->a[i][j]);
		cout << endl;
	}
}


Matrix &Matrix::readFromFile(char* path)
{
	ifstream stream;
	stream.open(path);

	if (stream.fail())
	{
		cout << "Incorrect filename";
		return Matrix();
	}

	int string, column;

	stream >> string >> column;
	int **mass = new int*[string];
	for (int i = 0; i < string; i++)
	{
		mass[i] = new int[column];
		for (int j = 0; j < column; j++)
			stream >> mass[i][j];
	}

	Matrix *temp = new Matrix(mass, string, column);
	stream.close();
	return *temp;
}

// ��������� ��������� ����� �������
int Matrix::getStringNumber(Matrix m) const
{
	return m.string;
}

// ��������� ���������� ����� �������
int Matrix::getColumnNumber(Matrix m) const
{
	return m.column;
}

// ������������
Matrix Matrix::operator =(Matrix& m2)
{
	if (flag != 1)
		if (this != &m2)
			(Matrix(m2)).swap(*this);
	return *this;
}

// �������� ���� ������
Matrix Matrix::operator +(Matrix &m2)
{
	flag = 0;
	if ((m2.string != this->string) || (m2.column != this->column))
	{
		Matrix temp = *this;
		return error(temp);
	}
	else
	{
		Matrix temp(this->string, this->column); // ������� ��������� �������, � ������� ����� ��������� ���������������� �������

		for (int i = 0; i < string; i++)
			for (int j = 0; j < column; j++)
				temp.a[i][j] = this->a[i][j] + m2.a[i][j];

		return temp;
	}
}

// ��������� ���� ������
Matrix Matrix::operator -(Matrix &m2)
{
	flag = 0;
	if ((m2.string != this->string) || (m2.column != this->column))
	{
		Matrix temp = *this;
		return error(temp);
	}
	else
	{
		Matrix temp(this->string, this->column); // ������� ��������� �������, � ������� ����� ��������� ���������������� �������

		for (int i = 0; i < string; i++)
			for (int j = 0; j < column; j++)
				temp.a[i][j] = this->a[i][j] - m2.a[i][j];

		return temp;
	}
}

// ��������� ������� �� �����
Matrix Matrix::operator *(double num) 
{
	Matrix temp(this->string, this->column); //� ������ ������ ������� - ������������ m1 ��� m2, �. �. ��� ���������� �������������, ������� ������ �����

	for (int i = 0; i < this->string; i++)
		for (int j = 0; j < this->column; j++)
			temp.a[i][j] = this->a[i][j] * num;

	return temp;
}

// ��������� ���� ������
Matrix Matrix::operator *(Matrix &m2) 
{
	flag = 0;
	if (this->column != m2.string)
	{
		Matrix temp = *this;
		return error(temp);
	}
	else
	{
		Matrix temp(this->string, m2.column); // � ������ ������ ������� - ������������ m1 ��� m2, �. �. ��� ���������� �������������, ������� ������ �����

		for (int row = 0; row < this->string; row++)
			for (int col = 0; col < m2.column; col++)
				for (int inner = 0; inner < m2.string; inner++)
					temp.a[row][col] += this->a[row][inner] * m2.a[inner][col];

		return temp;
	}
}

double* Matrix::operator[](int index) 
{
	return this->a[index];
}

// ������� ��� operator =
void Matrix::swap(Matrix & x)
{
	std::swap(x.a, a);
	std::swap(x.column, column);
	std::swap(x.string, string);
}

//����������
Matrix::~Matrix()
{
	for (int i = 0; i < string; i++)
		delete[] a[i];
	delete[] a;
}