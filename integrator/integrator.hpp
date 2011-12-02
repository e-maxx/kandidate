/** \file integrator.hpp
    \brief Содержит класс абстрактного интегратора - производящего численное интегрирование заданной функции.
*/

#pragma once
#ifndef INTEGRATOR_INTEGRATOR_H
#define INTEGRATOR_INTEGRATOR_H



#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <string>



/** Абстрактный класс интегратора.
 *
 * Предоставляет общую схему для алгоритмов вычисления определённых интегралов.
 *
 * @tparam T Тип значения, возвращаемого функцией.
 */
template <typename T>
class integrator {

public:

	//! Возвращает название метода.
	virtual std::string get_name() = 0;

	/** Выполняет численное интегрирование и возвращает результат.
	 *
	 * @param f Функция вида f(x), интеграл от которой требуется посчитать.
	 * @param x0 Левая граница интегрирования (откуда начинаем интегрировать).
	 * @param x1 Правая граница интегрирования (до которой интегрируем).
	 */
	virtual typename T integrate (boost::function < T(double) > f, double x0, double x1) = 0;

};



#include "simpson_integrator.hpp"


//! Погрешность метода Симпсона по умолчанию.
static double default_integrator_step = 1E-4;


//! Возвращает текущий выбранный алгоритм интегрирования (если никакой не выбран, то возвращает метод Симпсона).
template <typename T>
boost::shared_ptr< integrator<T> > default_integrator (boost::shared_ptr< integrator<T> > new_integrator = boost::shared_ptr< integrator<T> >()) {
	static boost::shared_ptr< integrator<T> > selected_integrator;
	if (new_integrator)
		selected_integrator = new_integrator;

	if (! selected_integrator)
		selected_integrator = boost::shared_ptr< integrator<T> > (new simpson_integrator<T> (default_integrator_step));

	return selected_integrator;
}



#endif // ifndef INTEGRATOR_INTEGRATOR_H
