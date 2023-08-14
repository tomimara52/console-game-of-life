#include <stdio.h>
#include <unistd.h>
#include <termios.h> 
#include <threads.h>

#include "game.h"

int getInput(char* res) {
    while (*res != 'q') {
        *res = getchar();
    }

    thrd_exit(0);
}

int main() {
    static struct termios oldt, newt;

    // copy current attributes to oldt
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;

    // do not wait for EOF or newline and don't print input chars
    newt.c_lflag &= ~(ICANON | ECHO);          

    // set newt settings to stdin now
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    game_t game = create_game(36, 36);

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

    thrd_t input_thread;
    char input = 0;

    thrd_create(&input_thread, (thrd_start_t)getInput, &input);

    char pause = 0;
    
    while (1) {
        if (input == 'q')
            break;
        else if (input == 'p') 
            pause = !pause;

        // clear terminal
        printf("\033c");

        if (!pause || input == 'n')
            step_game(game);

        print_game(game);

        input = 0;
        usleep(100 * 1000);
    }

    thrd_detach(input_thread);

    destroy_game(game);

    // reset stdin settings to before
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
