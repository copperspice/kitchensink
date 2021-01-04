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

#ifndef LIGHTING_H
#define LIGHTING_H

#include <QGraphicsScene>
#include <QGraphicsView>

class QResizeEvent;

class Lighting: public QGraphicsView
{
   CS_OBJECT(Lighting)

   public:
       Lighting(QWidget *parent = nullptr);
       QSize sizeHint() const;

   protected:
       void resizeEvent(QResizeEvent *event);

   private:
       void setupScene();

       CS_SLOT_1(Private, void animate())
       CS_SLOT_2(animate)

       qreal angle;
       QGraphicsScene m_scene;
       QGraphicsItem *m_lightSource;
       QList<QGraphicsItem*> m_items;
};

#endif
