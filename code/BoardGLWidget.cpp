#include <cstdio>

#include "BoardGLWidget.h"

BoardGLWidget::BoardGLWidget(QWidget *parent)
{
    mode_3d = false;

    setMouseTracking(true);
}

void BoardGLWidget::initializeGL()
{
    //glClearColor(200.0/255.0, 160.0/255.0, 100.0/255.0, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    textures.load_textures();

    abstract_board.init();

    goban2d.init(textures, abstract_board);
    goban3d.init(textures, abstract_board);

}

void BoardGLWidget::resizeGL(int w, int h)
{
    _w = w;
    _h = h;

    if (mode_3d)
        goban3d.reshape(w, h);
    else
        goban2d.reshape(w, h);
}

void BoardGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (mode_3d)
        goban3d.draw();
    else
        goban2d.draw();

    swapBuffers();
}

void BoardGLWidget::toggle_3D()
{
    if (mode_3d)
    {
        mode_3d = false;
        goban2d.set_as_active();
    }
    else
    {
        mode_3d = true;
        goban3d.set_as_active();
    }

    resizeGL(_w, _h);
    paintGL();
}

void BoardGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    //printf("mouse moved: (%d, %d)\n", event->x(), event->y());
}

void BoardGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    printf("mouse pressed: (%d, %d)\n", event->x(), event->y());

    if (mode_3d)
    {
        goban3d.processMousePress(event->x(), event->y());
    }
    else
    {
        goban2d.processMousePress(event->x(), event->y());
    }

    paintGL();
}
