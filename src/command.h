#ifndef COMMAND_H
#define COMMAND_H

#include "cube.h"
#include "rotation.h"

static inline void execute_when_newline(char walls[][SIZE][SIZE], char *front,
                                        int *layers, char *angle) {
    if (*front != 0) {
        // execute previous command
        rotate(walls, *front, *layers, *angle);
    }

    // set program state for new command
    *front = 0;
    *layers = 0;
    *angle = 0;

    display_cube(walls);
}

static inline void execute_when_letter(char walls[][SIZE][SIZE], int c,
                                       char *front, int *layers, char *angle) {
    if (*front != 0) {
        // execute previous command
        rotate(walls, *front, *layers, *angle);
    }

    // update program state
    *front = (char) c;
    *layers = 0;
    *angle = 0;
}

static inline int execute_when_digit(int c, int layers) {
    return layers * 10 + (c - '0');
}

static inline void execute_when_quote(char walls[][SIZE][SIZE], int c,
                        char *front, int *layers, char *angle) {
    *angle = (char) c;

    rotate(walls, *front, *layers, *angle);

    // set program state for new command
    *front = 0;
    *layers = 0;
    *angle = 0;
}

#endif // COMMAND_H
