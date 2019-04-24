#include "stdafx.h"
#include "TMatrix.h"
#include "TFraction.h"
#include "TPolynomial.h"
#include "Matrix.h"
#include "Fraction.h"
#include "Polynomial.h"

using namespace mathobj;
using namespace std;

template <typename T>
T foo(int, int) {
	return rand() % 10;
}

int main() {
	setlocale(LC_ALL, "rus");

	try {
		TMatrix<double> tm(3, 3, foo);
		cout << setw(5) << tm;
		cout << setw(5) << tm + tm;
		cout << setw(5) << tm - tm;
		cout << setw(5) << tm * tm;
		
		Matrix m1(2, 2, foo);
		TMatrix<Matrix> tm1(1, 1, m1);
		cout << setw(5) << tm1;
		cout << setw(5) << tm1 + tm1;
		cout << setw(5) << tm1 - tm1;
		cout << setw(5) << tm1 * tm1;

		Fraction f0(1, 3, 4);
		TMatrix<Fraction> tm2(1, 1, f0);
		cout << setw(5) << tm2;
		cout << setw(5) << tm2 + tm2;
		cout << setw(5) << tm2 - tm2;
		cout << setw(5) << tm2 * tm2;

		TMatrix<double> tm3(3, 3, foo);
		TMatrix<TMatrix<double>> tm4(1, 1, tm3);
		cout << setw(5) << tm4;
		cout << setw(5) << tm4 + tm4;
		cout << setw(5) << tm4 - tm4;
		cout << setw(5) << tm4 * tm4;

		Polynomial p1(2, 8.0, 4.0, 8.0);
		Polynomial p(2, 4.0, 2.0, 4.0);
		TFraction<Polynomial> td(p, p1);
		cout << setw(5) << td << endl;
		cout << setw(5) << td + td << endl;
		cout << setw(5) << td - td << endl;
		cout << setw(5) << td * td << endl;
		cout << setw(5) << td / td << endl;

		Fraction f(1, 2), f1(-4, 2), f2(3, 4);
		TPolynomial<Fraction> tp(2, f2, f1, f);
		cout << setw(5) << tp << endl;
		cout << setw(5) << tp + tp << endl;
		cout << setw(5) << tp - tp << endl;
		cout << setw(5) << tp * tp << endl;
		cout << setw(5) << tp / tp << endl;
	}
	catch (const string &msg) {
		cerr << msg << endl;
	}

	system("pause");
	return 0;
}

