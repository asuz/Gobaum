#include "AbstractBoard.h"

AbstractBoard::AbstractBoard()
{
    clean_board();
    clean_groups();
}

void AbstractBoard::init()
{
    turn = BLACK;
    group_id = 1;
}

void AbstractBoard::play_stone(int x, int y)
{
    if (board[y][x] == EMPTY)
    {
        board[y][x] = turn;
        if (is_valid_play())
            toggle_turn();
    }
    print_state();
}

void AbstractBoard::clean_board()
{
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++)
            board[i][j] = EMPTY;
}

void AbstractBoard::clean_groups()
{
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++)
            groups[i][j] = 0;
}

void AbstractBoard::print_state()
{
    printf("==================================================================\n\n\n");
    
    for (int y = 18; y >= 0; y--)
    {
        for (int x = 0; x < 19; x++)
            printf("%c ", (board[y][x] == WHITE)?'o':((board[y][x] == BLACK)?'*':'.'));
        printf("\n");
    }
}

void AbstractBoard::toggle_turn()
{
    if (turn == BLACK)
        turn = WHITE;
    else
        turn = BLACK;
}

bool AbstractBoard::is_valid_play()
{
    return true;
}
