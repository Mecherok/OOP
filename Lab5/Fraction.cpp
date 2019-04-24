#include "stdafx.h"
#include "Fraction.h"

using namespace mathobj;
using namespace std;

int Fraction::count = 0;

void Fraction::simplification() noexcept {
	if (this->numerator < 0 && this->denominator < 0) {
		this->numerator = -this->numerator;
		this->denominator = -this->denominator;
	}
	else if (this->numerator < 0 && this->denominator > 0) {
		this->numerator = -this->numerator;
		this->sign = -this->sign;
	}
	else if (this->numerator > 0 && this->denominator < 0) {
		this->denominator = -this->denominator;
		this->sign = -this->sign;
	}
	if (this->intPart < 0) {
		this->intPart = -this->intPart;
		this->sign = -this->sign;
	}
}

void Fraction::reduction() noexcept {
	if (numerator != 0) {
		int n = numerator;
		int m = denominator;
		int ost = m % n;
		while (ost != 0) {
			m = n;
			n = ost;
			ost = m % n;
		}
		if (n != 1) {
			numerator /= abs(n);
			denominator /= abs(n);
		}
	}
}

void Fraction::IntPart() noexcept {
	simplification();
	if (numerator >= denominator) {
		intPart += (numerator / denominator);
		numerator %= denominator;
	}
}

ostream& mathobj::operator<<(ostream &output, const Fraction &f) noexcept {
	if (f.sign < 0) {
		output << "-";
	}
	if (f.intPart != 0) {
		output << f.intPart << " ";
	}
	if (f.numerator != 0) {
		output << f.numerator << "/" << f.denominator << " ";
	}
	else if (f.intPart == 0 && f.numerator == 0) {
		output << "0";
	}
	return output;
}

Fraction mathobj::operator+(const Fraction &f1, const Fraction &f2) {
	return Fraction(f1) += f2;
}

Fraction mathobj::operator-(const Fraction &f1, const Fraction &f2) {
	return Fraction(f1) -= f2;
}

Fraction mathobj::operator*(const Fraction &f1, const Fraction &f2) {
	return Fraction(f1) *= f2;
}

Fraction mathobj::operator/(const Fraction &f1, const Fraction &f2) {
	return Fraction(f1) /= f2;
}

Fraction::Fraction() : Fraction(0, 0, 1, 1) {

}

Fraction::~Fraction() {

}

Fraction::Fraction(int numerator) : Fraction(0, numerator, 1, 1) {

}

Fraction::Fraction(int numerator, int denominator) : Fraction(0, numerator, denominator, 1) {

}

Fraction::Fraction(int intPart, int numerator, int denominator) : Fraction(intPart, numerator, denominator, 1) {

}

Fraction::Fraction(int intPart, int numerator, int denominator, int sign) {
	count++;
	ID = count;
	if (denominator == 0) throw "Невозможно создать объект №" + to_string(ID) + ". Знаменатель не может быть равен 0!";
	if (intPart != 0 && (numerator < 0 || denominator < 0)) throw "Невозможно создать объект №" + to_string(ID) + ". Неверный формат данных!";
	setSign(sign);
	this->intPart = intPart;
	this->numerator = numerator;
	this->denominator = denominator;
	getMixedFraction();
}

Fraction::Fraction(const Fraction &other) : Fraction(other.intPart, other.numerator, other.denominator, other.sign) {

}

int Fraction::getIntPart() const noexcept {
	return intPart;
}

int Fraction::getNominator() const noexcept {
	return numerator;
}

int Fraction::getDenominator() const noexcept {
	return denominator;
}

int Fraction::getSign() const noexcept {
	return sign < 0 ? -1 : 1;
}

double Fraction::getDouble() const noexcept {
	return (double)sign * (intPart * denominator + numerator) / denominator;
}

void Fraction::setIntPart(int number) {
	intPart = number;
	getMixedFraction();
}

void Fraction::setNominator(int number) {
	numerator = number;
	getMixedFraction();
}

void Fraction::setDenominator(int number) {
	if (number == 0) throw "Метод setDenominator для дроби №" + to_string(ID) + ": Ошибка! Знаменатель не может быть равен 0!";
	denominator = number;
	getMixedFraction();
}

void Fraction::setSign(int number) {
	if (number != 1 && number != -1) throw "Метод setSign для дроби №" + to_string(ID) + ": Ошибка! Неверный знак!";
	sign = number;
}

int Fraction::getCount() noexcept {
	return count;
}

int Fraction::getID() const noexcept {
	return ID;
}

void Fraction::swap(Fraction &other) noexcept {
	if (this != &other) {
		std::swap(intPart, other.intPart);
		std::swap(numerator, other.numerator);
		std::swap(denominator, other.denominator);
		std::swap(sign, other.sign);
	}
}

Fraction& Fraction::getMixedFraction() noexcept {
	IntPart();
	reduction();
	return *this;
}

Fraction& Fraction::getImproperFraction() noexcept {
	numerator = sign * (intPart * denominator + numerator);
	intPart = 0;
	return *this;
}

Fraction& Fraction::operator=(const Fraction &other) {
	if (this != &other) {
		numerator = other.numerator;
		denominator = other.denominator;
		intPart = other.intPart;
		sign = other.sign;
	}
	return *this;
}

Fraction& Fraction::operator++() {
	return Fraction::operator+=(Fraction(1));
}

Fraction Fraction::operator++(int) {
	Fraction temp(*this);
	++*this;
	return temp;
}

Fraction& Fraction::operator-() {
	sign = -sign;
	return *this;
}

Fraction& Fraction::operator--() {
	return Fraction::operator-=(Fraction(1));
}

Fraction Fraction::operator--(int) {
	Fraction temp(*this);
	--*this;
	return temp;
}

Fraction& Fraction::operator+=(const Fraction &other) {
	getImproperFraction();
	numerator = numerator * other.denominator + other.sign * (other.intPart * other.denominator + other.numerator) * denominator;
	denominator *= other.denominator;
	sign = 1;
	getMixedFraction();
	return *this;
}

Fraction& Fraction::operator-=(const Fraction &other) {
	getImproperFraction();
	numerator = numerator * other.denominator - other.sign * (other.intPart * other.denominator + other.numerator) * denominator;
	denominator *= other.denominator;
	sign = 1;
	getMixedFraction();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction &other) {
	getImproperFraction();
	numerator = numerator * other.sign * (other.intPart * other.denominator + other.numerator);
	denominator *= other.denominator;
	sign = 1;
	getMixedFraction();
	return *this;
}

Fraction& Fraction::operator/=(const Fraction &other) {
	return Fraction::operator*=(Fraction(other.denominator, other.sign *
		(other.intPart * other.denominator + other.numerator)));
}

bool Fraction::operator==(const Fraction &other) const noexcept {
	return sign == other.sign && intPart == other.intPart && numerator *
		other.denominator == denominator * other.numerator;
}

bool Fraction::operator!=(const Fraction &other) const noexcept {
	return !Fraction::operator==(other);
}

bool Fraction::operator>(const Fraction &other) const noexcept {
	return getDouble() > other.getDouble();
}

bool Fraction::operator<(const Fraction &other) const noexcept {
	return getDouble() < other.getDouble();
}

bool Fraction::operator>=(const Fraction &other) const noexcept {
	return getDouble() >= other.getDouble();
}

bool Fraction::operator<=(const Fraction &other) const noexcept {
	return getDouble() <= other.getDouble();
}
