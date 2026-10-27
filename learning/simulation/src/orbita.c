#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include "planets.h"

#define HALF_MINUTE (30.0)
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

void compute_accelerations(const struct body *bodies_arr, size_t nr_bodies,
						   double *accelerations_x_arr, double *accelerations_y_arr)
{
	for (size_t i = 0; i < nr_bodies; ++i) {
		accelerations_x_arr[i] = 0;
		accelerations_y_arr[i] = 0;
		for (size_t j = 0; j < nr_bodies; ++j) {
			if (j == i) {
				continue;
			}
			// delta x.
			double x_change_i_j = bodies_arr[j].position_x - bodies_arr[i].position_x;
			// delta y.
			double y_change_i_j = bodies_arr[j].position_y - bodies_arr[i].position_y;

			double r_i_j = x_change_i_j * x_change_i_j;
			r_i_j += y_change_i_j * y_change_i_j;
			r_i_j = sqrt(r_i_j); // r_i_j = sqrt((x ^ 2) + (y ^ 2)).
		
			double s = 1.0 / r_i_j;
			s /= r_i_j;
			s /= r_i_j; // s = 1 / (r_i_j ^ 3).

			accelerations_x_arr[i] += GRAVITATIONAL_CT * bodies_arr[j].mass * s * x_change_i_j;
			accelerations_y_arr[i] += GRAVITATIONAL_CT * bodies_arr[j].mass * s * y_change_i_j;
		}
	}
}

void write_to_csv(FILE *f, const struct body *bodies_arr, size_t nr_bodies)
{
	fprintf(f, "%e,%e", bodies_arr[0].position_x, bodies_arr[0].position_y);
	for (size_t i = 1; i < nr_bodies; ++i) {
		fprintf(f, ",%e,%e", bodies_arr[i].position_x, bodies_arr[i].position_y);
	}
	fprintf(f, "\n");
}

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

	struct body bodies_arr[] = {earth, moon};
	size_t nr_bodies = sizeof(bodies_arr) / sizeof(*bodies_arr);
	// a[i] is acceleration of body i.
	double accelerations_x_arr[nr_bodies];
	double accelerations_y_arr[nr_bodies];

	FILE *f = fopen("./points.csv", "w");
	if (!f) {
		perror("./points.csv");
		return -1;
	}

	write_to_csv(f, bodies_arr, nr_bodies);

	for (size_t step = 0; step < NR_STEPS; ++step) {
		compute_accelerations(bodies_arr, nr_bodies, accelerations_x_arr, accelerations_y_arr);

		for (size_t i = 0; i < nr_bodies; ++i) {
			bodies_arr[i].position_x += bodies_arr[i].velocity_x * TIME_CHANGE;
			bodies_arr[i].position_y += bodies_arr[i].velocity_y * TIME_CHANGE;
			bodies_arr[i].velocity_x += accelerations_x_arr[i] * TIME_CHANGE;
			bodies_arr[i].velocity_y += accelerations_y_arr[i] * TIME_CHANGE; 
		}

		write_to_csv(f, bodies_arr, nr_bodies);
	}
	fclose(f);
	return 0;
}
