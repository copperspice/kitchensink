/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
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

QSizeF SvgTextObject::intrinsicSize(QTextDocument * /*doc*/, int /*posInDocument*/, const QTextFormat &format)
{
   QImage bufferedImage = qVariantValue<QImage>(format.property(Svg_View::SvgData));

   QSize size = bufferedImage.size();
   size *= 150.0 / (double) size.height();

   return QSizeF(size);
}

void SvgTextObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument * /*doc*/,
         int /*posInDocument*/, const QTextFormat &format)
{
   QImage bufferedImage = qVariantValue<QImage>(format.property(Svg_View::SvgData));
   painter->drawImage(rect, bufferedImage);
}

