#ifndef __BOARD_DIMENSIONS_H__
#define __BOARD_DIMENSIONS_H__

class BoardDimensions
{
    public:
        static double LINE_THICKNESS;
        static double STAR_POINT_DIAMETER;
        static double STONE_DIAMETER;
        static double LINE_SPACE_LENGTHWISE;
        static double LINE_SPACE_WIDTHWISE;
        static double BOARD_THICKNESS;
        static double BOARD_FRAME_W;
        static double BOARD_FRAME_L;
        static double BOARD_LENGTH;
        static double BOARD_WIDTH;

        int *get_board_coords(double gl_x, double gl_y);
        double *to_quad_vertices(int x, int y);
};


#endif
