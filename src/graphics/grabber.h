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

      CS_SLOT_1(Private, void renderIntoPixmap())
      CS_SLOT_2(renderIntoPixmap)

      CS_SLOT_1(Private, void grabFrameBuffer())
      CS_SLOT_2(grabFrameBuffer)

      CS_SLOT_1(Private, void clearPixmap())
      CS_SLOT_2(clearPixmap)

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      CS_SLOT_1(Private, void about())
      CS_SLOT_2(about)

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
      QAction *aboutAct;
      QAction *aboutQtAct;
};

#endif
