#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h> 
#include <threads.h>

#include "game.h"

#define SLEEP_TIME 100000

struct input_args {
    char* input;
    char exit_char;
};

int getInput(struct input_args* args) {
    while (*(args->input) != args->exit_char) {
        *(args->input) = getchar();
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

void maybe_save_game(game_t game) {
    char choice;
    do {
        printf("Do you want to save this game to a file? [y/n]: ");
        scanf("%s", &choice);
    } while (choice != 'y' && choice != 'n');

    if (choice == 'n')
        return;

    char filename[256];
    printf("What do you want the file to be named? ");
    scanf("%s", filename);

    game_to_file(game, filename);    
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
    char input;
    struct input_args* args = malloc(sizeof(struct input_args));
    args->input = &input;
    args->exit_char = 'r';

    thrd_create(&input_thread, (thrd_start_t)getInput, args);

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

    thrd_detach(input_thread);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    maybe_save_game(game);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    set_cursor(game, -1, -1);

    char pause = 0;

    args->exit_char = 'q';

    thrd_create(&input_thread, (thrd_start_t)getInput, args);
    
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

    free(args);

    destroy_game(game);

    // reset stdin settings to before
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
