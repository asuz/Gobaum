#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include <cstdio>

#include "Point.h"

enum stone {EMPTY, WHITE, BLACK};

class AbstractBoard
{
    private:
        enum stone turn;
        int group_id;

        void clean_board();
        void clean_groups();
        void print_state();
        void toggle_turn();
        bool is_valid_play();

    public:
        enum stone board[19][19];
        int groups[19][19];

        AbstractBoard();
        void play_stone(int x, int y);
        void init();
};

#endif
