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

#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "ui_colorpicker.h"

#include <QWidget>

class ColorPicker : public QWidget
{
   CS_OBJECT(ColorPicker)

   public:
      explicit ColorPicker(QWidget *parent = nullptr);
      ~ColorPicker();

   private:
      CS_SLOT_1(Private, void setColor())
      CS_SLOT_2(setColor)

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      Ui::ColorPicker *ui;
};

#endif
