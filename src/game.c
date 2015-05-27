#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"

int main(){
    int ch, p_height, p_width;
    int score = 0;
    int quit = 0;
    WINDOW *p_win;
    direction dir = RIGHT;
    direction current_dir = RIGHT;
    snake_part *head, *ptr, *n_head;
    food *food;
    srand(time(NULL));

    //initialize ncurses
    initscr();
    cbreak();   //line buffering disabled
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    //initialize windows
    p_height = LINES-2;
    p_width = COLS-2;
    p_win = newwin(p_height, p_width, 1, 1);

    draw_borders(p_win);

    //initialize snake
    head = malloc(sizeof(snake_part));
    head->x = 6;
    head->y = 1;
    ptr = head;
    for(int i = 5; i > 0; --i){
        snake_part *tail = malloc(sizeof(snake_part));
        tail->x = i;
        tail->y = 1;
        ptr->tail = tail;
        ptr = ptr->tail;
    }
    
    //initialize food
    food = malloc(sizeof(food));
    food->x = (rand() % (p_width - 2)) + 1;
    food->y = (rand() % (p_height - 2)) + 1;

    //draw initial snake & food
    draw_snake(p_win, head);
    draw_food(p_win, food, head);

    //draw initial score
    draw_score(stdscr, score);

    wrefresh(p_win);

    //game loop
    timeout(100);   //loop doesn't wait for keyboard input
    
    while(!quit){
        ch = getch();
        switch(ch){
            case KEY_LEFT:
                if(current_dir != RIGHT){
                    dir = LEFT;
                }
                break;
            case KEY_RIGHT:
                if(current_dir != LEFT){
                    dir = RIGHT;
                }
                break;
            case KEY_UP:
                if(current_dir != DOWN){
                    dir = UP;
                }
                break;
            case KEY_DOWN:
                if(current_dir != UP){
                    dir = DOWN;
                }
                break;
            case 113:   //q -> quit
                quit = 1;
                break;
            default:
                break;
        }
        current_dir = dir;

        werase(p_win);
        //Snake logic
        n_head = malloc(sizeof(snake_part));
        n_head->x = head->x + x_dir[dir];
        n_head->y = head->y + y_dir[dir];
        n_head->tail = head;
        head = n_head;
        if(head->x == food->x && head->y == food->y){
            food->x = (rand() % (p_width - 2)) + 1;
            food->y = (rand() % (p_height - 2)) + 1;
            score += 10;
        } else {
            pop_bottom(head);
        }

        if(head->x >= p_width-1 || head->x <= -1 || head->y >= p_height-1 || 
                head->y <= -1 || !draw_snake(p_win, head)){
            quit = 1; 
        }
        draw_food(p_win, food, head);
        draw_borders(p_win);
        draw_score(stdscr, score);
        wnoutrefresh(p_win);
        doupdate();
    }
    
    free_snake(head);
    free(food);
    endwin();
    return 0;
}

void pop_bottom(snake_part* queue){
    snake_part *head = queue;
    if(head->tail != NULL){
        snake_part *current = head->tail;
        while(current->tail != NULL){
            head = current;
            current = current->tail;
        }
        free(head->tail);
        head->tail = NULL;
    }
}

void free_snake(snake_part *snake){
    while(snake->tail != NULL){
        pop_bottom(snake);
    }
    free(snake);
}

void draw_borders(WINDOW *p_win) {
    int x, y, i;
    getmaxyx(p_win, y, x);
    // 4 corners
    mvwprintw(p_win, 0, 0, "+");
    mvwprintw(p_win, y - 1, 0, "+");
    mvwprintw(p_win, 0, x - 1, "+");
    mvwprintw(p_win, y - 1, x - 1, "+");
    // sides
    for (i = 1; i < (y - 1); i++) {
        mvwprintw(p_win, i, 0, "|");
        mvwprintw(p_win, i, x - 1, "|");
    }
    // top and bottom
    for (i = 1; i < (x - 1); i++) {
        mvwprintw(p_win, 0, i, "-");
        mvwprintw(p_win, y - 1, i, "-");
    }
}

void draw_score(WINDOW *p_win, int score){
    //calc length of score
    int digits = score == 0 ? 1 : (int)floor(log10(abs(score))) + 1;
    werase(p_win);
    attron(COLOR_PAIR(1));
    mvwprintw(p_win, 0, COLS-(digits + 9), " Score: %d", score);
    attroff(COLOR_PAIR(1));

    mvwprintw(p_win, 0, 0,  " Press q to quit");
    wnoutrefresh(p_win);
}

int draw_snake(WINDOW *p_win, snake_part *snake){
    snake_part *head = snake;
    snake_part *ptr = snake;
    while(ptr != NULL){
        if(ptr->x == head->x && ptr->y == head->y && ptr != head){
            return 0;
        }
        mvwaddch(p_win, ptr->y, ptr->x, '#');
        ptr = ptr->tail;
    }
    return 1;
}

void draw_food(WINDOW *p_win, food *food, snake_part *snake){
    int overlap = 0;
    int w_x, w_y;
    snake_part *ptr = snake;
    while(ptr != NULL){
        if(ptr->x == food->x && ptr->y == food->y){
            overlap = 1;
            break;
        }
        ptr = ptr->tail;
    }
    if(overlap){
        srand(time(NULL));
        getmaxyx(p_win, w_y, w_x);
        food->x = (rand() % (w_x - 2)) + 1;
        food->y = (rand() % (w_y - 2)) + 1;
        draw_food(p_win, food, snake);
    }
    mvwaddch(p_win, food->y, food->x, 'o');
}
