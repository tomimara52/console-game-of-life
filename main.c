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

    thrd_t input_thread;
    char input = 0;

    thrd_create(&input_thread, (thrd_start_t)getInput, &input);

    set_cursor(game, 0, 0);

    while (input != 'r') {
        switch (input) {
        case 'w':
            move_cursor(game, UP);
            break;
        case 'a':
            move_cursor(game, LEFT);
            break;
        case 's':
            move_cursor(game, DOWN);
            break;
        case 'd':
            move_cursor(game, RIGHT);
            break;
        case ' ':
            swap_cell(game);
            break;
        }
        // clear terminal
        printf("\033c");

        print_game(game);

        input = 0;
        usleep(100 * 1000);
    }

    set_cursor(game, -1, -1);
    input = 0;

    char pause = 0;
    
    while (input != 'q') {
        if (input == 'p')
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
