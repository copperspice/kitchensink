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
       enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                    Chord, Pie, Path, Text };

       DrawArea(QWidget *parent = nullptr);

       QSize minimumSizeHint() const;
       QSize sizeHint() const;

       CS_SLOT_1(Public, void setShape(Shape shape))
       CS_SLOT_2(setShape)

       CS_SLOT_1(Public, void setPen(const QPen & pen))
       CS_SLOT_2(setPen)

       CS_SLOT_1(Public, void setBrush(const QBrush & brush))
       CS_SLOT_2(setBrush)

       CS_SLOT_1(Public, void setAntialiased(bool antialiased))

       CS_SLOT_2(setAntialiased)

       CS_SLOT_1(Public, void setTransformed(bool transformed))
       CS_SLOT_2(setTransformed)

   protected:
       void paintEvent(QPaintEvent *event);

   private:
       Shape shape;
       QPen pen;
       QBrush brush;
       bool antialiased;
       bool transformed;
       QPixmap pixmap;
};

#endif
