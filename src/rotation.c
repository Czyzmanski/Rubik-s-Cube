#include "rotation.h"

static inline void swap(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline void inverse_row(char row[SIZE]) {
    for (int i = 0, j = SIZE - 1; i < j; i++, j--) {
        swap(&row[i], &row[j]);
    }
}

static inline void swap_and_inverse_rows(char row1[SIZE], char row2[SIZE]) {
    for (int i = 0, j = SIZE - 1; i < SIZE && j >= 0; i++, j--) {
        swap(&row1[i], &row2[j]);
    }
}

static inline void swap_and_inverse_columns(char wall1[][SIZE], int col1,
                                            char wall2[][SIZE], int col2) {
    for (int i = 0, j = SIZE - 1; i < SIZE && j >= 0; i++, j--) {
        swap(&wall1[i][col1], &wall2[j][col2]);
    }
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
static void rotate_layer_left(char walls[][SIZE][SIZE],
                              const int order[6], int layer) {
    int upper = order[0];
    int left = order[1];
    int right = order[3];
    int down = order[5];

    for (int i = 0; i < SIZE; i++) {
        char tmp = walls[upper][SIZE - layer][i];
        walls[upper][SIZE - layer][i] = walls[right][i][layer - 1];
        walls[right][i][layer - 1] = walls[down][layer - 1][SIZE - 1 - i];
        walls[down][layer - 1][SIZE - 1 - i]
                = walls[left][SIZE - 1 - i][SIZE - layer];
        walls[left][SIZE - 1 - i][SIZE - layer] = tmp;
    }
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
static void rotate_layer_right(char walls[][SIZE][SIZE],
                               const int order[6], int layer) {
    int upper = order[0];
    int left = order[1];
    int right = order[3];
    int down = order[5];

    for (int i = 0; i < SIZE; i++) {
        char tmp = walls[upper][SIZE - layer][i];
        walls[upper][SIZE - layer][i] = walls[left][SIZE - 1 - i][SIZE - layer];
        walls[left][SIZE - 1 - i][SIZE - layer]
                = walls[down][layer - 1][SIZE - 1 - i];
        walls[down][layer - 1][SIZE - 1 - i] = walls[right][i][layer - 1];
        walls[right][i][layer - 1] = tmp;
    }
}

static void rotate_wall_left(char wall[][SIZE]) {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = i; j < SIZE - 1 - i; j++) {
            char tmp = wall[i][j];
            wall[i][j] = wall[j][SIZE - 1 - i];
            wall[j][SIZE - 1 - i] = wall[SIZE - 1 - i][SIZE - 1 - j];
            wall[SIZE - 1 - i][SIZE - 1 - j] = wall[SIZE - 1 - j][i];
            wall[SIZE - 1 - j][i] = tmp;
        }
    }
}

static void rotate_wall_right(char wall[][SIZE]) {
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = i; j < SIZE - 1 - i; j++) {
            char tmp = wall[i][j];
            wall[i][j] = wall[SIZE - 1 - j][i];
            wall[SIZE - 1 - j][i] = wall[SIZE - 1 - i][SIZE - 1 - j];
            wall[SIZE - 1 - i][SIZE - 1 - j] = wall[j][SIZE - 1 - i];
            wall[j][SIZE - 1 - i] = tmp;
        }
    }
}

