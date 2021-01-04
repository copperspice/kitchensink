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

#include "svgtextobject.h"
#include "svg_view.h"

#include <QImage>
#include <QSizeF>
#include <QPainter>
#include <QStyleFactory>

QSizeF SvgTextObject::intrinsicSize(QTextDocument *, int, const QTextFormat &format)
{
   QImage bufferedImage = format.property(Svg_View::SvgData).value<QImage>();

   QSize size = bufferedImage.size();
   size *= 150.0 / (double) size.height();

   return QSizeF(size);
}

void SvgTextObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *, int, const QTextFormat &format)
{
   QImage bufferedImage = format.property(Svg_View::SvgData).value<QImage>();
   painter->drawImage(rect, bufferedImage);
}

