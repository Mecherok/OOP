#pragma once
#include <iostream>

using namespace std;

namespace mathobj {
	template<typename T>
	class TMatrix;
	
	template <class T>
	ostream& operator<<(ostream &output, const TMatrix<T> &m) noexcept {
		for (int i = 0; i < m.row; i++) {
			for (int j = 0; j < m.col; j++) {
				output << m.arr[i * m.col + j] << setw(output.width());
			}
			output << endl;
		}
		output << endl;

		output << setw(0);
		return output;
	}

	template <class T>
	TMatrix<T> operator+(const TMatrix<T> &m1, const TMatrix<T> &m2) {
		if (!m1.checkSumOrSub(m2)) throw "Внешний оператор + для шаблонных матриц №" + to_string(m1.ID) + " и №" + to_string(m2.ID) +
			": Ошибка! Сложение невозможно!";

		return move(TMatrix<T>(m1) += m2);
	}

	template <class T>
	TMatrix<T> operator-(const TMatrix<T> &m1, const TMatrix<T> &m2) {
		if (!m1.checkSumOrSub(m2)) throw "Внешний оператор - для шаблонных матриц №" + to_string(m1.ID) + " и №" + to_string(m2.ID) +
			": Ошибка! Вычитание невозможно!";
		
		return move(TMatrix<T>(m1) -= m2);
	}
		
	template <class T>
	TMatrix<T> operator*(const TMatrix<T> &m1, const TMatrix<T> &m2) {
		if (!m1.checkMul(m2)) throw "Внешний оператор * для шаблонных матриц №" + to_string(m1.ID) + " и №" + to_string(m2.ID) +
			": Ошибка! Умножение невозможно!";
		
		TMatrix<T> tempMul(m1.row, m2.col);
		for (int i = 0; i < tempMul.row; i++) {
			for (int j = 0; j < tempMul.col; j++) {
				tempMul.arr[i * tempMul.col + j] = m1.arr[i * m1.col] * m2.arr[j];
				for (int k = 1; k < m1.col; k++) {
						tempMul.arr[i * tempMul.col + j] += m1.arr[i * m1.col + k] * m2.arr[k * m2.col + j];
				}
			}
		}

		return tempMul;
	}

	template <class T>
	TMatrix<T> operator*(const TMatrix<T> &m, const T& k) {
		return move(TMatrix<T>(m) *= k);
	}

	template <class T>
	TMatrix<T> operator*(const T& k, const TMatrix<T> &m) {
		return mathobj::operator*(m, k);
	}
	
	template <class T>
	class TMatrix {
	private:
		T *arr;
		int row;
		int col;
		static int count;
		int ID;
		friend ostream&::operator<< <T>(ostream &output, const TMatrix<T> &m) noexcept;
		friend TMatrix<T> operator+ <T>(const TMatrix<T> &m1, const TMatrix<T> &m2);
		friend TMatrix<T> operator- <T>(const TMatrix<T> &m1, const TMatrix<T> &m2);
		friend TMatrix<T> operator* <T>(const TMatrix<T> &m1, const TMatrix<T> &m2);
		friend TMatrix<T> operator* <T>(const TMatrix<T> &m, const T& k);
		friend TMatrix<T> operator* <T>(const T& k, const TMatrix<T> &m);
		class Tmp {
		private:
			TMatrix<T> *m;
			const TMatrix<T> *cm;
			int i;
		public:
			Tmp(TMatrix<T> *m, int i);
			Tmp(const TMatrix<T> *сm, int i);
			T& operator[](int j);
			const T& operator[](int j) const;
		};
	public:
		explicit TMatrix();
		~TMatrix();
		explicit TMatrix(int row, int col);
		explicit TMatrix(int row_col);
		explicit TMatrix(int row, int col, T el, ...);
		explicit TMatrix(int row, int col, const T *arr);
		explicit TMatrix(int row_col, const T *arr);
		explicit TMatrix(int row, int col, T (*func)(int, int));
		explicit TMatrix(int row_col, T (*func)(int, int));
		TMatrix(const TMatrix<T> &other);
		TMatrix(TMatrix<T> &&other);
		bool checkSumOrSub(const TMatrix<T> &other) const noexcept;
		bool checkMul(const TMatrix<T> &other) const noexcept;
		T max() const;
		T min() const;
		static int getCount() noexcept;
		int getID() const noexcept;
		int getRow() const noexcept;
		int getCol() const noexcept;
		TMatrix<T>& operator=(const TMatrix<T> &other);
		TMatrix<T>& operator=(TMatrix<T> &&other);
		TMatrix<T>& operator+=(const TMatrix<T> &other);
		TMatrix<T>& operator-=(const TMatrix<T> &other);
		TMatrix<T>& operator*=(const TMatrix<T> &other);
		TMatrix<T>& operator*=(const T& k);
		Tmp operator[](int i);
		const Tmp operator[](int i) const;
		bool operator==(const TMatrix<T>& other) const;
		bool operator!=(const TMatrix<T>& other) const;
		bool operator>(const TMatrix<T>& other) const;
		bool operator<(const TMatrix<T>& other) const;
		bool operator>=(const TMatrix<T>& other) const;
		bool operator<=(const TMatrix<T>& other) const;
	};
}

