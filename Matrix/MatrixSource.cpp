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
	M1 = M1.readFromFile(path);
	printf_s("���������� ������� M1:\n");
	M1.writeToConsole();

	// ������������� �������� ������
	int **A = (int**)malloc(N * sizeof(int*));
	int **B = (int**)malloc(N * sizeof(int*));
	int **C = (int**)malloc(N * sizeof(int*));
	int **D = (int**)malloc(M * sizeof(int*));

	for (int i = 0; i < N; i++)
	{
		A[i] = (int*)malloc(M * sizeof(int));
		B[i] = (int*)malloc(M * sizeof(int));
		C[i] = (int*)malloc(M * sizeof(int));
	}

	for (int i = 0; i < M; i++)
	{
		D[i] = (int*)malloc(N * sizeof(int*));
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

	Matrix M2(A, N, M), M3(B, N, M), M4(A, N, M), M5, M6(D, M, N), M7;
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
	system("pause");
	//exit(0);
	return 0;
}