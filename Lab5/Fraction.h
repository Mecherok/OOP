#pragma once

namespace mathobj {
	class Fraction {
	private:
		int numerator;
		int denominator;
		int intPart;
		int sign;
		int ID;
		static int count;
		void simplification() noexcept;
		void reduction() noexcept;
		void IntPart() noexcept;
		friend ostream& operator<<(ostream &output, const Fraction &f) noexcept;
		friend Fraction operator+(const Fraction &f1, const Fraction &f2);
		friend Fraction operator-(const Fraction &f1, const Fraction &f2);
		friend Fraction operator* (const Fraction &f1, const Fraction &f2);
		friend Fraction operator/(const Fraction &f1, const Fraction &f2);
	public:
		Fraction();
		~Fraction();
		Fraction(int numerator);
		Fraction(int numerator, int denominator);
		Fraction(int intPart, int numerator, int denominator);
		Fraction(int intPart, int numerator, int denomirator, int sign);
		Fraction(const Fraction &other);
		int getIntPart() const noexcept;
		int getNominator() const noexcept;
		int getDenominator() const noexcept;
		int getSign() const noexcept;
		double getDouble() const noexcept;
		void setIntPart(int number);
		void setNominator(int number);
		void setDenominator(int number);
		void setSign(int number);
		static int getCount() noexcept;
		int getID() const noexcept;
		Fraction& getMixedFraction() noexcept;
		Fraction& getImproperFraction() noexcept;
		Fraction& operator=(const Fraction &other);
		Fraction& operator++();
		Fraction operator++(int);
		Fraction& operator-();
		Fraction& operator--();
		Fraction operator--(int);
		Fraction& operator+=(const Fraction &other);
		Fraction& operator-=(const Fraction &other);
		Fraction& operator*=(const Fraction &other);
		Fraction& operator/=(const Fraction &other);
		bool operator==(const Fraction &other) const noexcept;
		bool operator!=(const Fraction &other) const noexcept;
		bool operator>(const Fraction &other) const noexcept;
		bool operator<(const Fraction &other) const noexcept;
		bool operator>=(const Fraction &other) const noexcept;
		bool operator<=(const Fraction &other) const noexcept;
	};
}