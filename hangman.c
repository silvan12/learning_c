#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define MAX_WORD_LEN 10

#define LIVES 10
#define MAX_GUESSES 1024

int lives;
char word[MAX_WORD_LEN];

void pick_word(char* file_path)
{
    FILE* file = fopen(file_path, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s: %s\n", file_path, strerror(errno));
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = malloc(size);

    fread(data, size, 1, file);
    fclose(file);
    
    size_t word_count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (data[i] == '\n')
        {
            word_count++;
        }
    }

    size_t word_index = rand() % word_count;

    word_count = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (word_count == word_index)
        {
            int offset = 0;
            while (data[i] != '\n' && data[i] != '\r')
            {
                word[offset] = data[i];

                offset++;
                i++;
            }
            word[offset] = 0;
            break;
        }

        if (data[i] == '\n')
        {
            word_count++;
        }
    }

    free(data);
}

char read_char()
{
 
    char c;

    scanf("%c", &c);

    while (getchar() != '\n');

    return c;
}

void get_letter(char letters[MAX_GUESSES])
{
    char letter;

    while (true)
    {
        // Take input
        printf("Guess a letter:\n> ");
        letter = read_char();

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

bool check(const char *word, char guessed_letters[MAX_GUESSES])
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

int main(int argc, char **argv)
{
    system("cls");

    // Random seed
    srand(time(NULL));

    lives = LIVES;

    pick_word(argv[1]);
    char guessed_letters[MAX_GUESSES];
    memset(guessed_letters, 0, MAX_GUESSES);

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
        printf("\nYou lose! The word was %s\n\n", word);
    }

    while (true)
    {
        printf("Would you like to play again? (y/n) ");

        char play_again = read_char();
        if (play_again == 'y')
        {
            return main(argc, argv);
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