#pragma once

typedef struct game_s* game_t;

game_t create_game(unsigned int width, unsigned int height);

void print_game(game_t game);

void destroy_game(game_t game);
