#include "Goban3D.h"
#include "BoardDimensions.h"
#include "Camera.h"

#include <cstdio>

void Goban3D::init(Textures tex, AbstractBoard absBoard)
{
    camera.init(45, 0.1, 10000);
    camera.setup_position(-dim.BOARD_WIDTH/2, 2*dim.BOARD_LENGTH/3, 500);
    camera.rot_left_right(180);
    camera.rot_up_down(-45);

    textures = tex;
    abstract_board = absBoard;
}

void Goban3D::draw_vertical_lines() const
{
    glColor3ub(0, 0, 0);

    double x = dim.BOARD_FRAME_W,
           y0 = dim.BOARD_FRAME_L,
           yf = dim.BOARD_LENGTH - dim.BOARD_FRAME_L;

    glBegin(GL_QUADS);
        for (int i = 0; i < 19; i++, x += dim.LINE_THICKNESS + dim.LINE_SPACE_WIDTHWISE)
        {
            glVertex3f(x, y0, -0.2);
            glVertex3f(x+dim.LINE_THICKNESS, y0, -0.2);
            glVertex3f(x+dim.LINE_THICKNESS, yf, -0.2);
            glVertex3f(x, yf, -0.2);
        }
    glEnd();
}


void Goban3D::draw_horizontal_lines() const
{
    glColor3ub(0, 0, 0);

    double x0 = dim.BOARD_FRAME_W,
           xf = dim.BOARD_WIDTH - dim.BOARD_FRAME_W,
           y = dim.BOARD_FRAME_L;

    glBegin(GL_QUADS);
        for (int i = 0; i < 19; i++, y += dim.LINE_THICKNESS + dim.LINE_SPACE_LENGTHWISE)
        {
            glVertex3f(x0, y, -0.2);
            glVertex3f(xf, y, -0.2);
            glVertex3f(xf, y+dim.LINE_THICKNESS, -0.2);
            glVertex3f(x0, y+dim.LINE_THICKNESS, -0.2);
        }
    glEnd();
}

void Goban3D::draw_board()
{
    glColor3ub(200, 160, 100);

    glBegin(GL_QUADS);
        //top
        glVertex3f(0, 0, 0);
        glVertex3f(dim.BOARD_WIDTH, 0, 0);
        glVertex3f(dim.BOARD_WIDTH, dim.BOARD_LENGTH, 0);
        glVertex3f(0, dim.BOARD_LENGTH, 0);

        //sides
        //glVertex3f(dim.BOARD_WIDTH, 0, 0);
        //glVertex3f(dim.BOARD_WIDTH, 0, dim.BOARD_THICKNESS);
        //glVertex3f(dim.BOARD_WIDTH, dim.BOARD_LENGTH, dim.BOARD_THICKNESS);
        //glVertex3f(dim.BOARD_WIDTH, dim.BOARD_LENGTH, 0);
    glEnd();

    textures.enable_textures();
    glBindTexture(GL_TEXTURE_2D, textures.board_tex);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3f(0, 0, -1.0f);
        glTexCoord2d(1, 0); glVertex3f(dim.BOARD_WIDTH, 0, -1.0f);
        glTexCoord2d(1, 1); glVertex3f(dim.BOARD_WIDTH, dim.BOARD_LENGTH, -1.0f);
        glTexCoord2d(0, 1); glVertex3f(0, dim.BOARD_LENGTH, -1.0f);
    glEnd();
    textures.disable_textures();

    //draw_vertical_lines();
    //draw_horizontal_lines();
}


void Goban3D::draw() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3ub(200, 160, 100);

    //draw_axis();

    draw_board();
}

void Goban3D::reshape(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    camera.fAspect = (GLfloat)w / (GLfloat)h;

    camera.look();
}

const double movement_ratio = 5;
const double rotation_ratio = 5;

void Goban3D::keyboard(unsigned char key)
{
    switch(key)
    {
        case 'w':
            camera.move_forward_back(-movement_ratio);
            break;
        case 's':
            camera.move_forward_back(movement_ratio);
            break;
        case 'a':
            camera.move_left_right(-movement_ratio);
            break;
        case 'd':
            camera.move_left_right(movement_ratio);
            break;
        case 'i':
            camera.rot_up_down(-rotation_ratio);
            break;
        case 'k':
            camera.rot_up_down(rotation_ratio);
            break;
        case 'l':
            camera.rot_left_right(rotation_ratio);
            break;
        case 'j':
            camera.rot_left_right(-rotation_ratio);
            break;
    }

    //printf("moving camera...\n");
    camera.look();
}

void Goban3D::set_as_active()
{
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

void Goban3D::processMousePress(int x, int y)
{
    printf("3d mouse press: (%d, %d)\n", x, y);

    GLdouble *coords = untransform_coords(x, y);
    printf("3D press coords: (%f, %f, %f)\n", coords[0], coords[1], coords[2]);
}

GLdouble *Goban3D::untransform_coords(int x, int y)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLdouble modelview[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

    GLdouble projection[16];
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    GLdouble *coords = new GLdouble[3];

    GLfloat wz;
    glReadPixels(x, viewport[3] - y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz);

    printf("z buffer value: %f\n", wz);

    gluUnProject(x, viewport[3] - y, wz, modelview, projection, viewport,
            &coords[0], &coords[1], &coords[2]);

    return coords;
}
