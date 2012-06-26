#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include <cstdio>
#include <vector>

#include "Point.h"

using namespace std;

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
        vector<int> get_same_color_neighbors(int x, int y);
        void merge_groups(vector<int> groups_members, int id);
        void convert_group(int old_id, int new_id);
        void process_captures();
        void try_group_capture(int id);
        int compute_group_liberties(int id);
        void erase_group(int id);
        int compute_stone_liberties(int x, int y);

    public:
        enum stone board[19][19];
        int groups[19][19];

        AbstractBoard();
        void play_stone(int x, int y);
        void init();
};

#endif
