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

#ifndef MANDELBROT_THREAD_H
#define MANDELBROT_THREAD_H

#include <QImage>
#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
#include <math.h>

class Mandelbrot_Thread : public QThread
{
   CS_OBJECT(Mandelbrot_Thread)

   public:
      Mandelbrot_Thread(QObject *parent = nullptr);
      ~Mandelbrot_Thread();

      void render(double centerX, double centerY, double scaleFactor,QSize resultSize);

      CS_SIGNAL_1(Public, void renderedImage(const QImage &image,double scaleFactor))
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
