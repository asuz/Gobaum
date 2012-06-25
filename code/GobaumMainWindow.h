#ifndef GOBAUMMAINWINDOW_H
#define GOBAUMMAINWINDOW_H

#include <QMainWindow>

class BoardGLWidget;

class GobaumMainWindow: public QMainWindow
{
    Q_OBJECT

    public:
        GobaumMainWindow(QWidget *parent = 0);

    private:

        BoardGLWidget *glwidget;
        QMenu *file;
        QMenu *window;
        QAction *quit;
        QAction *toggleFS;

        bool fullscreen;

    public slots:
        void toggleFullscreen();

    protected:
        void keyPressEvent(QKeyEvent *event);
};


#endif
