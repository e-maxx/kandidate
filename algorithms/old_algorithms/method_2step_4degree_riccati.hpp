/** \file method_2step_4degree_riccati.hpp
    \brief Содержит алгоритм "method_2step_4degree_riccati" - численный алгоритм (2-шаговый, 4-го порядка точности, по интегральным входным данным).
*/

#pragma once
#ifndef ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_RICCATI_H
#define ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_RICCATI_H



#include <cmath>
#include "../iterative_riccati_algorithm.hpp"
#include "../../types/quaternion.hpp"
#include "../../types/vector3.hpp"



/** Класс "method_2step_4degree_riccati" - численный алгоритм (2-шаговый, 4-го порядка точности, по интегральным входным данным).
 *
 * Алгоритм работает в кососимметрических переменных (т.е. по уравнению типа Риккати).
 */
class method_2step_4degree_riccati : public iterative_riccati_algorithm<quaternion,vector3> {

private:
	

	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Алгоритм (2-шаговый, 4-го порядка, по интегральным данным, в кососимм. операторах)";
	}


	/** Возвращает "Шаговость" алгоритма.
	 *
	 * Шаговость - это то, во сколько раз дискретность выдачи решения
	 * меньше дискретности входных данных.
	 */
	virtual int get_algorithm_steps_count_() {
		return 2;
	}


	/** Вычисляет решение на текущем временном отрезке.
	 *
	 * @param t Время, в которое требуется найти решение.
	 * @param gamma Вектор, состоящий из двух элементов - входных данных на текущем временном отрезке.
	 */
	virtual quaternion get_local_riccati_solution_ (long double t, const std::vector<vector3> & gamma) {
		quaternion q0 = gamma[0];
		quaternion q1 = gamma[1];

		quaternion tmp = q0 * q0 * q0 + q1 * q1 * q1;
		return (gamma[0] + gamma[1]) / 4 + crossProduct (gamma[0], gamma[1]) / 6 - tmp.get_vector() / 48;
	}


}; // class method_2step_4degree_riccati



#endif // ifndef ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_RICCATI_H
