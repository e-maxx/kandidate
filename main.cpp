#include <iostream>
#include "integrator/integrator.hpp"
#include "math_modelling/math_modelling.hpp"
#include "math_modelling/artifical_input/plane_angles/artifical_input_plane_angles_harmonious.hpp"
#include "algorithms/old_algorithms/average_speed_algorithm.hpp"
#include "algorithms/old_algorithms/average_speed_riccati_algorithm.hpp"
#include "algorithms/auto_generated/2_step.hpp"
#include "algorithms/old_algorithms/panov_algorithm.hpp"
#include "algorithms/old_algorithms/panov_riccati_algorithm.hpp"
#include "algorithms/old_algorithms/method_2step_4degree.hpp"
#include "types/plane_angles.hpp"
#include "types/biquaternion.hpp"



void test_algorithm (boost::shared_ptr < algorithm<quaternion,vector3> > alg, long double h) {
	alg->set_step (h);
	alg->set_last_time (3600);


	boost::shared_ptr < artifical_input<quaternion,vector3> > input (
		new artifical_input_plane_angles_harmonious (
			plane_angles (20 * PI/180, 15 * PI/180, 20 * PI/180),
			plane_angles (PI/2, PI, PI)
		)
	);
	

	math_modelling<quaternion,vector3> m;
	m.set_data (input);
	BOOST_AUTO( result, m.run_algorithm (alg) );

	BOOST_AUTO( res, *result );
	std::cerr << std::fixed << res.max_difference << ' ';
	std::cout << std::fixed << res.max_difference << '\t';
}

template <class alg>
void test_algorithm (long double h) {
	boost::shared_ptr < algorithm<quaternion,vector3> > alg (
		new alg ()
	);
	test_algorithm (alg, h);
}


int main() {
	freopen ("output.txt", "wt", stdout);

	std::cerr.precision (20);
	std::cout.precision (20);

    for (long double h=0.8; ; h/=2) {
		default_integrator (boost::shared_ptr< integrator<vector3> > (new simpson_integrator<vector3> (h / 10)));
		std::cout << std::fixed << h << '\t';

		test_algorithm < average_speed_algorithm<quaternion,vector3> > (h);
		test_algorithm < average_speed_riccati_algorithm<quaternion,vector3> > (h);
		test_algorithm < panov_algorithm > (h);
		test_algorithm < panov_riccati_algorithm > (h);
		test_algorithm < method_2step_4degree > (h);

		std::cerr << std::endl;
		std::cout << std::endl;
	}

}
