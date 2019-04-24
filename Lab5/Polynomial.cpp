#include "stdafx.h"
#include "Polynomial.h"

using namespace mathobj;
using namespace std;

int Polynomial::count = 0;

void Polynomial::correctDegree() noexcept {
	bool update = false;
	while (degree && arr[degree] == 0.0) {
		--degree;
		update = true;
	}
	if (update) {
		double *temp = new double[degree + 1];
		for (int i = degree; i >= 0; i--) {
			temp[i] = arr[i];
		}
		if (arr) delete[] arr;
		arr = temp;
		temp = nullptr;
	}
}

ostream& mathobj::operator<<(ostream &output, const Polynomial &p) noexcept {
	if (!p.arr) return output << 0.0;
	if (p.degree == 0) return output << p.arr[0];

	if (p.arr[p.degree] == 1) {
		output << "x^" << p.degree;
	}
	else if (p.arr[p.degree] == -1) {
		output << "-x^" << p.degree;
	}
	else {
		output << p.arr[p.degree] << "x^" << p.degree;
	}

	for (int i = p.degree - 1; i > 0; i--) {
		if (p.arr[i] > 0) {
			if (p.arr[i] == 1) {
				output << " + " << "x^" << i;
			}
			else {
				output << " + " << p.arr[i] << "x^" << i;
			}
		}
		else if (p.arr[i] < 0) {
			if (p.arr[i] == -1) {
				output << " - " << "x^" << i;
			}
			else {
				output << " - " << -p.arr[i] << "x^" << i;
			}
		}
	}

	if (p.arr[0] > 0) {
		output << " + " << p.arr[0];
	}
	else if (p.arr[0] < 0) {
		output << " - " << -p.arr[0];
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

Polynomial mathobj::operator*(const Polynomial &p1, double k) {
	if (!p1.arr) throw "��������� �������� �" + to_string(p1.ID) + " ����������!";
	return move(Polynomial(p1) *= k);
}

Polynomial mathobj::operator*(double k, const Polynomial &p1) {
	return mathobj::operator*(p1, k);
}

Polynomial mathobj::operator/(const Polynomial &p1, const Polynomial &p2) {
	if (!p1.arr || !p2.arr)throw "������� ��������� �" + to_string(p1.ID) + " � �" + to_string(p2.ID) + " ����������!";
	return move(Polynomial(p1) /= p2);
}

Polynomial mathobj::operator%(const Polynomial &p1, const Polynomial &p2) {
	if (!p1.arr || !p2.arr) throw "������� � �������� ��������� �" + to_string(p1.ID) + " � �" + to_string(p2.ID) + " ����������!";
	return move(Polynomial(p1) %= p2);
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
		while (this->degree && arr[this->degree] == 0.0) {
			--this->degree;
		}
	}
	this->arr = new double[this->degree + 1];
	for (int i = this->degree; i >= 0; i--) {
		this->arr[i] = arr ? arr[i] : 0.0;
	}
}

Polynomial::Polynomial(int degree, double(*func)(int)) : Polynomial(degree) {
	for (int i = this->degree; i >= 0; i--) {
		arr[i] = func(i);
	}
	correctDegree();
}

Polynomial::Polynomial(int degree, double el, ...) : Polynomial(degree, &el) {

}

Polynomial::Polynomial(const Polynomial &other) : Polynomial(other.degree, other.arr) {

}

Polynomial::Polynomial(Polynomial &&other) noexcept : Polynomial() {
	swap(other);
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

void Polynomial::swap(Polynomial &other) noexcept {
	if (this != &other) {
		std::swap(arr, other.arr);
		std::swap(degree, other.degree);
	}
}

Polynomial& Polynomial::operator=(const Polynomial &other) {
	if (this != &other) {
		if (!other.arr) {
			degree = 0;
			if (arr) delete[] arr;
			arr = nullptr;
			return *this;
		}
		if (degree != other.degree) {
			if (arr) delete[] arr;
			degree = other.degree;
			arr = new double[degree + 1];
		}
		if (degree == 0 && !arr) arr = new double[1];
		for (int i = degree; i >= 0; i--) {
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

Polynomial& Polynomial::operator=(Polynomial &&other) noexcept {
	if (this != &other) {
		if (arr) delete[] arr;
		arr = nullptr;
		degree = 0;
		swap(other);
	}
	return *this;
}

double Polynomial::operator()(double x) const {
	if (!arr) throw "��������� ��������� �������� � ������� �������� �" + to_string(ID);
	double sum = arr[degree];
	for (int i = 1; i <= degree; ++i) {
		sum *= x;
		sum += arr[degree - i];
	}

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

Polynomial& Polynomial::operator*=(double k) {
	if (!arr) throw "��������� ��������� �������� � ������� �������� �" + to_string(ID);
	
	for (int i = degree; i >= 0; i--) {
		arr[i] *= k;
	}
	
	correctDegree();
	return *this;
}

Polynomial& Polynomial::operator/=(const Polynomial &other) {
	if (!arr || !other.arr) throw "������� ��������� �" + to_string(ID) + " � �" + to_string(other.ID) + " ����������!";

	if (degree < other.degree) return *this = Polynomial(0);

	Polynomial result(degree - other.degree);

	if (other.arr[other.degree] == 0.0) throw "������� �� 0 � �������� �" + to_string(ID) + " � �" + to_string(other.ID);
	for (int i = 0; i <= result.degree; i++) {
		result.arr[result.degree - i] = arr[degree - i] / other.arr[other.degree];
		for (int j = 0; j <= other.degree; j++) {
			arr[degree - j - i] -= other.arr[other.degree - j] * result.arr[result.degree - i];
		}
	}

	result.correctDegree();
	return *this = move(result);
}

Polynomial& Polynomial::operator%=(const Polynomial &other) {
	if (!arr || !other.arr) throw "������� � �������� ��������� �" + to_string(ID) + " � �" + to_string(other.ID) + " ����������!";

	if (degree < other.degree) return *this;

	double k = 0;
	if (other.arr[other.degree] == 0.0) throw "������� �� 0 � �������� �" + to_string(ID) + " � �" + to_string(other.ID);
	for (int i = 0; i <= degree - other.degree; i++) {
		k = arr[degree - i] / other.arr[other.degree];
		for (int j = 0; j <= other.degree; j++) {
			arr[degree - j - i] -= other.arr[other.degree - j] * k;
		}
	}

	correctDegree();
	return *this;
}

bool Polynomial::operator==(const Polynomial &other) const noexcept {
	if (degree != other.degree) return false;
	for (int i = 0; i <= degree; i++) {
		if (arr[i] != other.arr[i]) return false;
	}
	return true;
}

bool Polynomial::operator==(int degree) const noexcept {
	return this->degree == degree;
}

bool mathobj::Polynomial::operator!() const noexcept {
	if (!arr) return true;
	return degree == 0 && arr[0] == 0 ? true : false;
}

bool Polynomial::operator!=(const Polynomial &other) const noexcept {
	return !Polynomial::operator==(other);
}

bool Polynomial::operator!=(int degree) const noexcept {
	return !Polynomial::operator==(degree);
}

bool Polynomial::operator<(const Polynomial &other) const noexcept {
	return degree < other.degree;
}

bool Polynomial::operator<(int degree) const noexcept {
	return this->degree < degree;
}

bool Polynomial::operator>(const Polynomial &other) const noexcept {
	return degree > other.degree;
}

bool Polynomial::operator>(int degree) const noexcept {
	return this->degree > degree;
}

bool Polynomial::operator<=(const Polynomial &other) const noexcept {
	return degree <= other.degree;
}

bool Polynomial::operator<=(int degree) const noexcept {
	return this->degree <= degree;
}

bool Polynomial::operator>=(const Polynomial &other) const noexcept {
	return degree >= other.degree;
}

bool Polynomial::operator>=(int degree) const noexcept {
	return this->degree >= degree;
}
