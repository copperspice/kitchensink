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

#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

class DrawArea : public QWidget
{
   CS_OBJECT(DrawArea)

 public:
   enum Shape {
      Line,
      Points,
      Polyline,
      Polygon,
      Rect,
      RoundedRect,
      Ellipse,
      Arc,
      Chord,
      Pie,
      Path,
      Text
   };

   DrawArea(QWidget *parent = nullptr);

   void setShape(Shape shape);
   void setPen(const QPen &pen);
   void setBrush(const QBrush &brush);
   void setAntialiased(bool antialiased);
   void setTransformed(bool transformed);

   QSize minimumSizeHint() const override;

 protected:
   void paintEvent(QPaintEvent *event) override;
   QSize sizeHint() const override;

 private:
   Shape m_shape;
   QPixmap m_pixmap;
   QPen m_pen;
   QBrush m_brush;
   bool m_antialiased;
   bool m_transformed;
};

#endif
