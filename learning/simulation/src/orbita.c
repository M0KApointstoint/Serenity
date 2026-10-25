#include <stdio.h>
#include <stddef.h>
#include <math.h>

#define GRAVITATIONAL_CT (6.674e-11)
#define EARTH_MASS (5.972e24)
#define MOON_MASS (7.342e22)

#define X_EARTH_INITIAL (-4.668e6)
#define Y_EARTH_INITIAL (0.0)
#define X_MOON_INITIAL (3.797e8)
#define Y_MOON_INITIAL (0.0)

#define V_X_EARTH_INITIAL (0.0)
#define V_Y_EARTH_INITIAL (-12.44)
#define V_X_MOON_INITIAL (0.0)
#define V_Y_MOON_INITIAL (1012.06)

// Use this for explicit Euler method.
#define HALF_MINUTE (30.0)
// Use this for semi-implicit Euler method.
#define ONE_MINUTE (60.0)

// Use these for numeric analysis.
#define ONE_HOUR (ONE_MINUTE * 60.0)
#define ONE_DAY (ONE_HOUR * 24.0)
#define ONE_WEEK (ONE_DAY * 7.0)

#define TIME_CHANGE HALF_MINUTE

#define MOON_PERIOD (2357500)

#define NR_STEPS ((size_t)(MOON_PERIOD / TIME_CHANGE))

struct body {
	double position_x;
	double position_y;
	double velocity_x;
	double velocity_y;
	double mass;
};

int main(void)
{
	struct body earth = {
		.position_x = X_EARTH_INITIAL,
		.position_y = Y_EARTH_INITIAL,
		.velocity_x = V_X_EARTH_INITIAL,
		.velocity_y = V_Y_EARTH_INITIAL,
		.mass = EARTH_MASS
	};

	struct body moon = {
		.position_x = X_MOON_INITIAL,
		.position_y = Y_MOON_INITIAL,
		.velocity_x = V_X_MOON_INITIAL,
		.velocity_y = V_Y_MOON_INITIAL,
		.mass = MOON_MASS
	};
	
	FILE *f = fopen("./points.csv", "w"); // No return value check :))
	fprintf(f, "%e,%e,%e,%e\n", earth.position_x, earth.position_y, moon.position_x, moon.position_y);

	for (size_t i = 0; i < NR_STEPS; ++i) {
		double x_change = moon.position_x - earth.position_x; // delta x.
		double y_change = moon.position_y - earth.position_y; // delta y.

		double r = x_change * x_change;
		r += y_change * y_change;
		r = sqrt(r); // r = sqrt((x ^ 2) + (y ^ 2)).
		
		double s = 1.0 / r;
		s /= r;
		s /= r; // s = 1 / (r ^ 3).

		double a_x_earth = GRAVITATIONAL_CT * MOON_MASS * s * x_change;
		double a_y_earth = GRAVITATIONAL_CT * MOON_MASS * s * y_change;
		double a_x_moon = - GRAVITATIONAL_CT * EARTH_MASS * s * x_change;
		double a_y_moon = - GRAVITATIONAL_CT * EARTH_MASS * s * y_change;

		earth.position_x += earth.velocity_x * TIME_CHANGE;
		earth.position_y += earth.velocity_y * TIME_CHANGE;
		moon.position_x += moon.velocity_x * TIME_CHANGE;
		moon.position_y += moon.velocity_y * TIME_CHANGE;

		earth.velocity_x += a_x_earth * TIME_CHANGE;
		earth.velocity_y += a_y_earth * TIME_CHANGE;
		moon.velocity_x += a_x_moon * TIME_CHANGE;
		moon.velocity_y += a_y_moon * TIME_CHANGE;

		fprintf(f, "%e,%e,%e,%e\n", earth.position_x, earth.position_y, moon.position_x, moon.position_y);
	}
	fclose(f);
	return 0;
}
