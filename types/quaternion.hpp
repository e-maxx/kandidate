/** \file quaternion.hpp
    \brief Содержит класс "кватернион".
*/

#pragma once
#ifndef TYPES_QUATERNION_H
#define TYPES_QUATERNION_H



#include <cmath>
#include <iosfwd>
#include <stdexcept>
#include "vector3.hpp"
#include "../constants.hpp"



/** Класс "Кватернион".
 *
 * Кватернион - это гиперкомплексное число с четырьмя компонентами (w, x, y, z).
 */
class quaternion {

public:

	
	/** Компоненты кватерниона. */
	//@{
	long double w, x, y, z;
	//@}

	
	//! Конструктор нулевого кватерниона.
	quaternion()
		: w(0), x(0), y(0), z(0)
	{ }

	quaternion (long double w, long double x, long double y, long double z)
		: w(w), x(x), y(y), z(z)
	{ }

	//! Конструктор кватерниона от скалярной и векторной частей.
	quaternion (long double w, const vector3 & v)
		: w(w), x(v.x), y(v.y), z(v.z)
	{ }

	//! Конструктор кватерниона с нулевой векторной частью.
	explicit quaternion (long double num)
		: w(num), x(0), y(0), z(0)
	{ }

	//! Конструктор кватерниона с нулевой скалярной частью.
	quaternion (const vector3 & v)
		: w(0), x(v.x), y(v.y), z(v.z)
	{ }


	/** Индексированный доступ к компонентам кватерниона.
	 *
	 * @throws std::invalid_argument В случае, если передано некорректное значение idx.
	 */
	long double operator[] (int idx) const {
		if (idx == 0)  return w;
		if (idx == 1)  return x;
		if (idx == 2)  return y;
		if (idx == 3)  return z;
		throw std::invalid_argument ("Invalid idx value.");
	}

	/** Индексированный доступ к компонентам кватерниона.
	 *
	 * @throws std::invalid_argument В случае, если передано некорректное значение idx.
	 */
	long double & operator[] (int idx) {
		if (idx == 0)  return w;
		if (idx == 1)  return x;
		if (idx == 2)  return y;
		if (idx == 3)  return z;
		throw std::invalid_argument ("Invalid idx value.");
	}


	//! Скалярная часть кватерниона - член w.
	long double get_scalar() const {
		return w;
	}

	//! Векторная часть кватерниона - вектор, образованный членами (x,y,z).
	vector3 get_vector() const {
		return vector3 (x, y, z);
	}

	
	quaternion operator+ (long double num) const {
		return quaternion (w+num, x, y, z);
	}

	quaternion operator+ (const quaternion & q) const {
		return quaternion (w+q.w, x+q.x, y+q.y, z+q.z);
	}

	quaternion operator- (long double num) const {
		return quaternion (w-num, x, y, z);
	}

	quaternion operator- (const quaternion & q) const {
		return quaternion (w-q.w, x-q.x, y-q.y, z-q.z);
	}

	//! Умножение на константу.
	quaternion operator* (long double num) const {
		return quaternion (w*num, x*num, y*num, z*num);
	}

	//! Деление на константу.
	quaternion operator/ (long double num) const {
		return quaternion (w/num, x/num, y/num, z/num);
	}

	//! Кватернионное произведение.
	quaternion operator* (const quaternion & q) const {
		quaternion result;
		result.w = w * q.w - x * q.x - y * q.y - z * q.z;
		result.x = w * q.x + x * q.w + y * q.z - z * q.y;
		result.y = w * q.y - x * q.z + y * q.w + z * q.x;
		result.z = w * q.z + x * q.y - y * q.x + z * q.w;
		return result;
	}

	quaternion operator- () const {
		return quaternion (-w, -x, -y, -z);
	}
	

	quaternion & operator+= (const quaternion & q) {
		*this = *this + q;
		return *this;
	}

	quaternion & operator-= (const quaternion & q) {
		*this = *this - q;
		return *this;
	}

	quaternion & operator*= (long double num) {
		*this = *this * num;
		return *this;
	}

	quaternion & operator/= (long double num) {
		*this = *this / num;
		return *this;
	}


	//! Сопряжённый кватернион.
	quaternion conjugate() const {
		return quaternion (w, -x, -y, -z);
	}

	//! Обратный кватернион - умножение на который слева/справа эквивалентно делению слева/справа на исходный кватернион.
	quaternion inverse() const {
		return conjugate() * (1 / norm());
	}

	
	bool operator== (const quaternion & q) const {
		return abs (w - q.w) < EPS && abs (x - q.x) < EPS && abs (y - q.y) < EPS && abs (z - q.z) < EPS;
	}


	//! Возвращает норму кватерниона - сумму квадратов компонент.
	long double norm() const {
		return w*w + x*x + y*y + z*z;
	}

	//! Возвращает длину (тензор) кватерниона - квадратный корень из суммы квадратов компонент.
	long double length() const {
		return sqrt (norm());
	}


	//! Возвращает единичный кватернион.
	static quaternion get_unit() {
		return quaternion (1);
	}


}; // class quaternion



inline quaternion operator+ (long double a, const quaternion & b) {
	return b + a;
}

inline quaternion operator- (long double a, const quaternion & b) {
	return quaternion (a-b.w, -b.x, -b.y, -b.z);
}

inline quaternion operator* (long double a, const quaternion & b) {
	return b * a;
}



//! Возвращает расстояние между кватернионами - т.е. модуль их разности.
inline long double distance (const quaternion & a, const quaternion & b) {
	return (a-b).length();
}


//! Вывод кватерниона.
std::ostream & operator<< (std::ostream & stream, const quaternion & q) {
	return stream << q.w << ' ' << q.x << ' ' << q.y << ' ' << q.z << ' ';
}



#endif // ifndef TYPES_QUATERNION_H
