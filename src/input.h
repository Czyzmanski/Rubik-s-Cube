#ifndef INPUT_H
#define INPUT_H

#include "cube.h"

#define END_OF_DATA '.'

int read_cube_size(int *size);

void read_commands(cube_t *cube, int c);

#endif // INPUT_H
