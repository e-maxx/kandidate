/*! \file artifical_input_harmonious.hpp
    \brief Содержит класс "artifical_input_harmonious" - источник мат-моделируемых входных данных, представляющих из себя гармонические колебания.
*/

#pragma once
#ifndef MATH_MODELLING_STUFF_ARTIFICAL_INPUT_HARMONIOUS_H
#define MATH_MODELLING_STUFF_ARTIFICAL_INPUT_HARMONIOUS_H



#include <boost/bind.hpp>
#include "artifical_input.hpp"
#include "../../types/plane_angles.hpp"
#include "../../types/quaternion.hpp"
#include "../../types/vector3.hpp"



/*! Класс "artifical_input_harmonious" - источник мат-моделируемых входных данных, представляющих из себя гармонические колебания.
 *
 * Данный класс применяется при мат. моделировании в качестве источника как
 * входных данных для алгоритма, так и точных решений.
 *
 * Данный класс просто реализует виртуальные методы
 * internal_get_instanteous_(), internal_get_integrated_(),
 * internal_get_exact_solution_().
 *
 * Всю остальную работу по "заворачиванию" этих данных в input_data/output_data
 * делает artifical_input.
 */
class artifical_input_harmonious : public artifical_input < quaternion, vector3 > {

public:


	/*! Конструктор, принимающий три набора самолётных углов: амплитуду, частоту и сдвиг колебаний.
	 *
	 * В результате каждый из трёх самолётных углов будет меняться по
	 * собственному гармоническому закону.
	 */
	artifical_input_harmonious (const plane_angles & amplitude, const plane_angles & frequency, const plane_angles & shift = plane_angles()) {
		amp_ = amplitude;
		freq_ = frequency;
		shift_ = shift;
	}

	virtual ~artifical_input_harmonious() {
	}


protected:
	
	//! Амплитуда колебаний, по каждому из самолётных углов.
	plane_angles amp_;
	//! Частота колебаний, по каждому из самолётных углов.
	plane_angles freq_;
	//! Сдвиг колебаний, по каждому из самолётных углов.
	plane_angles shift_;


	//! Возвращает мгновенные входные данные в данный момент времени.
	virtual vector3 internal_get_instanteous_ (double t) {
		return calc_omega_t_ (t);
	}

	//! Возвращает интегральные входные данные за указанный промежуток времени.
	virtual vector3 internal_get_integrated_ (double t1, double t2) {
		return default_integrator<vector3>()->integrate (boost::bind (&artifical_input_harmonious::calc_omega_t_, this, _1), t1, t2);
	}

	//! Возвращает точное решение в указанный момент времени.
	virtual quaternion internal_get_exact_solution_ (double t) {
		return get_angs_ (t);
	}


	//! Функция, описывающая вид колебаний.
	plane_angles get_angs_ (double t) {
		return plane_angles (
			amp_.psi   *  sin (freq_.psi   *  t  +  shift_.psi),
			amp_.teta  *  sin (freq_.teta  *  t  +  shift_.teta),
			amp_.gamma *  sin (freq_.gamma *  t  +  shift_.gamma)
			);
	}

	//! Функция - производная от get_angs_().
	plane_angles get_angs_diff_ (double t) {
		return plane_angles (
			amp_.psi   *  freq_.psi   * cos (freq_.psi   *  t  +  shift_.psi),
			amp_.teta  *  freq_.teta  * cos (freq_.teta  *  t  +  shift_.teta),
			amp_.gamma *  freq_.gamma * cos (freq_.gamma *  t  +  shift_.gamma)
			);
	}

	//! Функция, вычисляющая мгновенную угловую скорость в заданный момент времени.
	vector3 calc_omega_t_ (double t) {
		return calc_omega_ (get_angs_ (t), get_angs_diff_ (t));
	}

	//! Функция, вычисляющая мгновенную угловую скорость по заданным самолётным углам и их производным в текущий момент времени.
	vector3 calc_omega_ (const plane_angles & angs, const plane_angles & ang_diffs) {
		vector3 result;
		result.x = ang_diffs.gamma + ang_diffs.psi * sin (angs.teta);
		result.y = ang_diffs.teta * sin (angs.gamma) + ang_diffs.psi * cos (angs.teta) * cos (angs.gamma);
		result.z = ang_diffs.teta * cos (angs.gamma) - ang_diffs.psi * cos (angs.teta) * sin (angs.gamma);
		return result;
	}


}; // class artifical_input_harmonious



#endif // ifndef MATH_MODELLING_STUFF_ARTIFICAL_INPUT_HARMONIOUS_H
