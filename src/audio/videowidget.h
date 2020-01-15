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

#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "videosurface.h"

#include <QAbstractVideoSurface>
#include <QWidget>

class VideoWidget : public QWidget
{
      CS_OBJECT(VideoWidget)

   public:
      VideoWidget(QWidget *parent = nullptr);
      ~VideoWidget();

      QAbstractVideoSurface *videoSurface() const { return surface; }

      QSize sizeHint() const;

   protected:
      void paintEvent(QPaintEvent *event);
      void resizeEvent(QResizeEvent *event);

   private:
      VideoSurface *surface;
};

#endif
