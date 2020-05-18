#include "input.h"

#define DEFAULT_CUBE_SIZE 3

int main() {
    int cube_size = DEFAULT_CUBE_SIZE;
    int c = read_cube_size(&cube_size);

    cube_t cube;
    init_cube(&cube, cube_size);

    read_commands(&cube, c);
    dispose_cube(&cube);

    return 0;
}
