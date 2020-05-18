#include "rotation.h"

#define UP 'u'
#define LEFT 'l'
#define FRONT 'f'
#define RIGHT 'r'
#define BACK 'b'
#define DOWN 'd'

#define UPPER_WALL 0
#define LEFT_WALL 1
#define FRONT_WALL 2
#define RIGHT_WALL 3
#define BACK_WALL 4
#define DOWN_WALL 5

#define DEGREES_90_CLOCKWISE 0
#define DEGREES_90_COUNTERCLOCKWISE '\''
#define DEGREES_180 '"'

static inline void swap(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline void inverse_row(char row[], int size) {
    for (int i = 0, j = size - 1; i < j; i++, j--) {
        swap(&row[i], &row[j]);
    }
}

static inline void swap_and_inverse_rows(char row1[], char row2[], int size) {
    for (int i = 0, j = size - 1; i < size && j >= 0; i++, j--) {
        swap(&row1[i], &row2[j]);
    }
}

static inline void swap_and_inverse_columns(char *wall1[], int col1,
                                            char *wall2[], int col2, int size) {
    for (int i = 0, j = size - 1; i < size && j >= 0; i++, j--) {
        swap(&wall1[i][col1], &wall2[j][col2]);
    }
}

static void rotate_layer_left(cube_t *cube, const int order[WALLS], int layer) {
    int upper = order[UPPER_WALL];
    int left = order[LEFT_WALL];
    int right = order[RIGHT_WALL];
    int down = order[DOWN_WALL];

    int size = cube->size;
    char ***walls = cube->walls;

    for (int i = 0; i < size; i++) {
        char tmp = walls[upper][size - layer][i];
        walls[upper][size - layer][i] = walls[right][i][layer - 1];
        walls[right][i][layer - 1] = walls[down][layer - 1][size - 1 - i];
        walls[down][layer - 1][size - 1 - i] = walls[left][size - 1 - i][size - layer];
        walls[left][size - 1 - i][size - layer] = tmp;
    }
}

static void rotate_layer_right(cube_t *cube, const int order[WALLS], int layer) {
    int upper = order[UPPER_WALL];
    int left = order[LEFT_WALL];
    int right = order[RIGHT_WALL];
    int down = order[DOWN_WALL];

    int size = cube->size;
    char ***walls = cube->walls;

    for (int i = 0; i < size; i++) {
        char tmp = walls[upper][size - layer][i];
        walls[upper][size - layer][i] = walls[left][size - 1 - i][size - layer];
        walls[left][size - 1 - i][size - layer] = walls[down][layer - 1][size - 1 - i];
        walls[down][layer - 1][size - 1 - i] = walls[right][i][layer - 1];
        walls[right][i][layer - 1] = tmp;
    }
}

static void rotate_wall_left(char *wall[], int size) {
    for (int i = 0; i < size / 2; i++) {
        for (int j = i; j < size - 1 - i; j++) {
            char tmp = wall[i][j];
            wall[i][j] = wall[j][size - 1 - i];
            wall[j][size - 1 - i] = wall[size - 1 - i][size - 1 - j];
            wall[size - 1 - i][size - 1 - j] = wall[size - 1 - j][i];
            wall[size - 1 - j][i] = tmp;
        }
    }
}

static void rotate_wall_right(char *wall[], int size) {
    for (int i = 0; i < size / 2; i++) {
        for (int j = i; j < size - 1 - i; j++) {
            char tmp = wall[i][j];
            wall[i][j] = wall[size - 1 - j][i];
            wall[size - 1 - j][i] = wall[size - 1 - i][size - 1 - j];
            wall[size - 1 - i][size - 1 - j] = wall[j][size - 1 - i];
            wall[j][size - 1 - i] = tmp;
        }
    }
}

static void rotate_wall_upside_down(char *wall[], int size) {
    int i = 0, j = size - 1;
    while (i < j) {
        swap_and_inverse_rows(wall[i], wall[j], size);
        i++, j--;
    }
    if (i == j) {
        inverse_row(wall[i], size);
    }
}

static void rotate_left(cube_t *cube, const int order[WALLS], int layers) {
    int front = order[FRONT_WALL];
    int back = order[BACK_WALL];

    rotate_wall_left(cube->walls[front], cube->size);

    for (int i = 1; i <= layers; i++) {
        rotate_layer_left(cube, order, i);
    }

    if (layers == cube->size) {
        rotate_wall_right(cube->walls[back], cube->size);
    }
}

void rotate_right(cube_t *cube, const int order[WALLS], int layers) {
    int front = order[FRONT_WALL];
    int back = order[BACK_WALL];

    rotate_wall_right(cube->walls[front], cube->size);

    for (int i = 1; i <= layers; i++) {
        rotate_layer_right(cube, order, i);
    }

    if (layers == cube->size) {
        rotate_wall_left(cube->walls[back], cube->size);
    }
}

void rotate_layer_upside_down(cube_t *cube, const int order[WALLS], int layer) {
    int upper = order[UPPER_WALL];
    int left = order[LEFT_WALL];
    int right = order[RIGHT_WALL];
    int down = order[DOWN_WALL];

    int size = cube->size;

    swap_and_inverse_rows(cube->walls[upper][size - layer],
                          cube->walls[down][layer - 1], size);
    swap_and_inverse_columns(cube->walls[left], size - layer,
                             cube->walls[right], layer - 1, size);
}

static void rotate_upside_down(cube_t *cube, const int order[WALLS], int layers) {
    int front = order[FRONT_WALL];
    int back = order[BACK_WALL];

    rotate_wall_upside_down(cube->walls[front], cube->size);

    for (int i = 1; i <= layers; i++) {
        rotate_layer_upside_down(cube, order, i);
    }

    if (layers == cube->size) {
        rotate_wall_upside_down(cube->walls[back], cube->size);
    }
}

static void rotate_by_angle(cube_t *cube, const int order[WALLS],
                            int layers, char angle) {
    switch (angle) {
        case DEGREES_90_CLOCKWISE:
            rotate_right(cube, order, layers);
            break;
        case DEGREES_90_COUNTERCLOCKWISE:
            rotate_left(cube, order, layers);
            break;
        case DEGREES_180:
            rotate_upside_down(cube, order, layers);
            break;
    }
}

static void rotate_with_upper_as_front(cube_t *cube, int layers, char angle) {
    int size = cube->size;
    char ***walls = cube->walls;

    rotate_wall_right(walls[LEFT_WALL], size);
    rotate_wall_left(walls[RIGHT_WALL], size);
    rotate_wall_upside_down(walls[BACK_WALL], size);
    rotate_wall_upside_down(walls[DOWN_WALL], size);

    int order[] = {BACK_WALL, LEFT_WALL, UPPER_WALL, RIGHT_WALL, DOWN_WALL, FRONT_WALL};

    rotate_by_angle(cube, order, layers, angle);

    rotate_wall_left(walls[LEFT_WALL], size);
    rotate_wall_right(walls[RIGHT_WALL], size);
    rotate_wall_upside_down(walls[BACK_WALL], size);
    rotate_wall_upside_down(walls[DOWN_WALL], size);
}

static void rotate_with_left_as_front(cube_t *cube, int layers, char angle) {
    int size = cube->size;
    char ***walls = cube->walls;

    rotate_wall_left(walls[UPPER_WALL], size);
    rotate_wall_right(walls[DOWN_WALL], size);

    int order[] = {UPPER_WALL, BACK_WALL, LEFT_WALL, FRONT_WALL, RIGHT_WALL, DOWN_WALL};

    rotate_by_angle(cube, order, layers, angle);

    rotate_wall_right(walls[UPPER_WALL], size);
    rotate_wall_left(walls[DOWN_WALL], size);
}

static inline void rotate_with_front_as_front(cube_t *cube, int layers, char angle) {
    int order[] = {UPPER_WALL, LEFT_WALL, FRONT_WALL, RIGHT_WALL, BACK_WALL, DOWN_WALL};
    rotate_by_angle(cube, order, layers, angle);
}

static void rotate_with_right_as_front(cube_t *cube, int layers, char angle) {
    int size = cube->size;
    char ***walls = cube->walls;

    rotate_wall_right(walls[UPPER_WALL], size);
    rotate_wall_left(walls[DOWN_WALL], size);

    int order[] = {UPPER_WALL, FRONT_WALL, RIGHT_WALL, BACK_WALL, LEFT_WALL, DOWN_WALL};

    rotate_by_angle(cube, order, layers, angle);

    rotate_wall_left(walls[UPPER_WALL], size);
    rotate_wall_right(walls[DOWN_WALL], size);
}

static void rotate_with_back_as_front(cube_t *cube, int layers, char angle) {
    int size = cube->size;
    char ***walls = cube->walls;

    rotate_wall_upside_down(walls[LEFT_WALL], size);
    rotate_wall_upside_down(walls[FRONT_WALL], size);
    rotate_wall_upside_down(walls[RIGHT_WALL], size);
    rotate_wall_upside_down(walls[BACK_WALL], size);

    int order[] = {DOWN_WALL, LEFT_WALL, BACK_WALL, RIGHT_WALL, FRONT_WALL, UPPER_WALL};

    rotate_by_angle(cube, order, layers, angle);

    rotate_wall_upside_down(walls[LEFT_WALL], size);
    rotate_wall_upside_down(walls[FRONT_WALL], size);
    rotate_wall_upside_down(walls[RIGHT_WALL], size);
    rotate_wall_upside_down(walls[BACK_WALL], size);
}

static void rotate_with_down_as_front(cube_t *cube, int layers, char angle) {
    int size = cube->size;
    char ***walls = cube->walls;

    rotate_wall_upside_down(walls[UPPER_WALL], size);
    rotate_wall_left(walls[LEFT_WALL], size);
    rotate_wall_right(walls[RIGHT_WALL], size);
    rotate_wall_upside_down(walls[BACK_WALL], size);

    int order[] = {FRONT_WALL, LEFT_WALL, DOWN_WALL, RIGHT_WALL, UPPER_WALL, BACK_WALL};

    rotate_by_angle(cube, order, layers, angle);

    rotate_wall_upside_down(walls[UPPER_WALL], size);
    rotate_wall_right(walls[LEFT_WALL], size);
    rotate_wall_left(walls[RIGHT_WALL], size);
    rotate_wall_upside_down(walls[BACK_WALL], size);
}

void rotate(cube_t *cube, char front, int layers, char angle) {
    if (layers == 0) {
        /* Number of layers not given means number of layers is 1. */
        layers = 1;
    }

    switch (front) {
        case UP:
            rotate_with_upper_as_front(cube, layers, angle);
            break;
        case LEFT:
            rotate_with_left_as_front(cube, layers, angle);
            break;
        case FRONT:
            rotate_with_front_as_front(cube, layers, angle);
            break;
        case RIGHT:
            rotate_with_right_as_front(cube, layers, angle);
            break;
        case BACK:
            rotate_with_back_as_front(cube, layers, angle);
            break;
        case DOWN:
            rotate_with_down_as_front(cube, layers, angle);
            break;
    }
}