#pragma once
#ifndef MATRE_H
#define NATRE_H

class MatrixException {
private:
	char* msg;
public:
	MatrixException(char* _msg) : msg(_msg) {};
	char* what() { return this->msg; };
};

class incompatibleException : public MatrixException {
private:
	char* msg;
public:
	incompatibleException() : MatrixException("Wrong sizes of matrixes") {};
	char* what() { return "Wrong sizes of matrixes"; };
};

class initException : public MatrixException {
private:
	char* msg;
public:
	initException() : MatrixException("Error in initialization") {};
	char* what() { return "Error in initialization"; };
};

class indexException : public MatrixException {
private:
	char* msg;
public:
	indexException() : MatrixException("Wrong index") {};
	char* what() { return "Wrong index"; };
};

class emptyException : public MatrixException {
private:
	char* msg;
public:
	emptyException() : MatrixException("Empty matrix") {};
	char* what() { return "Empty matrix"; };
};
#endif