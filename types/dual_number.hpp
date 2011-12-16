/*! \file dual_number.hpp
    \brief Содержит класс "dual_number" - дуальное число (вида a+sb, где s - мнимая единица (такая, что s^2 = 0)).
*/
#pragma once
#ifndef TYPES_DUAL_NUMBER_H
#define TYPES_DUAL_NUMBER_H



/** Класс "дуальное число".
 *
 * Это число вида a+sb, где s - мнимая единица (такая, что s^2 = 0).
 */
class dual_number {

public:

	//! Действительная компонента числа.
	long double real;
	//! Мнимая компонента числа (домножающаяся на мнимую единицу s).
	long double imag;


	dual_number()
		: real(0), imag(0)
	{ }

	explicit dual_number (long double real)
		: real(real), imag(0)
	{ }

	dual_number (long double real, long double imag)
		: real(real), imag(imag)
	{ }


	dual_number operator+ (const dual_number & other) const {
		return dual_number (real + other.real, imag + other.imag);
	}

	dual_number operator- (const dual_number & other) const {
		return dual_number (real - other.real, imag - other.imag);
	}

	dual_number operator* (const dual_number & other) const {
		return dual_number (real * other.real, real * other.imag + other.real * imag);
	}

	dual_number operator/ (const dual_number & other) const {
		return dual_number (
			real / other.real,
			(imag * other.real - real * other.imag) / (other.real * other.real)
		);
	}

	dual_number operator* (long double num) const {
		return dual_number (real * num, imag * num);
	}

	dual_number operator/ (long double num) const {
		return dual_number (real / num, imag / num);
	}

	dual_number & operator+= (const dual_number & other) {
		*this = *this + other;
		return *this;
	}

	dual_number & operator-= (const dual_number & other) {
		*this = *this - other;
		return *this;
	}

	dual_number & operator*= (long double num) {
		*this = *this * num;
		return *this;
	}

	dual_number & operator/= (long double num) {
		*this = *this / num;
		return *this;
	}

}; // class dual_number



inline dual_number operator* (long double num, const dual_number & dual_num) {
	return dual_num * num;
}

inline dual_number sin (const dual_number & num) {
	return dual_number (
		sin (num.real),
		num.imag * cos (num.real)
	);
}

inline dual_number cos (const dual_number & num) {
	return dual_number (
		cos (num.real),
		- num.imag * sin (num.real)
	);
}

inline dual_number tan (const dual_number & num) {
	return dual_number (
		tan (num.real),
		num.imag / pow (cos (num.real), 2)
	);
}

inline dual_number log (const dual_number & num) {
	return dual_number (
		log (num.real),
		num.imag / num.real
	);
}

inline dual_number exp (const dual_number & num) {
	long double ex = exp (num.real);
	return dual_number (
		ex,
		ex * num.imag
	);
}

inline dual_number sqrt (const dual_number & num) {
	long double sq = sqrt (num.real);
	return dual_number (
		sq,
		num.imag / 2 / sq
	);
}




#endif // ifndef TYPES_DUAL_NUMBER_H
