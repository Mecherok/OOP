#pragma once

namespace mathobj {
	template<typename T>
	class TPolynomial;

	template<class T>
	ostream& operator<<(ostream &output, const TPolynomial<T> &p) noexcept {
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

	template<class T>
	TPolynomial<T> operator+(const TPolynomial<T> &p1, const TPolynomial<T> &p2) {
		if (!p1.arr || !p2.arr) throw "Сложение полиномов №" + to_string(p1.ID) + " и №" + to_string(p2.ID) + " невозможно!";
		return move(TPolynomial<T>(p1) += p2);
	}

	template<class T>
	TPolynomial<T> operator-(const TPolynomial<T> &p1, const TPolynomial<T> &p2) {
		if (!p1.arr || !p2.arr) throw "Вычитание полиномов №" + to_string(p1.ID) + " и №" + to_string(p2.ID) + " невозможно!";
		return move(TPolynomial<T>(p1) -= p2);
	}

	template<class T>
	TPolynomial<T> operator*(const TPolynomial<T> &p1, const TPolynomial<T> &p2) {
		if (!p1.arr || !p2.arr) throw "Умножение полиномов №" + to_string(p1.ID) + " и №" + to_string(p2.ID) + " невозможно!";
		return move(TPolynomial<T>(p1) *= p2);
	}

	template<class T>
	TPolynomial<T> operator*(const TPolynomial<T> &p1, int k) {
		if (!p1.arr) throw "Умножение полинома №" + to_string(p1.ID) + " невозможно!";
		return move(TPolynomial<T>(p1) *= k);
	}

	template<class T>
	TPolynomial<T> operator*(int k, const TPolynomial<T> &p1) {
		return mathobj::operator*(p1, k);
	}

	template<class T>
	TPolynomial<T> operator/(const TPolynomial<T> &p1, const TPolynomial<T> &p2) {
		if (!p1.arr || !p2.arr)throw "Деление полиномов №" + to_string(p1.ID) + " и №" + to_string(p2.ID) + " невозможно!";
		return move(TPolynomial<T>(p1) /= p2);
	}

	template<class T>
	TPolynomial<T> operator%(const TPolynomial<T> &p1, const TPolynomial<T> &p2) {
		if (p1.degree < p2.degree || !p1.arr || !p2.arr) throw "Деление с остатком полиномов №" + to_string(p1.ID) + " и №" + to_string(p2.ID) + " невозможно!";
		return TPolynomial<T>(p1) %= p2;
	}

	template<class T>
	class TPolynomial {
	private:
		int degree;
		T *arr;
		int ID;
		static int count;
		void correctDegree() noexcept;
		friend ostream&::operator<< <T>(ostream &output, const TPolynomial<T> &p) noexcept;
		friend TPolynomial<T> operator+ <T>(const TPolynomial<T> &p1, const TPolynomial<T> &p2);
		friend TPolynomial<T> operator- <T>(const TPolynomial<T> &p1, const TPolynomial<T> &p2);
		friend TPolynomial<T> operator* <T>(const TPolynomial<T> &p1, const TPolynomial<T> &p2);
		friend TPolynomial<T> operator* <T>(const TPolynomial<T> & p1, int k);
		friend TPolynomial<T> operator* <T>(int k, const TPolynomial<T> & p1);
		friend TPolynomial<T> operator/ <T>(const TPolynomial<T> &p1, const TPolynomial<T> &p2);
		friend TPolynomial<T> operator% <T>(const TPolynomial<T> &p1, const TPolynomial<T> &p2);
	public:
		TPolynomial<T>();
		~TPolynomial<T>();
		TPolynomial<T>(int degree);
		TPolynomial<T>(int degree, const T *arr);
		TPolynomial<T>(int degree, const T el, ...);
		TPolynomial<T>(const TPolynomial<T> &other);
		TPolynomial<T>(TPolynomial<T> &&other);
		int getDegree() const noexcept;
		T getCoefficient(int i) const;
		static int getCount() noexcept;
		int getID() const noexcept;
		void setCoefficient(int i, const T& number);
		TPolynomial<T>& operator=(const TPolynomial<T> &other);
		TPolynomial<T>& operator=(TPolynomial<T> &&other);
		T operator()(double x) const;
		T operator[](int i) const;
		TPolynomial<T>& operator+=(const TPolynomial<T> &other);
		TPolynomial<T>& operator-=(const TPolynomial<T> &other);
		TPolynomial<T>& operator*=(const TPolynomial<T> &other);
		TPolynomial<T>& operator*=(int k);
		TPolynomial<T>& operator/=(const TPolynomial<T> &other);
		TPolynomial<T>& operator%=(const TPolynomial<T> &other);
		bool operator==(const TPolynomial<T> &other) const noexcept;
		bool operator==(int degree) const noexcept;
		bool operator!=(const TPolynomial<T> &other) const noexcept;
		bool operator!=(int degree) const noexcept;
		bool operator<(const TPolynomial<T> &other) const noexcept;
		bool operator<(int degree) const noexcept;
		bool operator>(const TPolynomial<T> &other) const noexcept;
		bool operator>(int degree) const noexcept;
		bool operator<=(const TPolynomial<T> &other) const noexcept;
		bool operator<=(int degree) const noexcept;
		bool operator>=(const TPolynomial<T> &other) const noexcept;
		bool operator>=(int degree) const noexcept;
	};
}

using namespace mathobj;
template <class T>
int TPolynomial<T>::count = 0;

template<class T>
TPolynomial<T>::TPolynomial() {
	++count;
	ID = count;
	degree = 0;
	arr = nullptr;
}

template<class T>
TPolynomial<T>::~TPolynomial() {
	if (arr) delete[] arr;
}

template<class T>
TPolynomial<T>::TPolynomial(int degree) : TPolynomial<T>(degree, (const T*)nullptr) {

}


template<class T>
TPolynomial<T>::TPolynomial(int degree, const T *arr) {
	++count;
	ID = count;
	if (degree < 0) throw "Невозможно создать объект №" + to_string(ID);
	this->degree = degree;
	if (arr) {
		for (int i = 0; i <= degree; i++) {
			if (arr[i] != 0) this->degree = i;
		}
	}
	this->arr = new T[this->degree + 1];
	for (int i = 0; i <= this->degree; i++) {
		this->arr[i] = arr ? arr[i] : T(0);
	}
}

template<class T>
TPolynomial<T>::TPolynomial(int degree, const T el, ...) : TPolynomial<T>(degree) {
	this->arr[0] = el;
	va_list arg;
	va_start(arg, el);
	for (int i = 1; i <= this->degree; i++) {
		this->arr[i] = va_arg(arg, T);
	}
	va_end(arg);
}

template<class T>
TPolynomial<T>::TPolynomial(const TPolynomial<T> &other) : TPolynomial<T>(other.degree, other.arr) {

}

template<class T>
TPolynomial<T>::TPolynomial(TPolynomial<T> &&other) : TPolynomial<T>() {
	*this = move(other);
}

template<class T>
void TPolynomial<T>::correctDegree() noexcept {
	if (degree == 0) return;
	if (arr[degree] == 0) {
		do {
			degree--;
		} while (degree && arr[degree] == 0);
	}
}

template<class T>
int TPolynomial<T>::getDegree() const noexcept {
	return degree;
}

template<class T>
T TPolynomial<T>::getCoefficient(int i) const {
	if (!arr) throw "Невозмоно выполнить действие в нулевом полиноме №" + to_string(ID);
	if (i > degree || i < 0) throw "Неверная степень коэффициента в полиноме №" + to_string(ID);
	return arr[i];
}

template<class T>
int TPolynomial<T>::getCount() noexcept {
	return count;
}

template<class T>
int TPolynomial<T>::getID() const noexcept {
	return ID;
}

template<class T>
void TPolynomial<T>::setCoefficient(int i, const T& number) {
	if (!arr) throw "Невозмоно выполнить действие в нулевом полиноме №" + to_string(ID);
	if (i > degree || i < 0) throw "Неверная степень коэффициента в полиноме №" + to_string(ID);
	arr[i] = number;
	correctDegree();
}

template<class T>
TPolynomial<T>& TPolynomial<T>::operator=(const TPolynomial<T> &other) {
	if (this != &other) {
		if (!other.arr) {
			degree = 0;
			arr = nullptr;
			return *this;
		}
		if (degree != other.degree) {
			if (arr) delete[] arr;
			degree = other.degree;
			arr = new T[degree + 1];
		}
		if (degree == 0) arr = new T[1];
		for (int i = 0; i <= degree; i++) {
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

template<class T>
TPolynomial<T>& TPolynomial<T>::operator=(TPolynomial<T> &&other) {
	if (this != &other) {
		if (arr) delete[] arr;
		arr = other.arr;
		degree = other.degree;
		other.arr = nullptr;
		other.degree = 0;
	}
	return *this;
}

template<class T>
T TPolynomial<T>::operator()(double x) const {
	if (!arr) throw "Невозмоно выполнить действие в нулевом полиноме №" + to_string(ID);
	T sum(0);
	for (int i = degree; i > 0; i--) {
		sum += arr[i] * pow(x, i);
	}
	sum += arr[0];

	return sum;
}

template<class T>
T TPolynomial<T>::operator[](int i) const {
	if (!arr) throw "Невозмоно выполнить действие в нулевом полиноме №" + to_string(ID);
	if (i < 0 || i > degree) throw "Неверная степень полинома №" + to_string(ID);
	return arr[i];
}

template<class T>
TPolynomial<T>& TPolynomial<T>::operator+=(const TPolynomial<T> &other) {
	if (!arr || !other.arr) throw "Сложение полиномов №" + to_string(ID) + " и №" + to_string(other.ID) + " невозможно!";

	if (this->degree < other.degree) {
		TPolynomial<T> temp(other.degree);
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

template<class T>
TPolynomial<T>& TPolynomial<T>::operator-=(const TPolynomial<T> &other) {
	if (!arr || !other.arr) throw "Сложение полиномов №" + to_string(ID) + " и №" + to_string(other.ID) + " невозможно!";

	if (this->degree < other.degree) {
		TPolynomial<T> temp(other.degree);
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

template<class T>
TPolynomial<T>& TPolynomial<T>::operator*=(const TPolynomial<T> &other) {
	if (!arr || !other.arr) throw "Умножение полиномов №" + to_string(ID) + " и №" + to_string(other.ID) + " невозможно!";

	if (other.degree == 0) {
		for (int i = degree; i >= 0; i--) {
			arr[i] *= other.arr[0];
		}
	}
	else {
		TPolynomial<T> temp(degree + other.degree);
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

template<class T>
TPolynomial<T>& TPolynomial<T>::operator*=(int k) {
	if (!arr) throw "Невозмоно выполнить действие в нулевом полиноме №" + to_string(ID);
	for (int i = degree; i >= 0; i--) {
		arr[i] *= k;
	}
	correctDegree();
	return *this;
}

template<class T>
TPolynomial<T>& TPolynomial<T>::operator/=(const TPolynomial<T> &other) {
	if (degree < other.degree || !arr || !other.arr) throw "Деление полиномов №" + to_string(ID) + " и №" + to_string(other.ID) + " невозможно!";

	bool flag = true;
	TPolynomial<T> temp(degree - other.degree);
	TPolynomial<T> temp1(*this);
	TPolynomial<T> temp2(other);
	TPolynomial<T> temp3(temp1.degree);

	T gcd;
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
		temp1.degree--;

		if (temp2.degree > temp1.degree) flag = false;
	}

	temp.correctDegree();
	return *this = move(temp);
}

template<class T>
TPolynomial<T>& TPolynomial<T>::operator%=(const TPolynomial<T> &other) {
	if (degree < other.degree || !arr || !other.arr) throw "Деление с остатком полиномов №" + to_string(ID) + " и №" + to_string(other.ID) + " невозможно!";

	bool flag = true;
	TPolynomial<T> temp(*this);
	TPolynomial<T> temp1(other);
	TPolynomial<T> temp2(temp.degree);

	T gcd;
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

		if (temp.degree == 0) flag = 0;
		else temp.degree--;

		if (temp1.degree > temp.degree) flag = false;
	}

	temp.correctDegree();
	return *this = move(temp);
}

template<class T>
bool TPolynomial<T>::operator==(const TPolynomial<T> &other) const noexcept {
	if (degree != other.degree) return false;
	for (int i = 0; i <= degree; i++) {
		if (arr[i] != other.arr[i]) return false;
	}
	return true;
}

template<class T>
bool TPolynomial<T>::operator==(int degree) const noexcept {
	return this->degree == degree;
}

template<class T>
bool TPolynomial<T>::operator!=(const TPolynomial<T> &other) const noexcept {
	return !TPolynomial<T>::operator==(other);
}

template<class T>
bool TPolynomial<T>::operator!=(int degree) const noexcept {
	return !TPolynomial<T>::operator==(degree);
}

template<class T>
bool TPolynomial<T>::operator<(const TPolynomial<T> &other) const noexcept {
	return degree < other.degree;
}

template<class T>
bool TPolynomial<T>::operator<(int degree) const noexcept {
	return this->degree < degree;
}

template<class T>
bool TPolynomial<T>::operator>(const TPolynomial<T> &other) const noexcept {
	return !TPolynomial<T>::operator<(other);
}

template<class T>
bool TPolynomial<T>::operator>(int degree) const noexcept {
	return !TPolynomial<T>::operator<(degree);
}

template<class T>
bool TPolynomial<T>::operator<=(const TPolynomial<T> &other) const noexcept {
	return degree <= other.degree;
}

template<class T>
bool TPolynomial<T>::operator<=(int degree) const noexcept {
	return this->degree <= degree;
}

template<class T>
bool TPolynomial<T>::operator>=(const TPolynomial<T> &other) const noexcept {
	return degree >= other.degree;
}

template<class T>
bool TPolynomial<T>::operator>=(int degree) const noexcept {
	return this->degree >= degree;
}

