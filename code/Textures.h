#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include <GL/gl.h>
#include <GL/glu.h>

class Textures
{
    public:
        GLuint board_tex;
        GLuint white_stone_2D;
        GLuint black_stone_2D;

        Textures();
        void load_textures();
        void enable_textures();
        void disable_textures();

    private:
};

#endif
