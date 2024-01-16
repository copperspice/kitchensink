/***********************************************************************
*
* Copyright (c) 2012-2024 Barbara Geller
* Copyright (c) 2012-2024 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "qmlapplicationviewer.h"

#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QDeclarativeComponent>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

class QmlApplicationViewerPrivate
{
   QString mainQmlFile;
   friend class QmlApplicationViewer;
   static QString adjustPath(const QString &path);
};

QString QmlApplicationViewerPrivate::adjustPath(const QString &path)
{
#ifdef Q_OS_MAC
   if (! QDir::isAbsolutePath(path)) {
      return QString("%1/../Resources/%2").formatArg(QCoreApplication::applicationDirPath(), path);
   }

#else
   QString pathInInstallDir = QString("%1/../%2").formatArg(QCoreApplication::applicationDirPath(), path);

   if (QFileInfo(pathInInstallDir).exists()) {
      return pathInInstallDir;
   }

   pathInInstallDir = QString("%1/%2").formatArg(QCoreApplication::applicationDirPath(), path);

   if (QFileInfo(pathInInstallDir).exists()) {
      return pathInInstallDir;
   }
#endif

    return path;
}

QmlApplicationViewer::QmlApplicationViewer(QWidget *parent)
   : QDeclarativeView(parent), d(new QmlApplicationViewerPrivate())
{
   connect(engine(), SIGNAL(quit()), this, SLOT(close()));
   setResizeMode(QDeclarativeView::SizeRootObjectToView);
}

QmlApplicationViewer::~QmlApplicationViewer()
{
   delete d;
}

QmlApplicationViewer *QmlApplicationViewer::create()
{
   return new QmlApplicationViewer();
}

void QmlApplicationViewer::setMainQmlFile(const QString &file)
{
   d->mainQmlFile = QmlApplicationViewerPrivate::adjustPath(file);
   setSource(QUrl::fromLocalFile(d->mainQmlFile));
}

void QmlApplicationViewer::addImportPath(const QString &path)
{
   engine()->addImportPath(QmlApplicationViewerPrivate::adjustPath(path));
}

void QmlApplicationViewer::setOrientation(ScreenOrientation orientation)
{
   Qt::WidgetAttribute attribute;

   switch (orientation) {
      case ScreenOrientationLockPortrait:
         attribute = Qt::WA_LockPortraitOrientation;
         break;

      case ScreenOrientationLockLandscape:
         attribute = Qt::WA_LockLandscapeOrientation;
          break;

      case ScreenOrientationAuto:
      default:
         attribute = Qt::WA_AutoOrientation;
         break;
    };

    setAttribute(attribute, true);
}

void QmlApplicationViewer::showExpanded()
{
   show();
}

QApplication *createApplication(int &argc, char **argv)
{
   return new QApplication(argc, argv);
}
