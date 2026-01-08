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

 public:
   FridgeMagnet(QWidget *parent = nullptr);

 protected:
   void dragEnterEvent(QDragEnterEvent *event) override;
   void dragMoveEvent(QDragMoveEvent *event) override;
   void dropEvent(QDropEvent *event) override;
   void mousePressEvent(QMouseEvent *event) override;
   QSize sizeHint() const override;
};

#endif
