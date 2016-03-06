// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� MATRIXDLL_EXPORTS,
// � ��������� ������. ���� ������ �� ������ ���� ��������� � �����-���� �������
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� MATRIXDLL_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
#ifdef MATRIXDLL_EXPORTS
#define MATRIXDLL_API __declspec(dllexport)
#else
#define MATRIXDLL_API __declspec(dllimport)
#endif

// ���� ����� ������������� �� MatrixDLL.dll

class MATRIXDLL_API CMatrixDLL 
{

	void swap(CMatrixDLL & x);
	double **a;		// ������ (���� �������)
	int column;		// �������
	int string;		// ������
public:
	CMatrixDLL(void);
	CMatrixDLL(int **matr, int _n, int _m);		// ��������������� �����. ������ ������ ���������
	CMatrixDLL(int, int);						// �����������, ����������� ������� �������
	CMatrixDLL(CMatrixDLL const & x);
	~CMatrixDLL();

	void read(char *path);						// ������ ������� �� �������
	void write();								// ����� ������� �� �������
	int getStringNumber(CMatrixDLL);
	int getColumnNumber(CMatrixDLL);

	// ���������� ���������
	CMatrixDLL& operator =(const CMatrixDLL& m2);
	CMatrixDLL operator +(const CMatrixDLL& m2);
	CMatrixDLL operator -(const CMatrixDLL& m2);
	CMatrixDLL operator *(double num);
	CMatrixDLL operator *(const CMatrixDLL& m2);
	double*& operator [](int index);

	CMatrixDLL error(CMatrixDLL);
};

extern MATRIXDLL_API int nMatrixDLL;

MATRIXDLL_API int fnMatrixDLL(void);
