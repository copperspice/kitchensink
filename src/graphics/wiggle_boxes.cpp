/**********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
***********************************************************************/

#include "wiggle_boxes.h"

Wiggle_Boxes::Wiggle_Boxes(QWidget *parent)
   : QmlApplicationViewer(parent)
{
   QString fileName;

#ifdef Q_OS_MAC
    fileName = QCoreApplication::applicationDirPath() + "resources_qml/wiggle_boxes/wiggle_boxes.qml";
#else
    fileName = "/resources_qml/wiggle_boxes/Wiggle_Boxes.qml";
#endif

   this->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
   this->setMainQmlFile(fileName.toLatin1());
   this->setWindowTitle("Wiggle Boxes");
   this->showExpanded();
}
