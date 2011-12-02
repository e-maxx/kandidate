/** \file output_data.hpp
    \brief Содержит класс "output_data" - контейнер результатов вычислений для алгоритма (см. класс algorithm).
*/

#pragma once
#ifndef ALGORITHMS_STUFF_OUTPUT_DATA_H
#define ALGORITHMS_STUFF_OUTPUT_DATA_H



#include <vector>



/** Класс "output_data" - контейнер результатов вычислений для алгоритма (см. класс algorithm).
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 */
template <typename Q>
class output_data {

public:


	virtual ~output_data() {
	}


	/** Список времён, для которых алгоритм нашёл решения.
	 *
	 * Времена указаны в порядке возврастания.
	 */
	std::vector<double> ts;
	//! Список решений - по одному объекту класса Q для каждого момента времени.
	std::vector<Q> qs;


	/** Добавляет очередную запись-результаты алгоритма.
	 *
	 * Предполагается, что этот метод вызывается в порядке увеличения времён.
	 */
	void add (double t, const Q & q) {
		ts.push_back (t);
		qs.push_back (q);
	}

	//! Возвращает количество элементов.
	size_t get_count() const {
		return ts.size();
	}

	//! Метод для удобного доступа к списку времён.
	double get_time (int idx) const {
		return ts[idx];
	}

	//! Оператор для удобного доступа к списку решений.
	typename Q operator[] (int idx) const {
		return qs[idx];
	}

	//! Оператор для удобного доступа к списку решений.
	typename Q & operator[] (int idx) {
		return qs[idx];
	}


}; // class output_data



#endif // ifndef ALGORITHMS_STUFF_OUTPUT_DATA_H
