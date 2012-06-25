#ifndef __GOBAN3D_H__
#define __GOBAN3D_H__

#include <GL/gl.h>

#include "Textures.h"
#include "Camera.h"
#include "BoardDimensions.h"
#include "AbstractBoard.h"

class Goban3D
{
    public:
        Goban3D() {}
        Camera camera;
        BoardDimensions dim;

        void init(Textures tex, AbstractBoard absBoard);
        void draw();
        void reshape(GLsizei w, GLsizei h);
        void keyboard(unsigned char key);
        void set_as_active();
        void processMousePress(int x, int y);

    private:
        Textures textures;
        AbstractBoard abstract_board;

        void draw_board();
        void draw_vertical_lines() const;
        void draw_horizontal_lines() const;
        GLdouble *untransform_coords(int x, int y);
};

#endif
