/** \file artifical_input_plane_angles.hpp
    \brief Содержит класс "artifical_input_plane_angles" - источник мат-моделируемых входных данных, представляющих из себя те или иные колебания самолётных углов.
*/

#pragma once
#ifndef MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_PLANE_ANGLES_PLANE_ANGLES_H
#define MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_PLANE_ANGLES_PLANE_ANGLES_H



#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/typeof/typeof.hpp>
#include "../artifical_input.hpp"
#include "../../../types/plane_angles.hpp"
#include "../../../types/quaternion.hpp"
#include "../../../types/vector3.hpp"



/** Класс "artifical_input_plane_angles" - источник мат-моделируемых входных данных, представляющих из себя те или иные колебания самолётных углов.
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
class artifical_input_plane_angles : public artifical_input<quaternion,vector3> {

public:


	virtual ~artifical_input_plane_angles() {
	}


protected:


	/** Возвращает ориентацию в заданный момент времени.
	 * 
	 * Классы-потомки должны реализовывать этот метод, задавая тем самым
	 * конкретный вид колебаний.
	 */
	virtual plane_angles get_angs_ (double t) = 0;


	/** Возвращает производную от get_angs_() в заданный момент времени.
	 * 
	 * Классы-потомки должны реализовывать этот метод, задавая тем самым
	 * конкретный вид колебаний.
	 */
	virtual plane_angles get_angs_diff_ (double t) = 0;


private:


	//! Возвращает мгновенные входные данные в данный момент времени.
	virtual vector3 internal_get_instanteous_ (double t) {
		return calc_omega_ (this->get_angs_ (t), this->get_angs_diff_ (t));
	}

	//! Возвращает интегральные входные данные за указанный промежуток времени.
	virtual vector3 internal_get_integrated_ (double t1, double t2) {
		BOOST_AUTO( func, boost::bind (&artifical_input_plane_angles::internal_get_instanteous_, this, _1) );
		return default_integrator<vector3>()->integrate (func, t1, t2);
	}

	//! Возвращает точное решение в указанный момент времени.
	virtual quaternion internal_get_exact_solution_ (double t) {
		return (quaternion) get_angs_ (t);
	}


	//! Функция, вычисляющая мгновенную угловую скорость по заданным значениям самолётных углов и их производных.
	vector3 calc_omega_ (const plane_angles & angs, const plane_angles & angs_diff) const {
		vector3 result;
		result.x =  angs_diff.gamma                    +  angs_diff.psi * sin (angs.teta);
		result.y =  angs_diff.teta * sin (angs.gamma)  +  angs_diff.psi * cos (angs.teta) * cos (angs.gamma);
		result.z =  angs_diff.teta * cos (angs.gamma)  -  angs_diff.psi * cos (angs.teta) * sin (angs.gamma);
		return result;
	}


}; // class artifical_input_plane_angles



#endif // ifndef MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_PLANE_ANGLES_PLANE_ANGLES_H
