#include <stdlib.h>
#include <stdio.h>

#include "game.h"

#define WHITE_BG "\x1b[47m"
#define BLACK_FG "\x1b[30m"
#define RED_BG   "\x1b[41m"
#define RESET    "\x1b[0m"

struct game_s {
    char** board;
    size_t x_dim;
    size_t y_dim;
    unsigned int cursor_x;
    unsigned int cursor_y;
};

game_t create_game(unsigned int x_dim, unsigned int y_dim) {
    game_t game = malloc(sizeof(struct game_s));
    game->board = calloc(sizeof(char*), x_dim);

    for (size_t i = 0; i < x_dim; ++i) 
        (game->board)[i] = calloc(sizeof(char), y_dim);

    game->x_dim = x_dim;
    game->y_dim = y_dim;

    // yeah yeah i know it is unsigned
    game->cursor_x = -1;
    game->cursor_y = -1;

    return game;    
}

void print_game(game_t game) {
    for (size_t j = 0; j < game->y_dim; ++j) {
        for (size_t i = 0; i < game->x_dim; ++i) {
            if (game->cursor_x == i && game->cursor_y == j)
                printf(RED_BG);
            
            if ((game->board)[i][j]) {
                printf(WHITE_BG BLACK_FG "X");
            } else {
                printf("O");
            }

            printf(RESET " ");
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
            unsigned char neigh = 0;
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

void set_cursor(game_t game, unsigned int x, unsigned int y) {
    game->cursor_x = x;
    game->cursor_y = y;
}

void move_cursor(game_t game, char dir) {
    switch (dir) {
    case UP:
        game->cursor_y = (game->cursor_y ? game->cursor_y : game->y_dim) - 1;
        break;
    case RIGHT:
        game->cursor_x = (game->cursor_x + 1) % game->x_dim;
        break;
    case DOWN:
        game->cursor_y = (game->cursor_y + 1) % game->y_dim;
        break;
    case LEFT: 
        game->cursor_x = (game->cursor_x ? game->cursor_x : game->x_dim) - 1;
        break;
    }
}

void swap_cell(game_t game) {
    unsigned int x = game->cursor_x;
    unsigned int y = game->cursor_y;

    if (x < game->x_dim && y < game->y_dim) 
        (game->board)[x][y] = !(game->board)[x][y];
}
