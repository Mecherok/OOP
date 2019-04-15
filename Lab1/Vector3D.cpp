#include "stdafx.h"
#include "Vector3D.h"
using namespace mathobj;

int Vector3D::count = 0;

Vector3D::Vector3D() {
	x = 0;
	y = 0;
	z = 0;
	count++;
	ID = count;
#ifdef _DEBUG
	cout << "Сработал конструктор вектора " << ID << endl;
#endif
}

Vector3D::Vector3D(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
	count++;
	ID = count;
#ifdef _DEBUG
	cout << "Сработал конструктор вектора " << ID << endl;
#endif
}

Vector3D::~Vector3D() {
#ifdef _DEBUG
	cout << "Сработал деструктор вектора " << ID << endl;
#endif
}

void Vector3D::print() const {
	cout << "Значения вектора №" << ID << endl;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "z = " << z << endl;
}

double Vector3D::getX() const {
	return x;
}

double Vector3D::getY() const {
	return y;
}

double Vector3D::getZ() const {
	return z;
}

int Vector3D::getID() const {
	return ID;
}

int Vector3D::getCount() {
	return count;
}

void Vector3D::set(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3D::setX(double x) {
	this->x = x;
}

void Vector3D::setY(double y) {
	this->y = y;
}

void Vector3D::setZ(double z) {
	this->z = z;
}

double Vector3D::modul() const {
	return sqrt(x * x + y * y + z * z);
}

void Vector3D::norm() {
	double a = modul();
	if (a == 0) throw ("Функция norm для вектора №" + to_string(ID) +
		" : " + " Ошибка! Деление на 0!");
	x /= a;
	y /= a;
	z /= a;
}

void Vector3D::scalarMul(double k) {
	x *= k;
	y *= k;
	z *= k;
}

Vector3D::Vector3D(const Vector3D &other) {
	count++;
	ID = count;
#ifdef _DEBUG
	cout << "Сработал конструктор копирования " << ID << endl;
#endif
	*this = other;
}

Vector3D& Vector3D::operator=(const Vector3D &other) {
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

Vector3D mathobj::sum(const Vector3D &v1, const Vector3D &v2) {
	Vector3D tempSum;
	tempSum.x = v1.x + v2.x;
	tempSum.y = v1.y + v2.y;
	tempSum.z = v1.y + v2.y;
	return tempSum;
}

Vector3D mathobj::sub(const Vector3D &v1, const Vector3D &v2) {
	Vector3D tempSub;
	tempSub.x = v1.x - v2.x;
	tempSub.y = v1.y - v2.y;
	tempSub.z = v1.z - v2.z;
	return tempSub;
}

Vector3D mathobj::mul(const Vector3D &v1, const Vector3D &v2) {
	Vector3D tempMul;
	tempMul.x = v1.x * v2.x;
	tempMul.y = v1.y * v2.y;
	tempMul.z = v1.z * v2.z;
	return tempMul;
}

Vector3D mathobj::mulVectors(const Vector3D &v1, const Vector3D &v2) {
	Vector3D tempVectMul;
	tempVectMul.x = v1.y * v2.z - v1.z * v2.y;
	tempVectMul.y = v1.z * v2.x - v1.x * v2.z;
	tempVectMul.z = v1.x * v2.y - v1.y * v2.x;
	return tempVectMul;
}

double mathobj::scalarMulVectors(const Vector3D &v1, const Vector3D &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double mathobj::sina(const Vector3D &v1, const Vector3D &v2) {
	if ((v1.modul() * v2.modul()) == 0) throw ("Функция sina для векторов №" + to_string(v1.ID) +
		" и №" + to_string(v2.ID) + " : " + " Ошибка! Деление на 0!");
	return mulVectors(v1, v2).modul() / (v1.modul() * v2.modul());
}

double mathobj::cosa(const Vector3D &v1, const Vector3D &v2) {
	if ((v1.modul() * v2.modul()) == 0) throw ("Функция cosa для векторов №" + to_string(v1.ID) + 
		" и №" + to_string(v2.ID) +	" : " + " Ошибка! Деление на 0!");
		
	return scalarMulVectors(v1, v2) / (v1.modul() * v2.modul());
}

double mathobj::angle(const Vector3D &v1, const Vector3D &v2) {
	return atan2(sina(v1, v2), cosa(v1, v2)) * 180.0 / M_PI;
}