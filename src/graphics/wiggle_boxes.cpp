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
