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
    if (board[y][x] != EMPTY)
        return;

    board[y][x] = turn;
    groups[y][x] = group_id;
    group_id++;

    merge_groups(get_same_color_neighbors(x, y), groups[y][x]);
    process_captures();

    if (compute_group_liberties(groups[y][x]) == 0)
        return;

    toggle_turn();

    print_state();
}

void AbstractBoard::merge_groups(vector<int> groups_members, int id)
{
    if (groups_members.size() == 0)
        return;

    while (!groups_members.empty())
    {
        convert_group(groups_members.back(), id);
        groups_members.pop_back();
    }    
}

void AbstractBoard::process_captures()
{
    int *flags = new int[group_id+1];
    for (int i = 0; i < group_id+1; i++)
        flags[i] = 0;

    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (groups[i][j] != 0 && board[i][j] != turn && flags[groups[i][j]] == 0)
            {
                try_group_capture(groups[i][j]);
                flags[groups[i][j]] = 1;
            }
        }
    }
}

void AbstractBoard::try_group_capture(int id)
{
    int liberties = compute_group_liberties(id);

    if (liberties == 0)
        erase_group(id);
}

int AbstractBoard::compute_group_liberties(int id)
{
    int liberties = 0;

    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (groups[i][j] == id)
                liberties += compute_stone_liberties(j, i);
        }
    }

    return liberties;
}

void AbstractBoard::erase_group(int id)
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (groups[i][j] == id)
            {
                groups[i][j] = 0;
                board[i][j] = EMPTY;
            }
        }
    }
}

int AbstractBoard::compute_stone_liberties(int x, int y)
{
    int liberties = 4;

    if (y > 0)
    {
        if (board[y-1][x] != EMPTY)
            liberties--;
    }
    if (y < 18)
    {
        if (board[y+1][x] != EMPTY)
            liberties--;
    }
    if (x > 0)
    {
        if (board[y][x-1] != EMPTY)
            liberties--;
    }
    if (x < 18)
    {
        if (board[y][x+1] != EMPTY)
            liberties--;
    }

    return liberties;
}

void AbstractBoard::convert_group(int old_id, int new_id)
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (groups[i][j] == old_id)
                groups[i][j] = new_id;
        }
    }
}

vector<int> AbstractBoard::get_same_color_neighbors(int x, int y)
{
    enum stone color = board[y][x];
    vector<int> neighbors;

    if (y > 0)
    {
        if (board[y-1][x] == color)
            neighbors.push_back(groups[y-1][x]);
    }
    if (y < 18)
    {
        if (board[y+1][x] == color)
            neighbors.push_back(groups[y+1][x]);
    }
    if (x > 0)
    {
        if (board[y][x-1] == color)
            neighbors.push_back(groups[y][x-1]);
    }
    if (x < 18)
    {
        if (board[y][x+1] == color)
            neighbors.push_back(groups[y][x+1]);
    }
    
    return neighbors;
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
