/** \file method_2step_4degree_riccati_2.hpp
    \brief Содержит алгоритм "method_2step_4degree_riccati_2" - численный алгоритм (2-шаговый, 4-го порядка точности, по интегральным входным данным).
*/

#pragma once
#ifndef ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_RICCATI_2_H
#define ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_RICCATI_2_H



#include <cmath>
#include "../iterative_riccati_algorithm.hpp"
#include "../../types/quaternion.hpp"
#include "../../types/vector3.hpp"



/** Класс "method_2step_4degree_riccati_2" - численный алгоритм (2-шаговый, 4-го порядка точности, по интегральным входным данным).
 *
 * Алгоритм работает в кососимметрических переменных (т.е. по уравнению типа Риккати).
 *
 * Данный алгоритм был получен из алгоритма method_2step_4degree.hpp переводом его к виду кососимметрических операторов.
 */
class method_2step_4degree_riccati_2 : public iterative_riccati_algorithm<quaternion,vector3> {

private:
	

	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Алгоритм (2-шаговый, 4-го порядка, по интегральным данным, в кососимм. операторах №2)";
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
		vector3 sum = gamma[0] + gamma[1];

		return sum / 4 + gamma[0].crossProduct (gamma[1]) / 6 + sum * sum.norm() / 192;
	}


}; // class method_2step_4degree_riccati_2



#endif // ifndef ALGORITHMS_OLD_ALGORITHMS_METHOD_2_STEP_4_DEGREE_RICCATI_2_H
