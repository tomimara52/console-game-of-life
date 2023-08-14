#pragma once

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

typedef struct game_s* game_t;

game_t create_game(unsigned int x_dim, unsigned int y_dim);

void print_game(game_t game);

void destroy_game(game_t game);

void step_game(game_t game);

void set_game(game_t game, unsigned int x_pos, unsigned int y_pos);

void set_cursor(game_t game, unsigned int x, unsigned int y);

void move_cursor(game_t game, char dir);
