#include <stdlib.h>
#include <stdio.h>

#include "game.h"

struct game_s {
    char** board;
    size_t width;
    size_t height;
};

game_t create_game(unsigned int width, unsigned int height) {
    game_t game = malloc(sizeof(struct game_s));
    game->board = calloc(sizeof(char[width]), height);

    for (size_t i = 0; i < height; ++i) 
        (game->board)[i] = calloc(sizeof(char), width);

    game->width = width;
    game->height = height;

    return game;    
}

void print_game(game_t game) {
    for (size_t i = 0; i < game->height; ++i) {
        for (size_t j = 0; j < game->width; ++j) {
            char c = ((game->board)[i][j]) ? 'X' : 'O';
            printf("%c ", c);
        }
        printf("\n");
    }
}

void destroy_game(game_t game) {
    for (size_t i = 0; i < game->height; ++i) {
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