using namespace mathobj;
template <class T>
int TMatrix<T>::count = 0;

template <class T>
TMatrix<T>::Tmp::Tmp(TMatrix<T> *m, int i) {
	this->m = m;
	this->i = i;
}

template <class T>
TMatrix<T>::Tmp::Tmp(const TMatrix<T> *cm, int i) {
	this->cm = cm;
	this->i = i;
}

template <class T>
T& TMatrix<T>::Tmp::operator[](int j) {
	if (j >= this->m->col || j < 0) throw "Выход за размер массива в шаблонной матрице №" + to_string(m->ID);
	return m->arr[i * m->col + j];
}

template <class T>
const T& TMatrix<T>::Tmp::operator[](int j) const {
	if (j >= this->cm->col || j < 0) throw "Выход за размер массива в шаблонной матрице №" + to_string(cm->ID);
	return cm->arr[i * cm->col + j];
}

template <class T>
TMatrix<T>::TMatrix() : TMatrix(0, 0) {

}

template<class T>
TMatrix<T>::~TMatrix() {
	if (arr) delete[] arr;
}

template<class T>
TMatrix<T>::TMatrix(int row, int col) : TMatrix(row, col, (const T*)nullptr) {

}

template<class T>
TMatrix<T>::TMatrix(int row_col) : TMatrix(row_col, row_col) {

}

template<class T>
TMatrix<T>::TMatrix(int row, int col, T el, ...) : TMatrix(row, col, (const T*)nullptr) {
	this->arr[0] = el;
	va_list arg;
	va_start(arg, el);
	for (int i = 1; i < this->row * this->col; i++) {
		this->arr[i] = va_arg(arg, T);
	}
	va_end(arg);
}

template<class T>
TMatrix<T>::TMatrix(int row, int col, const T *arr) {
	count++;
	ID = count;
	if (row < 0 || col < 0) throw "Невозможно создать объект! Неверные размеры в шаблонной матрице №" + to_string(ID);
	if (row * col == 0) {
		this->row = 0;
		this->col = 0;
		this->arr = nullptr;
	}
	else {
		this->row = row;
		this->col = col;
		this->arr = new T[this->col * this->row];
		for (int i = 0; i < this->row * this->col; i++) {
			this->arr[i] = arr ? arr[i] : T();
		}
	}
}

template<class T>
TMatrix<T>::TMatrix(int row_col, const T *arr) : TMatrix(row_col, row_col, arr) {

}

template<class T>
TMatrix<T>::TMatrix(int row, int col, T(*func)(int, int)) : TMatrix(row, col, (const T*)nullptr) {
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			this->arr[i * this->col + j] = func(i, j);
		}
	}
}

template<class T>
TMatrix<T>::TMatrix(int row_col, T(*func)(int, int)) : TMatrix(row_col, row_col, func) {

}

template<class T>
TMatrix<T>::TMatrix(const TMatrix<T> &other) : TMatrix(other.row, other.col, other.arr) {
	
}

template<class T>
TMatrix<T>::TMatrix(TMatrix<T> &&other) : TMatrix(0, 0) {
	*this = move(other);
}

