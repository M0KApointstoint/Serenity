#include <stdio.h>
#include <stddef.h>
#include "planets.h"
#include "csv_handler.h"
#include "physics.h"

void compute_accelerations(const struct body *bodies_arr,
						   double *accelerations_x_arr, double *accelerations_y_arr)
{
	for (size_t i = 0; i < NR_BODIES; ++i) {
		accelerations_x_arr[i] = 0;
		accelerations_y_arr[i] = 0;
		for (size_t j = 0; j < NR_BODIES; ++j) {
			if (j == i) {
				continue;
			}
			// delta x.
			double x_change_i_j = bodies_arr[j].position_x - bodies_arr[i].position_x;
			// delta y.
			double y_change_i_j = bodies_arr[j].position_y - bodies_arr[i].position_y;

			double r_i_j = magnitude_vector_2d(x_change_i_j, y_change_i_j);

			double s = 1.0 / r_i_j;
			s /= r_i_j;
			s /= r_i_j; // s = 1 / (r_i_j ^ 3).

			accelerations_x_arr[i] += GRAVITATIONAL_CT * bodies_arr[j].mass * s * x_change_i_j;
			accelerations_y_arr[i] += GRAVITATIONAL_CT * bodies_arr[j].mass * s * y_change_i_j;
		}
	}
}

int main(void)
{
	FILE *f = fopen("./build/points.csv", "w");
	if (!f) {
		perror("./build/points.csv");
		return -1;
	}

	struct body bodies_arr[NR_BODIES];
	set_initial_conditions(bodies_arr);

	// a[i] is acceleration of body i.
	double accelerations_x_arr[NR_BODIES];
	double accelerations_y_arr[NR_BODIES];

	double energy_initial = total_energy_system(bodies_arr);

	for (size_t step = 0; step < NR_STEPS; ++step) {
		compute_accelerations(bodies_arr, accelerations_x_arr, accelerations_y_arr);
		for (size_t i = 0; i < NR_BODIES; ++i) {
			bodies_arr[i].position_x += bodies_arr[i].velocity_x * TIME_CHANGE;
			bodies_arr[i].position_y += bodies_arr[i].velocity_y * TIME_CHANGE;
			bodies_arr[i].velocity_x += accelerations_x_arr[i] * TIME_CHANGE;
			bodies_arr[i].velocity_y += accelerations_y_arr[i] * TIME_CHANGE;
		}
		if (!(step % 1000)) {
			write_to_csv(f, bodies_arr, NR_BODIES);
		}
	}

	fclose(f);

	double final_energy = total_energy_system(bodies_arr);
	double momentum_x_final = total_momentum_x(bodies_arr);
	double momentum_y_final = total_momentum_y(bodies_arr);

	double energy_error = relative_change(energy_initial, final_energy);

	printf("Analyzing conservation of energy:\n");
	printf("Relative change of the total energy in the system is: %lf%%.\n", energy_error);
	printf("Analyzing conservation of momentum:\n");
	printf("Final total momentum on the x-axis in the system is: %lf.\n", momentum_x_final);
	printf("Final total momentum on the y-axis in the system is: %lf.\n", momentum_y_final);
	return 0;
}
