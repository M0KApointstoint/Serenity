#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <stdio.h>
#include "planets.h"
#include <stddef.h>

void write_to_csv(FILE *f, const struct body *bodies_arr, size_t nr_bodies);

#endif
