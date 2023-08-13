#include "game.h"

int main() {
    game_t game = create_game(20, 10);
    print_game(game);

    destroy_game(game);
    
    return 0;
}
