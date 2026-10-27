#include <stddef.h>
#include <math.h>
#include "planets.h"

void set_initial_conditions(struct body *bodies_arr, size_t nr_bodies)
{
    const double masses_arr[NR_PLANETS] = {
        SUN_MASS,
        MERCURY_MASS,
        VENUS_MASS,
        EARTH_MASS,
        MARS_MASS,
        JUPITER_MASS
    };

	// Set masses and center of mass.
	for (size_t i = 0; i < nr_bodies; ++i) {
		bodies_arr[i].mass = masses_arr[i];
	}
	double center_of_mass_mass = 0.0;
	for (size_t i = 0; i < nr_bodies; ++i) {
		center_of_mass_mass += bodies_arr[i].mass;
	}

    const double semi_major_axes_sun[NR_PLANETS] = {
        SUN_SEMI_MAJOR_AXIS_SUN,
        MERCURY_SEMI_MAJOR_AXIS_SUN,
        VENUS_SEMI_MAJOR_AXIS_SUN,
        EARTH_SEMI_MAJOR_AXIS_SUN,
        MARS_SEMI_MAJOR_AXIS_SUN,
        JUPITER_SEMI_MAJOR_AXIS_SUN
    };

	// Set sun initial coordinates.
	bodies_arr[0].position_x = 0.0;
	bodies_arr[0].position_y = 0.0;
	for (size_t i = 1; i < nr_bodies; ++i) {
		bodies_arr[0].position_x -= bodies_arr[i].mass * semi_major_axes_sun[i];
	}
	bodies_arr[0].position_x /= center_of_mass_mass;

	// Set planets initial coordinates.
	for (size_t i = 1; i < nr_bodies; ++i) {
		bodies_arr[i].position_x = bodies_arr[0].position_x + semi_major_axes_sun[i];
		bodies_arr[i].position_y = 0.0;
	}

	// Set relative velocities to sun in isolated scenario.
	double omegas[nr_bodies];
	for (size_t i = 1; i < nr_bodies; ++i) {
		omegas[i] = sqrt(GRAVITATIONAL_CT * (bodies_arr[0].mass + bodies_arr[i].mass) / semi_major_axes_sun[i]);
	}

	// Set sun initial velocity.
	bodies_arr[0].velocity_x = 0.0;
	bodies_arr[0].velocity_y = 0.0;
	for (size_t i = 1; i < nr_bodies; ++i) {
		bodies_arr[0].velocity_y -= bodies_arr[i].mass * omegas[i];
	}
	bodies_arr[0].velocity_y /= center_of_mass_mass;

	// Set other planets initial velocities.
	for (size_t i = 1; i < nr_bodies; ++i) {
		bodies_arr[i].velocity_x = 0.0;
		bodies_arr[i].velocity_y = bodies_arr[0].velocity_y + omegas[i];
	}
}
