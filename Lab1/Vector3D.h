#pragma once

namespace mathobj {
	class Vector3D {
	private:
		double x;
		double y;
		double z;
		static int count;
		int ID;
		friend Vector3D sum(const Vector3D &v1, const Vector3D &v2);
		friend Vector3D sub(const Vector3D &v1, const Vector3D &v2);
		friend Vector3D mul(const Vector3D &v1, const Vector3D &v2);
		friend Vector3D mulVectors(const Vector3D &v1, const Vector3D &v2);
		friend double scalarMulVectors(const Vector3D &v1, const Vector3D &v2);
		friend double sina(const Vector3D &v1, const Vector3D &v2);
		friend double cosa(const Vector3D &v1, const Vector3D &v2);
		friend double angle(const Vector3D &v1, const Vector3D &v2);
	public:
		Vector3D();
		Vector3D(double x, double y, double z);
		~Vector3D();
		void print() const;
		double getX() const;
		double getY() const;
		double getZ() const;
		int getID() const;
		static int getCount();
		void set(double x, double y, double z);
		void setX(double x);
		void setY(double y);
		void setZ(double z);
		double modul() const;
		void norm();
		void scalarMul(double k);
		Vector3D& operator=(const Vector3D &other);
		Vector3D(const Vector3D &other);
	};
}