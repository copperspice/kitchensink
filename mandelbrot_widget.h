/**********************************************************************
*
* Copyright (c) 2012-2014 Barbara Geller
* Copyright (c) 2006-2012 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef MANDELBROT_WIDGET_H
#define MANDELBROT_WIDGET_H

#include "mandelbrot_thread.h"

#include <QWidget>
#include <QPixmap>
#include <QPoint>

class Mandelbrot_Widget : public QWidget
{
      CS_OBJECT(Mandelbrot_Widget)

   public:
      Mandelbrot_Widget(QWidget *parent = 0);

   protected:
      void paintEvent(QPaintEvent *event);
      void resizeEvent(QResizeEvent *event);
      void keyPressEvent(QKeyEvent *event);
      void wheelEvent(QWheelEvent *event);
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);
      void mouseReleaseEvent(QMouseEvent *event);

   private :
      CS_SLOT_1(Private, void updatePixmap(const QImage &image,double scaleFactor))
      CS_SLOT_2(updatePixmap)       CS_SLOT_1(Private, void zoom(double zoomFactor))
      CS_SLOT_2(zoom) 
   
      void scroll(int deltaX, int deltaY);

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
