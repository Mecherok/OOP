#pragma once
#include <iostream>

using namespace std;

namespace mathobj {
	template<typename T>
	class TFraction;

	template <class T>
	ostream& operator<<(ostream &output, const TFraction<T> &f) {
		if (!f.intPart && !f.numerator) {
			return output << "0";
		}
		if (f.sign < 0) {
			output << "-";
		}
		if (!!f.intPart) {
			output << f.intPart << " ";
		}
		if (!!f.numerator) {
			output << f.numerator << " / " << f.denominator << setw(output.width());
		}

		return output;
	}

	template <class T>
	TFraction<T> operator+(const TFraction<T> &f1, const TFraction<T> &f2) {
		return move(TFraction<T>(f1) += f2);
	}

	template <class T>
	TFraction<T> operator-(const TFraction<T> &f1, const TFraction<T> &f2) {
		return move(TFraction<T>(f1) -= f2);
	}

	template <class T>
	TFraction<T> operator*(const TFraction<T> &f1, const TFraction<T> &f2) {
		return move(TFraction<T>(f1) *= f2);
	}

	template <class T>
	TFraction<T> operator/(const TFraction<T> &f1, const TFraction<T> &f2) {
		return move(TFraction<T>(f1) /= f2);
	}

	template <class T>
	class TFraction {
	private:
		T numerator;
		T denominator;
		T intPart;
		int sign;
		int ID;
		static int count;
		void reduction();
		void IntPart();
		friend ostream&::operator<< <T>(ostream &output, const TFraction<T> &f);
		friend TFraction<T> operator+ <T>(const TFraction<T> &f1, const TFraction<T> &f2);
		friend TFraction<T> operator- <T>(const TFraction<T> &f1, const TFraction<T> &f2);
		friend TFraction<T> operator* <T>(const TFraction<T> &f1, const TFraction<T> &f2);
		friend TFraction<T> operator/ <T>(const TFraction<T> &f1, const TFraction<T> &f2);
	public:
		TFraction();
		~TFraction();
		TFraction(const T& numerator);
		TFraction(const T& numerator, const T& denominator);
		TFraction(const T& intPart, const T& numerator, const T& denominator);
		TFraction(const T& intPart, const T& numerator, const T& denominator, int sign);
		TFraction(const TFraction<T> &other);
		TFraction(TFraction<T> &&other) noexcept;
		T getIntPart() const noexcept;
		T getNominator() const noexcept;
		T getDenominator() const noexcept;
		int getSign() const noexcept;
		void setIntPart(const T& number);
		void setNominator(const T& number);
		void setDenominator(const T& number);
		void setSign(int sign);
		static int getCount() noexcept;
		int getID() const noexcept;
		TFraction<T>& getMixedFraction();
		TFraction<T>& getImproperFraction();
		TFraction<T>& operator=(const TFraction<T> &other);
		TFraction<T>& operator=(TFraction<T> &&other) noexcept;
		TFraction<T>& operator+=(const TFraction<T> &other);
		TFraction<T>& operator-();
		TFraction<T>& operator-=(const TFraction<T> &other);
		TFraction<T>& operator*=(const TFraction<T> &other);
		TFraction<T>& operator/=(const TFraction<T> &other);
	};
}

using namespace mathobj;
template <class T>
int TFraction<T>::count = 0;

template<class T>
void mathobj::TFraction<T>::reduction() {
	if (numerator != 0) {
		T n = numerator;
		T m = denominator;
		T ost = m % n;
		while (ost != 0) {
			m = n;
			n = ost;
			ost = m % n;
		}
		if (n != 1) {
			numerator /= n;
			denominator /= n;
		}
	}
}

template<class T>
void mathobj::TFraction<T>::IntPart() {
	if (numerator >= denominator) {
		intPart += (numerator / denominator);
		numerator %= denominator;
	}
}

template<class T>
TFraction<T>::TFraction() : TFraction(T(0), T(0), T(0, 1.0), 1) {

}

template<class T>
TFraction<T>::~TFraction() {

}
	
template<class T>
TFraction<T>::TFraction(const T& numerator) : TFraction(T(0), numerator, T(0, 1.0), 1) {
	
}
	
template<class T>
TFraction<T>::TFraction(const T& numerator, const T& denominator) : TFraction(T(0), numerator, denominator, 1) {
	
}
	
template<class T>
TFraction<T>::TFraction(const T& intPart, const T& numerator, const T& denominator) : TFraction(intPart, numerator, denominator, 1) {
	
}
	
