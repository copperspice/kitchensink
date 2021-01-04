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

#ifndef QMLAPPLICATIONVIEWER_H
#define QMLAPPLICATIONVIEWER_H

#include <QDeclarativeView>

class QmlApplicationViewer : public QDeclarativeView
{
   CS_OBJECT(QmlApplicationViewer)

   public:
       enum ScreenOrientation {
           ScreenOrientationLockPortrait,
           ScreenOrientationLockLandscape,
           ScreenOrientationAuto
       };

       explicit QmlApplicationViewer(QWidget *parent = nullptr);
       virtual ~QmlApplicationViewer();

       static QmlApplicationViewer *create();

       void setMainQmlFile(const QString &file);
       void addImportPath(const QString &path);

       // Note that this will only have an effect on Fremantle.
       void setOrientation(ScreenOrientation orientation);

       void showExpanded();

   private:
       class QmlApplicationViewerPrivate *d;
};

QApplication *createApplication(int &argc, char **argv);

#endif
