#pragma once

typedef struct game_s* game_t;

game_t create_game(unsigned int width, unsigned int height);

void print_game(game_t game);

void destroy_game(game_t game);

void set_game(game_t game, unsigned int x_pos, unsigned int y_pos);
