#include <stdio.h>
#include <ctype.h>

#include "input.h"
#include "command.h"

int read_cube_size(int *size) {
    int c;
    do {
        c = getchar();
    } while (isspace(c));

    if (isdigit(c)) {
        *size = 0;
        while (isdigit(c)) {
            *size = *size * 10 + (c - '0');
            c = getchar();
        }
    }

    return c;
}

void read_commands(cube_t *cube, int c) {
    char front = 0;
    int layers = 0;
    char angle = 0;

    while (c != END_OF_DATA) {
        if (c == '\n') {
            execute_when_newline(cube, &front, &layers, &angle);
        }
        else if (islower(c)) {
            execute_when_letter(cube, c, &front, &layers, &angle);
        }
        else if (isdigit(c)) {
            layers = execute_when_digit(c, layers);
        }
        else {
            execute_when_quote(cube, c, &front, &layers, &angle);
        }
        c = getchar();
    }
}