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

#define TIME_CHANGE (60.0)
#define NR_STEPS (39300)

int main(void)
{
	printf("Serenity in C!\n");

	double x_earth = X_EARTH_INITIAL;
	double y_earth = Y_EARTH_INITIAL;
	double x_moon = X_MOON_INITIAL;
	double y_moon = Y_MOON_INITIAL;

	double v_x_earth = V_X_EARTH_INITIAL;
	double v_y_earth = V_Y_EARTH_INITIAL;
	double v_x_moon = V_X_MOON_INITIAL;
	double v_y_moon = V_Y_MOON_INITIAL;

	for (size_t i = 0; i < NR_STEPS; ++i) {
		double x_change = x_moon - x_earth; // delta x.
		double y_change = y_moon - y_earth; // delta y.

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

		v_x_earth += a_x_earth * TIME_CHANGE;
		v_y_earth += a_y_earth * TIME_CHANGE;
		v_x_moon += a_x_moon * TIME_CHANGE;
		v_y_moon += a_y_moon * TIME_CHANGE;

		x_earth += v_x_earth * TIME_CHANGE;
		y_earth += v_y_earth * TIME_CHANGE;
		x_moon += v_x_moon * TIME_CHANGE;
		y_moon += v_y_moon * TIME_CHANGE;

		printf("--------------------\n");
		printf("Earth data:\n");
		printf("Position: (x, y) = (%e, %e)\n", x_earth, y_earth);
		printf("Moon data:\n");
		printf("Position: (x, y) = (%e, %e)\n", x_moon, y_moon);
	}
	return 0;
}

