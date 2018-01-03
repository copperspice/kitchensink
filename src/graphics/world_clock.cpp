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

#include "world_clock.h"

World_Clock::World_Clock(QWidget *parent)
   : QmlApplicationViewer(parent)
{
   QString fileName;

#ifdef Q_OS_MAC
    fileName = QCoreApplication::applicationDirPath() + "/resources_qml/world_clock/World_Clock.qml";
#else
    fileName = "/resources_qml/world_clock/World_Clock.qml";
#endif

   this->setOrientation(QmlApplicationViewer::ScreenOrientationLockLandscape);
   this->setMainQmlFile(fileName.toLatin1());
   this->setWindowTitle("World Clocks");
   this->showExpanded();
}
