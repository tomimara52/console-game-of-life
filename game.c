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
    game->board = calloc(sizeof(char[height]), width);

    for (size_t i = 0; i < width; ++i) 
        (game->board)[i] = calloc(sizeof(char), height);

    game->width = width;
    game->height = height;

    return game;    
}

void print_game(game_t game) {
    for (size_t i = 0; i < game->width; ++i) {
        for (size_t j = 0; j < game->height; ++j) {
            char c = ((game->board)[i][j]) ? 'X' : 'O';
            printf("%c", c);
        }
        printf("\n");
    }
}

void destroy_game(game_t game) {
    for (size_t i = 0; i < game->width; ++i) {
        free((game->board)[i]);
    }

    free(game->board);

    free(game);
}
