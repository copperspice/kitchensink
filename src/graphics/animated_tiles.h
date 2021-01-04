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

#ifndef ANIMATED_TILES_H
#define ANIMATED_TILES_H

#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QStateMachine>
#include <QTimer>
#include <QWidget>

class AnimatedTiles: public QWidget
{
   CS_OBJECT(AnimatedTiles)

   public:
      AnimatedTiles(QWidget *parent = nullptr);

   private:
      QGraphicsScene m_scene;
      QStateMachine m_stateMachine;
      QTimer m_timer;
};

class Pixmap : public QObject, public QGraphicsPixmapItem
{
   CS_OBJECT_MULTIPLE(Pixmap, QObject)

   CS_PROPERTY_READ(pos, pos)
   CS_PROPERTY_WRITE(pos, ks_setPos)

   public:
      Pixmap(const QPixmap &pix)
         : QObject(), QGraphicsPixmapItem(pix)
      {
         setCacheMode(DeviceCoordinateCache);
      }

      // wrapper for overloaded method
      inline void ks_setPos(const QPointF &pos);

};

void Pixmap::ks_setPos(const QPointF &pos)
   {
      setPos(pos);
   }

class Button : public QGraphicsWidget
{
   CS_OBJECT(Button)

   public:
      Button(const QPixmap &pixmap, QGraphicsItem *parent = nullptr)
         : QGraphicsWidget(parent), _pix(pixmap)
      {
         setAcceptHoverEvents(true);
         setCacheMode(DeviceCoordinateCache);
      }

      QRectF boundingRect() const
      {
         return QRectF(-65, -65, 130, 130);
      }

      QPainterPath shape() const
      {
         QPainterPath path;
         path.addEllipse(boundingRect());
         return path;
      }

      void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
      {
         bool down = option->state & QStyle::State_Sunken;
         QRectF r = boundingRect();

         QLinearGradient grad(r.topLeft(), r.bottomRight());
         grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);
         grad.setColorAt(down ? 0 : 1, Qt::darkGray);
         painter->setPen(Qt::darkGray);
         painter->setBrush(grad);
         painter->drawEllipse(r);

         QLinearGradient grad2(r.topLeft(), r.bottomRight());
         grad.setColorAt(down ? 1 : 0, Qt::darkGray);
         grad.setColorAt(down ? 0 : 1, Qt::lightGray);
         painter->setPen(Qt::NoPen);
         painter->setBrush(grad);

         if (down) {
            painter->translate(2, 2);
         }

         painter->drawEllipse(r.adjusted(5, 5, -5, -5));
         painter->drawPixmap(-_pix.width()/2, -_pix.height()/2, _pix);
      }

      CS_SIGNAL_1(Public, void pressed())
      CS_SIGNAL_2(pressed)

   protected:
      void mousePressEvent(QGraphicsSceneMouseEvent *)
      {
         emit pressed();
         update();
      }

      void mouseReleaseEvent(QGraphicsSceneMouseEvent *)
      {
         update();
      }

   private:
      QPixmap _pix;
};

class View : public QGraphicsView
{
   public:
      View(QGraphicsScene *scene, QWidget *parent)
         : QGraphicsView(scene, parent) { }

   protected:
      void resizeEvent(QResizeEvent *event)
      {
         QGraphicsView::resizeEvent(event);
         fitInView(sceneRect(), Qt::KeepAspectRatio);
      }
};

#endif
