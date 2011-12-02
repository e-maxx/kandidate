/*! \file biquaternion.hpp
    \brief Содержит класс "бикватернион".
*/

#pragma once
#ifndef TYPES_BIQUATERNION_H
#define TYPES_BIQUATERNION_H



#include <cmath>
#include "quaternion.hpp"



/*! Класс "Бикватернион".
 *
 * Бикватернион - это число вида a + s b, где a и b - кватернионы, s - мнимая единица (такая, что s^2 = 0).
 */
class biquaternion {

public:

	
	/*! Компоненты бикватерниона. */
	//@{
	quaternion a, b;
	//@}

	
	//! Конструктор нулевого бикватерниона.
	biquaternion()
		: a(), b()
	{ }

	biquaternion (quaternion a, quaternion b)
		: a(a), b(b)
	{ }

	
	biquaternion operator+ (const biquaternion & q) const {
		return biquaternion (a+q.a, b+q.b);
	}

	biquaternion operator- (const biquaternion & q) const {
		return biquaternion (a-q.a, b-q.b);
	}

	//! Умножение на константу.
	biquaternion operator* (double num) const {
		return biquaternion (a*num, b*num);
	}

	//! Деление на константу.
	biquaternion operator/ (double num) const {
		return biquaternion (a/num, b/num);
	}

	//! Бикватернионное произведение.
	biquaternion operator* (const biquaternion & q) const {
		biquaternion result;
		result.a = a * q.a + b * q.b;
		result.b = a * q.b + b * q.a;
		return result;
	}

	biquaternion operator- () const {
		return biquaternion (-a, -b);
	}


}; // class biquaternion



//! Возвращает расстояние между бикватернионами - максимум из расстояний между частями a и b.
inline double distance (const biquaternion & p, const biquaternion & q) {
	return std::max (distance (p.a, q.a), distance (p.b, q.b));
}



#endif // ifndef TYPES_BIQUATERNION_H
