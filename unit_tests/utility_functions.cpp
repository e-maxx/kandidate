/** \file utility_functions.cpp
    \brief Юнит-тесты для файла "utility_functions.hpp".
*/
#include <boost/test/unit_test.hpp>
#include "../utility_functions.hpp"


BOOST_AUTO_TEST_SUITE( utility_functions_test )


BOOST_AUTO_TEST_CASE( sqr_test )
{
	const double tolerance = 1E-7;

    BOOST_CHECK_CLOSE( sqr(0), 0, tolerance );
    BOOST_CHECK_CLOSE( sqr(2), 4, tolerance );
    BOOST_CHECK_CLOSE( sqr(-2), 4, tolerance );
    BOOST_CHECK_CLOSE( sqr(9), 81, tolerance );
    BOOST_CHECK_CLOSE( sqr(-9), 81, tolerance );
}


BOOST_AUTO_TEST_SUITE_END()