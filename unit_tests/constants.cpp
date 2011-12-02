/*! \file constants.cpp
    \brief Юнит-тесты для файла "constants.hpp".
*/
#include <boost/test/unit_test.hpp>
#include <cmath>
#include "../constants.hpp"


BOOST_AUTO_TEST_SUITE( constants_test )


BOOST_AUTO_TEST_CASE( EPS_test )
{
    BOOST_CHECK( abs(0.0) < EPS );
    BOOST_CHECK( abs( sin (2 * acos (0.0)) ) < EPS );
    BOOST_CHECK( abs(1.0) > EPS );
    BOOST_CHECK( abs(0.001) > EPS );
    BOOST_CHECK( abs( sqrt(144.0) - 12.0 ) < EPS );
    BOOST_CHECK( abs( sqrt(144.1) - 12.0 ) > EPS );
}


BOOST_AUTO_TEST_SUITE_END()
