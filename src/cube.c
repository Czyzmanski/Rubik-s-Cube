#include <stdio.h>
#include <stdlib.h>

#include "cube.h"

void init_cube(cube_t *cube, int size) {
    cube->size = size;

    for (int i = 0; i < WALLS; i++) {
        cube->walls[i] = calloc(cube->size, sizeof(char *));
        assert(cube->walls[i] != NULL);
        for (int j = 0; j < cube->size; j++) {
            cube->walls[i][j] = calloc(cube->size, sizeof(char));
            assert(cube->walls[i][j] != NULL);
        }
    }

    for (int i = 0; i < WALLS; i++) {
        for (int j = 0; j < cube->size; j++) {
            for (int k = 0; k < cube->size; k++) {
                cube->walls[i][j][k] = (char) ('0' + i);
            }
        }
    }
}

static inline void display_row(char row[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%c", row[i]);
    }
}

static inline void display_wall(char *wall[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size + 1; j++) {
            printf(" ");
        }
        display_row(wall[i], size);
        printf("\n");
    }
}

void display_cube(cube_t *cube) {
    printf("\n");
    display_wall(cube->walls[0], cube->size);

    for (int i = 0; i < cube->size; i++) {
        for (int w = 1; w < WALLS - 2; w++) {
            display_row(cube->walls[w][i], cube->size);
            printf("|");
        }
        display_row(cube->walls[WALLS - 2][i], cube->size);
        printf("\n");
    }

    display_wall(cube->walls[WALLS - 1], cube->size);
}