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
