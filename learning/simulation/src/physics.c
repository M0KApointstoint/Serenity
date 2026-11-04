#include <math.h>
#include "planets.h"

double magnitude_vector_2d(double component_x, double component_y)
{
	double magnitude = 0.0;
	magnitude = component_x * component_x;
	magnitude += component_y * component_y;
	magnitude = sqrt(magnitude);
	return magnitude;
}

double kinetic_energy(struct body *body_adr)
{
    double velocity_squared = ((body_adr->velocity_x) * (body_adr->velocity_x)) +
                              ((body_adr->velocity_y) * (body_adr->velocity_y));
    return (body_adr->mass) * velocity_squared / 2.0;
}

double gravitational_potential_energy(struct body *body_1_adr, struct body *body_2_adr)
{
    double distance_x = ((body_1_adr->position_x) - (body_2_adr->position_x));
    double distance_y = ((body_1_adr->position_y) - (body_2_adr->position_y));
    double distance_bodies = sqrt(distance_x * distance_x + distance_y * distance_y);
    return GRAVITATIONAL_CT * (body_1_adr->mass) * (body_2_adr->mass) / distance_bodies;
}

double total_kinetic_energy(struct body *bodies_arr)
{
    double total = 0.0;
    for (size_t i = 0; i < NR_BODIES; ++i) {
        total += kinetic_energy(bodies_arr + i);
    }
    return total;
}

double total_gravitational_potential_energy(struct body *bodies_arr)
{
    double total = 0.0;
    for (size_t i = 0; i < NR_BODIES; ++i) {
        for (size_t j = 0; j < i; ++j) {
            total -= gravitational_potential_energy(bodies_arr + i, bodies_arr + j);
        }
    }
    return total;
}

double total_energy_system(struct body *bodies_arr)
{
    return total_kinetic_energy(bodies_arr) + total_gravitational_potential_energy(bodies_arr);
}

double momentum_x(struct body *body_adr)
{
    return (body_adr->mass) * (body_adr->velocity_x);
}

double momentum_y(struct body *body_adr)
{
    return (body_adr->mass) * (body_adr->velocity_y);
}

double total_momentum_x(struct body *bodies_arr)
{
    double total = 0.0;
    for (size_t i = 0; i < NR_BODIES; ++i) {
        total += momentum_x(bodies_arr + i);
    }
    return total;
}

double total_momentum_y(struct body *bodies_arr)
{
    double total = 0.0;
    for (size_t i = 0; i < NR_BODIES; ++i) {
        total += momentum_y(bodies_arr + i);
    }
    return total;
}

double relative_change(double initial, double final)
{
    return (final - initial) / initial;
}
