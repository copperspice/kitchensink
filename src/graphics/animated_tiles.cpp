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

#include "animated_tiles.h"

#include <QGridLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSignalTransition>
#include <QState>

#include <math.h>

static const QString qmPath = ":/resources/animated_tiles";

AnimatedTiles::AnimatedTiles(QWidget *parent)
   : QWidget(parent), m_scene(-300, -325, 800, 650, this)
{
   setWindowTitle("Animated Tiles");
   setMinimumSize(800, 650);

   QPixmap spicePix(qmPath + "/spice.png");
   QPixmap bgPix(qmPath + "/background.jpg");

   QList<Pixmap *> items;
   for (int i = 0; i < 64; ++i) {
      Pixmap *item = new Pixmap(spicePix);
      item->setOffset(-spicePix.width()/2, -spicePix.height()/2);
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

   ellipseButton->setPos(300, -605);
   figure8Button->setPos(300, -445);
   randomButton->setPos(300, -285);
   tiledButton->setPos(300, -125);
   centeredButton->setPos(300, 35);

   m_scene.addItem(buttonParent);
   buttonParent->setTransform(QTransform::fromScale(0.75, 0.75), true);
   buttonParent->setPos(200, 200);
   buttonParent->setZValue(65);

   // States
   QState *rootState     = new QState;
   QState *ellipseState  = new QState(rootState);
   QState *figure8State  = new QState(rootState);
   QState *randomState   = new QState(rootState);
   QState *tiledState    = new QState(rootState);
   QState *centeredState = new QState(rootState);

   // values
   int scale = 200;

   for (int i = 0; i < items.count(); ++i) {
      Pixmap *item = items.at(i);

      // Ellipse
      ellipseState->assignProperty(item, "pos",
               QPointF(cos((i / 63.0) * 6.28) * scale, sin((i / 63.0) * 6.28) * scale));

      // Figure 8
      figure8State->assignProperty(item, "pos",
               QPointF(sin((i / 63.0) * 6.28) * scale, sin(((i * 2)/63.0) * 6.28) * scale));

      // Random
      randomState->assignProperty(item, "pos",
               QPointF(-scale + qrand() % (scale * 2), -scale + qrand() % (scale * 2)));

      // Tiled
      tiledState->assignProperty(item, "pos",
               QPointF(((i % 8) - 4) * spicePix.width() + spicePix.width() / 2,
               ((i / 8) - 4) * spicePix.height() + spicePix.height() / 2));

      // Centered
      centeredState->assignProperty(item, "pos", QPointF());
   }

   // ui
   View *view = new View(&m_scene, this);
   view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Animated Tiles"));
   view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
   view->setBackgroundBrush(bgPix);
   view->setCacheMode(QGraphicsView::CacheBackground);
   view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

   // layout
   QGridLayout *m_mainLayout = new QGridLayout;
   m_mainLayout->addWidget(view, 0, 0);
   m_mainLayout->setContentsMargins(0,0,0,0);
   setLayout(m_mainLayout);

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

   QSignalTransition *trans = rootState->addTransition(ellipseButton, &Button::pressed, ellipseState);
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

