/***********************************************************************
*
* Copyright (c) 2012-2026 Barbara Geller
* Copyright (c) 2012-2026 Ansel Sermersheim
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

#include <draw_area.h>

#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QSize>

DrawArea::DrawArea(QWidget *parent)
   : QWidget(parent)
{
   m_shape       = Polygon;
   m_antialiased = false;
   m_transformed = false;

   setBackgroundRole(QPalette::Base);
   setAutoFillBackground(true);
}

QSize DrawArea::minimumSizeHint() const
{
   return QSize(100, 100);
}

QSize DrawArea::sizeHint() const
{
   return QSize(400, 200);
}

void DrawArea::setShape(Shape shape)
{
   m_shape = shape;
   update();
}

void DrawArea::setPen(const QPen &pen)
{
   m_pen = pen;
   update();
}

void DrawArea::setBrush(const QBrush &brush)
{
   m_brush = brush;
   update();
}

void DrawArea::setAntialiased(bool antialiased)
{
   m_antialiased = antialiased;
   update();
}

void DrawArea::setTransformed(bool transformed)
{
   m_transformed = transformed;
   update();
}

void DrawArea::paintEvent(QPaintEvent *)
{
   static const QVector<QPoint> points = {
      QPoint(10, 80), QPoint(20, 10), QPoint(80, 30), QPoint(90, 70)
   };

   QRect rect(10, 20, 80, 60);

   QPainterPath path;
   path.moveTo(20, 80);
   path.lineTo(20, 30);
   path.cubicTo(80, 0, 50, 50, 80, 80);

   int startAngle = 20 * 16;
   int arcLength  = 120 * 16;

   QPainter painter(this);
   painter.setPen(m_pen);
   painter.setBrush(m_brush);

   if (m_antialiased) {
      painter.setRenderHint(QPainter::Antialiasing, true);
   }

   for (int x = 0; x < width(); x += 100) {
      for (int y = 0; y < height(); y += 100) {
         painter.save();
         painter.translate(x, y);

         if (m_transformed) {
            painter.translate(50, 50);
            painter.rotate(60.0);
            painter.scale(0.6, 0.9);
            painter.translate(-50, -50);
         }

         switch (m_shape) {
            case Line:
               painter.drawLine(rect.bottomLeft(), rect.topRight());
               break;

            case Points:
               painter.drawPoints(points.constData(), points.size());
               break;

            case Polyline:
               painter.drawPolyline(points.constData(), points.size());
               break;

            case Polygon:
               painter.drawPolygon(points.constData(), points.size());
               break;

            case Rect:
               painter.drawRect(rect);
               break;

            case RoundedRect:
               painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
               break;

            case Ellipse:
               painter.drawEllipse(rect);
               break;

            case Arc:
               painter.drawArc(rect, startAngle, arcLength);
               break;

            case Chord:
               painter.drawChord(rect, startAngle, arcLength);
               break;

            case Pie:
               painter.drawPie(rect, startAngle, arcLength);
               break;

            case Path:
               painter.drawPath(path);
               break;

            case Text:
               painter.drawText(rect, Qt::AlignCenter, tr("Drawing Sample"));
               break;
         }

         painter.restore();
      }
   }

   painter.setRenderHint(QPainter::Antialiasing, false);
   painter.setPen(palette().dark().color());
   painter.setBrush(Qt::NoBrush);

   painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}
