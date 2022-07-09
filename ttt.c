#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define TILE_EMPTY '.'
#define TILE_ONE   'O'
#define TILE_TWO   'X'

#define STATE_DRAW    0
#define STATE_ONGOING 1
#define STATE_WIN_ONE 2
#define STATE_WIN_TWO 3

#define KEY_UNKNOWN 0
#define KEY_UP      1
#define KEY_LEFT    2
#define KEY_DOWN    3
#define KEY_RIGHT   4
#define KEY_SUBMIT  5
#define KEY_QUIT    6

typedef struct
{
    int x;
    int y;
} Point;

char board[3][3];
Point cursor_pos;
bool turn = true;
int state;

int get_winner(char tile)
{
    switch (tile)
    {
    case TILE_ONE:
        return STATE_WIN_ONE;
    case TILE_TWO:
        return STATE_WIN_TWO;
    }

    return STATE_ONGOING;
}

int calculate_state()
{
    // 2 diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != TILE_EMPTY)
    {
        return get_winner(board[0][0]);
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != TILE_EMPTY)
    {
        return get_winner(board[0][2]);
    }

    // 3 vertical
    for (int y = 0; y < 3; y++)
    {
        if (board[y][0] == board[y][1] && board[y][1] == board[y][2] && board[y][2] != TILE_EMPTY)
        {
            return get_winner(board[y][0]);
        }
    }

    // 3 horizontal
    for (int x = 0; x < 3; x++)
    {
        if (board[0][x] == board[1][x] && board[1][x] == board[2][x] && board[2][x] != TILE_EMPTY)
        {
            return get_winner(board[0][x]);
        }
    }

    bool draw = true;
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (board[y][x] == TILE_EMPTY){
                draw = false;

                break;
            }
        }

        if (!draw)
        {
            break;
        }
    }

    if (draw)
    {
        return STATE_DRAW;
    }

    return STATE_ONGOING;
}

int read_key(bool is_special)
{
    int key = _getch();

    if (!is_special)
    {
        switch (key)
        {
        case 0:
            return read_key(true);
        case 27:
            exit(1);
        case 13: // Enter
            return KEY_SUBMIT;
        case 119: // W
            return KEY_UP;
        case 97: // A
            return KEY_LEFT;
        case 115: // S
            return KEY_DOWN;
        case 100: // D
            return KEY_RIGHT;
        }
    }
    else
    {
        switch (key)
        {
        case 72: // Arrow up
            return KEY_UP;
        case 75: // Arrow left
            return KEY_LEFT;
        case 80: // Arrow down
            return KEY_DOWN;
        case 77: // Arrow right
            return KEY_RIGHT;
        }
    }

    return KEY_UNKNOWN;
}

bool move_cursor()
{
    int key = read_key(false);

    switch (key)
    {
    case KEY_UP:
        cursor_pos.y--;
        break;
    case KEY_LEFT:
        cursor_pos.x--;
        break;
    case KEY_DOWN:
        cursor_pos.y++;
        break;
    case KEY_RIGHT:
        cursor_pos.x++;
        break;
    case KEY_SUBMIT:
        return board[cursor_pos.y][cursor_pos.x] == TILE_EMPTY;
    }

    // Clamp cursor pos
    if (cursor_pos.x < 0)
    {
        cursor_pos.x = 0;
    }
    else if (cursor_pos.x > 2)
    {
        cursor_pos.x = 2;
    }
    if (cursor_pos.y < 0)
    {
        cursor_pos.y = 0;
    }
    else if (cursor_pos.y > 2)
    {
        cursor_pos.y = 2;
    }

    return false;
}

void reset_cursor()
{
    cursor_pos.x = 0;
    cursor_pos.y = 0;
}

void reset_board()
{
    memset(board, TILE_EMPTY, 3 * 3);
}

void reset_game()
{
    state = STATE_ONGOING;

    reset_cursor();

    reset_board();
}

char get_turn_char()
{
    return turn ? TILE_ONE : TILE_TWO;
}

void print_board(bool print_turn)
{
    system("cls");

    if (print_turn)
    {
        printf("Turn: %c\n", get_turn_char());
    }

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (cursor_pos.x == x && cursor_pos.y == y)
            {
                printf("\e[1;33m");
                printf("%c", board[y][x]);
                printf("\e[0m");
                printf(" ");
            }
            else
            {
                printf("%c ", board[y][x]);
            }
        }
        printf("\n");
    }
}

void fill_spot()
{
    board[cursor_pos.y][cursor_pos.x] = get_turn_char();
}

int main()
{
    reset_game();

    while (true)
    {
        print_board(true);

        if (move_cursor())
        {
            fill_spot();

            turn = !turn;

            state = calculate_state();
            if (state != STATE_ONGOING)
            {
                break;
            }
        }
    }

    print_board(false);

    switch (state)
    {
        case STATE_DRAW:
            printf("Draw!\n");
            break;
        default:
            printf("Player %c wins!\n", state == STATE_WIN_ONE ? TILE_ONE : TILE_TWO);
            break;
    }

    printf("Would you like to play again (y/N)? ");
    
    char play_again;
    scanf("%c", &play_again);
    while (getchar() != '\n');

    if (play_again == 'y')
    {
        return main();
    }

    return 0;
}
