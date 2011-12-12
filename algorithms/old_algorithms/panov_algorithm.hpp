/** \file panov_algorithm.hpp
    \brief Содержит алгоритм "panov_algorithm" - алгоритм Панова (4-шаговый, 6-го порядка точности, по интегральным входным данным).
*/

#pragma once
#ifndef ALGORITHMS_OLD_ALGORITHMS_PANOV_ALGORITHM_H
#define ALGORITHMS_OLD_ALGORITHMS_PANOV_ALGORITHM_H



#include <cmath>
#include "../algorithm.hpp"
#include "../../types/quaternion.hpp"
#include "../../types/matrix33.hpp"
#include "../../types/vector3.hpp"



/** Класс "panov_algorithm" - алгоритм Панова (4-шаговый, 6-го порядка точности, по интегральным входным данным).
 */
class panov_algorithm : public algorithm<quaternion,vector3> {

public:


	//! Запускает алгоритм, возвращая полученные результаты работы.
	virtual t_output_data_ptr execute() {
		t_output_data_ptr result = init_output_data_();

		for (size_t i=1; i<result->get_count(); ++i) {
			double prev_t = result->ts[i-1];
			double h = step_;


			vector3 gamma[5];
			matrix33 Gamma[5];
			for (int j=1; j<=4; ++j) {
				vector3 & g = gamma[j];
				g = input_data_->get_integrated (prev_t + (j-1) * h/4, prev_t + j * h/4);

				Gamma[j] = matrix33 (
					    0,   -g[2],    g[1],
					 g[2],       0,   -g[0],
					-g[1],    g[0],       0
				);
			}

			vector3 phi =
				22.0/45 * (Gamma[1] + Gamma[2]) * (gamma[3] + gamma[4]) +
				32.0/45 * (Gamma[1] * gamma[2] + Gamma[3] * gamma[4]);

			vector3 delta_phi =
				32.0/45 * (Gamma[1]*Gamma[2]*gamma[4] - Gamma[4]*Gamma[1]*gamma[3]) +
				64.0/45 * (gamma[2].dotProduct (gamma[3])) * Gamma[2] * gamma[3];

			
			for (int j=1; j<=4; ++j)
				phi += gamma[j];
			phi += delta_phi;


			double phi_m = phi.length();
			quaternion lambda (
				cos (phi_m / 2),
				phi * sin (phi_m / 2) / phi_m
			);

			(*result)[i] = (*result)[i-1] * lambda;
		}

		return result;
	}


	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Алгоритм Панова (4-шаговый, 6-го порядка, по интегральным данным)";
	}


}; // class panov_algorithm



#endif // ifndef ALGORITHMS_OLD_ALGORITHMS_PANOV_ALGORITHM_H
