#include <iostream>
#include "integrator/integrator.hpp"
#include "math_modelling/math_modelling.hpp"
#include "math_modelling/artifical_input/plane_angles/artifical_input_plane_angles_harmonious.hpp"
#include "algorithms/old_algorithms/average_speed_algorithm.hpp"
#include "algorithms/auto_generated/2_step.hpp"
//#include "algorithms/biquaternion/average_speed_biquaternion_algorithm.hpp"
#include "types/plane_angles.hpp"
#include "types/biquaternion.hpp"


void test_average_speed_algorithm (double h) {
	boost::shared_ptr < algorithm<quaternion,vector3> > alg (
		new average_speed_algorithm<quaternion,vector3> ()
	);
	alg->set_step (0.0001);
	alg->set_last_time (10);


	boost::shared_ptr < artifical_input<quaternion,vector3> > input (
		new artifical_input_plane_angles_harmonious (
			plane_angles (0.1, 0.2, 0.3),
			plane_angles (1, 2, 3)
		)
	);
	

	math_modelling<quaternion,vector3> m;
	m.set_data (input);
	auto result = m.run_algorithm (alg);

	auto res = *result;
	std::cerr << res.max_difference << std::endl;
}


void test_auto_generated_2_step_algorithm (double h) {
	boost::shared_ptr < algorithm<quaternion,vector3> > alg (
		new auto_generated_2_step_algorithm<quaternion,vector3> ()
	);
	alg->set_step (h);
	alg->set_last_time (10);


	boost::shared_ptr < artifical_input<quaternion,vector3> > input (
		new artifical_input_plane_angles_harmonious (
			plane_angles (0.1, 0.2, 0.3),
			plane_angles (1, 2, 3)
		)
	);
	

	math_modelling<quaternion,vector3> m;
	m.set_data (input);
	auto result = m.run_algorithm (alg);

	auto res = *result;
	std::cerr << res.max_difference << std::endl;
}


int main() {
	
	test_auto_generated_2_step_algorithm (0.1);
	test_auto_generated_2_step_algorithm (0.01);
	test_auto_generated_2_step_algorithm (0.001);
	test_auto_generated_2_step_algorithm (0.0001);
	test_auto_generated_2_step_algorithm (0.00001);

}