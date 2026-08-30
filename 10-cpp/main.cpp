#include <QApplication>

#include "gamewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GameWindow ventana;
    ventana.show();

    return app.exec();
}
