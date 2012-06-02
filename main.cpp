#include "mdi.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Mdi mainWindow;
    mainWindow.show();

    return app.exec();
}
