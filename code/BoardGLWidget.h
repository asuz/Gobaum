#ifndef __BOARDGLWIDGET__H__
#define __BOARDGLWIDGET__H__

#include <QGLWidget>
#include <QtGui/QMouseEvent>

#include "Goban2D.h"
#include "Goban3D.h"
#include "Textures.h"
#include "AbstractBoard.h"

class BoardGLWidget: public QGLWidget
{
    Q_OBJECT

    public:
        BoardGLWidget(QWidget *parent = 0);
        void toggle_3D();

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int w, int h);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);

    private:
        Goban2D goban2d;
        Goban3D goban3d;
        Textures textures;
        AbstractBoard abstract_board;
        int _w, _h;

        bool mode_3d;
};

#endif
