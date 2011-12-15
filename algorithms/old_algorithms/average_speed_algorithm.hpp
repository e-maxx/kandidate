/** \file average_speed_algorithm.hpp
    \brief Содержит алгоритм "average_speed_algorithm" - метод средней скорости (1-шаговый, 2-го порядка точности, по интегральным входным данным).
*/

#pragma once
#ifndef ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_ALGORITHM_H
#define ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_ALGORITHM_H



#include <boost/typeof/typeof.hpp>
#include <cmath>
#include "../iterative_algorithm.hpp"



/** Класс "average_speed_algorithm" - метод средней скорости (1-шаговый, 2-го порядка точности, по интегральным входным данным).
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 * @tparam I Выбранный тип входных данных.
 */
template <typename Q, typename I>
class average_speed_algorithm : public iterative_algorithm<Q,I> {

private:


	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Метод средней скорости (1-шаговый, 2-го порядка, по интегральным данным)";
	}


	/** Вычисляет решение на текущем временном отрезке.
	 *
	 * @param t Время, в которое требуется найти решение.
	 * @param gamma Вектор, состоящий из единственного элемента - входных данных на текущем временном отрезке.
	 */
	virtual Q get_local_solution_ (double t, const std::vector<I> & gamma) {
		const I & phi = gamma[0];
		BOOST_AUTO( phi_m, phi.length() );

		return Q (
			cos (phi_m / 2),
			phi * sin (phi_m / 2) / phi_m
		);
	}


}; // class average_speed_algorithm



#endif // ifndef ALGORITHMS_OLD_ALGORITHMS_AVERAGE_SPEED_ALGORITHM_H