static void rotate_wall_upside_down(char wall[][SIZE]) {
    int i = 0, j = SIZE - 1;
    while (i < j) {
        swap_and_inverse_rows(wall[i], wall[j]);
        i++, j--;
    }
    if (i == j) {
        inverse_row(wall[i]);
    }
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
static void rotate_left(char walls[][SIZE][SIZE], int order[6], int layers) {
    int front = order[2];
    int back = order[4];

    rotate_wall_left(walls[front]);

    for (int i = 1; i <= layers; i++) {
        rotate_layer_left(walls, order, i);
    }

    if (layers == SIZE) {
        rotate_wall_right(walls[back]);
    }
}

void rotate_right(char walls[][SIZE][SIZE], int order[6], int layers) {
    int front = order[2];
    int back = order[4];

    rotate_wall_right(walls[front]);

    for (int i = 1; i <= layers; i++) {
        rotate_layer_right(walls, order, i);
    }

    if (layers == SIZE) {
        rotate_wall_left(walls[back]);
    }
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
void rotate_layer_upside_down(char walls[][SIZE][SIZE], int order[6], int layer) {
    int upper = order[0];
    int left = order[1];
    int right = order[3];
    int down = order[5];

    swap_and_inverse_rows(walls[upper][SIZE - layer], walls[down][layer - 1]);
    swap_and_inverse_columns(walls[left], SIZE - layer, walls[right], layer - 1);
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
static void rotate_upside_down(char walls[][SIZE][SIZE], int order[6], int layers) {
    int front = order[2];
    int back = order[4];

    rotate_wall_upside_down(walls[front]);

    for (int i = 1; i <= layers; i++) {
        rotate_layer_upside_down(walls, order, i);
    }

    if (layers == SIZE) {
        rotate_wall_upside_down(walls[back]);
    }
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
static void rotate_by_angle(char walls[][SIZE][SIZE], int order[6],
                            int layers, char angle) {
    switch (angle) {
        case 0:
            rotate_right(walls, order, layers);
            break;
        case '\'':
            rotate_left(walls, order, layers);
            break;
        case '"':
            rotate_upside_down(walls, order, layers);
            break;
    }
}

/* When treating front wall as front:
 * walls[0] denotes upper wall
 * walls[1] denotes left wall
 * walls[2] denotes front wall
 * walls[3] denotes right wall
 * walls[4] denotes back wall
 * walls[5] denotes down wall
 */
static void rotate_with_upper_as_front(char walls[][SIZE][SIZE],
                                       int layers, char angle) {
    rotate_wall_right(walls[1]);
    rotate_wall_left(walls[3]);
    rotate_wall_upside_down(walls[4]);
    rotate_wall_upside_down(walls[5]);

    /* When treating down wall as front:
     * walls[4] denotes upper wall
     * walls[1] denotes left wall
     * walls[0] denotes front wall
     * walls[3] denotes right wall
     * walls[5] denotes back wall
     * walls[2] denotes down wall
     */
    int order[] = {4, 1, 0, 3, 5, 2};

    rotate_by_angle(walls, order, layers, angle);

    rotate_wall_left(walls[1]);
    rotate_wall_right(walls[3]);
    rotate_wall_upside_down(walls[4]);
    rotate_wall_upside_down(walls[5]);
}

/* When treating front wall as front:
 * walls[0] denotes upper wall
 * walls[1] denotes left wall
 * walls[2] denotes front wall
 * walls[3] denotes right wall
 * walls[4] denotes back wall
 * walls[5] denotes down wall
 */
static void rotate_with_left_as_front(char walls[][SIZE][SIZE],
                                      int layers, char angle) {
    rotate_wall_left(walls[0]);
    rotate_wall_right(walls[5]);

    /* When treating down wall as front:
     * walls[0] denotes upper wall
     * walls[4] denotes left wall
     * walls[1] denotes front wall
     * walls[2] denotes right wall
     * walls[3] denotes back wall
     * walls[5] denotes down wall
     */
    int order[] = {0, 4, 1, 2, 3, 5};

    rotate_by_angle(walls, order, layers, angle);

    rotate_wall_right(walls[0]);
    rotate_wall_left(walls[5]);
}

/* When treating front wall as front:
 * walls[0] denotes upper wall
 * walls[1] denotes left wall
 * walls[2] denotes front wall
 * walls[3] denotes right wall
 * walls[4] denotes back wall
 * walls[5] denotes down wall
 */
static inline void rotate_with_front_as_front(char walls[][SIZE][SIZE],
                                              int layers, char angle) {
    int order[] = {0, 1, 2, 3, 4, 5};
    rotate_by_angle(walls, order, layers, angle);
}

/* When treating front wall as front:
 * walls[0] denotes upper wall
 * walls[1] denotes left wall
 * walls[2] denotes front wall
 * walls[3] denotes right wall
 * walls[4] denotes back wall
 * walls[5] denotes down wall
 */
static void rotate_with_right_as_front(char walls[][SIZE][SIZE],
                                       int layers, char angle) {
    rotate_wall_right(walls[0]);
    rotate_wall_left(walls[5]);

    /* When treating down wall as front:
     * walls[0] denotes upper wall
     * walls[2] denotes left wall
     * walls[3] denotes front wall
     * walls[4] denotes right wall
     * walls[1] denotes back wall
     * walls[5] denotes down wall
     */
    int order[] = {0, 2, 3, 4, 1, 5};

    rotate_by_angle(walls, order, layers, angle);

    rotate_wall_left(walls[0]);
    rotate_wall_right(walls[5]);
}

/* When treating front wall as front:
 * walls[0] denotes upper wall
 * walls[1] denotes left wall
 * walls[2] denotes front wall
 * walls[3] denotes right wall
 * walls[4] denotes back wall
 * walls[5] denotes down wall
 */
static void rotate_with_back_as_front(char walls[][SIZE][SIZE],
                                      int layers, char angle) {
    rotate_wall_upside_down(walls[1]);
    rotate_wall_upside_down(walls[2]);
    rotate_wall_upside_down(walls[3]);
    rotate_wall_upside_down(walls[4]);

    /* When treating down wall as front:
     * walls[5] denotes upper wall
     * walls[1] denotes left wall
     * walls[4] denotes front wall
     * walls[3] denotes right wall
     * walls[2] denotes back wall
     * walls[0] denotes down wall
     */
    int order[] = {5, 1, 4, 3, 2, 0};

    rotate_by_angle(walls, order, layers, angle);

    rotate_wall_upside_down(walls[1]);
    rotate_wall_upside_down(walls[2]);
    rotate_wall_upside_down(walls[3]);
    rotate_wall_upside_down(walls[4]);
}

/* When treating front wall as front:
 * walls[0] denotes upper wall
 * walls[1] denotes left wall
 * walls[2] denotes front wall
 * walls[3] denotes right wall
 * walls[4] denotes back wall
 * walls[5] denotes down wall
 */
static void rotate_with_down_as_front(char walls[][SIZE][SIZE],
                                      int layers, char angle) {
    rotate_wall_upside_down(walls[0]);
    rotate_wall_left(walls[1]);
    rotate_wall_right(walls[3]);
    rotate_wall_upside_down(walls[4]);

    /* When treating down wall as front:
     * walls[2] denotes upper wall
     * walls[1] denotes left wall
     * walls[5] denotes front wall
     * walls[3] denotes right wall
     * walls[0] denotes back wall
     * walls[4] denotes down wall
     */
    int order[] = {2, 1, 5, 3, 0, 4};

    rotate_by_angle(walls, order, layers, angle);

    rotate_wall_upside_down(walls[0]);
    rotate_wall_right(walls[1]);
    rotate_wall_left(walls[3]);
    rotate_wall_upside_down(walls[4]);
}

void rotate(char walls[][SIZE][SIZE], char front, int layers, char angle) {
    if (layers == 0) {
        layers = 1; // not given number of layers means number of layers is 1
    }

    switch (front) {
        case 'u':
            rotate_with_upper_as_front(walls, layers, angle);
            break;
        case 'l':
            rotate_with_left_as_front(walls, layers, angle);
            break;
        case 'f':
            rotate_with_front_as_front(walls, layers, angle);
            break;
        case 'r':
            rotate_with_right_as_front(walls, layers, angle);
            break;
        case 'b':
            rotate_with_back_as_front(walls, layers, angle);
            break;
        case 'd':
            rotate_with_down_as_front(walls, layers, angle);
            break;
    }
}