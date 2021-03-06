#include "stdafx.h"
#include "Vector3D.h"

using namespace mathobj;
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	
	try {
		Vector3D v1;
		v1.set(2, 2, 0);
		v1.print();

		Vector3D v2;
		v2.set(-2, -1, 0);
		v2.print();

		sum(v1, v2).print();

		Vector3D v3;
		v3 = sum(v1, v2);
		v3.print();

		double a = cosa(v1, v2);;
		double b = sina(v1, v2);
		double c = angle(v1, v2);
		cout << a << endl;
		cout << b << endl;
		cout << c << endl;
	}
	catch (const string &msg) {
		cerr << msg << endl;
	}
	
	system("pause");
	return 0;
}

