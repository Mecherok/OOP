#include "stdafx.h"
#include "Polynomial.h"
using namespace mathobj;

int Polynomial::count = 0;

void Polynomial::correctDegree() noexcept {
	if (degree == 0) return;
	while (degree && arr[degree] == 0) {
		degree--;
	}
}

ostream& mathobj::operator<<(ostream &output, const Polynomial &p) noexcept {
	if (!p.arr) return output << 0.0;
	if (p.degree == 0) return output << p.arr[0];
	if (p.arr[p.degree] == 1) {
		cout << "x^" << p.degree;
	}
	else if (p.arr[p.degree] == -1) {
		cout << "-x^" << p.degree;
	}
	else {
		cout << p.arr[p.degree] << "x^" << p.degree;
	}

	for (int i = p.degree - 1; i > 0; i--) {
		if (p.arr[i] > 0) {
			if (p.arr[i] == 1) {
				cout << " + " << "x^" << i;
			}
			else {
				cout << " + " << p.arr[i] << "x^" << i;
			}
		}
		else if (p.arr[i] < 0) {
			if (p.arr[i] == -1) {
				cout << " - " << "x^" << i;
			}
			else {
				cout << " - " << (-1) * p.arr[i] << "x^" << i;
			}
		}
	}

	if (p.arr[0] > 0) {
		cout << " + " << p.arr[0];
	}
	else if (p.arr[0] < 0) {
		cout << " - " << (-1) * p.arr[0];
	}

	return output;
}

Polynomial mathobj::operator+(const Polynomial &p1, const Polynomial &p2) {
	if (!p1.arr || !p2.arr) throw "�������� ��������� �" + to_string(p1.ID) + " � �" + to_string(p2.ID) + " ����������!";
	return move(Polynomial(p1) += p2);
}

Polynomial mathobj::operator-(const Polynomial &p1, const Polynomial &p2) {
	if (!p1.arr || !p2.arr) throw "��������� ��������� �" + to_string(p1.ID) + " � �" + to_string(p2.ID) + " ����������!";
	return move(Polynomial(p1) -= p2);
}

Polynomial mathobj::operator*(const Polynomial &p1, const Polynomial &p2) {
	if (!p1.arr || !p2.arr) throw "��������� ��������� �" + to_string(p1.ID) + " � �" + to_string(p2.ID) + " ����������!";
	return move(Polynomial(p1) *= p2);
}

Polynomial mathobj::operator/(const Polynomial &p1, const Polynomial &p2) {
	if (!p1.arr || !p2.arr)throw "������� ��������� �" + to_string(p1.ID) + " � �" + to_string(p2.ID) + " ����������!";
	return move(Polynomial(p1) /= p2);
}

Polynomial mathobj::operator%(const Polynomial &p1, const Polynomial &p2) {
	if (p1.degree < p2.degree || !p1.arr || !p2.arr) throw "������� � �������� ��������� �" + to_string(p1.ID) + " � �" + to_string(p2.ID) + " ����������!";
	return Polynomial(p1) %= p2;
}

Polynomial::Polynomial() {
	++count;
	ID = count;
	degree = 0;
	arr = nullptr;
}

Polynomial::~Polynomial() {
	if (arr) delete[] arr;
}

Polynomial::Polynomial(int degree) : Polynomial(degree, (const double*)nullptr) {

}


Polynomial::Polynomial(int degree, const double *arr) {
	++count;
	ID = count;
	if (degree < 0) throw "���������� ������� ������ �" + to_string(ID);
	this->degree = degree;
	if (arr) {
		for (int i = 0; i <= degree; i++) {
			if (arr[i] != 0) this->degree = i;
		}
	}
	this->arr = new double[this->degree + 1];
	for (int i = 0; i <= this->degree; i++) {
		this->arr[i] = arr ? arr[i] : 0.0;
	}
}

Polynomial::Polynomial(int degree, double(*func)(int)) : Polynomial(degree) {
	for (int i = 0; i <= this->degree; i++) {
		arr[i] = func(i);
	}
	correctDegree();
}

