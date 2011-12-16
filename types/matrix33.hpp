/** \file matrix33.hpp
    \brief Содержит класс "матрица 3x3".
*/

#pragma once
#ifndef TYPES_MATRIX33_H
#define TYPES_MATRIX33_H



#include <cmath>
#include <stdexcept>
#include "vector3.hpp"



//! Класс "матрица 3x3".
class matrix33 {


public:

	
	//! Конструктор нулевой матрицы.
	matrix33() {
		memset (data_, 0, sizeof data_);
	}

	matrix33 (long double data[3][3]) {
		for (int i=0; i<3; ++i)
			for (int j=0; j<3; ++j)
				data_[i][j] = data[i][j];
	}

	matrix33 (long double a11, long double a12, long double a13, long double a21, long double a22, long double a23, long double a31, long double a32, long double a33) {
		data_[0][0] = a11;
		data_[0][1] = a12;
		data_[0][2] = a13;
		data_[1][0] = a21;
		data_[1][1] = a22;
		data_[1][2] = a23;
		data_[2][0] = a31;
		data_[2][1] = a32;
		data_[2][2] = a33;
	}


	/** Индексированный доступ к элементам матрицы.
	 *
	 * @throws std::invalid_argument В случае, если передано некорректное значение row или column.
	 */
	long double operator() (int row, int column) const {
		if (row < 0 || row >= 3)
			throw std::invalid_argument ("Invalid row value.");
		if (column < 0 || column >= 3)
			throw std::invalid_argument ("Invalid column value.");
		return data_[row][column];
	}

	/** Индексированный доступ к элементам матрицы.
	 *
	 * @throws std::invalid_argument В случае, если передано некорректное значение row или column.
	 */
	long double & operator() (int row, int column) {
		if (row < 0 || row >= 3)
			throw std::invalid_argument ("Invalid row value.");
		if (column < 0 || column >= 3)
			throw std::invalid_argument ("Invalid column value.");
		return data_[row][column];
	}

	
	matrix33 operator+ (const matrix33 & m) const {
		matrix33 result = *this;
		return result += m;
	}

	matrix33 operator- (const matrix33 & m) const {
		matrix33 result = *this;
		return result -= m;
	}

	//! Умножение на константу.
	matrix33 operator* (long double num) const {
		matrix33 result = *this;
		return result *= num;
	}

	//! Матричное произведение.
	matrix33 operator* (const matrix33 & m) const {
		matrix33 result;
		for (int i=0; i<3; ++i)
			for (int j=0; j<3; ++j)
				result.data_[i][j] =
					data_[i][0] * m.data_[0][j] +
					data_[i][1] * m.data_[1][j] +
					data_[i][2] * m.data_[2][j];
		return result;
	}
	
	//! Умножение на вектор.
	vector3 operator* (const vector3 & v) const {
		return vector3 (
			data_[0][0] * v.x + data_[0][1] * v.y + data_[0][2] * v.z,
			data_[1][0] * v.x + data_[1][1] * v.y + data_[1][2] * v.z,
			data_[2][0] * v.x + data_[2][1] * v.y + data_[2][2] * v.z
		);
	}

	//! Деление на константу.
	matrix33 operator/ (long double num) const {
		matrix33 result = *this;
		return result /= num;
	}

	//! Унарный минус.
	matrix33 operator- () const {
		return matrix33() - *this;
	}


	matrix33 & operator+= (const matrix33 & m) {
		for (int i=0; i<3; ++i)
			for (int j=0; j<3; ++j)
				data_[i][j] += m.data_[i][j];
		return *this;
	}

	matrix33 & operator-= (const matrix33 & m) {
		for (int i=0; i<3; ++i)
			for (int j=0; j<3; ++j)
				data_[i][j] -= m.data_[i][j];
		return *this;
	}

	//! Умножение на константу.
	matrix33 & operator*= (long double num) {
		for (int i=0; i<3; ++i)
			for (int j=0; j<3; ++j)
				data_[i][j] *= num;
		return *this;
	}

	//! Матричное произведение.
	matrix33 & operator*= (const matrix33 & m) {
		*this = *this * m;
		return *this;
	}
	
	//! Деление на константу.
	matrix33 & operator/= (long double num) {
		for (int i=0; i<3; ++i)
			for (int j=0; j<3; ++j)
				data_[i][j] /= num;
		return *this;
	}
	

protected:


	//! Компоненты матрицы.
	long double data_[3][3];


}; // class matrix33



//! Умножение на константу
inline matrix33 operator* (long double num, const matrix33 & m) {
	return m * num;
}



#endif // ifndef TYPES_MATRIX33_H