template<class T>
TFraction<T>::TFraction(const T& intPart, const T& numerator, const T& denominator, int sign) {
	count++;
	ID = count;
	if (!denominator) throw "Невозможно создать объект №" + to_string(ID) + ". Знаменатель не может быть равен 0!";
	if (sign != 1 && sign != -1) throw "Невозможно создать объект №" + to_string(ID) + ". Неверный знак!";
	this->intPart = intPart;
	this->numerator = numerator;
	this->denominator = denominator;
	this->sign = sign;
	getMixedFraction();
}
	
template<class T>
TFraction<T>::TFraction(const TFraction<T>& other) : TFraction(other.intPart, other.numerator, other.denominator, other.sign) {
	
}

template<class T>
TFraction<T>::TFraction(TFraction<T>&& other) noexcept : TFraction() {
	*this = move(other);
}
	
template<class T>
T TFraction<T>::getIntPart() const noexcept {
	return intPart;
}
	
template<class T>
T TFraction<T>::getNominator() const noexcept {
	return numerator;
}
	
template<class T>
T TFraction<T>::getDenominator() const noexcept {
	return denominator;
}
	
template<class T>
int TFraction<T>::getSign() const noexcept {
	return sign < 0 ? -1 : 1;
}
	
template<class T>
void TFraction<T>::setIntPart(const T& number) {
	intPart = number;
	getMixedFraction();
}
	
template<class T>
void TFraction<T>::setNominator(const T& number) {
	numerator = number;
	getMixedFraction();
}
	
template<class T>
void TFraction<T>::setDenominator(const T& number) {
	if (number == 0) throw "Метод setDenominator для дроби №" + to_string(ID) + ": Ошибка! Знаменатель не может быть равен 0!";
	denominator = number;
	getMixedFraction();
}
	
template<class T>
void TFraction<T>::setSign(int sign) {
	if (sign != 1 && sign != -1) throw "Метод setSign для дроби №" + to_string(ID) + ": Ошибка! Неверный знак!";
	this->sign = sign;
}
	
template<class T>
int TFraction<T>::getCount() noexcept {
	return count;
}
	
template<class T>
int TFraction<T>::getID() const noexcept {
	return ID;
}
	
template<class T>
TFraction<T>& TFraction<T>::getMixedFraction() {
	IntPart();
	reduction();
	return *this;
}

template<class T>
TFraction<T>& TFraction<T>::getImproperFraction() {
	numerator = sign * (intPart * denominator + numerator);
	intPart(0);
	return *this;
}

template<class T>
TFraction<T>& TFraction<T>::operator=(const TFraction<T>& other) {
	if (this != &other) {
		numerator = other.numerator;
		denominator = other.denominator;
		intPart = other.intPart;
		sign = other.sign;
	}
	return *this;
}

template<class T>
TFraction<T>& TFraction<T>::operator=(TFraction<T>&& other) noexcept {
	if (this != &other) {
		numerator = move(other.numerator);
		denominator = move(other.denominator);
		intPart = move(other.intPart);
		sign = other.sign;
	}
	return *this;
}
		
template<class T>
TFraction<T>& TFraction<T>::operator+=(const TFraction<T>& other) {
	getImproperFraction();
	numerator = numerator * other.denominator + other.sign * (other.intPart * other.denominator + other.numerator) * denominator;
	denominator *= other.denominator;
	sign = 1;
	getMixedFraction();
	return *this;
}
	
template<class T>
TFraction<T>& TFraction<T>::operator-() {
	sign = -sign;
	return *this;
}
	
template<class T>
TFraction<T>& TFraction<T>::operator-=(const TFraction<T>& other) {
	getImproperFraction();
	numerator = numerator * other.denominator - other.sign * (other.intPart * other.denominator + other.numerator) * denominator;
	denominator *= other.denominator;
	sign = 1;
	getMixedFraction();
	return *this;
}

template<class T>
TFraction<T>& TFraction<T>::operator*=(const TFraction<T>& other) {
	getImproperFraction();
	numerator = numerator * other.sign * (other.intPart * other.denominator + other.numerator);
	denominator *= other.denominator;
	sign = 1;
	getMixedFraction();
	return *this;
}

template<class T>
TFraction<T>& TFraction<T>::operator/=(const TFraction<T>& other) {
	return TFraction::operator*=(TFraction<T>(other.denominator, other.sign *
		(other.intPart * other.denominator + other.numerator)));
}