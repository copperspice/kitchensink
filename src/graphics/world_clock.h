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
