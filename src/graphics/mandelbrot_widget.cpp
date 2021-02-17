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

#include "mandelbrot_widget.h"

#include <QKeyEvent>
#include <QPainter>
#include <QRectF>

#include <math.h>

const double DefaultCenterX = -0.637011f;
const double DefaultCenterY = -0.0395159f;
const double DefaultScale = 0.00403897f;

const double ZoomInFactor = 0.8f;
const double ZoomOutFactor = 1 / ZoomInFactor;
const int ScrollStep = 20;

Mandelbrot_Widget::Mandelbrot_Widget(QWidget *parent)
   : QWidget(parent)
{
   setWindowTitle(tr("Mandelbrot"));

   centerX     = DefaultCenterX;
   centerY     = DefaultCenterY;
   pixmapScale = DefaultScale;
   curScale    = DefaultScale;

   connect(&thread, SIGNAL(renderedImage(const QImage &,double)),this, SLOT(updatePixmap(const QImage &,double)));

   setCursor(Qt::CrossCursor);
}

void Mandelbrot_Widget::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.fillRect(rect(), Qt::black);

   if (pixmap.isNull()) {
      painter.setPen(Qt::white);
      painter.drawText(rect(), Qt::AlignCenter,tr("Rendering initial image, please wait..."));

      return;
   }

   if (curScale == pixmapScale) {
      painter.drawPixmap(pixmapOffset, pixmap);

   } else {
      double scaleFactor = pixmapScale / curScale;
      int newWidth = int(pixmap.width() * scaleFactor);
      int newHeight = int(pixmap.height() * scaleFactor);
      int newX = pixmapOffset.x() + (pixmap.width() - newWidth) / 2;
      int newY = pixmapOffset.y() + (pixmap.height() - newHeight) / 2;

      painter.save();
      painter.translate(newX, newY);
      painter.scale(scaleFactor, scaleFactor);

      QRectF exposed = painter.matrix().inverted().mapRect(rect()).adjusted(-1, -1, 1, 1);
      painter.drawPixmap(exposed, pixmap, exposed);
      painter.restore();
   }

   QString text = tr("Use mouse wheel or the '+' and '-' keys to zoom. "
                     "Press and hold left mouse button to scroll.");
   QFontMetrics metrics = painter.fontMetrics();
   int textWidth = metrics.width(text);

   painter.setPen(Qt::NoPen);
   painter.setBrush(QColor(0, 0, 0, 127));
   painter.drawRect((width() - textWidth) / 2 - 5, 0, textWidth + 10, metrics.lineSpacing() + 5);
   painter.setPen(Qt::white);
   painter.drawText((width() - textWidth) / 2, metrics.leading() + metrics.ascent(), text);

}

void Mandelbrot_Widget::resizeEvent(QResizeEvent *)
{
   thread.render(centerX, centerY, curScale, size());
}

void Mandelbrot_Widget::keyPressEvent(QKeyEvent *event)
{
   switch (event->key()) {
      case Qt::Key_Plus:
         zoom(ZoomInFactor);
         break;
      case Qt::Key_Minus:
         zoom(ZoomOutFactor);
         break;
      case Qt::Key_Left:
         scroll(-ScrollStep, 0);
         break;
      case Qt::Key_Right:
         scroll(+ScrollStep, 0);
         break;
      case Qt::Key_Down:
         scroll(0, -ScrollStep);
         break;
      case Qt::Key_Up:
         scroll(0, +ScrollStep);
         break;
      default:
         QWidget::keyPressEvent(event);
   }
}

void Mandelbrot_Widget::mousePressEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton)
      lastDragPos = event->pos();
}

void Mandelbrot_Widget::mouseMoveEvent(QMouseEvent *event)
{
   if (event->buttons() & Qt::LeftButton) {
      pixmapOffset += event->pos() - lastDragPos;
      lastDragPos = event->pos();
      update();
   }
}

void Mandelbrot_Widget::mouseReleaseEvent(QMouseEvent *event)
{
   if (event->button() == Qt::LeftButton) {
      pixmapOffset += event->pos() - lastDragPos;
      lastDragPos = QPoint();

      int deltaX = (width() - pixmap.width()) / 2 - pixmapOffset.x();
      int deltaY = (height() - pixmap.height()) / 2 - pixmapOffset.y();
      scroll(deltaX, deltaY);
   }
}

void Mandelbrot_Widget::scroll(int deltaX, int deltaY)
{
   centerX += deltaX * curScale;
   centerY += deltaY * curScale;
   update();
   thread.render(centerX, centerY, curScale, size());
}

QSize Mandelbrot_Widget::sizeHint() const
{
   return QSize(400,300);
}

void Mandelbrot_Widget::updatePixmap(const QImage &image, double scaleFactor)
{
   if (! lastDragPos.isNull()) {
      return;
   }

   pixmap = QPixmap::fromImage(image);
   pixmapOffset = QPoint();
   lastDragPos = QPoint();
   pixmapScale = scaleFactor;
   update();
}

void Mandelbrot_Widget::wheelEvent(QWheelEvent *event)
{
   int numDegrees = event->delta() / 8;
   double numSteps = numDegrees / 15.0f;
   zoom(pow(ZoomInFactor, numSteps));
}

void Mandelbrot_Widget::zoom(double zoomFactor)
{
   curScale *= zoomFactor;
   update();
   thread.render(centerX, centerY, curScale, size());
}

