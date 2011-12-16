/** \file plane_angles.hpp
    \brief Содержит класс "plane_angles" - самолётные углы.
*/

#pragma once
#ifndef TYPES_PLANE_ANGLES_H
#define TYPES_PLANE_ANGLES_H



#include <cmath>
#include "quaternion.hpp"
#include "../utility_functions.hpp"



/** Класс "plane_angles" - самолётные углы.
 *
 * Самолётные углы - это тройка углов (psi, teta, gamma - курс, крен, тангаж).
 */
class plane_angles {

public:

	
	/** @name Тройка углов.
	 */
	//@{
	long double psi, //!< угол psi - географический курс
		teta, //!< угол teta - угол тангажа
		gamma; //!< угол gamma - угол крена
	//@}

	//! Конструктор нулевой тройки углов.
	plane_angles()
		: psi(0), teta(0), gamma(0)
	{ }

	//! Конструктор от тройки углов.
	plane_angles (long double psi, long double teta, long double gamma)
		: psi(psi), teta(teta), gamma(gamma)
	{ }

	//! Конструктор из кватерниона.
	explicit plane_angles (const quaternion & lambda) {
		psi = atan ((lambda[0] * lambda[2] - lambda[1] * lambda[3]) / (sqr(lambda[0]) + sqr(lambda[1]) - 0.5));
		teta = asin (2 * (lambda[1] * lambda[2] + lambda[0] * lambda[3]));
		gamma = atan ((lambda[0] * lambda[1] - lambda[2] * lambda[3]) / (sqr(lambda[0]) + sqr(lambda[2]) - 0.5));
	}

	//! Преобразование к кватерниону.
	operator quaternion() const {
		return quaternion (
			cos(psi/2) * cos(teta/2) * cos(gamma/2) - sin(psi/2) * sin(teta/2) * sin(gamma/2),
			sin(psi/2) * sin(teta/2) * cos(gamma/2) + cos(psi/2) * cos(teta/2) * sin(gamma/2),
			sin(psi/2) * cos(teta/2) * cos(gamma/2) + cos(psi/2) * sin(teta/2) * sin(gamma/2),
			cos(psi/2) * sin(teta/2) * cos(gamma/2) - sin(psi/2) * cos(teta/2) * sin(gamma/2)
		);
	}


	plane_angles operator+ (const plane_angles & p) const {
		return plane_angles (
			psi   + p.psi,
			teta  + p.teta,
			gamma + p.gamma
		);
	}

	plane_angles operator- (const plane_angles & p) const {
		return plane_angles (
			psi   - p.psi,
			teta  - p.teta,
			gamma - p.gamma
		);
	}

	plane_angles operator* (long double p) const {
		return plane_angles (
			psi   * p,
			teta  * p,
			gamma * p
		);
	}

	//! Скалярное произведение.
	plane_angles operator* (const plane_angles & p) const {
		return plane_angles (
			psi   * p.psi,
			teta  * p.teta,
			gamma * p.gamma
		);
	}


}; // class plane_angles



//! Взятие синуса покомпонентно.
inline plane_angles sin (const plane_angles & p) {
	return plane_angles (
		sin (p.psi),
		sin (p.teta),
		sin (p.gamma)
	);
}

//! Взятие косинуса покомпонентно.
inline plane_angles cos (const plane_angles & p) {
	return plane_angles (
		cos (p.psi),
		cos (p.teta),
		cos (p.gamma)
	);
}



#endif // ifndef TYPES_PLANE_ANGLES_H
