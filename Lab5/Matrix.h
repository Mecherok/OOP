#pragma once
#include <iostream>

namespace mathobj {
	class Matrix {
	private:
		double *arr;
		int row;
		int col;
		static int count;
		int ID;
		friend std::istream& operator>>(std::istream &input, Matrix &m);
		friend std::ostream& operator<<(std::ostream &output, const Matrix &m);
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
			double& operator[](int j);
			double operator[](int j) const;
		};
	public:
		explicit Matrix();
		~Matrix();
		explicit Matrix(int row, int col);
		explicit Matrix(int row_col);
		explicit Matrix(int row, int col, double, ...);
		explicit Matrix(int row, int col, const double *arr);
		explicit Matrix(int row_col, const double *arr);
		explicit Matrix(int row, int col, double(*func)(int, int));
		explicit Matrix(int row_col, double(*func)(int, int));
		Matrix(const Matrix &other);
		Matrix(Matrix &&other) noexcept;
		bool checkSumOrSub(const Matrix &other) const noexcept;
		bool checkMul(const Matrix &other) const noexcept;
		double max() const;
		double min() const;
		static int getCount() noexcept;
		int getID() const noexcept;
		int getRow() const noexcept;
		int getCol() const noexcept;
		Matrix& operator=(const Matrix &other);
		Matrix& operator=(Matrix &&other) noexcept;
		Matrix& operator+=(const Matrix &other);
		Matrix& operator-=(const Matrix &other);
		Matrix& operator*=(const Matrix &other);
		Matrix& operator*=(double k);
		Tmp operator[](int i);
		const Tmp operator[](int i) const;
		bool operator==(const Matrix &other) const;
		bool operator!=(const Matrix &other) const;
		bool operator>(const Matrix &other) const;
		bool operator<(const Matrix &other) const;
		bool operator>=(const Matrix &other) const;
		bool operator<=(const Matrix &other) const;
	};
}