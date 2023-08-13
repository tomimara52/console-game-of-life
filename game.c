#include <stdlib.h>
#include <stdio.h>

#include "game.h"

struct game_s {
    char** board;
    size_t x_dim;
    size_t y_dim;
};

game_t create_game(unsigned int x_dim, unsigned int y_dim) {
    game_t game = malloc(sizeof(struct game_s));
    game->board = calloc(sizeof(char*), x_dim);

    for (size_t i = 0; i < x_dim; ++i) 
        (game->board)[i] = calloc(sizeof(char), y_dim);

    game->x_dim = x_dim;
    game->y_dim = y_dim;

    return game;    
}

void print_game(game_t game) {
    for (size_t j = 0; j < game->y_dim; ++j) {
        for (size_t i = 0; i < game->x_dim; ++i) {
            char c = ((game->board)[i][j]) ? 'X' : 'O';
            printf("%c ", c);
        }
        printf("\n");
    }
}

void destroy_game(game_t game) {
    for (size_t i = 0; i < game->x_dim; ++i) {
        free((game->board)[i]);
    }

    free(game->board);

    free(game);
}

void set_game(game_t game, unsigned int x_pos, unsigned int y_pos) {
    (game->board)[x_pos][y_pos] = 1;
}
/*
void step_game(game_t game) {

}
*/
