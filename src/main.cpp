/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   MainWindow dw;
   dw.show();

   return app.exec();
}
