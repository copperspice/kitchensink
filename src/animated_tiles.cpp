/**********************************************************************
*
* Copyright (c) 2012-2016 Barbara Geller
* Copyright (c) 2006-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the Nokia Corporation nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
***********************************************************************/

#include "animated_tiles.h"

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSignalTransition>

#include <math.h>

static const QString qmPath = ":/resources/animated_tiles";

AnimatedTiles::AnimatedTiles(QWidget *parent)
   : QWidget(parent), m_scene(-350, -350, 700, 700, this)
{
   setWindowTitle("Animated Tiles");
   setMinimumSize(700, 700);

   QPixmap kineticPix(qmPath + "/kinetic.png");
   QPixmap bgPix(qmPath + "/Time-For-Lunch-2.jpg");

   QList<Pixmap *> items;
   for (int i = 0; i < 64; ++i) {
      Pixmap *item = new Pixmap(kineticPix);
      item->setOffset(-kineticPix.width()/2, -kineticPix.height()/2);
      item->setZValue(i);
      items << item;
      m_scene.addItem(item);
   }

   // Buttons
   QGraphicsItem *buttonParent = new QGraphicsRectItem;
   Button *ellipseButton  = new Button(QPixmap(qmPath + "/ellipse.png"), buttonParent);
   Button *figure8Button  = new Button(QPixmap(qmPath + "/figure8.png"), buttonParent);
   Button *randomButton   = new Button(QPixmap(qmPath + "/random.png"), buttonParent);
   Button *tiledButton    = new Button(QPixmap(qmPath + "/tile.png"), buttonParent);
   Button *centeredButton = new Button(QPixmap(qmPath + "/centered.png"), buttonParent);

   ellipseButton->setPos(-100, -100);
   figure8Button->setPos(100, -100);
   randomButton->setPos(0, 0);
   tiledButton->setPos(-100, 100);
   centeredButton->setPos(100, 100);

   m_scene.addItem(buttonParent);
   buttonParent->scale(0.75, 0.75);
   buttonParent->setPos(200, 200);
   buttonParent->setZValue(65);

   // States
   QState *rootState     = new QState;
   QState *ellipseState  = new QState(rootState);
   QState *figure8State  = new QState(rootState);
   QState *randomState   = new QState(rootState);
   QState *tiledState    = new QState(rootState);
   QState *centeredState = new QState(rootState);

   // Values
   for (int i = 0; i < items.count(); ++i) {
      Pixmap *item = items.at(i);

      // Ellipse
      ellipseState->assignProperty(item, "pos",
               QPointF(cos((i / 63.0) * 6.28) * 250, sin((i / 63.0) * 6.28) * 250));

      // Figure 8
      figure8State->assignProperty(item, "pos",
               QPointF(sin((i / 63.0) * 6.28) * 250, sin(((i * 2)/63.0) * 6.28) * 250));

      // Random
      randomState->assignProperty(item, "pos",
               QPointF(-250 + qrand() % 500, -250 + qrand() % 500));

      // Tiled
      tiledState->assignProperty(item, "pos",
               QPointF(((i % 8) - 4) * kineticPix.width() + kineticPix.width() / 2,
               ((i / 8) - 4) * kineticPix.height() + kineticPix.height() / 2));

      // Centered
      centeredState->assignProperty(item, "pos", QPointF());
   }

   // Ui
   View *view = new View(&m_scene, this);
   view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Animated Tiles"));
   view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
   view->setBackgroundBrush(bgPix);
   view->setCacheMode(QGraphicsView::CacheBackground);
   view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

   view->show();

   //
   m_stateMachine.addState(rootState);
   m_stateMachine.setInitialState(rootState);
   rootState->setInitialState(centeredState);

   QParallelAnimationGroup *group = new QParallelAnimationGroup;
   for (int i = 0; i < items.count(); ++i) {
      QPropertyAnimation *anim = new QPropertyAnimation(items[i], "pos");
      anim->setDuration(750 + i * 25);
      anim->setEasingCurve(QEasingCurve::InOutBack);
      group->addAnimation(anim);
   }

   QAbstractTransition *trans = rootState->addTransition(ellipseButton, &Button::pressed, ellipseState);
   trans->addAnimation(group);

   trans = rootState->addTransition(figure8Button, &Button::pressed, figure8State);
   trans->addAnimation(group);

   trans = rootState->addTransition(randomButton, &Button::pressed, randomState);
   trans->addAnimation(group);

   trans = rootState->addTransition(tiledButton, &Button::pressed, tiledState);
   trans->addAnimation(group);

   trans = rootState->addTransition(centeredButton, &Button::pressed, centeredState);
   trans->addAnimation(group);

   m_timer.start(125);
   m_timer.setSingleShot(true);

   trans = rootState->addTransition(&m_timer, &QTimer::timeout, ellipseState);
   trans->addAnimation(group);

   m_stateMachine.start();
}


