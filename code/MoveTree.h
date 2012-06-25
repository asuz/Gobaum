#ifndef MOVETREE_H
#define MOVETREE_H

#include <vector>

class MoveTreeCell
{
    public:
        int x, y;
        int color;
};

class MoveTree
{
    private:
        std::vector<MoveTreeCell *> moves;

    public:
        MoveTree();
        void addMove(int x, int y, int color);
        std::vector<MoveTreeCell *> *getMoveList();
        void clear();
};

#endif

