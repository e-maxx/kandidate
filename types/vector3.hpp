/*! \file vector3.hpp
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

	
	/*! Компоненты вектора. */
	//@{
	double x, y, z;
	//@}

	
	//! Конструктор нулевого вектора.
	vector3()
		: x(0), y(0), z(0)
	{ }

	vector3 (double x, double y, double z)
		: x(x), y(y), z(z)
	{ }

	vector3 (const vector3 & v)
		: x(v.x), y(v.y), z(v.z)
	{ }


	/*! Индексированный доступ к компонентам вектора.
	 *
	 * @throws std::invalid_argument В случае, если передано некорректное значение idx.
	 */
	double operator[] (int idx) {
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
	vector3 operator* (double num) const {
		return vector3 (x*num, y*num, z*num);
	}

	vector3 operator- () const {
		return vector3 (-x, -y, -z);
	}


	//! Возвращает норму вектора - сумму квадратов компонент.
	double norm() const {
		return x*x + y*y + z*z;
	}

	//! Возвращает длину (тензор) вектора - квадратный корень из суммы квадратов компонент.
	double length() const {
		return sqrt (norm());
	}


}; // class vector3



//! Возвращает расстояние между векторами - т.е. модуль их разности.
inline double distance (const vector3 & a, const vector3 & b) {
	return (a-b).length();
}



#endif // ifndef TYPES_VECTOR3_H
