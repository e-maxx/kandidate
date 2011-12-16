/** \file vector3.hpp
    \brief Содержит класс "трёхмерный вектор".
*/

#pragma once
#ifndef TYPES_VECTOR3_H
#define TYPES_VECTOR3_H



#include <cmath>
#include <stdexcept>



//! Класс "Трёхмерный вектор".
class vector3 {

public:

	
	/** Компоненты вектора. */
	//@{
	long double x, y, z;
	//@}

	
	//! Конструктор нулевого вектора.
	vector3()
		: x(0), y(0), z(0)
	{ }

	vector3 (long double x, long double y, long double z)
		: x(x), y(y), z(z)
	{ }

	vector3 (const vector3 & v)
		: x(v.x), y(v.y), z(v.z)
	{ }


	/** Индексированный доступ к компонентам вектора.
	 *
	 * @throws std::invalid_argument В случае, если передано некорректное значение idx.
	 */
	long double operator[] (int idx) const {
		if (idx == 0)  return x;
		if (idx == 1)  return y;
		if (idx == 2)  return z;
		throw std::invalid_argument ("Invalid idx value.");
	}

	/** Индексированный доступ к компонентам вектора.
	 *
	 * @throws std::invalid_argument В случае, если передано некорректное значение idx.
	 */
	long double & operator[] (int idx) {
		if (idx == 0)  return x;
		if (idx == 1)  return y;
		if (idx == 2)  return z;
		throw std::invalid_argument ("Invalid idx value.");
	}

	
	vector3 operator+ (const vector3 & v) const {
		return vector3 (x+v.x, y+v.y, z+v.z);
	}

	vector3 operator- (const vector3 & v) const {
		return vector3 (x-v.x, y-v.y, z-v.z);
	}

	//! Умножение на константу.
	vector3 operator* (long double num) const {
		return vector3 (x*num, y*num, z*num);
	}

	//! Деление на константу.
	vector3 operator/ (long double num) const {
		return vector3 (x/num, y/num, z/num);
	}

	//! Унарный минус.
	vector3 operator- () const {
		return vector3 (-x, -y, -z);
	}

	vector3 & operator+= (const vector3 & v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vector3 & operator-= (const vector3 & v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}


	//! Скалярное произведение.
	long double dotProduct (const vector3 & v) const {
		return x * v.x + y * v.y + z * v.z;
	}

	//! Векторное произведение.
	vector3 crossProduct (const vector3 & v) const {
		return vector3 (
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}


	//! Возвращает норму вектора - сумму квадратов компонент.
	long double norm() const {
		return x*x + y*y + z*z;
	}

	//! Возвращает длину (тензор) вектора - квадратный корень из суммы квадратов компонент.
	long double length() const {
		return sqrt (norm());
	}


}; // class vector3



//! Умножение на константу
inline vector3 operator* (long double num, const vector3 & v) {
	return v * num;
}

//! Возвращает расстояние между векторами - т.е. модуль их разности.
inline long double distance (const vector3 & a, const vector3 & b) {
	return (a-b).length();
}

//! Скалярное произведение.
inline long double dotProduct (const vector3 & a, const vector3 & b) {
	return a.dotProduct (b);
}

//! Векторное произведение.
inline vector3 crossProduct (const vector3 & a, const vector3 & b) {
	return a.crossProduct (b);
}



#endif // ifndef TYPES_VECTOR3_H
