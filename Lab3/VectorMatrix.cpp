#include "stdafx.h"
#include "VectorMatrix.h"
using namespace mathobj;
using namespace std;

int Base::countBase = 0;
int Matrix::countMtr = 0;
int Vector::countVect = 0;

ostream& mathobj::operator<<(ostream &output, const Base &b) noexcept {
	for (int i = 0; i < b.row; i++) {
		for (int j = 0; j < b.col; j++) {
			output << b.arr[i * b.col + j] << setw(output.width());
		}
		output << endl;
	}

	return output;
}

Base mathobj::operator+(const Base &b1, const Base &b2) {
	if (!b1.checkSumOrSub(b2)) throw "Внешний оператор + для объектов №" + to_string(b1.ID) + " и №" + to_string(b2.ID) +
		": Ошибка! Сложение невозможно!";

	Base tempSum(b1);
	tempSum.operator+=(b2);

	return tempSum;
}

Base mathobj::operator-(const Base &b1, const Base &b2) {
	if (!b1.checkSumOrSub(b2)) throw "Внешний оператор - для объектов №" + to_string(b1.ID) + " и №" + to_string(b2.ID) +
		": Ошибка! Вычитание невозможно!";

	Base tempSub(b1);
	tempSub.operator-=(b2);

	return tempSub;
}

Base mathobj::operator*(const Base &b1, const Base &b2) {
	if (!b1.checkMul(b2)) throw "Внешний оператор * для объектов №" + to_string(b1.ID) + " и №" + to_string(b2.ID) +
		": Ошибка! Умножение невозможно!";

	Base tempMul(b1.row, b2.col, (const double*)nullptr);
	for (int i = 0; i < tempMul.row; i++) {
		for (int j = 0; j < tempMul.col; j++) {
			for (int k = 0; k < b1.col; k++) {
				tempMul.arr[i * tempMul.col + j] += b1.arr[i * b1.col + k] * b2.arr[k * b2.col + j];
			}
		}
	}
	
	return tempMul;
}

Base mathobj::operator*(const Base &b, double k) {
	Base tempScalarMul(b);
	tempScalarMul.operator*=(k);
	return tempScalarMul;
}

Base mathobj::operator*(double k, const Base &b) {
	return mathobj::operator*(b, k);
}

Base::Base() : Base(0, 0, (const double*)nullptr) {
	
}

Base::~Base() {
	if (arr) delete[] arr;
}

Base::Base(int row, int col, const double *arr) {
	++countBase;
	ID = countBase;
	if (row * col < 0) throw "Невозможно создать объект №" + to_string(ID);
	if (col * row == 0) {
		this->row = this->col = this->size = 0;
		this->arr = nullptr;
	}
	else {
		this->row = row;
		this->col = col;
		this->size = this->row * this->col;
		this->arr = new double[this->size];
		for (int i = 0; i < this->size; i++) {
			this->arr[i] = arr ? arr[i] : 0.0;
		}
	}
}

Base::Base(const Base &other) : Base(other.row, other.col, other.arr) {
	
}

Base::Base(Base &&other) : Base(0, 0, (const double*)nullptr) {
	*this = move(other);
}

bool Base::checkSumOrSub(const Base &other) const noexcept {
	return row == other.row && col == other.col;
}

bool Base::checkMul(const Base &other) const noexcept {
	return col == other.row;
}

bool Base::checkToVector() const noexcept {
	return col >= 1 && row == 1 || row >= 1 && col == 1 || !arr;
}

double Base::max() const {
	if (!arr) throw "Невозможно найти максимальный элемент в нулевом объекте №" + to_string(ID);
	double max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) max = arr[i];
	}

	return max;
}

double Base::min() const {
	if (!arr) throw "Невозможно найти минимальный элемент в нулевом объекте №" + to_string(ID);
	double min = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] < min) min = arr[i];
	}

	return min;
}

int Base::getCount() noexcept {
	return countBase;
}

int Base::getID() const noexcept {
	return ID;
}

int Base::getSize() const noexcept {
	return size;
}

Base& Base::operator=(const Base &other) {
	if (this != &other) {
		if (size != other.size) {
			if (arr) delete[] arr;
			size = other.size;
			size == 0 ? arr = nullptr : arr = new double[size];
		}

		col = other.col;
		row = other.row;

		for (int i = 0; i < size; i++) {
			arr[i] = other.arr[i];
		}
	}

	return *this;
}

Base& Base::operator=(Base &&other) {
	if (this != &other) {
		if (arr) delete[] arr;
		row = other.row;
		col = other.col;
		size = other.size;
		this->arr = other.arr;
		other.arr = nullptr;
		other.row = other.col = other.size = 0;
	}

	return *this;
}

Base& Base::transposition() {
	if (!checkToVector()) {
		int j = 0;
		int k = row * col - 2;
		double buff = 0;
		int buff_col = col;

		while (buff_col > 1) {
			for (int i = row - 2; i != -1; --i) {
				j = i * buff_col + (buff_col - 1);
				buff = arr[j];
				while (j < k) {
					arr[j] = arr[j + 1];
					++j;
				}
				arr[k] = buff;
				--k;
			}
			--k;
			--buff_col;
		}
	}
	
	swap(row, col);
	return *this;
}

Base& Base::operator+=(const Base &other) {
	if (!checkSumOrSub(other)) throw "Оператор += для объектов №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Сложение невозможно!";

	for (int i = 0; i < size; i++) {
		arr[i] += other.arr[i];
	}

	return *this;
}

