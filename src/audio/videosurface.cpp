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

#include "videosurface.h"
#include "util.h"

#include <QtMultimedia>

VideoSurface::VideoSurface(QWidget *widget, QObject *parent)
   : QAbstractVideoSurface(parent)
{
   m_widget = widget;
   m_imageFormat = QImage::Format_Invalid;
}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(
      QAbstractVideoBuffer::HandleType handleType) const
{
   if (handleType == QAbstractVideoBuffer::NoHandle) {

      return QList<QVideoFrame::PixelFormat>()
            << QVideoFrame::Format_RGB32
            << QVideoFrame::Format_ARGB32
            << QVideoFrame::Format_ARGB32_Premultiplied
            << QVideoFrame::Format_RGB565
            << QVideoFrame::Format_RGB555;

   } else {
      return QList<QVideoFrame::PixelFormat>();

   }
}

bool VideoSurface::isFormatSupported(const QVideoSurfaceFormat &format, QVideoSurfaceFormat *) const
{
   const QImage::Format temp = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
   const QSize size = format.frameSize();

   bool retval = (temp != QImage::Format_Invalid) && ! size.isEmpty()
                 && format.handleType() == QAbstractVideoBuffer::NoHandle;

   return retval;
}

bool VideoSurface::start(const QVideoSurfaceFormat &format)
{
   const QImage::Format temp = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
   const QSize size = format.frameSize();

   if (temp != QImage::Format_Invalid && ! size.isEmpty()) {

      m_imageFormat = temp;
      imageSize     = size;
      sourceRect    = format.viewport();

      QAbstractVideoSurface::start(format);

      m_widget->updateGeometry();
      updateVideoRect();

      return true;

   } else {
      return false;

   }
}

void VideoSurface::stop()
{
   currentFrame = QVideoFrame();
   targetRect   = QRect();

   QAbstractVideoSurface::stop();

   m_widget->update();
}

bool VideoSurface::present(const QVideoFrame &frame)
{
   if (surfaceFormat().pixelFormat() != frame.pixelFormat()
       || surfaceFormat().frameSize() != frame.size()) {

      setError(IncorrectFormatError);
      stop();

      return false;

   } else {
      currentFrame = frame;

      m_widget->repaint(targetRect);

      return true;
   }
}

void VideoSurface::updateVideoRect()
{
   QSize size = surfaceFormat().sizeHint();
   size.scale(m_widget->size().boundedTo(size), Qt::KeepAspectRatio);

   targetRect = QRect(QPoint(0, 0), size);
   targetRect.moveCenter(m_widget->rect().center());
}

void VideoSurface::paint(QPainter *painter)
{
   if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {
      const QTransform oldTransform = painter->transform();

      if (surfaceFormat().scanLineDirection() == QVideoSurfaceFormat::BottomToTop) {
         painter->scale(1, -1);
         painter->translate(0, 0-m_widget->height());
      }

      QImage image(
               currentFrame.bits(),
               currentFrame.width(),
               currentFrame.height(),
               currentFrame.bytesPerLine(),
               m_imageFormat);

      painter->drawImage(targetRect, image, sourceRect);

      painter->setTransform(oldTransform);

      currentFrame.unmap();
   }
}

