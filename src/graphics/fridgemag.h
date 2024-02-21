/***********************************************************************
*
* Copyright (c) 2012-2024 Barbara Geller
* Copyright (c) 2012-2024 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef FRIDGEMAG_H
#define FRIDGEMAG_H

#include <QWidget>

class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
class QSize;

class FridgeMagnet : public QWidget
{
   CS_OBJECT(FridgeMagnet)

      QSize sizeHint() const;
 public:
   FridgeMagnet(QWidget *parent = nullptr);

   protected:
      void dragEnterEvent(QDragEnterEvent *event);
      void dragMoveEvent(QDragMoveEvent *event);
      void dropEvent(QDropEvent *event);
      void mousePressEvent(QMouseEvent *event);
};

#endif
