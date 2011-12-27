/** \file average_speed_riccati_algorithm.hpp
    \brief Содержит алгоритм "average_speed_riccati_algorithm" - метод средней скорости, модифицированный под уравнения типа Риккати (1-шаговый, 2-го порядка точности, по интегральным входным данным).
*/

#pragma once
#ifndef ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_RICCATI_ALGORITHM_H
#define ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_RICCATI_ALGORITHM_H



#include <boost/typeof/typeof.hpp>
#include <cmath>
#include "../iterative_riccati_algorithm.hpp"



/** Класс "average_speed_riccati_algorithm" - метод средней скорости, модифицированный под уравнения типа Риккати (1-шаговый, 2-го порядка точности, по интегральным входным данным).
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 * @tparam I Выбранный тип входных данных.
 */
template <typename Q, typename I>
class average_speed_riccati_algorithm : public iterative_riccati_algorithm<Q,I> {

private:


	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Метод средней скорости, модифицированный под уравнения типа Риккати (1-шаговый, 2-го порядка, по интегральным данным)";
	}


	/** Вычисляет решение на текущем временном отрезке.
	 *
	 * @param t Время, в которое требуется найти решение.
	 * @param gamma Вектор, состоящий из единственного элемента - входных данных на текущем временном отрезке.
	 */
	virtual Q get_local_riccati_solution_ (long double t, const std::vector<I> & gamma) {
		const I & phi = gamma[0];
		BOOST_AUTO( phi_m, phi.length() );

		return phi / phi_m * tan (phi_m / 4);
	}


}; // class average_speed_riccati_algorithm



#endif // ifndef ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_RICCATI_ALGORITHM_H
