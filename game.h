#pragma once

typedef struct game_s* game_t;

game_t create_game(unsigned int x_dim, unsigned int y_dim);

void print_game(game_t game);

void destroy_game(game_t game);

void step_game(game_t game);

void set_game(game_t game, unsigned int x_pos, unsigned int y_pos);
