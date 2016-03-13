#include "stdafx.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Matrix::Matrix(unsigned int _m_rows, unsigned int _m_columns) : a(new double *[_m_rows]), m_rows(_m_rows), m_columns(_m_columns) {
	for (int i = 0; i < m_rows; i++) {
		a[i] = new double[m_columns];
		for (int j = 0; j < m_columns; j++) {
			a[i][j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix & x) : a(new double *[x.m_rows]), m_columns(x.m_columns), m_rows(x.m_rows) {
	for (int i = 0; i < m_rows; i++) {
		a[i] = new double[m_columns];
		for (int j = 0; j < m_columns; j++) {
			a[i][j] = x.a[i][j];
		}
	}
}

Matrix::Matrix(double **matr, unsigned int _m_rows, unsigned int _m_columns) : a(new double *[_m_rows]), m_rows(_m_rows), m_columns(_m_columns) {
	for (int i = 0; i < m_rows; i++) {
		a[i] = new double[m_columns];
		for (int j = 0; j < m_columns; j++) {
			a[i][j] = matr[i][j];
		}
	}
}

void Matrix::writeToConsole() const {
	if (this->a == nullptr || this->m_rows == 0 || this->m_columns == 0) {
		cout << "Empty matrix\n";
	}
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < this->m_columns; j++) {
			cout.width(4);
			cout << (int)this->a[i][j];
		}
		cout << endl;
	}
}

void Matrix::readFromFile(char* path) {
	ifstream stream;
	try {
		stream.open(path);

		int m_rows, m_columns;

		stream >> m_rows >> m_columns;
		double **mass = new double*[m_rows];
		for (int i = 0; i < m_rows; i++) {
			mass[i] = new double[m_columns];
			for (int j = 0; j < m_columns; j++) {
				stream >> mass[i][j];
			}
		}

		this->a = mass;
		this->m_rows = m_rows;
		this->m_columns = m_columns;
		stream.close();
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
		return;
	}
}

unsigned int Matrix::rowsNumber() const {
	return m_rows;
}

unsigned int Matrix::columnsNumber() const {
	return m_columns;
}

Matrix& Matrix::operator =(const Matrix& m2) {
	if (this != &m2) {
		(Matrix(m2)).swap(*this);
	}
	return *this;
}

Matrix Matrix::operator +(const Matrix &m2) {
	if (m2.m_columns != this->m_columns || m2.m_rows != this->m_rows) {
		throw "Wrong matrix dimensions when adding\n";
	}
	Matrix temp(this->m_rows, this->m_columns);
	for (int i = 0; i < this->m_rows; i++) {
		for (int j = 0; j < this->m_columns; j++) {
			temp[i][j] = m2.a[i][j] + this->a[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator -(const Matrix &m2) {
	if (m2.m_columns != this->m_columns || m2.m_rows != this->m_rows)
		throw "Wrong matrix dimensions when subtracting\n";
	Matrix temp(this->m_rows, this->m_columns);
	for (int i = 0; i < this->m_rows; i++) {
		for (int j = 0; j < this->m_columns; j++) {
			temp.a[i][j] = m2.a[i][j] - a[i][j];
		}
	}
	return temp;
}

Matrix Matrix::operator *(double num) {
	if (this->a == nullptr || this->m_rows == 0 || this->m_columns == 0) {
		throw "Error. Matrix is empty\n";
	}
	Matrix temp(this->m_rows, this->m_columns);
	for (int i = 0; i < this->m_rows; i++) {
		for (int j = 0; j < this->m_columns; j++) {
			temp.a[i][j] = this->a[i][j] * num;
		}
	}
	return temp;
}

Matrix Matrix::operator *(const Matrix &m2) {
	if (this->m_columns != m2.m_rows) {
		throw "Wrong matrix dimensions when multiplication\n";
	}
	Matrix temp(this->m_rows, m2.m_columns);

	double t = 0;

	for (int row = 0; row < this->m_rows; row++) {
		for (int col = 0; col < m2.m_columns; col++) {
			t = 0;
			for (int inner = 0; inner < this->m_columns; inner++) {
				t = t + this->a[row][inner] * m2.a[inner][col];
			}
			temp.a[row][col] = t;
		}
	}
	return temp;
}


double* Matrix::operator[](unsigned int index) {
	return this->a[index];
}

void Matrix::swap(Matrix & x) {
	std::swap(x.a, a);
	std::swap(x.m_columns, m_columns);
	std::swap(x.m_rows, m_rows);
}

Matrix::~Matrix() {
	m_rows = 0;
	m_columns = 0;
	if (a != nullptr) {
		for (int i = 0; i < m_rows; i++) {
			delete[] a[i];
		}
		delete[] a;
	}
}