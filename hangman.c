#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define LIVES 10
#define LETTER_COUNT 26

int lives;

const char words[10][10] = {"apple", "tree", "gun", "blue", "berry", "game", "program", "hunt", "banana"};

char read_char()
{
    char c;

    scanf("%c", &c);

    while (getchar() != '\n')
        ;

    return c;
}

void get_letter(char letters[LETTER_COUNT])
{
    char letter;

    while (true)
    {
        // Take input
        printf("Guess a letter:\n> ");
        letter = read_char();

        // TODO: Check if letter is already guessed
        bool already_guessed = false;
        for (int i = 0; i < strlen(letters); i++)
        {
            if (letters[i] == letter)
            {
                already_guessed = true;
                break;
            }
        }

        if (already_guessed)
        {
            printf("Letter %c has already been guessed\n", letter);
        }
        else
        {
            break;
        }
    }

    int n = strlen(letters);
    letters[n] = letter;
}

const char *pick_word()
{
    // Random number from 0 to 8
    int ai_pick = rand() % 8;

    return words[ai_pick];
}

bool check(const char *word, char guessed_letters[LETTER_COUNT])
{
    int len = strlen(word);
    int len2 = strlen(guessed_letters);

    bool last_letter_correct = false;
    bool word_correct = true;

    for (int i = 0; i < len; i++)
    {
        bool letter_correct = false;
        for (int j = 0; j < len2; j++)
        {
            if (word[i] == guessed_letters[j])
            {
                if (guessed_letters[j] == guessed_letters[len2 - 1])
                {
                    last_letter_correct = true;
                }

                printf("%c ", word[i]);
                letter_correct = true;
                break;
            }
        }

        if (!letter_correct)
        {
            printf("_ ");

            word_correct = false;
        }
    }
    printf("\n");

    if (!last_letter_correct && len2 > 0)
    {
        lives--;
    }

    printf("Guessed letters: ");
    for (int i = 0; i < strlen(guessed_letters); i++)
    {
        printf("%c ", guessed_letters[i]);
    }
    printf("\n");

    printf("Lives remaining: %d\n\n", lives);

    return word_correct;
}

int main()
{
    system("cls");

    // Random seed
    srand(time(NULL));

    lives = LIVES;

    const char *word = pick_word();
    char guessed_letters[LETTER_COUNT];
    memset(guessed_letters, 0, LETTER_COUNT);

    bool win = true;
    while (!check(word, guessed_letters))
    {
        if (lives <= 0)
        {
            win = false;
            break;
        }

        get_letter(guessed_letters);

        system("cls");
    }

    if (win)
    {
        printf("\nYou win!\n\n");
    }
    else
    {
        printf("\nYou lose! The word was: %s\n\n", word);
    }

    while (true)
    {
        printf("Would you like to play again? (y/n) ");

        char play_again = read_char();
        if (play_again == 'y')
        {
            return main();
        }
        else if (play_again == 'n')
        {
            break;
        }
        else
        {
            system("cls");
            printf("Input invalid. Please try again.\n");
        }
    }

    return 0;
}