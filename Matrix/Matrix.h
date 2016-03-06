#pragma once

class Matrix
{
private:
	void swap(Matrix & x);
	double **a;     // ������ (���� �������)
	int column;     // �������
	int string;     // ������

public:
	Matrix();
	Matrix(unsigned int n, unsigned int m); // �����������, ����������� ������� �������
	Matrix(int **matr, int _n, int _m);     // ������ ������ ���������
	Matrix(Matrix const & x);
	static Matrix &readFromFile(char* path);            // ������ ������� �� �������
	~Matrix();

	void writeToConsole() const;                          // ����� ������� �� �������
	int getStringNumber(Matrix) const;
	int getColumnNumber(Matrix) const;

	// ���������� �����������
	Matrix operator =(Matrix& m2);
	Matrix operator +(Matrix& m2);
	Matrix operator -(Matrix& m2);
	Matrix operator *(double num);
	Matrix operator *(Matrix& m2);
	double* operator [](int index);

	Matrix error(Matrix) const;
};