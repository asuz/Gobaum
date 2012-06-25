#include "Point.h"

Point::Point(int _x, int _y)
{
    x = _x;
    y = _y;
}

bool Point::equals(Point other)
{
    if (x == other.x && y == other.y)
        return true;
    else
        return false;
}
