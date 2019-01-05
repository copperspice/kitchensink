/**********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
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

#ifndef FRIDGEMAG_H
#define FRIDGEMAG_H

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QWidget>

class QSize;

class FridgeMagnet : public QWidget
{
   CS_OBJECT(FridgeMagnet)

   public:
      FridgeMagnet(QWidget *parent = nullptr);
      QSize sizeHint() const;

   protected:
      void dragEnterEvent(QDragEnterEvent *event);
      void dragMoveEvent(QDragMoveEvent *event);
      void dropEvent(QDropEvent *event);
      void mousePressEvent(QMouseEvent *event);
};

#endif
