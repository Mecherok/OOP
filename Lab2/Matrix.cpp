#include "stdafx.h"
#include "Matrix.h"

using namespace mathobj;
using namespace std;

int Matrix::count = 0;

istream& mathobj::operator>>(istream &input, Matrix &m) {
	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			cout << "m[" << i << "][" << j << "] = ";
			input >> m.arr[i * m.col + j];
		}
	}
	cout << endl;

	return input;
}

ostream& mathobj::operator<<(ostream &output, const Matrix &m) {
	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			output << m.arr[i * m.col + j] << setw(output.width());
		}
		output << endl;
	}
	cout << endl;

	return output;
}

Matrix mathobj::operator+(const Matrix &m1, const Matrix &m2) {
	if (!m1.checkSumOrSub(m2)) throw "Внешний оператор + для матриц №" + to_string(m1.ID) + " и №" + to_string(m2.ID) +
		": Ошибка! Сложение невозможно!";
	return move(Matrix(m1) += m2);
}

Matrix mathobj::operator-(const Matrix &m1, const Matrix &m2) {
	if (!m1.checkSumOrSub(m2)) throw "Внешний оператор - для матриц №" + to_string(m1.ID) + " и №" + to_string(m2.ID) +
		": Ошибка! Вычитание невозможно!";
	return move(Matrix(m1) -= m2);
}

Matrix mathobj::operator*(const Matrix &m1, const Matrix &m2) {
	if (!m1.checkMul(m2)) throw "Внешний оператор * для матриц №" + to_string(m1.ID) + " и №" + to_string(m2.ID) +
		": Ошибка! Умножение невозможно!";

	Matrix tempMul(m1.row, m2.col);
	for (int i = 0; i < tempMul.row; i++) {
		for (int j = 0; j < tempMul.col; j++) {
			for (int k = 0; k < m1.col; k++) {
				tempMul.arr[i * tempMul.col + j] += m1.arr[i * m1.col + k] * m2.arr[k * m2.col + j];
			}
		}
	}

	return tempMul;
}

Matrix mathobj::operator*(const Matrix &m, double k) {
	return move(Matrix(m) *= k);
}

Matrix mathobj::operator*(double k, const Matrix &m) {
	return mathobj::operator*(m, k);
}

Matrix::Tmp::Tmp(Matrix *m, int i) {
	this->m = m;
	this->i = i;
#ifdef _DEBUG
	cout << "Конструктор для TMP №" << m->ID << endl;
#endif	
}

Matrix::Tmp::Tmp(const Matrix *cm, int i) {
	this->cm = cm;
	this->i = i;
#ifdef _DEBUG
	cout << "Конструктор для TMP №" << cm->ID << endl;
#endif
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
#ifdef _DEBUG
	cout << "Деструктор для матрицы №" << ID << endl;
#endif
	if (arr) delete[] arr;
}
Matrix::Matrix(int row, int col) : Matrix(row, col, (const double*)nullptr) {

}

Matrix::Matrix(int row_col) : Matrix(row_col, row_col) {
	
}

Matrix::Matrix(int row, int col, double el, ...) : Matrix(row, col, &el) {

}

Matrix::Matrix(int row, int col, const double *arr) {
	count++;
	ID = count;
	if (row < 0 || col < 0) throw "Невозможно создать объект! Неверные размеры в матрице №" + to_string(ID);
#ifdef _DEBUG
	cout << "Конструктор для матрицы №" << ID << endl;
#endif
	if (row * col == 0) {
		this->row = 0;
		this->col = 0;
		this->arr = nullptr;
	}
	else {
		this->row = row;
		this->col = col;
		this->arr = new double[this->col * this->row];
		for (int i = 0; i < this->row * this->col; i++) {
			this->arr[i] = arr ? arr[i] : 0.0;
		}
	}
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

Matrix::Matrix(const Matrix &other) : Matrix(other.row, other.col, other.arr) {

}

Matrix::Matrix(Matrix &&other) noexcept : Matrix(0, 0) {
	*this = move(other);
}

bool Matrix::checkSumOrSub(const Matrix &other) const noexcept {
	return this->col == other.col && this->row == other.row && arr && other.arr;
}

bool Matrix::checkMul(const Matrix &other) const noexcept {
	return this->col == other.row && arr && other.arr;
}

double Matrix::max() const {
	if (!arr) throw "Невозможно найти максимальный элемент в нулевой матрице №" + to_string(ID);
	double max = arr[0];
	for (int i = 0; i < row * col; i++) {
		if (arr[i] > max) max = arr[i];
	}

	return max;
}

double Matrix::min() const {
	if (!arr) throw "Невозможно найти минимальный элемент в нулевой матрице №" + to_string(ID);
	double min = arr[0];
	for (int i = 0; i < row * col; i++) {
		if (arr[i] < min) min = arr[i];
	}

	return min;
}

int Matrix::getCount() noexcept {
	return count;
}

int Matrix::getID() const noexcept {
	return ID;
}

int Matrix::getRow() const noexcept {
	return row;
}

int Matrix::getCol() const noexcept {
	return col;
}

Matrix& Matrix::operator=(const Matrix &other) {
	if (this != &other) {
		if (col * row != other.col * other.row) {
			if (arr != nullptr) delete[] arr;
			other.col * other.row == 0 ? arr = nullptr : arr = new double[other.col * other.row];
		}
		
		col = other.col;
		row = other.row;
		
		for (int i = 0; i < row * col; i++) {
			arr[i] = other.arr[i];
		}
	}
	
	return *this;
}

Matrix& Matrix::operator=(Matrix &&other) noexcept {
#ifdef _DEBUG
	cout << "Оператор присваивания перемещения для матрицы №" << ID << endl;
#endif
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

Matrix& Matrix::operator+=(const Matrix &other) {
	if (!checkSumOrSub(other)) throw "Оператор += для матриц №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Сложение невозможно!";

	for (int i = 0; i < row * col; i++) {
		arr[i] += other.arr[i];
	}

	return *this;
}

Matrix& Matrix::operator-=(const Matrix &other) {
	if (!checkSumOrSub(other)) throw "Оператор -= для матриц №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Вычитание невозможно!";
	
	for (int i = 0; i < row * col; i++) {
		arr[i] -= other.arr[i];
	}
	
	return *this;
}

Matrix& Matrix::operator*=(const Matrix &other) {
	if (!checkMul(other)) throw "Оператор *= для матриц №" + to_string(ID) + " и №" + to_string(other.ID) +
		": Ошибка! Умножение невозможно!";

	return *this = *this * other;
}

Matrix& Matrix::operator*=(double k) {
	if (!arr) throw "Оператор *= k для матрицы №" + to_string(ID) + ": Ошибка! Умножение невозможно!";

	for (int i = 0; i < row * col; i++) {
		arr[i] *= k;
	}

	return *this;
}

Matrix::Tmp Matrix::operator[](int i) {
	if (i >= this->row || i < 0 || arr == nullptr) throw "Выход за размер массива в матрице №" + to_string(ID);
	return Tmp(this, i);
}

const Matrix::Tmp Matrix::operator[](int i) const {
	if (i >= this->row || i < 0 || arr == nullptr) throw "Выход за размер массива в матрице №" + to_string(ID);
	return Tmp(this, i);
}