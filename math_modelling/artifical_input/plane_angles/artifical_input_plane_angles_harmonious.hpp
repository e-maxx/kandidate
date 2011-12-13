/** \file artifical_input_plane_angles_harmonious.hpp
    \brief Содержит класс "artifical_input_plane_angles_harmonious" - источник мат-моделируемых входных данных, представляющих из себя те или иные колебания самолётных углов.
*/

#pragma once
#ifndef MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_PLANE_ANGLES_PLANE_ANGLES_HARMONIOUS_H
#define MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_PLANE_ANGLES_PLANE_ANGLES_HARMONIOUS_H



#include "artifical_input_plane_angles.hpp"



/** Класс "artifical_input_plane_angles_harmonious" - источник мат-моделируемых входных данных, представляющих из себя те или иные колебания самолётных углов.
 *
 * Данный класс применяется при мат. моделировании в качестве источника как
 * входных данных для алгоритма, так и точных решений.
 *
 * Этот класс абстрактный, поскольку конкретный вид зависимости самолётных
 * углов и их производных - конкретный вид задаётся в классах-потомках (путём
 * реализации методов get_angs_() и get_angs_diff_()).
 *
 * Собственно, сам класс предоставляет реализацию виртуальных методов
 * internal_get_instanteous_(), internal_get_integrated_(),
 * internal_get_exact_solution_(). (Для получения мгновенных данных по
 * самолётным углам и их производным вычисляется угловая скорость, для
 * получения интегральных данных производится численное интегрирование,
 * а для получения точного решения самолётные углы конвертируются в
 * кватернион.)
 */
class artifical_input_plane_angles_harmonious : public artifical_input_plane_angles {

public:


	/** Конструктор, принимающий три набора самолётных углов: амплитуду, частоту и сдвиг колебаний.
	 *
	 * В результате каждый из трёх самолётных углов будет меняться по
	 * собственному гармоническому закону.
	 */
	artifical_input_plane_angles_harmonious (
		const plane_angles & amplitude,
		const plane_angles & frequency,
		const plane_angles & shift = plane_angles()
	)
		: amp_   (amplitude),
		  freq_  (frequency),
		  shift_ (shift)
	{ }


	virtual ~artifical_input_plane_angles_harmonious() {
	}


private:

	
	//! Амплитуда колебаний, по каждому из самолётных углов.
	plane_angles amp_;
	//! Частота колебаний, по каждому из самолётных углов.
	plane_angles freq_;
	//! Сдвиг колебаний, по каждому из самолётных углов.
	plane_angles shift_;


	//! Возвращает ориентацию в заданный момент времени.
	virtual plane_angles get_angs_ (double t) {
		return amp_ * sin (freq_ * t + shift_);
	}


	//! Возвращает производную от get_angs_() в заданный момент времени.
	virtual plane_angles get_angs_diff_ (double t) {
		return amp_ * freq_ * cos (freq_ * t + shift_);
	}


}; // class artifical_input_plane_angles_harmonious



#endif // ifndef MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_PLANE_ANGLES_PLANE_ANGLES_HARMONIOUS_H
