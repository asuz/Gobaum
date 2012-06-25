#include <QImage>
#include <QGLWidget>
#include <cstdio>
#include <SOIL/SOIL.h>

#include "Textures.h"

Textures::Textures()
{
}

void Textures::load_textures()
{
    enable_textures();

    /*QImage board;

    if (!board.load("../images/goban.png"))
    {
        printf("Image load problem: goban.png\n");
    }
    QImage t = QGLWidget::convertToGLFormat(board);

    glGenTextures(1, &board_tex);
    glBindTexture(GL_TEXTURE_2D, board_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());*/

    board_tex = SOIL_load_OGL_texture(
            "../images/goban.png",
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS);

    printf("Board_tex id: %u\n", board_tex);

    white_stone_2D = SOIL_load_OGL_texture(
            "../images/white_128.png",
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS);

    printf("white tex id: %u\n", white_stone_2D);

    black_stone_2D = SOIL_load_OGL_texture(
            "../images/black_128.png",
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_MIPMAPS);

    printf("black tex id: %u\n", black_stone_2D);

    disable_textures();
}

void Textures::enable_textures()
{
    glEnable(GL_TEXTURE_2D);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    ////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    ////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvf(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, -0.99);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Textures::disable_textures()
{
    glDisable(GL_TEXTURE_2D);
}
