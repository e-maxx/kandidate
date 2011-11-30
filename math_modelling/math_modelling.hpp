/*! \file math_modelling.hpp
    \brief Содержит класс "math_modelling" - класс для тестирования алгоритмов по методике математического моделирования.
*/

#pragma once
#ifndef MATH_MODELLING_MATH_MODELLING_H
#define MATH_MODELLING_MATH_MODELLING_H



#include <boost/range/algorithm.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <memory>
#include <string>
#include "../algorithms/algorithm.hpp"
#include "stuff/artifical_input.hpp"



/*! Класс "math_modelling" - класс для тестирования алгоритмов по методике математического моделирования.
 *
 * Основная задача данного класса - связать алгоритм (см. класс algorithm) и
 * искусственные входные данные для него (см. класс artifical_input).
 *
 * Данный класс имеет свойство data типа artifical_input - это некий класс,
 * который предоставляет методы как для получения входных данных, так и точных
 * решений. Иными словами, само точное решение и генерируемые по нему входные
 * данные спрятаны в этом классе artifical_input, а вся работа по запуску на нём
 * алгоритма производится здесь.
 *
 * Для тестирования имеется метод run_algorithm(), который тестирует указанный
 * алгоритм и сравнивает его решения с точными решениями, возвращая всё в виде
 * контейнера типа result. Передаваемый алгоритм должен быть полностью
 * корректно инициализирован, за исключением входных данных input_data - они
 * будут выставлены здесь.
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 * @tparam I Выбранный тип входных данных.
 */
template <typename Q, typename I>
class math_modelling {

public:


	/*! Устанавливает новый источник входных данных и точных решений.
	 *
	 * Данный метод должен быть вызван хотя бы один раз до первого вызова
	 * метода run_algorithm().
	 */
	void set_data (boost::shared_ptr < artifical_input<Q,I> > data) {
		data_ = data;
	}


	//! Контейнер для результатов тестирования алгоритма.
	class result {
	
	public:
	
		//! Название алгоритма.
		std::string algorithm_title;
		//! Решение, найденное алгоритмом.
		boost::shared_ptr < output_data<Q> > algorithm_output;
		//! Точное решение.
		boost::shared_ptr < output_data<Q> > exact_solution;
		//! Массив погрешностей - погрешность подсчитана для каждого момента времени.
		std::vector<double> differences;
		//! Наибольшая погрешность.
		double max_difference;


	private:

		//! Финализирует объект, довычисляя все характеристики, которые нельзя вычислить "на ходу".
		void finalize_() {
			size_t count = algorithm_output->get_count();
			
			differences.resize (count);
			for (size_t i=0; i<count; ++i)
				differences[i] = distance (algorithm_solution->get(i), exact_solution->get(i));
			max_difference = * boost::max_element (differences);
		}

		friend class math_modelling;
	};

	
	/*! Тестирует указанный алгоритм и возвращает результат тестирования.
	 *
	 * Передаваемый алгоритм должен быть полностью корректно инициализирован,
	 * за исключением входных данных input_data - они будут проставлены в
	 * данном методе.
	 */
	std::auto_ptr<result> run_algorithm (boost::shared_ptr < algorithm<Q,I> > alg) {
		alg->set_input_data (data_->get_input_data());

		std::auto_ptr<result> ret (new result());

		ret->algorithm_title = alg->get_title();
		ret->algorithm_output = alg->execute();
		ret->exact_solution = data_->get_exact_solution (alg->get_step());

		ret->finalize_();
		return ret;
	}


protected:

	//! Источник входных данных и точных решений.
	boost::shared_ptr < artifical_input<Q,I> > data_;


}; // class math_modelling



#endif // ifndef MATH_MODELLING_MATH_MODELLING_H
