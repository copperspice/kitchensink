/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

//#include <QGraphicsEffect>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsWidget>

#include <QState>
#include <QStateMachine>
#include <QTimer>
#include <QWidget>

class AnimatedTiles: public QWidget
{
      Q_OBJECT

   public:
      AnimatedTiles(QWidget *parent = 0);

   private:
      QGraphicsScene m_scene;
      QStateMachine m_stateMachine;
      QTimer m_timer;

};

class Pixmap : public QObject, public QGraphicsPixmapItem
{
      Q_OBJECT
      Q_PROPERTY(QPointF pos READ pos WRITE setPos)

   public:
      Pixmap(const QPixmap &pix)
         : QObject(), QGraphicsPixmapItem(pix)
      {
         setCacheMode(DeviceCoordinateCache);
      }
};

class Button : public QGraphicsWidget
{
      Q_OBJECT

   public:
      Button(const QPixmap &pixmap, QGraphicsItem *parent = 0)
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
         if (down)
            painter->translate(2, 2);
         painter->drawEllipse(r.adjusted(5, 5, -5, -5));
         painter->drawPixmap(-_pix.width()/2, -_pix.height()/2, _pix);
      }

   signals:
      void pressed();

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

