#ifndef POINT_H
#define POINT_H

class Point
{
    public:
        Point(int _x, int _y);
        int x, y;

        bool equals(Point other);
};

#endif
