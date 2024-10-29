#pragma once
#include "checkML.h"

#include <iostream>

template <class T = int> //double?¿

class Vector2D {
private:
	T x, y;

public:
	Vector2D() {}
	Vector2D(T a, T b) {
		x = a;
		y = b;
	}

	T getX() const {
		return x;
	}
	T getY() const {
		return y;
	}
	void setX(T newX) {
		x = newX;
	}
	void setY(T newY) {
		y = newY;
	}
	Vector2D operator+(const Vector2D& v) const {
		//new vector2D sol(x + v.getX(), y + v.getY());
		Vector2D vec;
		vec.x = x + v.getX();
		vec.y = y + v.getY();
		return vec;
	}
	Vector2D operator-(const Vector2D& v) const {
		Vector2D r;
		r.x = x - v.x;
		r.y = y - v.y;
		return r;
	}
	Vector2D operator*(double d) const {
		Vector2D r;
		r.x = x * d;
		r.y = y * d;
		return r;
	}

	/*void operator+=(const Vector2D v) {
		this->x = this->x + v.x;
		this->y = this->x + v.y;
	}*/

	T operator*(const Vector2D& v) const {
		return v.getX * x + v.getY * y;
	}
	void operator=(const Vector2D& v) {
		x = v.getX();
		y = v.getY();
	}
};

template <class T> using Point2D = Vector2D<T>;