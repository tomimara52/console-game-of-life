#include "game.h"

int main() {
    game_t game = create_game(36, 9);

    set_game(game, 24, 0);
    set_game(game, 22, 1);
    set_game(game, 24, 1);
    set_game(game, 12, 2);
    set_game(game, 13, 2);
    set_game(game, 20, 2);
    set_game(game, 21, 2);
    set_game(game, 34, 2);
    set_game(game, 35, 2);
    set_game(game, 11, 3);
    set_game(game, 15, 3);
    set_game(game, 20, 3);
    set_game(game, 21, 3);
    set_game(game, 34, 3);
    set_game(game, 35, 3);
    set_game(game, 0, 4);
    set_game(game, 1, 4);
    set_game(game, 10, 4);
    set_game(game, 16, 4);
    set_game(game, 20, 4);
    set_game(game, 21, 4);
    set_game(game, 0, 5);
    set_game(game, 1, 5);
    set_game(game, 10, 5);
    set_game(game, 14, 5);
    set_game(game, 16, 5);
    set_game(game, 17, 5);
    set_game(game, 22, 5);
    set_game(game, 24, 5);
    set_game(game, 10, 6);
    set_game(game, 16, 6);
    set_game(game, 24, 6);
    set_game(game, 11, 7);
    set_game(game, 15, 7);
    set_game(game, 12, 8);
    set_game(game, 13, 8);
    
    print_game(game);

    destroy_game(game);
    
    return 0;
}
