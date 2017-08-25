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


#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QtCore/QRect>
#include <QtGui/QImage>
#include <QtMultimedia/QAbstractVideoSurface>
#include <QtMultimedia/QVideoFrame>

class VideoSurface : public QAbstractVideoSurface
{
   CS_OBJECT(VideoSurface)

   public:
      VideoSurface(QWidget *widget, QObject *parent = nullptr);

      QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
      bool isFormatSupported(const QVideoSurfaceFormat &format, QVideoSurfaceFormat *similar) const;

      bool start(const QVideoSurfaceFormat &format);
      void stop();

      bool present(const QVideoFrame &frame);

      QRect videoRect() const { return targetRect; }
      void updateVideoRect();

      void paint(QPainter *painter);

   private:
      QWidget *m_widget;
      QImage::Format m_imageFormat;
      QRect targetRect;
      QSize imageSize;
      QRect sourceRect;
      QVideoFrame currentFrame;
};


#endif
