/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
***********************************************************************/

#include "svgtextobject.h"
#include "svg_view.h"

#include <QImage>
#include <QSizeF>
#include <QPainter>
#include <QStyleFactory>

QSizeF SvgTextObject::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
   QImage bufferedImage = format.property(Svg_View::SvgData).value<QImage>();

   QSize size = bufferedImage.size();
   size *= 150.0 / (double) size.height();

   return QSizeF(size);
}

void SvgTextObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
   QImage bufferedImage = format.property(Svg_View::SvgData).value<QImage>();
   painter->drawImage(rect, bufferedImage);
}

