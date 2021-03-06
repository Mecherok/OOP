#include "stdafx.h"
#include "VectorMatrix.h"
using namespace mathobj;
using namespace std;

double func(int i, int j) {
	return rand() % 12;
}

double ident(int i, int j) {
	return i == j;
}

double foo(int i) {
	return rand() % 12;
}

int main() {
	setlocale(LC_ALL, "ru");


	try {
		Vector v1(5), v2(5);
		Matrix m(2, 5, func), m1(5, 2, func);
		v1.transposition();
		cout << setw(5) << m << endl;
		cout << setw(5) << m1 << endl;
		(m *= m1).transposition();
		cout << setw(5) << m;
		v1 *= 2.9;
		v1.getCount();
	}
	catch (const string &msg) {
		cerr << msg << endl;
	}
	
	system("pause");
	return 0;
}

