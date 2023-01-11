/***********************************************************************
*
* Copyright (c) 2012-2023 Barbara Geller
* Copyright (c) 2012-2023 Ansel Sermersheim
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

#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#ifndef QT_NO_MULTIMEDIA

#include <QAbstractVideoSurface>
#include <QWidget>

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

#endif   // ! QT_NO_MULTIMEDIA

#endif
