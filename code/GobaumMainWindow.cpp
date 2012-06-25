#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QtGui/QMouseEvent>
#include <cstdio>
#include "GobaumMainWindow.h"
#include "BoardGLWidget.h"

GobaumMainWindow::GobaumMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    glwidget = new BoardGLWidget;
    setCentralWidget(glwidget);

    fullscreen = false;

    quit = new QAction("&Quit", this);
    toggleFS = new QAction("Toggle &Fullscreen", this);

    file = menuBar()->addMenu("&File");
    file->addAction(quit);

    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    window = menuBar()->addMenu("&Window");
    window->addAction(toggleFS);

    connect(toggleFS, SIGNAL(triggered()), this, SLOT(toggleFullscreen()));
}

void GobaumMainWindow::toggleFullscreen()
{
    if (!fullscreen)
    {
        showFullScreen();
        fullscreen = true;
    }
    else
    {
        showNormal();
        fullscreen = false;
    }
}

void GobaumMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case 'F':
            toggleFullscreen();
            break;
        case 'Q':
            glwidget->toggle_3D();
            break;
        case Qt::Key_Escape:
            qApp->quit();
            break;
        default:
            event->ignore();
            break;
    }
}
