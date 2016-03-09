// Matrix.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <time.h>
#include <locale>
#include <fstream>

using namespace std;

#define N 3
#define M 5

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	char* path = new char[256];
	printf_s("������� ���� � �����, � ������� ���������� �������:\n");
	cin >> path;
	Matrix M1;
	M1.readFromFile(path);
	printf_s("���������� ������� M1:\n");
	M1.writeToConsole();

	// ������������� �������� ������
	double **A = (double**)malloc(N * sizeof(double*));
	double **B = (double**)malloc(N * sizeof(double*));
	double **C = (double**)malloc(N * sizeof(double*));
	double **D = (double**)malloc(M * sizeof(double*));

	for (int i = 0; i < N; i++)
	{
		A[i] = (double*)malloc(M * sizeof(double));
		B[i] = (double*)malloc(M * sizeof(double));
		C[i] = (double*)malloc(M * sizeof(double));
	}

	for (int i = 0; i < M; i++)
	{
		D[i] = (double*)malloc(N * sizeof(double*));
	}

	srand(time(NULL));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
		}
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			D[i][j] = rand() % 10;

	Matrix M2(A, N, M), M3(B, N, M), M4(A, N, M), M5, M6(D, M, N), M7, M8, M9 = M8, M10;
	printf_s("�������� ������� M2:\n");
	M2.writeToConsole();
	printf_s("�������� ������� M3:\n");
	M3.writeToConsole();
	printf_s("�������� ������� M4 = M2 + M3:\n");
	M4 = M2 + M3;
	M4.writeToConsole();
	printf_s("�������� ������� M5 = 2 * M3:\n");
	M5 = M3 * 2;
	M5.writeToConsole();
	printf_s("�������� ������� M6:\n");
	M6.writeToConsole();
	printf_s("�������� ������� M7 = M2 * M6:\n");
	M7 = M2 * M6;
	M7.writeToConsole();
	printf_s("�������� ������� M8 = M2 + M6:\n");
	M8 = M6 + M2;
	M8.writeToConsole();
	printf_s("�������� ������� M9 (������):\n");
	M9.writeToConsole();
	printf_s("�������� ������� M10 (�� ������ => M2 + M2):\n");
	M10 = M2 + M2;
	M10.writeToConsole();
	system("pause");
	//exit(0);
	return 0;
}