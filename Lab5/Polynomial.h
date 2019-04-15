#pragma once

namespace mathobj {
	class Polynomial {
	private:
		int degree;
		double *arr;
		int ID;
		static int count;
		void correctDegree() noexcept;
		friend ostream& operator<<(ostream &output, const Polynomial &p) noexcept;
		friend Polynomial operator+(const Polynomial &p1, const Polynomial &p2);
		friend Polynomial operator-(const Polynomial &p1, const Polynomial &p2);
		friend Polynomial operator*(const Polynomial &p1, const Polynomial &p2);
		friend Polynomial operator*(const Polynomial & p1, double k);
		friend Polynomial operator*(double k, const Polynomial & p1);
		friend Polynomial operator/(const Polynomial &p1, const Polynomial &p2);
		friend Polynomial operator%(const Polynomial &p1, const Polynomial &p2);
	public:
		Polynomial();
		~Polynomial();
		Polynomial(int degree);
		Polynomial(int degree, const double *arr);
		Polynomial(int degree, double (*func)(int));
		Polynomial(int degree, double el, ...);
		Polynomial(const Polynomial &other);
		Polynomial(Polynomial &&other);
		int getDegree() const noexcept;
		double getCoefficient(int i) const;
		static int getCount() noexcept;
		int getID() const noexcept;
		void setCoefficient(int i, double number);
		Polynomial& operator=(const Polynomial &other);
		Polynomial& operator=(Polynomial &&other);
		double operator()(double x) const;
		double operator[](int i) const;
		Polynomial& operator+=(const Polynomial &other);
		Polynomial& operator-=(const Polynomial &other);
		Polynomial& operator*=(const Polynomial &other);
		Polynomial& operator*=(double k);
		Polynomial& operator/=(const Polynomial &other);
		Polynomial& operator%=(const Polynomial &other);
		bool operator==(const Polynomial &other) const noexcept;
		bool operator==(int degree) const noexcept;
		bool operator!() const noexcept;
		bool operator!=(const Polynomial &other) const noexcept;
		bool operator!=(int degree) const noexcept;
		bool operator<(const Polynomial &other) const noexcept;
		bool operator<(int degree) const noexcept;
		bool operator>(const Polynomial &other) const noexcept;
		bool operator>(int degree) const noexcept;
		bool operator<=(const Polynomial &other) const noexcept;
		bool operator<=(int degree) const noexcept;
		bool operator>=(const Polynomial &other) const noexcept;
		bool operator>=(int degree) const noexcept;
	};
}
