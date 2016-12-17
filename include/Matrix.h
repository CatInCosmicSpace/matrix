#pragma once
#ifndef MATR_H
#define NATR_H

#include "MatrixException.h"
#include <iostream>
#include <cstring>

template <typename T>
class CMatrix;

template <class T>
std::ostream & operator<<(std::ostream & output, const CMatrix<T> &);

template <class T>
std::istream & operator>>(std::istream & input, CMatrix<T> &);


template <typename T>
class CMatrix {
private:
	void swap(CMatrix & x);
	T **matrix;
	int m_columns;
	int m_rows;

public:
	CMatrix() : m_rows(0), m_columns(0), matrix(nullptr) {};	// Done
	CMatrix(unsigned int n, unsigned int m);					// Done
	CMatrix(T **matr, unsigned int _n, unsigned int _m);
	CMatrix(CMatrix const & x);
	~CMatrix();

	unsigned int rowsNumber() const;							// Done
	unsigned int columnsNumber() const;							// Done
	bool readFromFile(char *path);								// Done

	CMatrix &operator =(const CMatrix& m2);
	CMatrix operator +(const CMatrix& m2);						// Done
	CMatrix operator -(const CMatrix& m2);						// Done
	CMatrix operator *(double num);								// Done
	CMatrix operator *(const CMatrix& m2);						// Done
	bool operator ==(const CMatrix& m2);						// Done
	T* operator [](unsigned int index);							// Done

	friend std::ostream & operator<< <>(std::ostream & output, const CMatrix & matrix);	// Done
	friend std::istream & operator>> <>(std::istream & input, CMatrix<T> & matrix);		// Done
};


#include "Matrix.cpp"

#endif