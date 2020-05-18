#include <stdio.h>

#include "cube.h"

static inline void display_row(char row[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%c", row[i]);
    }
}

static inline void display_wall(char wall[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE + 1; j++) {
            printf(" ");
        }
        display_row(wall[i]);
        printf("\n");
    }
}

void display_cube(char walls[][SIZE][SIZE]) {
    printf("\n");
    display_wall(walls[0]);

    for (int i = 0; i < SIZE; i++) {
        for (int w = 1; w < 4; w++) {
            display_row(walls[w][i]);
            printf("|");
        }
        display_row(walls[4][i]);
        printf("\n");
    }

    display_wall(walls[5]);
}