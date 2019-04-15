#pragma once

namespace mathobj {
	class Matrix {
	private:
		double *arr;
		int row;
		int col;
		static int count;
		int ID;
		friend istream& operator>>(istream &input, Matrix &m);
		friend ostream& operator<<(ostream &output, const Matrix &m);
		friend Matrix operator+(const Matrix &m1, const Matrix &m2);
		friend Matrix operator-(const Matrix &m1, const Matrix &m2);
		friend Matrix operator*(const Matrix &m1, const Matrix &m2);
		friend Matrix operator*(const Matrix &m, double k);
		friend Matrix operator*(double k, const Matrix &m);
		class Tmp {
		private:
			Matrix *m;
			const Matrix *cm;
			int i;
		public:
			Tmp(Matrix *m, int i);
			Tmp(const Matrix *ñm, int i);
			double& operator[](int j); // L-value - T&
			double operator[](int j) const; // R-value - T, const T, const T&
		};
	public:
		Matrix();
		~Matrix();
		Matrix(int row, int col);
		Matrix(int row_col);
		Matrix(int row, int col, double, ...);
		Matrix(int row, int col, const double *arr);
		Matrix(int row_col, const double *arr);
		Matrix(int row, int col, double (*func)(int, int));
		Matrix(int row_col, double (*func)(int, int));
		Matrix(const Matrix &other);
		Matrix(Matrix &&other);
		bool checkSumOrSub(const Matrix &other) const;
		bool checkMul(const Matrix &other) const;
		double max() const;
		double min() const;
		static int getCount();
		int getID() const;
		int getRow() const;
		int getCol() const;
		Matrix& operator=(const Matrix &other);
		Matrix& operator=(Matrix &&other);
		Matrix& operator+=(const Matrix &other);
		Matrix& operator-=(const Matrix &other);
		Matrix& operator*=(const Matrix &other);
		Matrix& operator*=(double k);
		Tmp operator[](int i);
		const Tmp operator[](int i) const;
	};
}