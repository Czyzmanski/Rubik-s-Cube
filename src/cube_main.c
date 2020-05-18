#include "input.h"

int main() {
    int cube_size;
    int c = read_cube_size(&cube_size);

    cube_t cube;
    init_cube(&cube, cube_size);

    read_commands(&cube, c);
    dispose_cube(&cube);

    return 0;
}
