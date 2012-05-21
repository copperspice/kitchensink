#include "mdi.h"

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mdi mainWindow;
    mainWindow.show();

    return a.exec();
}
