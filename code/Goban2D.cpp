#include "Goban2D.h"
#include "BoardDimensions.h"

#include <cstdio>

BoardDimensions dim;

Goban2D::Goban2D()
{
}

Goban2D::~Goban2D()
{

}

void Goban2D::init(Textures tex, AbstractBoard absBoard)
{
    textures = tex;
    abstract_board = absBoard;
    font = new FTGLPixmapFont("DejaVuSerif.ttf");
}

void Goban2D::reshape(GLsizei w, GLsizei h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    if (w > h)
        glOrtho(-5*aspect, (dim.BOARD_WIDTH)*aspect, -5, dim.BOARD_LENGTH+5, 20, -20);
    else
        glOrtho(-5, dim.BOARD_WIDTH, 0/aspect, (dim.BOARD_LENGTH)/aspect, 20, -20);
}

void Goban2D::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0, -1.0, 0.0);

    //draw_border();
    draw_board();
    draw_text();
}

void Goban2D::draw_board()
{   
    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textures.board_tex);
    glPolygonMode(GL_FRONT, GL_FILL);

    glColor3ub(200, 160, 100);

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(dim.BOARD_WIDTH, 0.0f);
        glVertex2f(dim.BOARD_WIDTH, dim.BOARD_LENGTH);
        glVertex2f(0.0f, dim.BOARD_LENGTH);
    glEnd();

    textures.enable_textures();
    
    glColor3f(1.0f, 1.0f, 1.0f);
    //glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3f(0.0f, 0.0f, -10.0f);
        glTexCoord2d(1, 0); glVertex3f(dim.BOARD_WIDTH, 0.0f, -10.0f);
        glTexCoord2d(1, 1); glVertex3f(dim.BOARD_WIDTH, dim.BOARD_LENGTH, -10.0f);
        glTexCoord2d(0, 1); glVertex3f(0.0f, dim.BOARD_LENGTH, -10.0f);
    glEnd();

    textures.disable_textures();

    draw_stones();
}

void Goban2D::draw_single_stone(int x, int y)
{
    double *quad = dim.to_quad_vertices(x, y);

    glTexCoord2d(0, 0); glVertex3f(quad[0], quad[2], -12.0f);
    glTexCoord2d(1, 0); glVertex3f(quad[1], quad[2], -12.0f);
    glTexCoord2d(1, 1); glVertex3f(quad[1], quad[3], -12.0f);
    glTexCoord2d(0, 1); glVertex3f(quad[0], quad[3], -12.0f);


}

void Goban2D::draw_stones()
{
    textures.enable_textures();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, textures.white_stone_2D);

    glBegin(GL_QUADS);
        for (int i = 0; i < 19; i++)
        {
            for (int j = 0; j < 19; j++)
            {
                if (abstract_board.board[i][j] == WHITE)
                    draw_single_stone(j, i);
            }
        }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textures.black_stone_2D);

    glBegin(GL_QUADS);
        for (int i = 0; i < 19; i++)
        {
            for (int j = 0; j < 19; j++)
            {
                if (abstract_board.board[i][j] == BLACK)
                    draw_single_stone(j, i);
            }
        }
    glEnd();

    textures.disable_textures();
}

void Goban2D::draw_border()
{
    glColor3ub(0, 0, 0);

    glBegin(GL_QUADS);
        glVertex3f(-1.5, -1, 1);
        glVertex3f(dim.BOARD_WIDTH+1, -1, 1);
        glVertex3f(dim.BOARD_WIDTH+1, dim.BOARD_LENGTH+1, 1);
        glVertex3f(-1.5, dim.BOARD_LENGTH+1, 1);
    glEnd();
}

void Goban2D::set_as_active()
{
}

void Goban2D::processMousePress(int x, int y)
{
    GLdouble *coords = untransformCoords(x, y);

    printf("gl mouse press: (%f, %f)\n", coords[0], coords[1]);

    int *board_coords = dim.get_board_coords(coords[0], coords[1]);
    printf("board coords: (%d, %d)\n", board_coords[0], board_coords[1]);

    if (board_coords[0] != -1 && board_coords[1] != -1)
        abstract_board.play_stone(board_coords[0], board_coords[1]);
}

GLdouble *Goban2D::untransformCoords(int x, int y)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLdouble modelview[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

    GLdouble projection[16];
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    GLdouble zcoord;
    GLdouble *coords = new GLdouble[2];
    gluUnProject(x, viewport[3] - y, 0, modelview, projection, viewport, 
            &coords[0], &coords[1], &zcoord);

    return coords;
}

void Goban2D::draw_text()
{
    glColor3ub(0, 0, 0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glRasterPos3f(10, 10, -19);

    font->FaceSize(12);
    font->Render("Hello world!");

    glPopMatrix();

    glColor3ub(133, 173, 0);
    for (int x = 0; x < 19; x++)
        for (int y = 0; y < 19; y++)
            draw_number(x, y, abstract_board.groups[y][x]);
}

void Goban2D::draw_number(int x, int y, int num)
{
    char number_str[256];

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    double *coords = dim.to_quad_vertices(x, y);
    double xpos = coords[0] + 2*(coords[1] - coords[0])/5;
    double ypos = coords[2] + 2*(coords[3] - coords[2])/5;

    glRasterPos3f(xpos, ypos, -19);

    sprintf(number_str, "%d", num);
    font->Render(number_str);

    glPopMatrix();
}
