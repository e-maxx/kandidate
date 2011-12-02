/*! \file quaternion.cpp
    \brief Юнит-тесты для файла "types/quaternion.hpp".
*/
#include <boost/test/unit_test.hpp>
#include "../../types/quaternion.hpp"


static const double tolerance = 1E-7;


BOOST_AUTO_TEST_SUITE( quaternion_test )


BOOST_AUTO_TEST_CASE( default_constructor_test )
{
	quaternion q;

	BOOST_CHECK_CLOSE (q.w, 0, tolerance);
	BOOST_CHECK_CLOSE (q.x, 0, tolerance);
	BOOST_CHECK_CLOSE (q.y, 0, tolerance);
	BOOST_CHECK_CLOSE (q.z, 0, tolerance);
}


BOOST_AUTO_TEST_CASE( constructor_from_doubles_test )
{
	quaternion q (1, 2, 3, 4);

	BOOST_CHECK_CLOSE (q.w, 1, tolerance);
	BOOST_CHECK_CLOSE (q.x, 2, tolerance);
	BOOST_CHECK_CLOSE (q.y, 3, tolerance);
	BOOST_CHECK_CLOSE (q.z, 4, tolerance);

	double
		w = 1.0 / 3,
		x = sqrt (2.0),
		y = asin (1.0),
		z = tan (1.5);
	quaternion q2 (w, x, y, z);

	BOOST_CHECK_CLOSE (q2.w, w, tolerance);
	BOOST_CHECK_CLOSE (q2.x, x, tolerance);
	BOOST_CHECK_CLOSE (q2.y, y, tolerance);
	BOOST_CHECK_CLOSE (q2.z, z, tolerance);
}


BOOST_AUTO_TEST_CASE( copy_constructor_test )
{
	quaternion q (1, 2, 3, 4);
	quaternion qcopy (q);

	BOOST_CHECK_CLOSE (qcopy.w, 1, tolerance);
	BOOST_CHECK_CLOSE (qcopy.x, 2, tolerance);
	BOOST_CHECK_CLOSE (qcopy.y, 3, tolerance);
	BOOST_CHECK_CLOSE (qcopy.z, 4, tolerance);
}


BOOST_AUTO_TEST_CASE( constructor_from_1_double_test )
{
	quaternion q (10);

	BOOST_CHECK_CLOSE (q.w, 10, tolerance);
	BOOST_CHECK_CLOSE (q.x, 0, tolerance);
	BOOST_CHECK_CLOSE (q.y, 0, tolerance);
	BOOST_CHECK_CLOSE (q.z, 0, tolerance);
}


BOOST_AUTO_TEST_CASE( constructor_from_vector3_test )
{
	quaternion q (vector3 (1, 2, 3));

	BOOST_CHECK_CLOSE (q.w, 0, tolerance);
	BOOST_CHECK_CLOSE (q.x, 1, tolerance);
	BOOST_CHECK_CLOSE (q.y, 2, tolerance);
	BOOST_CHECK_CLOSE (q.z, 3, tolerance);
}


// после проверки конструкторов и operator==, дальше будем пользоваться в тестах operator==


BOOST_AUTO_TEST_CASE( operator_brackets_test )
{
	quaternion q (1, 2, 3, 4);
	BOOST_CHECK_CLOSE (q[0], 1, tolerance);
	BOOST_CHECK_CLOSE (q[1], 2, tolerance);
	BOOST_CHECK_CLOSE (q[2], 3, tolerance);
	BOOST_CHECK_CLOSE (q[3], 4, tolerance);

	q[0] = 5;
	BOOST_CHECK_CLOSE (q[0], 5, tolerance);
	BOOST_CHECK_CLOSE (q[1], 2, tolerance);
	BOOST_CHECK_CLOSE (q[2], 3, tolerance);
	BOOST_CHECK_CLOSE (q[3], 4, tolerance);

	q[1] = 6;
	BOOST_CHECK_CLOSE (q[0], 5, tolerance);
	BOOST_CHECK_CLOSE (q[1], 6, tolerance);
	BOOST_CHECK_CLOSE (q[2], 3, tolerance);
	BOOST_CHECK_CLOSE (q[3], 4, tolerance);

	q[2] = 7;
	BOOST_CHECK_CLOSE (q[0], 5, tolerance);
	BOOST_CHECK_CLOSE (q[1], 6, tolerance);
	BOOST_CHECK_CLOSE (q[2], 7, tolerance);
	BOOST_CHECK_CLOSE (q[3], 4, tolerance);

	q[3] = 8;
	BOOST_CHECK_CLOSE (q[0], 5, tolerance);
	BOOST_CHECK_CLOSE (q[1], 6, tolerance);
	BOOST_CHECK_CLOSE (q[2], 7, tolerance);
	BOOST_CHECK_CLOSE (q[3], 8, tolerance);

	BOOST_CHECK_THROW (q[-1], std::invalid_argument);
	BOOST_CHECK_THROW (q[4], std::invalid_argument);
}


