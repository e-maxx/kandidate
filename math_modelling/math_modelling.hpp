/** \file math_modelling.hpp
    \brief Содержит класс "math_modelling" - класс для тестирования алгоритмов по методике математического моделирования.
*/

#pragma once
#ifndef MATH_MODELLING_MATH_MODELLING_H
#define MATH_MODELLING_MATH_MODELLING_H



#include <boost/range/algorithm.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <string>
#include "../algorithms/algorithm.hpp"
#include "artifical_input/artifical_input.hpp"



/** Класс "math_modelling" - класс для тестирования алгоритмов по методике математического моделирования.
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
	

	//! Сокращение для типа алгоритма.
	typedef algorithm<Q,I> t_algorithm;
	//! Сокращение для типа источника данных.
	typedef artifical_input<Q,I> t_artifical_input;
	//! Сокращение для типа выходных данных.
	typedef output_data<Q> t_output_data;
	//! Сокращение для указателя на алгоритм.
	typedef boost::shared_ptr < t_algorithm > t_algorithm_ptr;
	//! Сокращение для указателя на источник данных.
	typedef boost::shared_ptr < t_artifical_input > t_artifical_input_ptr;
	//! Сокращение для указателя на выходные данные.
	typedef boost::shared_ptr < t_output_data > t_output_data_ptr;


	/** Устанавливает новый источник входных данных и точных решений.
	 *
	 * Данный метод должен быть вызван хотя бы один раз до первого вызова
	 * метода run_algorithm().
	 */
	void set_data (t_artifical_input_ptr data) {
		data_ = data;
	}


	//! Контейнер для результатов тестирования алгоритма.
	class result {
	
	public:
	
		//! Название алгоритма.
		std::string algorithm_title;
		//! Решение, найденное алгоритмом.
		t_output_data_ptr algorithm_output;
		//! Точное решение.
		t_output_data_ptr exact_solution;
		//! Массив погрешностей - погрешность подсчитана для каждого момента времени.
		std::vector<long double> differences;
		//! Наибольшая погрешность.
		long double max_difference;


	private:

		//! Финализирует объект, довычисляя все характеристики, которые нельзя вычислить "на ходу".
		void finalize_() {
			size_t count = algorithm_output->get_count();
			
			differences.resize (count);
			for (size_t i=0; i<count; ++i)
				differences[i] = distance ((*algorithm_output)[i], (*exact_solution)[i]);
			max_difference = * boost::max_element (differences);
		}

		friend class math_modelling;
	};


	//! Сокращение для типа указателя на результат тестирования алгоритма.
	typedef boost::shared_ptr < result > t_result_ptr;

	
	/** Тестирует указанный алгоритм и возвращает результат тестирования.
	 *
	 * Передаваемый алгоритм должен быть полностью корректно инициализирован,
	 * за исключением входных данных input_data - они будут проставлены в
	 * данном методе.
	 *
	 * @throws std::logic_error Кидает исключение, если входные данные не были указаны.
	 */
	t_result_ptr run_algorithm (t_algorithm_ptr alg) {
		if (! data_)
			throw std::logic_error ("Перед запуском тестирования должны были быть указаны входные данные.");

		alg->set_input_data (data_->get_input_data());

		t_result_ptr ret (new result());

		ret->algorithm_title = alg->get_algorithm_title();
		ret->algorithm_output = alg->execute();
		ret->exact_solution = data_->get_exact_solution (alg->get_step(), alg->get_last_time());

		ret->finalize_();
		return ret;
	}


protected:

	//! Источник входных данных и точных решений.
	t_artifical_input_ptr data_;


}; // class math_modelling



#endif // ifndef MATH_MODELLING_MATH_MODELLING_H
