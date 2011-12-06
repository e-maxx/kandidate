/*! \file speed_and_angle_speed.hpp
    \brief Содержит класс "speed_and_angle_speed", являющийся входными данными для бикватернионных алгоритмов (это пара из двух векторов: обычной скорости и угловой скорости).
*/

#pragma once
#ifndef TYPES_SPEED_AND_ANGLE_SPEED_H
#define TYPES_SPEED_AND_ANGLE_SPEED_H



#include "vector3.hpp"



/** Класс "speed_and_angle_speed", являющийся входными данными для бикватернионных алгоритмов.
 *
 * Это пара из двух векторов: обычной скорости speed и угловой скорости angle_speed.
 */
class speed_and_angle_speed {

public:


	vector3 speed, angle_speed;


	speed_and_angle_speed()
	{ }

	speed_and_angle_speed (vector3 speed, vector3 angle_speed)
		: speed(speed), angle_speed(angle_speed)
	{ }


}; // class speed_and_angle_speed



#endif // ifndef TYPES_SPEED_AND_ANGLE_SPEED_H
