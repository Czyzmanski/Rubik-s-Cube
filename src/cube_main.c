#include "input.h"

int main() {
    char walls[6][SIZE][SIZE];
    init_cube(walls);
    read_data(walls);
    return 0;
}
