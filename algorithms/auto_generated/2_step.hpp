/** \file 2_step.hpp
    \brief Содержит алгоритм "auto_generated_2_step_algorithm" - автоматически сгенерированный двухшаговый алгоритм.
*/

#pragma once
#ifndef ALGORITHMS_AUTO_GENERATED_2_STEP_H
#define ALGORITHMS_AUTO_GENERATED_2_STEP_H



#include <cmath>
#include "../algorithm.hpp"



/** Класс "auto_generated_2_step_algorithm" - автоматически сгенерированный двухшаговый алгоритм.
 */
template <typename Q, typename I>
class auto_generated_2_step_algorithm : public algorithm<Q,I> {

public:


	//! Запускает алгоритм, возвращая полученные результаты работы.
	virtual typename algorithm<Q, I>::t_output_data_ptr execute() {
		typename algorithm<Q, I>::t_output_data_ptr result = this->init_output_data_();

		for (size_t i=1; i<result->get_count(); ++i) {
			I phi = this->input_data_->get_integrated (result->ts[i-1], result->ts[i]);
			quaternion lambda;

			if (i == 1) {
				long double phi_m = phi.length();

				lambda = quaternion (
					cos (phi_m / 2),
					phi * sin (phi_m / 2) / phi_m
				);
			}
			else {
				I phi2 = this->input_data_->get_integrated (result->ts[i-2], result->ts[i-1]);
				
				Q omega1 = phi;
				Q omega2 = phi2;

				lambda = quaternion(1) + 0.5 * omega1 + 17.0/192 * omega1*omega1 + 1./64 * omega1*omega2 + 1./64 * omega2*omega1 + 1./192 * omega2*omega2;
			}

			(*result)[i] = (*result)[i-1] * lambda;
		}

		return result;
	}


	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() {
		return "Автоматически сгенерированный алгоритм (2-шаговый)";
	}


}; // class auto_generated_2_step_algorithm



#endif // ifndef ALGORITHMS_AUTO_GENERATED_2_STEP_H
