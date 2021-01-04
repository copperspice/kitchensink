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

#ifndef MANDELBROT_WIDGET_H
#define MANDELBROT_WIDGET_H

#include "mandelbrot_thread.h"

#include <QPixmap>
#include <QPoint>
#include <QWidget>

class Mandelbrot_Widget : public QWidget
{
   CS_OBJECT(Mandelbrot_Widget)

   public:
      Mandelbrot_Widget(QWidget *parent = nullptr);
      QSize sizeHint() const;

   protected:
      void paintEvent(QPaintEvent *event);
      void resizeEvent(QResizeEvent *event);
      void keyPressEvent(QKeyEvent *event);
      void wheelEvent(QWheelEvent *event);
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);
      void mouseReleaseEvent(QMouseEvent *event);

   private:
      void scroll(int deltaX, int deltaY);

      CS_SLOT_1(Private, void updatePixmap(const QImage &image,double scaleFactor))
      CS_SLOT_2(updatePixmap)

      CS_SLOT_1(Private, void zoom(double zoomFactor))
      CS_SLOT_2(zoom)

      Mandelbrot_Thread thread;
      QPixmap pixmap;
      QPoint pixmapOffset;
      QPoint lastDragPos;
      double centerX;
      double centerY;
      double pixmapScale;
      double curScale;
};

#endif