template<class T>
bool TMatrix<T>::checkSumOrSub(const TMatrix<T> &other) const noexcept {
	return this->col == other.col && this->row == other.row;
}

template<class T>
bool TMatrix<T>::checkMul(const TMatrix<T> &other) const noexcept {
	return this->col == other.row;
}

template<class T>
T TMatrix<T>::max() const {
	if (!arr) throw "Невозможно найти максимальный элемент в нулевой шаблонной матрице №" + to_string(ID);
	T max = arr[0];
	for (int i = 0; i < row * col; i++) {
		if (arr[i] > max) max = arr[i];
	}

	return max;
}

template<class T>
T TMatrix<T>::min() const {
	if (!arr) throw "Невозможно найти минимальный элемент в нулевой шаблонной матрице №" + to_string(ID);
	T min = arr[0];
	for (int i = 0; i < row * col; i++) {
		if (arr[i] < min) min = arr[i];
	}

	return min;
}

template<class T>
int TMatrix<T>::getCount() noexcept {
	return count;
}

template<class T>
int  TMatrix<T>::getID() const noexcept {
	return ID;
}

template<class T>
int TMatrix<T>::getRow() const noexcept {
	return row;
}

template<class T>
int TMatrix<T>::getCol() const noexcept {
	return col;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator=(const TMatrix<T> &other) {
	if (this != &other) {
		if (col * row != other.col * other.row) {
			if (arr) delete[] arr;
			other.col * other.row == 0 ? arr = nullptr : arr = new T[other.col * other.row];
		}

		col = other.col;
		row = other.row;

		for (int i = 0; i < row * col; i++) {
			arr[i] = other.arr[i];
		}
	}

	return *this;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator=(TMatrix<T> &&other) {
	if (this != &other) {
		delete[] arr;
		row = other.row;
		col = other.col;
		this->arr = other.arr;
		other.arr = nullptr;
		other.row = other.col = 0;
	}

	return *this;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator+=(const TMatrix<T> &other) {
	if (!checkSumOrSub(other)) throw "Оператор += для шаблонных матриц №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Сложение невозможно!";

	for (int i = 0; i < row * col; i++) {
		arr[i] += other.arr[i];
	}

	return *this;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator-=(const TMatrix<T> &other) {
	if (!checkSumOrSub(other)) throw "Оператор -= для шаблонных матриц №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Вычитание невозможно!";

	for (int i = 0; i < row * col; i++) {
		arr[i] -= other.arr[i];
	}

	return *this;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator*=(const TMatrix<T> &other) {
	if (!checkMul(other)) throw "Оператор *= для шаблонных матриц №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Умножение невозможно!";

	return *this = *this * other;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator*=(const T& k) {
	for (int i = 0; i < row * col; i++) {
		arr[i] *= k;
	}

	return *this;
}

template<class T>
typename TMatrix<T>::Tmp TMatrix<T>::operator[](int i) {
	if (i >= this->row || i < 0 || arr == nullptr) throw "Выход за размер массива в шаблонной матрице №" + to_string(ID);
	return Tmp(this, i);
}

template<class T>
typename const TMatrix<T>::Tmp TMatrix<T>::operator[](int i) const {
	if (i >= this->row || i < 0 || arr == nullptr) throw "Выход за размер массива в шаблонной матрице №" + to_string(ID);
	return Tmp(this, i);
}

template<class T>
bool TMatrix<T>::operator==(const TMatrix<T> &other) const {
	return col == other.col && row == other.row;
}

template<class T>
bool TMatrix<T>::operator!=(const TMatrix<T> &other) const {
	return !Matrix::operator==(other);
}

template<class T>
bool TMatrix<T>::operator>(const TMatrix<T> &other) const {
	return col * row > other.col * other.row;
}

template<class T>
bool TMatrix<T>::operator<(const TMatrix<T> &other) const {
	return col * row < other.col * other.row;
}

template<class T>
bool TMatrix<T>::operator>=(const TMatrix<T> &other) const {
	return col * row >= other.col * other.row;
}

template<class T>
bool TMatrix<T>::operator<=(const TMatrix<T> &other) const {
	return col * row <= other.col * other.row;
}