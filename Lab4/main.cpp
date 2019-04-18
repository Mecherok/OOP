#include "stdafx.h"
#include "Fraction.h"
#include "Polynomial.h"

using namespace mathobj;
using namespace std;

double func(int i) {
	return rand() % 10;
}

int main() {
	setlocale(LC_ALL, "rus");
	
	try {
		/*Fraction f(-1, 3, 3);
		Fraction f1(-2);
		cout << setw(5) << f << endl;
		cout << setw(5) << f1 << endl;
		cout << setw(5) << f + f1 << endl;
		cout << setw(5) << f - f1 << endl;
		cout << setw(5) << f * f1 << endl;
		cout << setw(5) << f / f1 << endl;*/
		
		Polynomial p(2, 2.0, 4.0, 0.0);
		Polynomial p1(3, 2.0, 2.0, 1.0, 12.0);
		cout << setw(5) << p << endl;
		cout << setw(5) << p1 << endl;
		cout << setw(5) << p1 + p << endl;
		cout << setw(5) << p1 - p << endl;
		cout << setw(5) << p1 * p << endl;
		cout << setw(5) << p1 / p << endl;
		cout << setw(5) << p1 % p << endl;
		cout << setw(5) << p1(2) << endl;
	}
	catch (const string &msg) {
		cerr << msg << endl;
	}

	system("pause");
	return 0;
}

