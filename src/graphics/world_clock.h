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

#ifndef WORLD_CLOCK_H
#define WORLD_CLOCK_H

#include "qmlapplicationviewer.h"

#include <QWidget>

class World_Clock : public QmlApplicationViewer
{
   CS_OBJECT(World_Clock)

   public:
     World_Clock(QWidget *parent = nullptr);

};

#endif
