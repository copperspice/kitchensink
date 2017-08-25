/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/


#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "videosurface.h"

#include <QWidget>
#include <QAbstractVideoSurface>

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
