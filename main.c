#include "game.h"

int main() {
    game_t game = create_game(20, 20);

    set_game(game, 10, 10);
    
    print_game(game);

    destroy_game(game);
    
    return 0;
}
