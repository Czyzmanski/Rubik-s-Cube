#include <stdio.h>

#include "command.h"

void read_data(char walls[][SIZE][SIZE]) {
    char front = 0;
    int layers = 0;
    char angle = 0;

    int c = getchar();
    while (c != '.') {
        if (c == '\n') {
            execute_when_newline(walls, &front, &layers, &angle);
        }
        else if ('a' <= c && c <= 'z') {
            execute_when_letter(walls, c, &front, &layers, &angle);
        }
        else if ('0' <= c && c <= '9') {
            layers = execute_when_digit(c, layers);
        }
        else {
            execute_when_quote(walls, c, &front, &layers, &angle);
        }
        c = getchar();
    }
}

int main() {
    char walls[6][SIZE][SIZE];
    init_cube(walls);
    read_data(walls);
    return 0;
}
