#include <stdio.h>
#include <ctype.h>

#include "input.h"
#include "command.h"

void read_data(char walls[][SIZE][SIZE]) {
    char front = 0;
    int layers = 0;
    char angle = 0;

    int c = getchar();
    while (c != END_OF_DATA) {
        if (c == '\n') {
            execute_when_newline(walls, &front, &layers, &angle);
        }
        else if (islower(c)) {
            execute_when_letter(walls, c, &front, &layers, &angle);
        }
        else if (isdigit(c)) {
            layers = execute_when_digit(c, layers);
        }
        else {
            execute_when_quote(walls, c, &front, &layers, &angle);
        }
        c = getchar();
    }
}