BOOST_AUTO_TEST_CASE( operator_plus_test )
{
	quaternion q = quaternion (1, 2, 3, 4) + quaternion (10, 20, 30, 40);
	BOOST_CHECK_EQUAL (q, quaternion (11, 22, 33, 44));
}


BOOST_AUTO_TEST_CASE( operator_minus_test )
{
	quaternion q = quaternion (1, 2, 3, 4) - quaternion (10, 20, 30, 40);
	BOOST_CHECK_EQUAL (q, quaternion (-9, -18, -27, -36));
}


BOOST_AUTO_TEST_CASE( operator_mult_double_test )
{
	quaternion q = quaternion (1, 2, 3, 4) * 5;
	BOOST_CHECK_EQUAL (q, quaternion (5, 10, 15, 20));
}


BOOST_AUTO_TEST_CASE( operator_div_double_test )
{
	quaternion q = quaternion (10, 20, 30, 40) / 5;
	BOOST_CHECK_EQUAL (q, quaternion (2, 4, 6, 8));
}


BOOST_AUTO_TEST_CASE( operator_mult_quaternion_test )
{
	{
		quaternion q = quaternion (2) * quaternion (3);
		BOOST_CHECK_EQUAL (q, quaternion (6));
	}

	{
		quaternion q = quaternion (vector3 (2, 0, 0)) * quaternion (vector3 (3, 0, 0));
		BOOST_CHECK_EQUAL (q, quaternion (-6));
	}

	{
		quaternion q = quaternion (vector3 (3, 0, 0)) * quaternion (vector3 (2, 0, 0));
		BOOST_CHECK_EQUAL (q, quaternion (-6));
	}

	{
		quaternion q = quaternion (2) * quaternion (vector3 (3, 4, 5));
		BOOST_CHECK_EQUAL (q, quaternion (vector3 (6, 8, 10)));
	}

	{
		quaternion q = quaternion (vector3 (3, 4, 5)) * quaternion (2);
		BOOST_CHECK_EQUAL (q, quaternion (vector3 (6, 8, 10)));
	}

	{
		quaternion q = quaternion (vector3 (1, 2, 3)) * quaternion (vector3 (2, 4, 6));
		BOOST_CHECK_EQUAL (q, quaternion (-28));
	}

	{
		quaternion a = quaternion (1, 2, 3, 4) * quaternion (5, 6, 7, 8);
		quaternion b = quaternion (5, 6, 7, 8) * quaternion (1, 2, 3, 4);
		BOOST_CHECK (! (a == b));
	}

	{
		quaternion q = quaternion (vector3 (1, 0, 0)) * quaternion (vector3 (0, 1, 0));
		BOOST_CHECK_EQUAL (q, quaternion (vector3 (0, 0, 1)));
	}
}


BOOST_AUTO_TEST_CASE( operator_minus_unary_test )
{
	quaternion q = - quaternion (1, 2, 3, 4);
	BOOST_CHECK_EQUAL (q, quaternion (-1, -2, -3, -4));
}


BOOST_AUTO_TEST_CASE( conjugate_test )
{
	quaternion q = quaternion (1, 2, 3, 4) .conjugate();
	BOOST_CHECK_EQUAL (q, quaternion (1, -2, -3, -4));
}


BOOST_AUTO_TEST_CASE( inverse_test )
{
	quaternion q = quaternion (1, 2, 3, 4);
	quaternion t = q * q.inverse();
	BOOST_CHECK_CLOSE (t.norm(), 1, tolerance);
}


BOOST_AUTO_TEST_CASE( operator_equals_test )
{
	BOOST_CHECK_EQUAL (quaternion (1, 2, 3, 4), quaternion (1, 2, 3, 4));
	BOOST_CHECK (! (quaternion (1, 2, 3, 4) == quaternion (10, 2, 3, 4)));
	BOOST_CHECK (! (quaternion (1, 2, 3, 4) == quaternion (1, 20, 3, 4)));
	BOOST_CHECK (! (quaternion (1, 2, 3, 4) == quaternion (1, 2, 30, 4)));
	BOOST_CHECK (! (quaternion (1, 2, 3, 4) == quaternion (1, 2, 3, 40)));
}


BOOST_AUTO_TEST_CASE( norm_test )
{
	quaternion q = quaternion (1, 2, 3, 4);
	BOOST_CHECK_CLOSE (q.norm(), 30, tolerance);
}


BOOST_AUTO_TEST_CASE( length_test )
{
	quaternion q = quaternion (1, 2, 3, 4);
	BOOST_CHECK_CLOSE (q.length(), sqrt(30.0), tolerance);
}


BOOST_AUTO_TEST_CASE( get_unit_test )
{
	quaternion q = quaternion::get_unit();
	BOOST_CHECK_EQUAL (q, quaternion (1, 0, 0, 0));
	BOOST_CHECK_CLOSE (q.norm(), 1, tolerance);
}


BOOST_AUTO_TEST_CASE( distance_test )
{
	quaternion a (1, 2, 3, 4);
	quaternion b (2, 0, 6, 8);
	BOOST_CHECK_CLOSE (distance (a, b), sqrt(30.0), tolerance);
}


BOOST_AUTO_TEST_SUITE_END()
