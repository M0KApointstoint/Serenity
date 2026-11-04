#ifndef PHYSICS_H
#define PHYSICS_H

double magnitude_vector_2d(double component_x, double component_y);
double total_energy_system(struct body *bodies_arr);
double total_momentum_x(struct body *bodies_arr);
double total_momentum_y(struct body *bodies_arr);
double relative_change(double initial, double final);

#endif
