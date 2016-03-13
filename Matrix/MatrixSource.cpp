// Matrix.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <time.h>
#include <fstream>

using namespace std;

#define N 3
#define M 5

int main() {
	setlocale(LC_CTYPE, "Russian_Russia.1251");
	char* path = new char[256];
	printf_s("Введите путь к файлу, в котором содержится матрица:\n");
	cin >> path;
	Matrix M1;
	try {
		M1.readFromFile(path);
		printf_s("Полученная матрица M1:\n");
		M1.writeToConsole();
	}
	catch (const char* msg) {
		cout << msg;
	}
	// Инициализация тестовых матриц
	double **A = (double**)malloc(N * sizeof(double*));
	double **B = (double**)malloc(N * sizeof(double*));
	double **C = (double**)malloc(N * sizeof(double*));
	double **D = (double**)malloc(M * sizeof(double*));

	for (int i = 0; i < N; i++) {
		A[i] = (double*)malloc(M * sizeof(double));
		B[i] = (double*)malloc(M * sizeof(double));
		C[i] = (double*)malloc(M * sizeof(double));
	}

	for (int i = 0; i < M; i++) {
		D[i] = (double*)malloc(N * sizeof(double*));
	}

	srand(time(NULL));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
		}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			D[i][j] = rand() % 10;

	Matrix M2(A, N, M), M3(B, N, M), M4(A, N, M), M5, M6(D, M, N), M7, M8, M9 = M8, M10;
	printf_s("Тестовая матрица M2:\n");
	M2.writeToConsole();
	printf_s("Тестовая матрица M3:\n");
	M3.writeToConsole();
	printf_s("Тестовая матрица M4 = M2 + M3:\n");
	M4 = M2 + M3;
	M4.writeToConsole();
	printf_s("Тестовая матрица M5 = 2 * M3:\n");
	M5 = M3 * 2;
	M5.writeToConsole();
	printf_s("Тестовая матрица M6:\n");
	M6.writeToConsole();
	printf_s("Тестовая матрица M7 = M2 * M6:\n");
	M7 = M2 * M6;
	M7.writeToConsole();
	printf_s("Тестовая матрица M8 = M2 + M6:\n");
	try {
		M8 = M6 + M2;
		M8.writeToConsole();
	}
	catch (const char *msg) {
		cout << msg;
	}
	printf_s("Тестовая матрица M9 (пустая):\n");
	M9.writeToConsole();
	printf_s("Тестовая матрица M10 (из пустой => M2 + M2):\n");
	M10 = M2 + M2;
	M10.writeToConsole();
	system("pause");

	return 0;
}
