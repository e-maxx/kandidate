/** \file method_2step_4degree.hpp
    \brief Содержит алгоритм "method_2step_4degree" - численный алгоритм (2-шаговый, 4-го порядка точности, по интегральным входным данным).
*/

#pragma once
#ifndef ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_H
#define ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_H



#include <cmath>
#include "../iterative_algorithm.hpp"
#include "../../types/quaternion.hpp"
#include "../../types/vector3.hpp"



/** Класс "method_2step_4degree" - численный алгоритм (2-шаговый, 4-го порядка точности, по интегральным входным данным).
 */
class method_2step_4degree : public iterative_algorithm<quaternion,vector3> {

private:
	

	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Алгоритм (2-шаговый, 4-го порядка, по интегральным данным)";
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
	virtual quaternion get_local_solution_ (long double t, const std::vector<vector3> & gamma) {
		vector3 gamma_s = gamma[0] + gamma[1];
		long double gamma_s_SQ = gamma_s.norm();

		return quaternion (
			1 - gamma_s_SQ / 8,
			(0.5 - gamma_s_SQ / 48) * (gamma_s + crossProduct (gamma[0], gamma[1]) * 2 / 3)
		);
	}


}; // class method_2step_4degree



#endif // ifndef ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_H
