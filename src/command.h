#ifndef COMMAND_H
#define COMMAND_H

#include "cube.h"
#include "rotation.h"

static inline void execute_when_newline(cube_t *cube, char *front,
                                        int *layers, char *angle) {
    if (*front != 0) {
        /* Execute previous command. */
        rotate(cube, *front, *layers, *angle);
    }

    /* Set program state for new command. */
    *front = 0;
    *layers = 0;
    *angle = 0;

    display_cube(cube);
}

static inline void execute_when_letter(cube_t *cube, int c, char *front,
                                       int *layers, char *angle) {
    if (*front != 0) {
        /* Execute previous command. */
        rotate(cube, *front, *layers, *angle);
    }

    /* Update program state. */
    *front = (char) c;
    *layers = 0;
    *angle = 0;
}

static inline int execute_when_digit(int c, int layers) {
    return layers * 10 + (c - '0');
}

static inline void execute_when_quote(cube_t *cube, int c, char *front,
                                      int *layers, char *angle) {
    *angle = (char) c;

    rotate(cube, *front, *layers, *angle);

    /* Set program state for new command. */
    *front = 0;
    *layers = 0;
    *angle = 0;
}

#endif // COMMAND_H