Polynomial::Polynomial(int degree, double el, ...) : Polynomial(degree, &el) {

}

Polynomial::Polynomial(const Polynomial &other) : Polynomial(other.degree, other.arr) {

}

Polynomial::Polynomial(Polynomial &&other) : Polynomial() {
	*this = move(other);
}

int Polynomial::getDegree() const noexcept {
	return degree;
}

double Polynomial::getCoefficient(int i) const {
	if (!arr) throw "��������� ��������� �������� � ������� �������� �" + to_string(ID);
	if (i > degree || i < 0) throw "�������� ������� ������������ � �������� �" + to_string(ID);
	return arr[i];
}

int Polynomial::getCount() noexcept {
	return count;
}

int Polynomial::getID() const noexcept {
	return ID;
}

void Polynomial::setCoefficient(int i, double number) {
	if (!arr) throw "��������� ��������� �������� � ������� �������� �" + to_string(ID);
	if (i > degree || i < 0) throw "�������� ������� ������������ � �������� �" + to_string(ID);
	arr[i] = number;
	correctDegree();
}

Polynomial& Polynomial::operator=(const Polynomial &other) {
	if (this != &other) {
		if (!other.arr) {
			degree = 0;
			arr = nullptr;
			return *this;
		}
		if (degree != other.degree) {
			if (arr) delete[] arr;
			degree = other.degree;
			arr = new double[degree + 1];
		}
		if (degree == 0 && !arr) arr = new double[1];
		for (int i = 0; i <= degree; i++) {
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

Polynomial& Polynomial::operator=(Polynomial &&other) {
	if (this != &other) {
		if (arr) delete[] arr;
		arr = other.arr;
		degree = other.degree;
		other.arr = nullptr;
		other.degree = 0;
	}
	return *this;
}

double Polynomial::operator()(double x) const {
	if (!arr) throw "��������� ��������� �������� � ������� �������� �" + to_string(ID);
	double sum = 0;
	for (int i = degree; i > 0; i--) {
		sum += arr[i] * pow(x, i);
	}
	sum += arr[0];

	return sum;
}

double Polynomial::operator[](int i) const {
	if (!arr) throw "��������� ��������� �������� � ������� �������� �" + to_string(ID);
	if (i < 0 || i > degree) throw "�������� ������� �������� �" + to_string(ID);
	return arr[i];
}

Polynomial& Polynomial::operator+=(const Polynomial &other) {
	if (!arr || !other.arr) throw "�������� ��������� �" + to_string(ID) + " � �" + to_string(other.ID) + " ����������!";

	if (this->degree < other.degree) {
		Polynomial temp(other.degree);
		for (int i = other.degree; i > degree; i--) {
			temp.arr[i] = other.arr[i];
		}
		for (int i = degree; i >= 0; i--) {
			temp.arr[i] = arr[i] + other.arr[i];
		}
		*this = move(temp);
	}
	else {
		for (int i = other.degree; i >= 0; i--) {
			arr[i] += other.arr[i];
		}
	}

	correctDegree();
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial &other) {
	if (!arr || !other.arr) throw "�������� ��������� �" + to_string(ID) + " � �" + to_string(other.ID) + " ����������!";

	if (this->degree < other.degree) {
		Polynomial temp(other.degree);
		for (int i = other.degree; i > degree; i--) {
			temp.arr[i] = other.arr[i];
		}
		for (int i = degree; i >= 0; i--) {
			temp.arr[i] = arr[i] - other.arr[i];
		}
		*this = move(temp);
	}
	else {
		for (int i = other.degree; i >= 0; i--) {
			arr[i] -= other.arr[i];
		}
	}

	correctDegree();
	return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial &other) {
	if (!arr || !other.arr) throw "��������� ��������� �" + to_string(ID) + " � �" + to_string(other.ID) + " ����������!";

	if (other.degree == 0) {
		for (int i = degree; i >= 0; i--) {
			arr[i] *= other.arr[0];
		}
	}
	else {
		Polynomial temp(degree + other.degree);
		for (int i = degree; i >= 0; i--) {
			for (int j = other.degree; j >= 0; j--) {
				temp.arr[i + j] += arr[i] * other.arr[j];
			}
		}
		*this = move(temp);
	}

	correctDegree();
	return *this;
}

Polynomial& Polynomial::operator/=(const Polynomial &other) {
	if (degree < other.degree || !arr || !other.arr) throw "������� ��������� �" + to_string(ID) + " � �" + to_string(other.ID) + " ����������!";

	bool flag = true;
	Polynomial temp(degree - other.degree);
	Polynomial temp1(*this);
	Polynomial temp2(other);
	Polynomial temp3(temp1.degree);

	double gcd;
	int k = 0;
	while (flag) {
		for (int i = other.degree; i >= 0; i--) {
			temp3.arr[i] = other.arr[i];
		}

		if (temp2.degree < temp1.degree) {
			for (int i = temp1.degree, j = temp2.degree; i >= 0; i--, j--) {
				if (j < 0) {
					temp3.arr[i] = 0;
				}
				else {
					temp3.arr[i] = temp2.arr[j];
				}
			}
		}

		gcd = temp1.arr[temp1.degree] / temp3.arr[temp1.degree];

		temp.arr[temp.degree - k] = gcd;
		k++;

		for (int i = 0; i <= temp1.degree; i++) {
			temp3.arr[i] *= gcd;
		}
		for (int i = 0; i <= temp1.degree; i++) {
			temp1.arr[i] -= temp3.arr[i];
		}
		temp1.degree == 0 ? flag = false : --temp1.degree;

		if (temp2.degree > temp1.degree) flag = false;
	}

	temp.correctDegree();
	return *this = move(temp);
}

Polynomial& Polynomial::operator%=(const Polynomial &other) {
	if (degree < other.degree || !arr || !other.arr) throw "������� � �������� ��������� �" + to_string(ID) + " � �" + to_string(other.ID) + " ����������!";

	bool flag = true;
	Polynomial temp(*this);
	Polynomial temp1(other);
	Polynomial temp2(temp.degree);

	double gcd;
	while (flag) {
		for (int i = other.degree; i >= 0; i--) {
			temp2.arr[i] = other.arr[i];
		}

		if (temp1.degree < temp.degree) {
			for (int i = temp.degree, j = temp1.degree; i >= 0; i--, j--)
				if (j < 0) {
					temp2.arr[i] = 0;
				}
				else {
					temp2.arr[i] = temp1.arr[j];
				}
		}

		gcd = temp.arr[temp.degree] / temp2.arr[temp.degree];

		for (int i = 0; i <= temp.degree; i++) {
			temp2.arr[i] *= gcd;
		}

		for (int i = 0; i <= temp.degree; i++) {
			temp.arr[i] -= temp2.arr[i];
		}
		temp.degree == 0 ? flag = false : --temp.degree;

		if (temp1.degree > temp.degree) flag = false;
	}

	temp.correctDegree();
	return *this = move(temp);
}

bool Polynomial::operator==(const Polynomial &other) const noexcept {
	if (degree != other.degree) return false;
	for (int i = 0; i <= degree; i++) {
		if (arr[i] != other.arr[i]) return false;
	}
	return true;
}

bool Polynomial::operator!=(const Polynomial &other) const noexcept {
	return !Polynomial::operator==(other);
}

bool Polynomial::operator<(const Polynomial &other) const noexcept {
	return degree < other.degree;
}

bool Polynomial::operator>(const Polynomial &other) const noexcept {
	return degree > other.degree;
}

bool Polynomial::operator<=(const Polynomial &other) const noexcept {
	return degree <= other.degree;
}

bool Polynomial::operator>=(const Polynomial &other) const noexcept {
	return degree >= other.degree;
}
