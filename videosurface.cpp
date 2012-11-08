/**********************************************************************
*
* Copyright (c) 2012 Barbara Geller
* Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the Nokia Corporation nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
***********************************************************************/

#include "util.h"
#include "videosurface.h"

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

