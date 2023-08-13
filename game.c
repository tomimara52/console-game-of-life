#include <stdlib.h>
#include <stdio.h>

#include "game.h"

#define WHITE_BG "\x1b[47m"
#define BLACK_FG "\x1b[30m"
#define RESET    "\x1b[0m"

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
            if ((game->board)[i][j]) {
                printf(WHITE_BG BLACK_FG "X" RESET " ");
            } else {
                printf("O ");
            }
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
