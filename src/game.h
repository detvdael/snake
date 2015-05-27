#ifndef __GAME_H__
#define __GAME_H__

#include <ncurses.h>

typedef enum {LEFT, RIGHT, UP, DOWN} direction;
const int x_dir[4] = {-1, 1, 0, 0};
const int y_dir[4] = {0, 0, -1, 1};

typedef struct snake_part {
    int x, y;
    struct snake_part* tail;
}snake_part;

typedef struct food {
    int x, y;
}food;

//pop off and free the last tail element
void pop_bottom(snake_part *queue);

void free_snake(snake_part *snake);

void draw_borders(WINDOW *p_win);
void draw_score(WINDOW *p_win, int score);

//returns if the snake eats itself or not
int draw_snake(WINDOW *p_win, snake_part *snake);
//makes sure food doesn't get drawn on top of the snake
void draw_food(WINDOW *p_win, food *food, snake_part *snake);

#endif