Base& Base::operator-=(const Base &other) {
	if (!checkSumOrSub(other)) throw "Оператор -= для объектов №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Вычитание невозможно!";

	for (int i = 0; i < size; i++) {
		arr[i] -= other.arr[i];
	}

	return *this;
}

Base& Base::operator*=(const Base &other) {
	if (!checkMul(other)) throw "Оператор *= для объектов №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Умножение невозможно!";

	return *this = *this * other;
}

Base& Base::operator*=(double k) {
	for (int i = 0; i < size; i++) {
		arr[i] *= k;
	}

	return *this;
}

Vector::Vector() : Vector(0) {

}

Vector::~Vector() {

}

Vector::Vector(int size) : Vector(size, (const double*)nullptr) {

}

Vector::Vector(int size, double d, ...) : Vector(size, &d) {

}

Vector::Vector(int size, const double *arr) : Base(size, 1, arr) {
	++countVect;
}

Vector::Vector(int size, double (*func)(int)) : Vector(size) {
	for (int i = 0; i < this->size; i++) {
		this->arr[i] = func(i);
	}
}

Vector::Vector(const Base &other) {
	if (!other.checkToVector()) throw "Копирование двумерного объекта №" + to_string(other.getID()) +
		" в объект №" + to_string(ID) + " невозможно!";
	Base::operator=(other);
}

Vector::Vector(Base &&other) {
	if (!other.checkToVector()) throw "Копирование двумерного объекта №" + to_string(other.getID()) +
		" в объект №" + to_string(ID) + " невозможно!";
	Base::operator=(move(other));
}

Vector::Vector(const Vector &other) : Vector(other.size, other.arr) {

}

Vector::Vector(Vector &&other) : Vector(0) {
	*this = move(other);
}

int Vector::getCount() noexcept {
	return countVect;
}

Vector& Vector::operator=(const Base &other) {
	if (!other.checkToVector()) throw "Копирование двумерного объекта №" + to_string(other.getID()) +
		" в объект №" + to_string(ID) + " невозможно!";
	Base::operator=(other);
	return *this;
}

Vector& Vector::operator=(Base &&other) {
	if (!other.checkToVector()) throw "Копирование двумерного объекта №" + to_string(other.getID()) +
		" в объект №" + to_string(ID) + " невозможно!";
	Base::operator=(move(other));
	return *this;
}

Vector& Vector::operator=(const Vector &other) {
	Base::operator=(other);
	return *this;
}

double& Vector::operator[](int i) {
	if (i >= size || i < 0) throw "Выход за размер массива в векторе №" + to_string(ID);
	return arr[i];
}

double Vector::operator[](int i) const {
	if (i >= size || i < 0) throw "Выход за размер массива в векторе №" + to_string(ID);
	return arr[i];
}

Matrix::Tmp::Tmp(Matrix *m, int i) {
	this->m = m;
	this->i = i;
}

Matrix::Tmp::Tmp(const Matrix *cm, int i) {
	this->cm = cm;
	this->i = i;
}

double& Matrix::Tmp::operator[](int j) {
	if (j >= this->m->col || j < 0) throw "Выход за размер массива в матрице №" + to_string(m->ID);
	return m->arr[i * m->col + j];
}

double Matrix::Tmp::operator[](int j) const {
	if (j >= this->cm->col || j < 0) throw "Выход за размер массива в матрице №" + to_string(cm->ID);
	return cm->arr[i * cm->col + j];
}

Matrix::Matrix() : Matrix(0, 0) {
	
}

Matrix::~Matrix() {

}

Matrix::Matrix(int row, int col) : Matrix(row, col, (const double*)nullptr) {

}

Matrix::Matrix(int row_col) : Matrix(row_col, row_col) {

}

Matrix::Matrix(int row, int col, double el, ...) : Matrix(row, col, &el) {

}

Matrix::Matrix(int row, int col, const double *arr) : Base(row, col, arr) {
	++countMtr;
}

Matrix::Matrix(int row_col, const double *arr) : Matrix(row_col, row_col, arr) {

}

Matrix::Matrix(int row, int col, double (*func)(int, int)) : Matrix(row, col) {
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			this->arr[i * this->col + j] = func(i, j);
		}
	}
}

Matrix::Matrix(int row_col, double (*func)(int, int)) : Matrix(row_col, row_col, func) {

}

Matrix::Matrix(const Base &other) {
	Base::operator=(other);
}

Matrix::Matrix(Base &&other) {
	Base::operator=(move(other));
}

Matrix::Matrix(const Matrix &other) : Matrix(other.row, other.col, other.arr) {

}

Matrix::Matrix(Matrix &&other) : Matrix(0, 0) {
	*this = move(other);
}

int Matrix::getCount() noexcept {
	return countMtr;
}

int Matrix::getRow() const noexcept {
	return row;
}

int Matrix::getCol() const noexcept {
	return col;
}

Matrix& Matrix::operator=(const Base &other) {
	Base::operator=(other);
	return *this;
}

Matrix& Matrix::operator=(Base &&other) {
	Base::operator=(move(other));
	return *this;
}

Matrix& Matrix::operator=(const Matrix &other) {
	Base::operator=(other);
	return *this;
}

Matrix::Tmp Matrix::operator[](int i) {
	if (i >= this->row || i < 0) throw "Выход за размер массива в матрице №" + to_string(ID);
	return Tmp(this, i);
}

const Matrix::Tmp Matrix::operator[](int i) const {
	if (i >= this->row || i < 0) throw "Выход за размер массива в матрице №" + to_string(ID);
	return Tmp(this, i);
}