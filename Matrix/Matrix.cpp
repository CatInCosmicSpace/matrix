#include "stdafx.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef MATR_CPP
#define MATR_CPP

template <typename T>
CMatrix<T>::CMatrix(unsigned int _m_rows, unsigned int _m_columns) : matrix(new T *[_m_rows]), m_rows(_m_rows), m_columns(_m_columns) {
	for (int i = 0; i < m_rows; i++) {
		matrix[i] = new T[m_columns];
		for (int j = 0; j < m_columns; j++) {
			matrix[i][j] = 0;
		}
	}
}

template <typename T>
CMatrix<T>::CMatrix(const CMatrix & x) : matrix(new T *[x.m_rows]), m_columns(x.m_columns), m_rows(x.m_rows) {
	for (int i = 0; i < m_rows; i++) {
		matrix[i] = new T[m_columns];
		for (int j = 0; j < m_columns; j++) {
			matrix[i][j] = x.matrix[i][j];
		}
	}
}

template <typename T>
CMatrix<T>::CMatrix(T **matr, unsigned int _m_rows, unsigned int _m_columns) : matrix(new T *[_m_rows]), m_rows(_m_rows), m_columns(_m_columns) {
	for (int i = 0; i < m_rows; i++) {
		matrix[i] = new T[m_columns];
		for (int j = 0; j < m_columns; j++) {
			matrix[i][j] = matr[i][j];
		}
	}
}

template <typename T>
void CMatrix<T>::writeToConsole() const {
	if (this->matrix == nullptr || this->m_rows == 0 || this->m_columns == 0) {
		cout << "Empty matrix\n";
	}
	for (int i = 0; i < m_rows; i++) {
		for (int j = 0; j < m_columns; j++) {
			cout.width(4);
			cout << this->matrix[i][j];
		}
		cout << endl;
	}
}

template <typename T>
bool CMatrix<T>::readFromFile(char* path) {
	ifstream stream;
	try {
		stream.open(path);

		if (stream.is_open()) {
			unsigned int m_rows, m_columns;

			stream >> m_rows >> m_columns;
			T **mass = new T*[m_rows];
			for (int i = 0; i < m_rows; i++) {
				mass[i] = new T[m_columns];
				for (int j = 0; j < m_columns; j++) {
					stream >> mass[i][j];
				}
			}

			this->matrix = mass;
			this->m_rows = m_rows;
			this->m_columns = m_columns;
			stream.close();

			return true;
		}
	}
	catch (const std::exception& e) {
		cout << e.what() << '\n';
		return false;
	}
	return false;
}

template <typename T>
unsigned int CMatrix<T>::rowsNumber() const {
	return m_rows;
}

template <typename T>
unsigned int CMatrix<T>::columnsNumber() const {
	return m_columns;
}

template <typename T>
double ** CMatrix<T>::getCMatrix() const {
	return matrix;
}

template <typename T>
CMatrix<T> & CMatrix<T>::operator =(const CMatrix<T>& m2) {
	if (this != &m2) {
		(CMatrix(m2)).swap(*this);
	}
	return *this;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator +(const CMatrix<T> &m2) {
	if (m2.m_columns != this->m_columns || m2.m_rows != this->m_rows) {
		throw "Wrong sizes of matrixes\n";
	}
	CMatrix temp(this->m_rows, this->m_columns);
	for (int i = 0; i < this->m_rows; i++) {
		for (int j = 0; j < this->m_columns; j++) {
			temp[i][j] = m2.matrix[i][j] + this->matrix[i][j];
		}
	}
	return temp;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator -(const CMatrix<T> &m2) {
	if (m2.m_columns != this->m_columns || m2.m_rows != this->m_rows)
		throw "Wrong sizes of matrixes\n";
	CMatrix temp(this->m_rows, this->m_columns);
	for (int i = 0; i < this->m_rows; i++) {
		for (int j = 0; j < this->m_columns; j++) {
			temp.matrix[i][j] = m2.matrix[i][j] - matrix[i][j];
		}
	}
	return temp;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator *(double num) {
	if (this->matrix == nullptr || this->m_rows == 0 || this->m_columns == 0) {
		throw "Error. CMatrix is empty\n";
	}
	CMatrix temp(this->m_rows, this->m_columns);
	for (int i = 0; i < this->m_rows; i++) {
		for (int j = 0; j < this->m_columns; j++) {
			temp.matrix[i][j] = this->matrix[i][j] * num;
		}
	}
	return temp;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator *(const CMatrix &m2) {
	if (this->m_columns != m2.m_rows) {
		throw "Wrong sizes of matrixes\n";
	}
	CMatrix temp(this->m_rows, m2.m_columns);

	T t = 0;

	for (int row = 0; row < this->m_rows; row++) {
		for (int col = 0; col < m2.m_columns; col++) {
			t = 0;
			for (int inner = 0; inner < this->m_columns; inner++) {
				t = t + this->matrix[row][inner] * m2.matrix[inner][col];
			}
			temp.matrix[row][col] = t;
		}
	}
	return temp;
}

template <typename T>
bool CMatrix<T>::operator ==(const CMatrix & m2) {
	if (m_rows != m2.m_rows || m_columns != m2.m_columns) {
		return false;
	}

	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < m_columns; ++j) {
			if (matrix[i][j] != m2.matrix[i][j]) {
				return false;
			}
		}
	}

	return true;
}

template <typename T>
T* CMatrix<T>::operator[](unsigned int index) {
	return this->matrix[index];
}

template <typename T>
void CMatrix<T>::swap(CMatrix & x) {
	std::swap(x.matrix, matrix);
	std::swap(x.m_columns, m_columns);
	std::swap(x.m_rows, m_rows);
}

template <typename T>
CMatrix<T>::~CMatrix() {
	if (matrix != nullptr) {
		for (int i = 0; i < m_rows; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
}
#endif
