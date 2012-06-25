#include "MoveTree.h"

#include <iostream>

MoveTree::MoveTree()
{
}

void MoveTree::addMove(int x, int y, int color)
{
    MoveTreeCell *c = new MoveTreeCell;
    c->x = x; c->y = y; c->color = color;

    moves.push_back(c);
}

std::vector<MoveTreeCell *> *MoveTree::getMoveList()
{
    std::vector<MoveTreeCell *> *move_list = new std::vector<MoveTreeCell *>;
    
    std::vector<MoveTreeCell *>::iterator it;
    for (it = moves.begin(); it != moves.end(); it++)
    {
        MoveTreeCell *c = new MoveTreeCell;
        c->x = (*it)->x; c->y = (*it)->y; c->color = (*it)->color;

        move_list->push_back(c);
    }

    return move_list;
}
   
void MoveTree::clear()
{
    moves.clear();
}
