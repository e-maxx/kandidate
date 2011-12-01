/*! \file simpson_integrator.h
    \brief Содержит класс интегратора с помощью метода Симпсона
*/

#pragma once
#ifndef INTEGRATOR_SIMPSON_INTEGRATOR_H
#define INTEGRATOR_SIMPSON_INTEGRATOR_H



#include <sstream>
#include <string>
#include "integrator.hpp"



/*! Класс для интегратора по методу Симпсона
 *
 * Имеет точность порядка O(1/N^4), где N - число точек разбиения (параметр алгоритма).
 */
template <class T>
class simpson_integrator : public integrator<T> {

public:

	//! Конструктор, принимает в качестве параметра число N точек разбиения
	/*! \param h шаг разбиения - параметр, определяющий точность алгоритма (меньше h - выше точность)
	*/
	simpson_integrator (double h)
		: h(h)
	{ }

	//! Возвращает название метода
	std::string get_name() {
		std::ostringstream oss;
		oss << "Метод Симпсона (шаг = " << h << ")";
		return oss.str();
	}

	//! Выполняет численное интегрирование и возвращает результат
	typename T integrate (boost::function < T(double) > f, double x0, double x1) {
		int N = int ((x1 - x0) / h);
		N = std::max (N, 10);
		if (N % 2)  ++N;

		double h = (x1 - x0) / N;
		T res = T();
		for (int i=0; i<=N; ++i) {
			double x = x0 + h * i;
			res += f(x) * ((i==0 || i==N) ? 1 : (i%2==0) ? 2 : 4);
		}
		return res * (x1 - x0) / N / 3.0;
	}

protected:

	//! параметр метода - h - шаг интегрирования
	double h;

}; // class simpson_integrator



#endif // ifndef INTEGRATOR_SIMPSON_INTEGRATOR_H
