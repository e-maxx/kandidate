/** \file utility_functions.hpp
    \brief Содержит мелкие вспомогательные функции.
*/

#pragma once
#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H


//! Вычисляет квадрат числа.
template <class T>
inline T sqr (const T & x) {
	return x * x;
}


#endif // ifndef UTILITY_FUNCTIONS_H
