/** \file constants.hpp
    \brief Содержит общие константы.
*/

#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H


#include <boost/math/constants/constants.hpp>


//! Константа, с которой сравниваются дробные числа.
#define EPS 1E-9


//! Число "пи"
#define PI boost::math::constants::pi<long double>()


#endif // CONSTANTS_H
