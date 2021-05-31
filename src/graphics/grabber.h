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

#ifndef GRABBER_H
#define GRABBER_H

#include "glwidget.h"

#include <QAction>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QScrollArea>
#include <QSlider>

class Grabber : public QMainWindow
{
   CS_OBJECT(Grabber)

   public:
      Grabber(QWidget *parent = nullptr);
      QSize sizeHint() const;

   private:
      void createActions();
      void createMenus();
      QSlider *createSlider(const QString &changedSignal, const QString &setterSlot);
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
