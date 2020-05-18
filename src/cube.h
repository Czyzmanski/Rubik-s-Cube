#ifndef CUBE_H
#define CUBE_H

#define SIZE 5

static inline void init_cube(char walls[][SIZE][SIZE]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                walls[i][j][k] = (char) ('0' + i);
            }
        }
    }
}

void display_cube(char walls[][SIZE][SIZE]);

#endif // CUBE_H
