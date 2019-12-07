
#include <stdio.h>

#ifndef N
#define N 5
#endif

void swap(char* a, char* b){
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void inverse_row(char row[N]){
	for(int i = 0, j = N-1; i < j; i++, j--){
		swap(&row[i], &row[j]);
	}
}

void swap_and_inverse_rows(char row1[N], char row2[N]){
	for(int i = 0, j = N-1; i < N && j >= 0; i++, j--){
		swap(&row1[i], &row2[j]);
	}
}

void swap_and_inverse_columns(char wall1[][N], int col1, char wall2[][N], int col2){
	for(int i = 0, j = N-1; i < N && j >= 0; i++, j--){
		swap(&wall1[i][col1], &wall2[j][col2]);
	}
}

void rotate_wall_left(char wall[][N]){
	for(int i = 0; i < N/2; i++){
		for(int j = i; j < N-1-i; j++){
			char tmp = wall[i][j];
			wall[i][j] = wall[j][N-1-i];
			wall[j][N-1-i] = wall[N-1-i][N-1-j];
			wall[N-1-i][N-1-j] = wall[N-1-j][i];
			wall[N-1-j][i] = tmp;
		}
	}
}

void rotate_wall_right(char wall[][N]){
	for(int i = 0; i < N/2; i++){
		for(int j = i; j < N-1-i; j++){
			char tmp = wall[i][j];
			wall[i][j] = wall[N-1-j][i];
			wall[N-1-j][i] = wall[N-1-i][N-1-j];
			wall[N-1-i][N-1-j] = wall[j][N-1-i];
			wall[j][N-1-i] = tmp;
		}
	}
}

void rotate_wall_upside_down(char wall[][N]){
	int i = 0, j = N-1;
	while(i < j){
		swap_and_inverse_rows(wall[i], wall[j]);
		i++, j--;
	}
	if(i == j){
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
void rotate_layer_left(char walls[][N][N] , int order[6], int layer){
	int upper = order[0];
	int left = order[1];
	int right = order[3];
	int down = order[5];
	
	for(int i = 0; i < N; i++){
		char tmp = walls[upper][N-layer][i];
		walls[upper][N-layer][i] = walls[right][i][layer-1];
		walls[right][i][layer-1] = walls[down][layer-1][N-1-i];
		walls[down][layer-1][N-1-i] = walls[left][N-1-i][N-layer];
		walls[left][N-1-i][N-layer] = tmp;
	}
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
void rotate_left(char walls[][N][N], int order[6], int layers){
	int front = order[2];
	int back = order[4];
	
	rotate_wall_left(walls[front]);
	
	for(int i = 1; i <= layers; i++){
		rotate_layer_left(walls, order, i);
	}
	
	if(layers == N){
		rotate_wall_right(walls[back]);
	}
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
void rotate_layer_right(char walls[][N][N] , int order[6], int layer){
	int upper = order[0];
	int left = order[1];
	int right = order[3];
	int down = order[5];
	
	for(int i = 0; i < N; i++){
		char tmp = walls[upper][N-layer][i];
		walls[upper][N-layer][i] = walls[left][N-1-i][N-layer];
		walls[left][N-1-i][N-layer] = walls[down][layer-1][N-1-i];
		walls[down][layer-1][N-1-i] = walls[right][i][layer-1];
		walls[right][i][layer-1] = tmp;
	}
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
void rotate_right(char walls[][N][N], int order[6], int layers){
	int front = order[2];
	int back = order[4];
	
	rotate_wall_right(walls[front]);
	
	for(int i = 1; i <= layers; i++){
		rotate_layer_right(walls, order, i);
	}
	
	if(layers == N){
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
void rotate_layer_upside_down(char walls[][N][N] , int order[6], int layer){
	int upper = order[0];
	int left = order[1];
	int right = order[3];
	int down = order[5];
	
	swap_and_inverse_rows(walls[upper][N-layer], walls[down][layer-1]);
	swap_and_inverse_columns(walls[left], N-layer, walls[right], layer-1);
}

/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
void rotate_upside_down(char walls[][N][N], int order[6], int layers){
	int front = order[2];
	int back = order[4];
	
	rotate_wall_upside_down(walls[front]);
	
	for(int i = 1; i <= layers; i++){
		rotate_layer_upside_down(walls, order, i);
	}
	
	if(layers == N){
		rotate_wall_upside_down(walls[back]);
	}
}

void init_cube(char walls[][N][N]){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < N; j++){
			for(int k = 0; k < N; k++){
				walls[i][j][k] = (char) ('0' + i);
			}
		}
	}
}

void display_row(char row[N]){
	for(int i = 0; i < N; i++){
		printf("%c", row[i]);
	}
}

void display_wall(char wall[][N]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N + 1; j++){
			printf(" ");
		}
		display_row(wall[i]);
		printf("\n");
	}
}

void display_cube(char walls[][N][N]){
	printf("\n");
	display_wall(walls[0]);
	
	for(int i = 0; i < N; i++){
		for(int w = 1; w < 4; w++){
			display_row(walls[w][i]);
			printf("|");
		}
		display_row(walls[4][i]);
		printf("\n");
	}
	
	display_wall(walls[5]);
}


/* walls[order[0]] denotes upper wall
 * walls[order[1]] denotes left wall
 * walls[order[2]] denotes front wall
 * walls[order[3]] denotes right wall
 * walls[order[4]] denotes back wall
 * walls[order[5]] denotes down wall
 */
void rotate_by_angle(char walls[][N][N], int order[6], int layers, char angle){
	switch(angle){
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
void rotate_with_upper_as_front(char walls[][N][N], int layers, char angle){
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
void rotate_with_left_as_front(char walls[][N][N], int layers, char angle){
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
void rotate_with_front_as_front(char walls[][N][N], int layers, char angle){
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
void rotate_with_right_as_front(char walls[][N][N], int layers, char angle){
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
void rotate_with_back_as_front(char walls[][N][N], int layers, char angle){
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
void rotate_with_down_as_front(char walls[][N][N], int layers, char angle){
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

void rotate(char walls[][N][N], char front, int layers, char angle){
	if(layers == 0){
		layers = 1; // not given number of layers means number of layers is 1
	}
	
	switch(front){
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

void execute_when_newline(char walls[][N][N], char* front, int* layers, char* angle){
	if(*front != 0){
		rotate(walls, *front, *layers, *angle); // execute previous command
	}
	
	// set program state for new command
	*front = 0;
	*layers = 0;
	*angle = 0;
	
	display_cube(walls);
}

void execute_when_letter(char walls[][N][N], int c, char* front, int* layers, char* angle){
	if(*front != 0){
		rotate(walls, *front, *layers, *angle); // execute previous command
	}
	
	// update program state
	*front = (char) c;
	*layers = 0;
	*angle = 0;
}

int execute_when_digit(int c, int layers){
	return layers * 10 + (c - '0');
}

void execute_when_quote(char walls[][N][N], int c, char* front, int* layers, char* angle){
	*angle = (char) c;
	
	rotate(walls, *front, *layers, *angle);
	
	// set program state for new command
	*front = 0;
	*layers = 0;
	*angle = 0;
}

void read_data(char walls[][N][N]){
	char front = 0;
	int layers = 0;
	char angle = 0;
	
	int c = getchar();
	while(c != '.'){
		if(c == '\n'){
			execute_when_newline(walls, &front, &layers, &angle);
		} else if('a' <= c && c <= 'z'){
			execute_when_letter(walls, c, &front, &layers, &angle);
		} else if('0' <= c && c <= '9'){
			layers = execute_when_digit(c, layers);
		} else {
			execute_when_quote(walls, c, &front, &layers, &angle);
		}
		c = getchar();
	}
}

int main(){
	char walls[6][N][N];
	init_cube(walls);
	read_data(walls);
	return 0;
}
