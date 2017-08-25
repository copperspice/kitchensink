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

#ifndef WIGGLE_BOXES_H
#define WIGGLE_BOXES_H

#include "qmlapplicationviewer.h"
#include <QWidget>

class Wiggle_Boxes : public QmlApplicationViewer
{
   CS_OBJECT(Wiggle_Boxes)

   public:
      Wiggle_Boxes(QWidget *parent = nullptr);

};

#endif
