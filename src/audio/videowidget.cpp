/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
***********************************************************************/

#include "videowidget.h"
#include "videosurface.h"

#include <QtMultimedia>

VideoWidget::VideoWidget(QWidget *parent)
   : QWidget(parent), surface(0)
{
   setAutoFillBackground(false);
   setAttribute(Qt::WA_NoSystemBackground, true);
   setAttribute(Qt::WA_PaintOnScreen, true);

   setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

   surface = new VideoSurface(this);
}

VideoWidget::~VideoWidget()
{
   delete surface;
}

QSize VideoWidget::sizeHint() const
{
   return surface->surfaceFormat().sizeHint();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);

   if (surface->isActive()) {
      const QRect videoRect = surface->videoRect();

      if (!videoRect.contains(event->rect())) {
         QRegion region = event->region();
         region.subtracted(videoRect);

         QBrush brush = palette().background();

         for (const QRect &rect : region.rects()) {
            painter.fillRect(rect, brush);
         }
      }

      surface->paint(&painter);

   } else {
      painter.fillRect(event->rect(), palette().background());
   }
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
   QWidget::resizeEvent(event);

   surface->updateVideoRect();
}

