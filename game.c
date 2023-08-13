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

char** copy_board(game_t game) {
    char** board = calloc(sizeof(char*), game->x_dim);

    for (size_t i = 0; i < game->x_dim; ++i) {
        board[i] = calloc(sizeof(char), game->y_dim);
        for (size_t j = 0; j < game->y_dim; ++j) {
            board[i][j] = (game->board)[i][j];
        }
    }

    return board;
}

void step_game(game_t game) {
    char** board = copy_board(game);
    for (size_t x = 0; x < game->x_dim; ++x) {
        for (size_t y = 0; y < game->y_dim; ++y) {
            unsigned int neigh = 0;
            if (x > 0) {
                neigh += board[x-1][y];
                if (y > 0) 
                    neigh += board[x-1][y-1];
                if (y < game->y_dim - 1) 
                    neigh += board[x-1][y+1];
            }

            if (y > 0) 
                neigh += board[x][y-1];
            if (y < game->y_dim - 1) 
                neigh += board[x][y+1];

            if (x < game->x_dim - 1) {
                neigh += board[x+1][y];
                if (y > 0) 
                    neigh += board[x+1][y-1];
                if (y < game->y_dim - 1) 
                    neigh += board[x+1][y+1];
            }

            if (!board[x][y] && neigh == 3)
                (game->board)[x][y] = 1;
            else if (board[x][y] && (neigh < 2 || neigh > 3))
                (game->board)[x][y] = 0;
        }
    }

    for (size_t i = 0; i < game->x_dim; ++i) {
        free(board[i]);
    }

    free(board);

}
