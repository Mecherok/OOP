#include "stdafx.h"
#include "Matrix.h"

using namespace mathobj;
using namespace std;

double func(int, int) {
	return rand() % 12;
}

double ident(int i, int j) {
	return i == j;
}

int main()
{
	setlocale(LC_ALL, "rus");
	
	try {
		Matrix m;
		Matrix m1(1, 4, func);
		m = m1 + m1;
		cout << setw(5) << m << endl;
	}
	catch (const string &msg) {
		cerr << msg << endl;
	}
	
	system("pause");
 	return 0;
}
