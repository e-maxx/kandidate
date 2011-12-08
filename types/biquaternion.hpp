/** \file biquaternion.hpp
    \brief Содержит класс "бикватернион".
*/

#pragma once
#ifndef TYPES_BIQUATERNION_H
#define TYPES_BIQUATERNION_H



#include <cmath>
#include "dual_number.hpp"
#include "dual_vector.hpp"
#include "quaternion.hpp"



/** Класс "Бикватернион".
 *
 * Бикватернион - это дуальный кватернион вида a + s b, где a и b - кватернионы, s - мнимая единица (такая, что s^2 = 0).
 */
class biquaternion {

public:

	
	/** Компоненты бикватерниона. */
	//@{
	quaternion a, b;
	//@}

	
	//! Конструктор нулевого бикватерниона.
	biquaternion()
		: a(), b()
	{ }

	biquaternion (const quaternion & a, const quaternion & b)
		: a(a), b(b)
	{ }

	biquaternion (const dual_number & n0, const dual_number & n1, const dual_number & n2, const dual_number & n3)
		: a (n0.real, n1.real, n2.real, n3.real),
		  b (n0.imag, n1.imag, n2.imag, n3.imag)
	{ }

	biquaternion (const dual_number & scalar, const dual_vector & vector)
		: a (scalar.real, vector.real),
		  b (scalar.imag, vector.imag)
	{ }


	//! Компоненты бикватерниона - дуальные числа.
	dual_number operator[] (int idx) const {
		return dual_number (a[idx], b[idx]);
	}

	//! Скалярная часть бикватерниона - дуальное число, образованное скалярными частями кватернионов.
	dual_number get_scalar() const {
		return dual_number (a.get_scalar(), b.get_scalar());
	}

	//! Векторная часть бикватерниона - дуальный вектор, образованный векторными частями кватернионов.
	dual_vector get_vector() const {
		return dual_vector (a.get_vector(), b.get_vector());
	}


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
