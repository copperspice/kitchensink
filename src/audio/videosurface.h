/**********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
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

#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QWidget>

class QImage;
class QRect;
class QSize;
class QVideoFrame;

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
