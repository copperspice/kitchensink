/***********************************************************************
*
* Copyright (c) 2012-2026 Barbara Geller
* Copyright (c) 2012-2026 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef GRABBER_H
#define GRABBER_H

#include "glwidget.h"

#include <QMainWindow>
#include <QMenu>
#include <QSize>

class QAction;
class QLabel;
class QPixmap;
class QScrollArea;
class QSlider;

class Grabber : public QMainWindow
{
   CS_OBJECT(Grabber)

 public:
   Grabber(QWidget *parent = nullptr);

 protected:
   QSize sizeHint() const override;

 private:
   void createActions();
   void createMenus();
   QSlider *createSlider(const QString &changedSignal, const QString &adjustSlider);
   void setPixmap(const QPixmap &pixmap);
   QSize getSize();

   // slots
   void renderIntoPixmap();
   void grabFrameBuffer();
   void clearPixmap();
   void actionClose();
   void about();

   QWidget *centralWidget;
   QScrollArea *glWidgetArea;
   QScrollArea *pixmapLabelArea;
   GLWidget *glWidget;
   QLabel *pixmapLabel;
   QSlider *xSlider;
   QSlider *ySlider;
   QSlider *zSlider;

   QMenu *fileMenu;
   QMenu *helpMenu;

   QAction *grabFrameBufferAct;
   QAction *renderIntoPixmapAct;
   QAction *clearPixmapAct;
   QAction *exitAct;
   QAction *aboutGrabber;
   QAction *aboutGrabber_Cs;
};

#endif
