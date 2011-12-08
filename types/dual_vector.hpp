/*! \file dual_vector.hpp
    \brief Содержит класс "dual_vector" - дуальный вектор (вида a+sb, где s - мнимая единица (такая, что s^2 = 0), a и b - вектора).
*/
#pragma once
#ifndef TYPES_DUAL_VECTOR_H
#define TYPES_DUAL_VECTOR_H



#include "dual_number.hpp"
#include "vector3.hpp"



/** Класс "дуальный вектор".
 *
 * Это вектор вида a+sb, где s - мнимая единица (такая, что s^2 = 0), a и b - вектора.
 */
class dual_vector {

public:

	//! Действительная компонента дуального вектора.
	vector3 real;
	//! Мнимая компонента дуального вектора (домножающаяся на мнимую единицу s).
	vector3 imag;


	dual_vector()
	{ }

	dual_vector (const vector3 & real, const vector3 & imag)
		: real(real), imag(imag)
	{ }

	dual_vector (const dual_number & x, const dual_number & y, const dual_number & z)
		: real (x.real, y.real, z.real),
		  imag (x.imag, y.imag, z.imag)
	{ }


	/** Индексированный доступ к компонентам дуального вектора, которые являются дуальными числами.
	 *
	 * @throws std::invalid_argument В случае, если передано некорректное значение idx.
	 */
	dual_number operator[] (int idx) const {
		if (idx == 0)  return dual_number (real.x, imag.x);
		if (idx == 1)  return dual_number (real.y, imag.y);
		if (idx == 2)  return dual_number (real.z, imag.z);
		throw std::invalid_argument ("Invalid idx value.");
	}


	dual_number get_x() const {
		return dual_number (real.x, imag.x);
	}

	dual_number get_y() const {
		return dual_number (real.y, imag.y);
	}

	dual_number get_z() const {
		return dual_number (real.z, imag.z);
	}


	dual_vector operator+ (const dual_vector & other) const {
		return dual_vector (real + other.real, imag + other.imag);
	}

	dual_vector operator- (const dual_vector & other) const {
		return dual_vector (real - other.real, imag - other.imag);
	}

	dual_vector operator* (double num) const {
		return dual_vector (real * num, imag * num);
	}

	dual_vector operator/ (double num) const {
		return dual_vector (real / num, imag / num);
	}

	dual_vector operator* (const dual_number & num) const {
		return dual_vector (
			get_x() * num,
			get_y() * num,
			get_z() * num
		);
	}

	dual_vector operator/ (const dual_number & num) const {
		return dual_vector (
			get_x() / num,
			get_y() / num,
			get_z() / num
		);
	}


	//! Модуль дуального вектора - дуальное число.
	dual_number length() const {
		dual_number sum;
		for (int i=0; i<3; ++i) {
			dual_number cur = (*this)[i];
			sum += cur * cur;
		}
		return sqrt (sum);
	}


}; // class dual_vector



inline dual_vector operator* (double num, const dual_vector & dual_vec) {
	return dual_vec * num;
}

inline dual_vector operator* (const dual_number & num, const dual_vector & dual_vec) {
	return dual_vec * num;
}



#endif // ifndef TYPES_DUAL_VECTOR_H
