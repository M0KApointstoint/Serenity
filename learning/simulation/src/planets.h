#ifndef PLANETS_H
#define PLANETS_H

#include <stddef.h>

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

#define HALF_MINUTE (30.0)
#define ONE_MINUTE (60.0)
#define ONE_HOUR (ONE_MINUTE * 60.0)
#define ONE_DAY (ONE_HOUR * 24.0)
#define ONE_WEEK (ONE_DAY * 7.0)

#define TIME_CHANGE HALF_MINUTE

#define JUPITER_PERIOD (4333 * ONE_DAY)

#define NR_STEPS ((size_t)(JUPITER_PERIOD / TIME_CHANGE))

struct body {
	double position_x;
	double position_y;
	double velocity_x;
	double velocity_y;
	double mass;
};

void set_initial_conditions(struct body *bodies_arr, size_t nr_bodies);

#endif
