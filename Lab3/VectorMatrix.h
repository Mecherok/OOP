#pragma once

namespace mathobj {
	class Base {
	protected:
		double *arr;
		int row;
		int col;
		int size;
		int ID;
		Base();
		Base(int row, int col, const double *arr);
		Base(const Base &other);
		Base(Base &&other);
	private:
		friend ostream& operator<<(ostream &output, const Base &m) noexcept;
		friend Base operator+(const Base &m1, const Base &m2);
		friend Base operator-(const Base &m1, const Base &m2);
		friend Base operator*(const Base &m1, const Base &m2);
		friend Base operator*(const Base &m, double k);
		friend Base operator*(double k, const Base &m);
		static int countBase;
	public:
		virtual ~Base();
		bool checkSumOrSub(const Base &other) const noexcept;
		bool checkMul(const Base &other) const noexcept;
		bool checkToVector() const noexcept;
		double max() const;
		double min() const;
		static int getCount() noexcept;
		int getID() const noexcept;
		int getSize() const noexcept;
		Base& operator=(const Base &other);
		Base& operator=(Base &&other);
		Base& transposition();
		Base& operator+=(const Base &other);
		Base& operator-=(const Base &other);
		Base& operator*=(const Base &other);
		Base& operator*=(double k);
	};
	
	class Vector : public Base {
	private:
		static int countVect;
	public:
		Vector();
		virtual ~Vector();
		Vector(int size);
		Vector(int size, double, ...);
		Vector(int size, const double *arr);
		Vector(int size, double (*func)(int));
		Vector(const Base &other);
		Vector(Base &&other);
		Vector(const Vector &other);
		Vector(Vector &&other);
		static int getCount() noexcept;
		Vector& operator=(const Base &other);
		Vector& operator=(Base &&other);
		Vector& operator=(const Vector &other);
		double& operator[](int i);
		double operator[](int i) const;
	};
	
	class Matrix : public Base {
	private:
		static int countMtr;
		class Tmp {
		private:
			Matrix *m;
			const Matrix *cm;
			int i;
		public:
			Tmp(Matrix *m, int i);
			Tmp(const Matrix *�m, int i);
			double& operator[](int j);
			double operator[](int j) const;
		};
	public:
		Matrix();
		virtual ~Matrix();
		Matrix(int row, int col);
		Matrix(int row_col);
		Matrix(int row, int col, double, ...);
		Matrix(int row, int col, const double *arr);
		Matrix(int row_col, const double *arr);
		Matrix(int row, int col, double (*func)(int, int));
		Matrix(int row_col, double (*func)(int, int));
		Matrix(const Base &other);
		Matrix(Base &&other);
		Matrix(const Matrix &other);
		Matrix(Matrix &&other);
		static int getCount() noexcept;
		int getRow() const noexcept;
		int getCol() const noexcept;
		Matrix& operator=(const Base &other);
		Matrix& operator=(Base &&other);
		Matrix& operator=(const Matrix &other);
		Tmp operator[](int i);
		const Tmp operator[](int i) const;
	};
};