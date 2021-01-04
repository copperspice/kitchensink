/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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
