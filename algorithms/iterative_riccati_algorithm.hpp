/** \file iterative_riccati_algorithm.hpp
    \brief Содержит абстрактный шаблонный класс "итеративный алгоритм типа
	Риккати" - разновидность итеративного алгоритма, который работает по типу
	Риккати, т.е. когда алгоритм ищет не (би)кватернион, соответствующий
	решению на текущем шаге, а некоторую переменную x, через которую этот
	(би)кватернион выражается.
*/

#pragma once
#ifndef ALGORITHMS_ITERATIVE_RICCATI_ALGORITHM_H
#define ALGORITHMS_ITERATIVE_RICCATI_ALGORITHM_H



#include <boost/typeof/typeof.hpp>
#include <vector>
#include "iterative_algorithm.hpp"



/** Класс "итеративный алгоритм типа Риккати".
 *
 * Этот класс является абстрактным шаблонным классом, описывающим интерфейс
 * любого итеративного алгоритма, работающего по уравнениям типа Риккати.
 *
 * Такой алгоритм ищет не (би)кватернион, соответствующий решению на текущем
 * шаге, а некоторую переменную x, через которую этот (би)кватернион
 * выражается.
 *
 * Классы-потомки должны будут реализовать метод get_local_riccati_solution_(),
 * а также могут переопределять метод get_algorithm_steps_count_().
 *
 * Метод get_local_solution_() уже реализован в данном классе: он представляет
 * собой вызов get_local_riccati_solution_() и последующее вычисление по
 * полученному результату искомого (би)кватерниона - решения на текущем шаге.
 *
 * @tparam Q Выбранная алгебра (кватернионы/бикватернионы).
 * @tparam I Выбранный тип входных данных (классы-потомки, как правило, будут жёстко фиксировать этот тип в соответствии с их потребностями).
 */
template <typename Q, typename I>
class iterative_riccati_algorithm : public iterative_algorithm<Q,I> {

public:


	virtual ~iterative_riccati_algorithm() {
	}


protected:

	
	/** Вычисляет решение x по типу Риккати на текущем временном отрезке.
	 *
	 * @param t Время, в которое требуется найти решение.
	 * @param gamma Входные данные на временном отрезке (это вектор, поскольку для многошаговых алгоритмов (см. get_algorithm_steps_count_()) передаётся соответствующее число входных данных: на нескольких подотрезках, в порядке их следования во времени).
	 */
	virtual Q get_local_riccati_solution_ (double t, const std::vector<I> & gamma) = 0;


private:


	/** Вычисляет решение на текущем временном отрезке.
	 *
	 * @param t Время, в которое требуется найти решение.
	 * @param gamma Входные данные на временном отрезке (это вектор, поскольку для многошаговых алгоритмов (см. get_algorithm_steps_count_()) передаётся соответствующее число входных данных: на нескольких подотрезках, в порядке их следования во времени).
	 */
	virtual Q get_local_solution_ (double t, const std::vector<I> & gamma) {
		Q x = this->get_local_riccati_solution_ (t, gamma);
		
		BOOST_AUTO( norm, x.norm() );
		return (Q(1) - Q(norm) + 2*x) / (1 + norm);
	}


}; // class iterative_riccati_algorithm



#endif // ifndef ALGORITHMS_ITERATIVE_RICCATI_ALGORITHM_H
