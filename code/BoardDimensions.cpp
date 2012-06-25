#include "BoardDimensions.h"


double BoardDimensions::LINE_THICKNESS        =   1.0;
double BoardDimensions::STAR_POINT_DIAMETER   =   4.0 * LINE_THICKNESS;
double BoardDimensions::STONE_DIAMETER        =  23.0 * LINE_THICKNESS;
double BoardDimensions::LINE_SPACE_LENGTHWISE =  22.0 * LINE_THICKNESS;
double BoardDimensions::LINE_SPACE_WIDTHWISE  =  22.0 * LINE_THICKNESS;
double BoardDimensions::BOARD_THICKNESS       = 151.5 * LINE_THICKNESS;
double BoardDimensions::BOARD_FRAME_W         =         LINE_SPACE_WIDTHWISE;
double BoardDimensions::BOARD_FRAME_L         =         LINE_SPACE_LENGTHWISE;
double BoardDimensions::BOARD_LENGTH          = 2*BOARD_FRAME_L + 19*LINE_THICKNESS + 18*LINE_SPACE_LENGTHWISE;
double BoardDimensions::BOARD_WIDTH           = 2*BOARD_FRAME_W + 19*LINE_THICKNESS + 18*LINE_SPACE_WIDTHWISE;

int *BoardDimensions::get_board_coords(double gl_x, double gl_y)
{
    int *board_coords = new int[2];

    if (gl_x < BOARD_FRAME_W/2 || gl_x > BOARD_WIDTH - (BOARD_FRAME_W/2))
    {
        board_coords[0] = -1;
    }
    else
    {
        board_coords[0] = (gl_x - BOARD_FRAME_W/2)/(LINE_SPACE_WIDTHWISE+LINE_THICKNESS);
    }

    if (gl_y < BOARD_FRAME_L/2 || gl_y > BOARD_LENGTH - (BOARD_FRAME_L/2))
    {
        board_coords[1] = -1;
    }
    else 
    {
        board_coords[1] = (gl_y - BOARD_FRAME_L/2)/(LINE_SPACE_LENGTHWISE+LINE_THICKNESS);
    }

    return board_coords;
}

double *BoardDimensions::to_quad_vertices(int x, int y)
{
    double quad_w = LINE_SPACE_WIDTHWISE + LINE_THICKNESS;
    double quad_l = LINE_SPACE_LENGTHWISE + LINE_THICKNESS;

    double x_min, x_max, y_min, y_max;

    x_min = BOARD_FRAME_W/2 + x*quad_w;
    x_max = x_min + quad_w;

    y_min = BOARD_FRAME_L/2 + y*quad_l;
    y_max = y_min + quad_l;

    double *quad = new double[4];
    quad[0] = x_min;
    quad[1] = x_max;
    quad[2] = y_min;
    quad[3] = y_max;

    return quad;
}
