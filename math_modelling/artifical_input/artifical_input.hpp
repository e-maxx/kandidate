/** \file artifical_input.hpp
    \brief Содержит класс "artifical_input" - абстрактный источник мат-моделируемых входных данных для алгоритма (см. класс algorithm).
*/

#pragma once
#ifndef MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_H
#define MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_H



#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include "../../algorithms/stuff/input_data.hpp"
#include "../../algorithms/stuff/output_data.hpp"
#include "../../constants.hpp"



/** Класс "artifical_input" - абстрактный источник мат-моделируемых входных данных для алгоритма (см. класс algorithm).
 *
 * Данный класс применяется при мат. моделировании в качестве источника как
 * входных данных для алгоритма, так и точных решений.
 *
 * Предполагается, что потомки, т.е. конкретные реализации, будут иметь набор
 * неких формул, по которым вычисляются входные данные (мгновенные или
 * интегральные), а также по которым ищется точное решение. Всё это потомки
 * должны будут определить, просто реализовав виртуальные методы
 * internal_get_instanteous_(), internal_get_integrated_(),
 * internal_get_exact_solution_().
 *
 * Всю остальную работу по "заворачиванию" этих данных в input_data/output_data
 * сделает данный класс.
 *
 * Как и в классе input_data, потомки не обязаны реализовывать оба вида входных
 * данных (мгновенные и интегральные), и если во время работы программы
 * потребуются данные, вычисление которых потомок не определил, то обработчик
 * по умолчанию бросит исключение.
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 * @tparam I Выбранный тип входных данных.
 */
template <typename Q, typename I>
class artifical_input {

public:


	//! Сокращение для типа входных данных.
	typedef input_data<Q,I> t_input_data;
	//! Сокращение для типа выходных данных.
	typedef output_data<Q> t_output_data;
	//! Сокращение для указателя на входные данные.
	typedef boost::shared_ptr < t_input_data > t_input_data_ptr;
	//! Сокращение для указателя на выходные данные.
	typedef boost::shared_ptr < t_output_data > t_output_data_ptr;


	virtual ~artifical_input() {
	}


	//! Возвращает тонкую прослойку, создающую input_data-интерфейс к нашему классу.
	t_input_data_ptr get_input_data() {
		return t_input_data_ptr (new input_data_layer_ (this));
	}

	//! Вычисляет и возвращает точное решение во все требуемые моменты времени.
	t_output_data_ptr get_exact_solution (double step, double last_time) {
		t_output_data_ptr result (new t_output_data);
		for (double t=0; t<=last_time+EPS; t+=step)
			result->add (t, this->internal_get_exact_solution_ (t));
		return result;
	}


protected:


	/** Возвращает мгновенные входные данные в данный момент времени.
	 *
	 * По умолчанию кидает исключение, т.е. классы-потомки должны
	 * переопределять этот метод, если планируется использовать
	 * мгновенные входные данные.
	 *
	 * @throws std::runtime_exception Всегда кидает это исключение, если вызов дошёл до данной реализации.
	 */
	virtual typename I internal_get_instanteous_ (double t) {
		throw std::runtime_error ("Not implemented: instanteous input data was not calculated.");
	}

	/** Возвращает интегральные входные данные за указанный промежуток времени.
	 *
	 * По умолчанию кидает исключение, т.е. классы-потомки должны
	 * переопределять этот метод, если планируется использовать
	 * мгновенные входные данные.
	 *
	 * @throws std::runtime_exception Всегда кидает это исключение, если вызов дошёл до данной реализации.
	 */
	virtual typename I internal_get_integrated_ (double t1, double t2) {
		throw std::runtime_error ("Not implemented: integrated input data was not calculated.");
	}

	//! Возвращает точное решение в указанный момент времени.
	virtual typename Q internal_get_exact_solution_ (double t) = 0;


private:
	
	//! Тонкая прослойка от нашего класса к классу input_data.
	class input_data_layer_ : public input_data<Q,I> {
	public:

		input_data_layer_ (artifical_input * that)
			: that(that)
		{ }

		virtual typename Q get_initial_solution() {
			return that->internal_get_exact_solution_ (0);
		}

		virtual typename I get_instanteous (double t) {
			return that->internal_get_instanteous_ (t);
		}

		virtual typename I get_integrated (double t1, double t2) {
			return that->internal_get_integrated_ (t1, t2);
		}

	private:
		artifical_input * that;
	};


}; // class artifical_input



#endif // ifndef MATH_MODELLING_ARTIFICAL_INPUT_ARTIFICAL_INPUT_H
