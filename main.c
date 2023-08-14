#include <stdio.h>
#include <unistd.h>
#include <termios.h> 
#include <threads.h>

#include "game.h"

#define SLEEP_TIME 100000

int getInput(char* res) {
    while (*res != 'q') {
        *res = getchar();
    }

    thrd_exit(0);
}

game_t read_game_from_file(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("ERROR: file nonexistent\n");
        return NULL;
    }


    unsigned int x_dim, y_dim;
    fscanf(fp, "%ux%u", &x_dim, &y_dim);

    game_t game = create_game(x_dim, y_dim);

    while (!feof(fp)) {
        unsigned int x, y;
        fscanf(fp, "%u,%u", &x, &y);
        set_game(game, x, y); 
    }

    fclose(fp);
    
    return game;
}

game_t create_game_interactive() {
    unsigned int x_dim, y_dim;
    printf("Type the x dimension of the board: ");
    scanf("%u", &x_dim);
    printf("Type the y dimension of the board: ");
    scanf("%u", &y_dim);
    return create_game(x_dim, y_dim); 
}

int main(int argc, char** argv) {

    game_t game;
    if (argc == 1) {
        game = create_game_interactive();
    } else {
        game = read_game_from_file(argv[1]);
        if (!game) 
            game = create_game_interactive();
    }

    static struct termios oldt, newt;

    // copy current attributes to oldt
    tcgetattr(STDIN_FILENO, &oldt);

    newt = oldt;

    // do not wait for EOF or newline and don't print input chars
    newt.c_lflag &= ~(ICANON | ECHO);          

    // set newt settings to stdin now
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

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
        usleep(SLEEP_TIME);
    }

    set_cursor(game, -1, -1);

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
        usleep(SLEEP_TIME);
    }

    thrd_detach(input_thread);

    destroy_game(game);

    // reset stdin settings to before
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
