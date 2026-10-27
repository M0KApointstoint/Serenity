#include <stdio.h>
#include "planets.h"
#include <stddef.h>

void write_to_csv(FILE *f, const struct body *bodies_arr, size_t nr_bodies)
{
	fprintf(f, "%e,%e", bodies_arr[0].position_x, bodies_arr[0].position_y);
	for (size_t i = 1; i < nr_bodies; ++i) {
		fprintf(f, ",%e,%e", bodies_arr[i].position_x, bodies_arr[i].position_y);
	}
	fprintf(f, "\n");
}
