#include "GobaumMainWindow.h"
#include <QDesktopWidget>
#include <QApplication>

void center(QWidget &widget)
{
    int x, y;
    int screenWidth;
    int screenHeight;
    int width, height;
    QSize windowSize;

    QDesktopWidget *desktop = QApplication::desktop();

    width = widget.frameGeometry().width();
    height = widget.frameGeometry().height();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;

    widget.move(x, y);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GobaumMainWindow window;

    window.setWindowTitle("Gobaum");
    window.resize(1024, 768);
    QSize minSize(640, 480);
    window.setMinimumSize(minSize);
    window.show();
    center(window);

    return app.exec();
}


