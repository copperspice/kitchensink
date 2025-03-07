/***********************************************************************
*
* Copyright (c) 2012-2025 Barbara Geller
* Copyright (c) 2012-2025 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "mandelbrot_thread.h"

#include <QImage>

#include <math.h>

Mandelbrot_Thread::Mandelbrot_Thread(QObject *parent)
   : QThread(parent)
{
   m_restart = false;
   m_abort   = false;

   for (int i = 0; i < ColormapSize; ++i) {
      colormap[i] = rgbFromWaveLength(380.0 + (i * 400.0 / ColormapSize));
   }
}

Mandelbrot_Thread::~Mandelbrot_Thread()
{
   m_mutex.lock();
   m_abort = true;
   m_condition.wakeOne();
   m_mutex.unlock();

   wait();
}

void Mandelbrot_Thread::render(double centerX, double centerY, double scaleFactor, QSize resultSize)
{
   QMutexLocker locker(&m_mutex);

   m_centerX     = centerX;
   m_centerY     = centerY;
   m_scaleFactor = scaleFactor;
   m_resultSize  = resultSize;

   if (! isRunning()) {
      start(LowPriority);
   } else {
      m_restart = true;
      m_condition.wakeOne();
   }
}

void Mandelbrot_Thread::run()
{
   while (true) {
      m_mutex.lock();

      double scaleFactor = m_scaleFactor;
      double centerX     = m_centerX;
      double centerY     = m_centerY;

      m_mutex.unlock();

      int halfWidth  = m_resultSize.width() / 2;
      int halfHeight = m_resultSize.height() / 2;
      QImage image(m_resultSize, QImage::Format_RGB32);

      const int NumPasses = 8;
      int pass = 0;

      while (pass < NumPasses) {
         const int MaxIterations = (1 << (2 * pass + 6)) + 32;
         const int Limit = 4;
         bool allBlack = true;

         for (int y = -halfHeight; y < halfHeight; ++y) {
            if (m_restart) {
               break;
            }

            if (m_abort) {
               return;
            }

            uint *scanLine = reinterpret_cast<uint *>(image.scanLine(y + halfHeight));
            double ay = centerY + (y * scaleFactor);

            for (int x = -halfWidth; x < halfWidth; ++x) {
               double ax = centerX + (x * scaleFactor);
               double a1 = ax;
               double b1 = ay;
               int numIterations = 0;

               do {
                  ++numIterations;

                  double a2 = (a1 * a1) - (b1 * b1) + ax;
                  double b2 = (2 * a1 * b1) + ay;

                  if ((a2 * a2) + (b2 * b2) > Limit) {
                     break;
                  }

                  ++numIterations;
                  a1 = (a2 * a2) - (b2 * b2) + ax;
                  b1 = (2 * a2 * b2) + ay;

                  if ((a1 * a1) + (b1 * b1) > Limit) {
                     break;
                  }

               } while (numIterations < MaxIterations);

               if (numIterations < MaxIterations) {
                  *scanLine = colormap[numIterations % ColormapSize];
                  allBlack = false;

               } else {
                  *scanLine = qRgb(0, 0, 0);

               }

               ++scanLine;
            }
         }

         if (allBlack && pass == 0) {
            pass = 4;

         } else {
            if (! m_restart) {
               emit renderedImage(image, scaleFactor);
            }

            ++pass;
         }

      }

      m_mutex.lock();

      if (! m_restart) {
         m_condition.wait(&m_mutex);
      }

      m_restart = false;
      m_mutex.unlock();
   }
}

uint Mandelbrot_Thread::rgbFromWaveLength(double wave)
{
   double r = 0.0;
   double g = 0.0;
   double b = 0.0;

   if (wave >= 380.0 && wave <= 440.0) {
      r = -1.0 * (wave - 440.0) / (440.0 - 380.0);
      b = 1.0;

   } else if (wave >= 440.0 && wave <= 490.0) {
      g = (wave - 440.0) / (490.0 - 440.0);
      b = 1.0;

   } else if (wave >= 490.0 && wave <= 510.0) {
      g = 1.0;
      b = -1.0 * (wave - 510.0) / (510.0 - 490.0);

   } else if (wave >= 510.0 && wave <= 580.0) {
      r = (wave - 510.0) / (580.0 - 510.0);
      g = 1.0;

   } else if (wave >= 580.0 && wave <= 645.0) {
      r = 1.0;
      g = -1.0 * (wave - 645.0) / (645.0 - 580.0);

   } else if (wave >= 645.0 && wave <= 780.0) {
      r = 1.0;
   }

   double s = 1.0;

   if (wave > 700.0) {
      s = 0.3 + 0.7 * (780.0 - wave) / (780.0 - 700.0);

   } else if (wave <  420.0) {
      s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);
   }

   r = pow(r * s, 0.8);
   g = pow(g * s, 0.8);
   b = pow(b * s, 0.8);

   return qRgb(int(r * 255), int(g * 255), int(b * 255));
}
