/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QWidget>

class QPaintEvent;

class AnalogClock : public QWidget
{
   CS_OBJECT(AnalogClock)

   public:
      AnalogClock(QWidget *parent = nullptr);

   protected:
      void paintEvent(QPaintEvent *event);
};

#endif
