#ifndef CUBE_H
#define CUBE_H

#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define WALLS 6

struct cube {
    int size;
    char **walls[WALLS];
};

typedef struct cube cube_t;

void init_cube(cube_t *cube, int size);

void display_cube(cube_t *cube);

static inline void dispose_cube(cube_t *cube) {
    for (int i = 0; i < WALLS; i++) {
        for (int j = 0; j < cube->size; j++) {
            free(cube->walls[i][j]);
        }
        free(cube->walls[i]);
    }
}

#endif // CUBE_H
