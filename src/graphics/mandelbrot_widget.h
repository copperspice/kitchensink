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

#ifndef MANDELBROT_WIDGET_H
#define MANDELBROT_WIDGET_H

#include "mandelbrot_thread.h"

#include <QPixmap>
#include <QPoint>
#include <QSize>
#include <QWidget>

class QImage;

class Mandelbrot_Widget : public QWidget
{
   CS_OBJECT(Mandelbrot_Widget)

 public:
   Mandelbrot_Widget(QWidget *parent = nullptr);

 protected:
   void keyPressEvent(QKeyEvent *event) override;
   void mouseMoveEvent(QMouseEvent *event) override;
   void mousePressEvent(QMouseEvent *event) override;
   void mouseReleaseEvent(QMouseEvent *event) override;
   void paintEvent(QPaintEvent *event) override;
   void resizeEvent(QResizeEvent *event) override;
   void wheelEvent(QWheelEvent *event) override;

   QSize sizeHint() const override;

 private:
   void scroll(int deltaX, int deltaY);

   // slot
   void updatePixmap(const QImage &image, double scaleFactor);

   void zoom(double zoomFactor);

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
