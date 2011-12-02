/** \file algorithm.hpp
    \brief Содержит абстрактный шаблонный класс "алгоритм".
*/

#pragma once
#ifndef ALGORITHMS_ALGORITHM_H
#define ALGORITHMS_ALGORITHM_H



#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <string>
#include "../constants.hpp"
#include "stuff/input_data.hpp"
#include "stuff/output_data.hpp"



/** Класс "алгоритм".
 *
 * Этот класс является абстрактным шаблонным классом, описывающим интерфейс
 * любого используемого алгоритма.
 *
 * Любой алгоритм должен работать с входными данными заданного вида (см. класс
 * input_data) и возвращать результаты в заданном виде (см. класс
 * output_data).
 *
 * Кроме того, у алгоритма обязательно должны быть выставлены временной шаг
 * step, а также время last_time, до которого должен работать алгоритм (т.е.
 * алгоритм найдёт решения для следующих моментов времени:
 * 0; step; 2*step; ... ; last_time).
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 * @tparam I Выбранный тип входных данных (классы-потомки, как правило, будут жёстко фиксировать этот тип в соответствии с их потребностями).
 */
template <typename Q, typename I>
class algorithm {

public:


	//! Сокращение для типа входных данных.
	typedef input_data<Q,I> t_input_data;
	//! Сокращение для типа выходных данных.
	typedef output_data<Q> t_output_data;
	//! Сокращение для указателя на входные данные.
	typedef boost::shared_ptr < t_input_data > t_input_data_ptr;
	//! Сокращение для указателя на выходные данные.
	typedef boost::shared_ptr < t_output_data > t_output_data_ptr;


	virtual ~algorithm() {
	}


	/** Присваивает новый источник входных данных.
	 *
	 * Этот метод должен быть вызван хотя бы один раз до запуска алгоритма.
	 */
	void set_input_data (t_input_data_ptr data) {
		input_data_ = data;
	}


	/** Присваивает временной шаг алгоритма (т.е. шаг, с которым алгоритм будет выдавать решение).
	 *
	 * Этот метод должен быть вызван хотя бы один раз до запуска алгоритма.
	 */
	void set_step (double step) {
		step_ = step;
	}

	//! Возвращает временной шаг алгоритма (т.е. шаг, с которым алгоритм будет выдавать решение).
	double get_step() const {
		return step_;
	}


	/** Присваивает время, до которого должен работать алгоритм.
	 *
	 * Этот метод должен быть вызван хотя бы один раз до запуска алгоритма.
	 */
	void set_last_time (double last_time) {
		last_time_ = last_time;
	}

	//! Возвращает время, до которого должен работать алгоритм.
	double get_last_time() const {
		return last_time_;
	}


	//! Запускает алгоритм, возвращая полученные результаты работы.
	virtual t_output_data_ptr execute() = 0;


	//! Возвращает название алгоритма в виде строки.
	virtual std::string get_algorithm_title() = 0;


protected:

	//! Источник входных данных для алгоритма.
	t_input_data_ptr input_data_;

	//! Временной шаг алгоритма (т.е. шаг, с которым алгоритм будет выдавать решение).
	double step_;

	//! Время, до которого должен работать алгоритм.
	double last_time_;

	/** Возвращает созданную и подготовленную структуру output_data.
	 *
	 * А именно, в ней заполняется список времён ts, в которые надо посчитать
	 * решение.
	 *
	 * Также списку qs сразу выделяется нужный размер, а в нулевой элемент
	 * записывается начальное решение.
	 *
	 * @throws std::logic_exception Кидает исключение, если заранее не были выставлены параметры step или last_time.
	 */
	t_output_data_ptr init_output_data_() {
		if (step_ <= 0)
			throw new std::logic_error ("Перед запуском алгоритма должно быть указано корректное значение параметра step.");
		if (last_time_ <= 0)
			throw new std::logic_error ("Перед запуском алгоритма должно быть указано корректное значение параметра last_time.");

		t_output_data_ptr result (new t_output_data);

		for (double t=0; t<=last_time_+EPS; t+=step_)
			result->ts.push_back (t);
		result->qs.resize (result->ts.size());

		result->qs[0] = input_data_->get_initial_solution();

		return result;
	}


}; // class algorithm



#endif // ifndef ALGORITHMS_ALGORITHM_H
