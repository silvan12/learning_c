#include <stdlib.h> // rand
#include <stdio.h> // printf
#include <time.h> // time
#include <string.h> // strcmp

const char options[3][8] = {"Rock", "Paper", "Scissor"};

// Min and max are both inclusive
int random_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int logic(char player_pick[], int ai_pick){
    if (!strcmp(player_pick, options[0])){
        // Player: Rock
        switch (ai_pick){
        case 0: // Rock
            return 0;
        case 1: // Paper
            return -1;
        case 2: // Scissor
            return 1;
        }
    }
    if (!strcmp(player_pick, options[1])){
        // Player: Paper
        switch (ai_pick){
        case 0: // Rock
            return 1;
        case 1: // Paper
            return 0;
        case 2: // Scissor
            return -1;
        }
    }
    if (!strcmp(player_pick, options[2])){
        // Player: Scissor
        switch (ai_pick){
        case 0: // Rock
            return -1;
        case 1: // Paper
            return 1;
        case 2: // Scissor
            return 0;
        }
    }
    else {
        // Player: Invalid input
        return -2;
    }
}

int main()
{
    // Set random seed
    srand(time(NULL));

    int ai_pick = random_int(0, 2);
    char player_pick[9];

    printf("%s %s %s!\n>", options[0], options[1], options[2]);
    scanf("%s", &player_pick);

    printf("AI picked: %s\n", options + ai_pick);

    int result = logic(player_pick, ai_pick);

    switch (result){
    case -1:
        printf("You lose!\n");
        break;
    case 0:
        printf("It's a draw!\n");
        break;
    case 1:
        printf("You win!\n");
        break;
    case -2:
        printf("Invalid input!\n");
        break;
    }

    // Clear buffer
    while (getchar() != '\n');

    char play_again;

    printf("Would you like to play again? (y/N)\n>");
    scanf("%c", &play_again); // bug

    if (play_again == 'y'){
        return main();
    }

    return 0;
}