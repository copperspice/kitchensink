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

#ifndef MANDELBROT_THREAD_H
#define MANDELBROT_THREAD_H

#include <QImage>
#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>

class Mandelbrot_Thread : public QThread
{
   CS_OBJECT(Mandelbrot_Thread)

   public:
      Mandelbrot_Thread(QObject *parent = nullptr);
      ~Mandelbrot_Thread();

      void render(double centerX, double centerY, double scaleFactor, QSize resultSize);

      CS_SIGNAL_1(Public, void renderedImage(const QImage &image, double scaleFactor))
      CS_SIGNAL_2(renderedImage,image,scaleFactor)

   protected:
      void run();

   private:
      uint rgbFromWaveLength(double wave);

      QMutex mutex;
      QWaitCondition condition;
      double centerX;
      double centerY;
      double scaleFactor;
      QSize resultSize;
      bool restart;
      bool abort;

      enum { ColormapSize = 512 };
      uint colormap[ColormapSize];
};

#endif
