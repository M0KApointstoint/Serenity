#include <stddef.h>
#include <math.h>

#define GRAVITATIONAL_CT (6.674e-11)

#define NR_PLANETS (6)

#define SUN_MASS (1.989e30)
#define MERCURY_MASS (3.301e23)
#define VENUS_MASS (4.867e24)
#define EARTH_MASS (5.972e24)
#define MARS_MASS (6.417e23)
#define JUPITER_MASS (1.898e27)

#define SUN_SEMI_MAJOR_AXIS_SUN (0.0)
#define MERCURY_SEMI_MAJOR_AXIS_SUN (5.791e10)
#define VENUS_SEMI_MAJOR_AXIS_SUN (1.082e11)
#define EARTH_SEMI_MAJOR_AXIS_SUN (1.496e11)
#define MARS_SEMI_MAJOR_AXIS_SUN (2.279e11)
#define JUPITER_SEMI_MAJOR_AXIS_SUN (7.785e11)

struct body {
	double position_x;
	double position_y;
	double velocity_x;
	double velocity_y;
	double mass;
};

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
	for (size_t i = 2; i < nr_bodies; ++i) {
		bodies_arr[0].velocity_y -= bodies_arr[i].mass * omegas[i];
	}
	bodies_arr[0].velocity_y /= center_of_mass_mass;

	// Set other planets initial velocities.
	for (size_t i = 1; i < nr_bodies; ++i) {
		bodies_arr[i].velocity_x = 0.0;
		bodies_arr[i].velocity_y = bodies_arr[0].velocity_y + omegas[i];
	}
}
