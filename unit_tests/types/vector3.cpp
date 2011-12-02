/** \file vector3.cpp
    \brief Юнит-тесты для файла "types/vector3.hpp".
*/
#include <boost/test/unit_test.hpp>
#include "../../types/vector3.hpp"


static const double tolerance = 1E-7;


BOOST_AUTO_TEST_SUITE( vector3_test )


BOOST_AUTO_TEST_CASE( default_constructor_test )
{
	vector3 v;

	BOOST_CHECK_CLOSE (v.x, 0, tolerance);
	BOOST_CHECK_CLOSE (v.y, 0, tolerance);
	BOOST_CHECK_CLOSE (v.z, 0, tolerance);
}


BOOST_AUTO_TEST_CASE( constructor_from_doubles_test )
{
	vector3 v (1, 2, 3);

	BOOST_CHECK_CLOSE (v.x, 1, tolerance);
	BOOST_CHECK_CLOSE (v.y, 2, tolerance);
	BOOST_CHECK_CLOSE (v.z, 3, tolerance);

	double
		x = sqrt (2.0),
		y = asin (1.0),
		z = tan (1.5);
	vector3 v2 (x, y, z);

	BOOST_CHECK_CLOSE (v2.x, x, tolerance);
	BOOST_CHECK_CLOSE (v2.y, y, tolerance);
	BOOST_CHECK_CLOSE (v2.z, z, tolerance);
}


BOOST_AUTO_TEST_CASE( copy_constructor_test )
{
	vector3 v (1, 2, 3);
	vector3 vcopy (v);

	BOOST_CHECK_CLOSE (vcopy.x, 1, tolerance);
	BOOST_CHECK_CLOSE (vcopy.y, 2, tolerance);
	BOOST_CHECK_CLOSE (vcopy.z, 3, tolerance);
}


BOOST_AUTO_TEST_CASE( operator_brackets_test )
{
	vector3 v (1, 2, 3);
	BOOST_CHECK_CLOSE (v[0], 1, tolerance);
	BOOST_CHECK_CLOSE (v[1], 2, tolerance);
	BOOST_CHECK_CLOSE (v[2], 3, tolerance);

	v[0] = 4;
	BOOST_CHECK_CLOSE (v[0], 4, tolerance);
	BOOST_CHECK_CLOSE (v[1], 2, tolerance);
	BOOST_CHECK_CLOSE (v[2], 3, tolerance);

	v[1] = 5;
	BOOST_CHECK_CLOSE (v[0], 4, tolerance);
	BOOST_CHECK_CLOSE (v[1], 5, tolerance);
	BOOST_CHECK_CLOSE (v[2], 3, tolerance);

	v[2] = 6;
	BOOST_CHECK_CLOSE (v[0], 4, tolerance);
	BOOST_CHECK_CLOSE (v[1], 5, tolerance);
	BOOST_CHECK_CLOSE (v[2], 6, tolerance);

	BOOST_CHECK_THROW (v[-1], std::invalid_argument);
	BOOST_CHECK_THROW (v[3], std::invalid_argument);
}


BOOST_AUTO_TEST_CASE( operator_plus_test )
{
	vector3 a (1, 2, 3);
	vector3 b (10, 20, 30);
	vector3 c = a + b;

	BOOST_CHECK_CLOSE (c[0], 11, tolerance);
	BOOST_CHECK_CLOSE (c[1], 22, tolerance);
	BOOST_CHECK_CLOSE (c[2], 33, tolerance);
}


BOOST_AUTO_TEST_CASE( operator_minus_test )
{
	vector3 a (10, 20, 30);
	vector3 b (1, 2, 3);
	vector3 c = a - b;

	BOOST_CHECK_CLOSE (c[0], 9, tolerance);
	BOOST_CHECK_CLOSE (c[1], 18, tolerance);
	BOOST_CHECK_CLOSE (c[2], 27, tolerance);
}


BOOST_AUTO_TEST_CASE( operator_mult_double_test )
{
	vector3 v = vector3 (1, 2, 3) * 5;

	BOOST_CHECK_CLOSE (v[0], 5, tolerance);
	BOOST_CHECK_CLOSE (v[1], 10, tolerance);
	BOOST_CHECK_CLOSE (v[2], 15, tolerance);
}


BOOST_AUTO_TEST_CASE( operator_div_double_test )
{
	vector3 v = vector3 (10, 20, 30) / 5;

	BOOST_CHECK_CLOSE (v[0], 2, tolerance);
	BOOST_CHECK_CLOSE (v[1], 4, tolerance);
	BOOST_CHECK_CLOSE (v[2], 6, tolerance);
}


BOOST_AUTO_TEST_CASE( operator_minus_unary_test )
{
	vector3 v = - vector3 (1, 2, 3);

	BOOST_CHECK_CLOSE (v[0], -1, tolerance);
	BOOST_CHECK_CLOSE (v[1], -2, tolerance);
	BOOST_CHECK_CLOSE (v[2], -3, tolerance);
}


BOOST_AUTO_TEST_CASE( operator_plus_eq_test )
{
	vector3 v = vector3 (1, 2, 3);
	v += vector3 (10, 20, 30);

	BOOST_CHECK_CLOSE (v[0], 11, tolerance);
	BOOST_CHECK_CLOSE (v[1], 22, tolerance);
	BOOST_CHECK_CLOSE (v[2], 33, tolerance);
}


BOOST_AUTO_TEST_CASE( operator_minus_eq_test )
{
	vector3 v = vector3 (1, 2, 3);
	v -= vector3 (10, 20, 30);

	BOOST_CHECK_CLOSE (v[0], -9, tolerance);
	BOOST_CHECK_CLOSE (v[1], -18, tolerance);
	BOOST_CHECK_CLOSE (v[2], -27, tolerance);
}


BOOST_AUTO_TEST_CASE( norm_test )
{
	vector3 v = vector3 (1, 2, 3);

	BOOST_CHECK_CLOSE (v.norm(), 14, tolerance);
}


BOOST_AUTO_TEST_CASE( length_test )
{
	vector3 v = vector3 (1, 2, 3);

	BOOST_CHECK_CLOSE (v.length(), sqrt(14.0), tolerance);
}


BOOST_AUTO_TEST_CASE( distance_test )
{
	vector3 a = vector3 (1, 2, 3);
	vector3 b = vector3 (0, 1, 4);

	BOOST_CHECK_CLOSE (distance (a, b), sqrt(3.0), tolerance);
}


BOOST_AUTO_TEST_SUITE_END()
