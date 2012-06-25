#ifndef __GOBAN2D_H__
#define __GOBAN2D_H__

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <freetype2/freetype/config/ftheader.h>
#include <FTGL/ftgl.h>

#include "Textures.h"
#include "AbstractBoard.h"

class Goban2D
{
    public:
        Goban2D();
        ~Goban2D();

        void init(Textures tex, AbstractBoard absBoard);
        void reshape(GLsizei w, GLsizei h);
        void draw();
        void set_as_active();
        void processMousePress(int x, int y);

    private:
        Textures textures;
        AbstractBoard abstract_board;
        FTGLPixmapFont *font;

        void draw_border();
        void draw_board();
        GLdouble *untransformCoords(int x, int y);
        void draw_stones();
        void draw_single_stone(int x, int y);
        void draw_text();
        void draw_number(int x, int y, int num);
};

#endif
